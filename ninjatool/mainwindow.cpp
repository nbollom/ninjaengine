//
// Created by nbollom on 7/11/16.
//

#include "mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

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
    center->setLayout(layout);
    selectedIndex = 0;
    for (int i = 0; i < 5; ++i) {
        QPushButton *button = new QPushButton(QString("Button: ") + QString::number(i + 1), center);
        button->setFixedHeight(30);
        connect(button, &QPushButton::pressed, this, &MainWindow::buttonPressed);
        buttons.append(button);
        layout->addWidget(button);
        QListView *list = new QListView(center);
        list->setVisible(i == selectedIndex);
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
    qDebug() << "Clicked Button";
    QPushButton *button = (QPushButton*)sender();
    int selected = buttons.indexOf(button);
    if (selected != selectedIndex) {
        QListView *current = lists[selectedIndex];
        QPropertyAnimation *currentAnimation = new QPropertyAnimation(current, "maximumHeight");
        currentAnimation->setDuration(100);
        currentAnimation->setEndValue(0);
        QListView * next = lists[selected];
        QPropertyAnimation *nextAnimation = new QPropertyAnimation(next, "maximumHeight");
        nextAnimation->setDuration(100);
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
