//
// Created by nbollom on 7/11/16.
//

#include "mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "objecttype.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("NinjaTool");
    setMinimumSize(320, 320);
    QDesktopWidget dw;
    int height = (int) (dw.screen()->height() * 0.9f);
    int width = (int) (dw.screen()->width() * 0.9f);
    resize(320, height);
    move((int) ((dw.screen()->width() - width) / 2.0f), (int) ((dw.screen()->height() - height) / 2.0f));
    center = new QWidget(this);
    setCentralWidget(center);
    layout = new QVBoxLayout();
    layout->setSpacing(1);
    center->setLayout(layout);
    selectedIndex = 0;
    int current = 0;
    for (QList<ObjectType*>::iterator i = objectTypes.begin(); i != objectTypes.end(); ++i) {
        ObjectType *type = *i;
        QPushButton *button = new QPushButton(type->GetTitle(), center);
        button->setFixedHeight(30);
        connect(button, &QPushButton::pressed, this, &MainWindow::buttonPressed);
        buttons.append(button);
        layout->addWidget(button);
        QListView *list = new QListView(center);
        list->setSelectionMode(QListView::SingleSelection);
        list->setSelectionBehavior(QListView::SelectRows);
        list->setViewMode(QListView::ListMode);
        list->setEditTriggers(QListView::NoEditTriggers);
        list->setVisible(current++ == selectedIndex);
        list->setModel(type->GetModel());
        lists.append(list);
        layout->addWidget(list);
    }
}

MainWindow::~MainWindow() {
    for (QList<QPushButton*>::iterator i = buttons.begin(); i != buttons.end(); ++i) {
        delete *i;
    }
    buttons.clear();
    for (QList<QListView*>::iterator i = lists.begin(); i != lists.end(); ++i) {
        delete *i;
    }
    lists.clear();
    delete layout;
    delete center;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing";
}

void MainWindow::buttonPressed() {
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
