//
// Created by nbollom on 14/12/16.
//

#include "carousel.h"
#include "projectmanager.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

Carousel::Carousel(CarouselType type) {
    selectedIndex = 0;
    QVBoxLayout *layout = new QVBoxLayout();
#ifndef __APPLE__
    layout->setSpacing(1);
#endif
    setLayout(layout);
    int current = 0;
    QStringList sections = (type == CarouselTypeResources ? ProjectManager::GetResourceTypes() : ProjectManager::GetObjectTypes());
    for (QStringList::iterator i = sections.begin(); i != sections.end(); ++i) {
        QString section = *i;
        QPushButton *button = new QPushButton(section, this);
        button->setFixedHeight(30);
        connect(button, &QPushButton::pressed, this, &Carousel::buttonPressed);
        buttons.append(button);
        layout->addWidget(button);
        QListView *list = new QListView(this);
        list->setSelectionMode(QListView::SingleSelection);
        list->setSelectionBehavior(QListView::SelectRows);
        list->setViewMode(QListView::ListMode);
        list->setEditTriggers(QListView::NoEditTriggers);
        list->setVisible(current++ == selectedIndex);
        list->setModel(type == CarouselTypeResources ? ProjectManager::GetResourceData(section) : ProjectManager::GetObjectData(section));
        lists.append(list);
        layout->addWidget(list);
    }
}

Carousel::~Carousel() {
    for (QList<QPushButton*>::iterator i = buttons.begin(); i != buttons.end(); ++i) {
        delete *i;
    }
    buttons.clear();
    for (QList<QListView*>::iterator i = lists.begin(); i != lists.end(); ++i) {
        delete *i;
    }
    lists.clear();
}

void Carousel::buttonPressed() {
    QPushButton *button = (QPushButton*)sender();
    int selected = buttons.indexOf(button);
    qDebug() << "Clicked Button " << (selected + 1);
    if (selected != selectedIndex) {
        QListView *current = lists[selectedIndex];
        QPropertyAnimation *currentAnimation = new QPropertyAnimation(current, "maximumHeight");
        currentAnimation->setDuration(200);
        currentAnimation->setEndValue(0);
        QListView * next = lists[selected];
        QPropertyAnimation *nextAnimation = new QPropertyAnimation(next, "maximumHeight");
        nextAnimation->setDuration(200);
        nextAnimation->setStartValue(0);
        nextAnimation->setEndValue(current->height());
        next->setVisible(true);
        QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
        animationGroup->addAnimation(currentAnimation);
        animationGroup->addAnimation(nextAnimation);
        connect(animationGroup, &QParallelAnimationGroup::finished, [=](){
            current->setVisible(false);
        });
        animationGroup->start();
    }
    selectedIndex = selected;
}
