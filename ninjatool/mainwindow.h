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
#include <QToolBar>
#include "documentwidget.h"



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

protected:
    void SetupActions();
    DocumentWidget *FindOpenDocument(QString type, QString name);
    void SaveLayout();

    // Window event overloads
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;

    // Carousel slots
    void typeButtonPressed();

    // Action slots
    void closeApp();
    void showSettingsScreen();
    void settingsChanged();
    void widgetClosed(DocumentWidget *widget);

private:
    bool loaded; // ignore layout events until true
    int selectedIndex;
    QWidget *center;
    QToolBar *toolbar;
    QVBoxLayout *layout;
    QList<QPushButton*> buttons;
    QList<QListView*> lists;

    QList<DocumentWidget*> openDocuments;

};

#endif //PROJECT_MAINWINDOW_H
