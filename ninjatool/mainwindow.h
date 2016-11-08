//
// Created by nbollom on 7/11/16.
//

#ifndef PROJECT_MAINWINDOW_H
#define PROJECT_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QListView>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void buttonPressed();

private:
    QWidget *center;
    QVBoxLayout *layout;
    QList<QPushButton*> butons;
    QList<QListView*> lists;

};

#endif //PROJECT_MAINWINDOW_H
