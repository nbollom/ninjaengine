//
// Created by nbollom on 7/11/16.
//

#include "mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QtCore/QCoreApplication>
#include "objecttype.h"
#include "ninjatoolsettingswidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("NinjaTool");
    setMinimumSize(320, 320);
    QDesktopWidget dw;
    int height = (int) (dw.screen()->height() * 0.9f);
    int width = (int) (dw.screen()->width() * 0.9f);
    resize(400, height);
    move((int) ((dw.screen()->width() - width) / 2.0f), (int) ((dw.screen()->height() - height) / 2.0f));
    toolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    SetupActions();
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
        connect(button, &QPushButton::pressed, this, &MainWindow::typeButtonPressed);
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

static inline void AddToMenu(QAction *action, QMenu *menu) {
    menu->addAction(action);
}

static inline void AddToMenuAndBar(QAction *action, QMenu *menu, QToolBar *bar) {
    menu->addAction(action);
    bar->addAction(action);
}

static inline QIcon icon_named(QString name) {
#ifdef __APPLE__
    static const QString fallbackpath = "%1/../Resources/%2.svg";
    return QPixmap(fallbackpath.arg(QCoreApplication::applicationDirPath(), name));
#else
    static const QString fallbackpath = "%1/Icons/%2.svg";
    return QIcon::fromTheme(name, QIcon(fallbackpath.arg(QCoreApplication::applicationDirPath(), name)));
#endif
}

void MainWindow::SetupActions() {
    {// File Menu
        QMenu *fileMenu = new QMenu("File", this);

        QAction *settings = new QAction(icon_named("preferences-system"), "Settings", this);
        connect(settings, &QAction::triggered, this, &MainWindow::showSettingsScreen);
        AddToMenu(settings, fileMenu);

        QAction *quit = new QAction(icon_named("application-exit"), "Exit", this);
        connect(quit, &QAction::triggered, this, &MainWindow::closeApp);
        AddToMenu(quit, fileMenu);

        menuBar()->addMenu(fileMenu);
    }
    {// Project Menu
        QMenu *projectMenu = new QMenu("Project", this);

        QAction *newProject = new QAction(icon_named("document-new"), "New Project", this);
        AddToMenuAndBar(newProject, projectMenu, toolbar);

        QAction *loadProject = new QAction(icon_named("document-open"), "Load Project", this);
        AddToMenuAndBar(loadProject, projectMenu, toolbar);

        QAction *projectSettings = new QAction(icon_named("document-properties"), "Project Settings", this);
        AddToMenuAndBar(projectSettings, projectMenu, toolbar);

        menuBar()->addMenu(projectMenu);
    }
}

DocumentWidget* MainWindow::FindOpenDocument(QString type, QString name) {
    for (QList<DocumentWidget*>::iterator i = openDocuments.begin(); i != openDocuments.end(); ++i) {
        DocumentWidget *widget = *i;
        if (widget->GetDocumentType() == type && widget->GetDocumentType() == type) {
            return widget;
        }
    }
    return Q_NULLPTR;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing";
    for(QList<DocumentWidget*>::iterator i = openDocuments.begin(); i != openDocuments.end(); ++i) {
        DocumentWidget *window = *i;
        if (window->SaveDocument()) { // Save first
            window->close();
            openDocuments.removeOne(window);
            delete (window);
        }
        else {
            event->ignore();
        }
    }
}

void MainWindow::typeButtonPressed() {
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

void MainWindow::closeApp() {
    close();
}

void MainWindow::showSettingsScreen() {
    DocumentWidget *settings = FindOpenDocument(NinjaToolSettingsWidget::DocumentType, NinjaToolSettingsWidget::DocumentName);
    if (settings == Q_NULLPTR) {
        settings = new NinjaToolSettingsWidget();
        openDocuments.append(settings);
        settings->show();
    } else {
        settings->activateWindow();
        settings->raise();
    }
}
