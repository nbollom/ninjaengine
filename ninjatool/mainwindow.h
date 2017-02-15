//
// Created by nbollom on 7/11/16.
//

#ifndef PROJECT_MAINWINDOW_H
#define PROJECT_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QToolBar>
#include <QTabWidget>
#include "editors/documentwidget.h"
#include "carousel.h"

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

    // Action slots
    void closeApp();
    void showSettingsScreen();
    void settingsChanged();
    void widgetClosed(DocumentWidget *widget);
    void newProject();
    void openProject();

private:
    bool loaded; // ignore layout events until true
    QTabWidget *tabs;
    QToolBar *toolbar;
    QList<DocumentWidget*> openDocuments;
    Carousel *objects;
    Carousel *resources;
};

#endif //PROJECT_MAINWINDOW_H
