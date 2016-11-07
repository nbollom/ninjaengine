//
// Created by nbollom on 7/11/16.
//

#include "mainwindow.h"

MainWindow::MainWindow() {
    setWindowTitle("NinjaTool");
    setMinimumSize(320, 320);
    QDesktopWidget dw;
    int height = (int) (dw.screen()->height() * 0.9f);
    int width = (int) (dw.screen()->width() * 0.9f);
    resize(320, height);
    move((int) ((dw.screen()->width() - width) / 2.0f), (int) ((dw.screen()->height() - height) / 2.0f));
    center = new QWidget();
    setCentralWidget(center);
    layout = new QVBoxLayout();
    center->setLayout(layout);
    int selected = 5;
    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString("Button: ") + QString::number(i + 1));
        button->setDown(i == selected);
        connect(button, SIGNAL(pressed()), this, SLOT(buttonPressed()));
        butons.append(button);
        layout->addWidget(button);
        QListView *list = new QListView();
        list->setVisible(i == selected);
        lists.append(list);
        layout->addWidget(list);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing";
}

void MainWindow::buttonPressed() {
    qDebug() << "Clicked Button";
}
