//
// Created by nbollom on 7/11/16.
//

#include <QtWidgets>

#ifndef PROJECT_MAINWINDOW_H
#define PROJECT_MAINWINDOW_H

class MainWindow : public QMainWindow {

public:
    MainWindow();

private slots:
    void buttonPressed();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    QWidget *center;
    QVBoxLayout *layout;
    QList<QPushButton*> butons;
    QList<QListView*> lists;

};

#endif //PROJECT_MAINWINDOW_H
