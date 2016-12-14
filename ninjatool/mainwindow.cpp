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
#include "editors/settingswidget.h"
#include "settingsmanager.h"
#include "settingsconstants.h"

const QString WINDOW_KEY = "MainWindow";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QString configPath = QCoreApplication::applicationDirPath() + "/config.json";
    SettingsManager::Init(configPath);
    setWindowTitle("NinjaTool");
    setMinimumSize(320, 320);
    QDesktopWidget dw;
    int height = (int) (dw.screen()->height() * 0.9f);
    int width = (int) (dw.screen()->width() * 0.9f);
    resize(
            SettingsManager::GetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, WIDTH_KEY), 400),
            SettingsManager::GetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, HEIGHT_KEY), height)
    );
    int x = (int) ((dw.screen()->width() - width) / 2.0f);
    int y = (int) ((dw.screen()->height() - height) / 2.0f);
    move(
            SettingsManager::GetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, X_KEY), x),
            SettingsManager::GetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, Y_KEY), y)
    );
    toolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    SetupActions();
    tabs = new QTabWidget(this);
    objects = new Carousel(objectTypes);
    tabs->addTab(objects, "Objects");
    resources = new Carousel(resourceTypes);
    tabs->addTab(resources, "Resources");
    setCentralWidget(tabs);
    loaded = true;
}

MainWindow::~MainWindow() {
    delete objects;
    delete resources;
    SettingsManager::Free();
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

void MainWindow::SaveLayout() {
    if (loaded && SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT)) {
        SettingsManager::SetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, WIDTH_KEY), width());
        SettingsManager::SetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, HEIGHT_KEY), height());
        SettingsManager::SetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, X_KEY), x());
        SettingsManager::SetInt(BuildKey(LAYOUT_KEY, WINDOW_KEY, Y_KEY), y());
        SettingsManager::Sync();
    }
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

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    SaveLayout();
}

void MainWindow::moveEvent(QMoveEvent *event) {
    QMainWindow::moveEvent(event);
    SaveLayout();
}

void MainWindow::closeApp() {
    close();
}

void MainWindow::showSettingsScreen() {
    SettingsWidget *settings = (SettingsWidget*)FindOpenDocument(SettingsWidget::DocumentType, SettingsWidget::DocumentName);
    if (settings == Q_NULLPTR) {
        settings = new SettingsWidget();
        connect(settings, &SettingsWidget::settingsChanged, this, &MainWindow::settingsChanged);
        connect(settings, &DocumentWidget::widgetClosed, this, &MainWindow::widgetClosed);
        openDocuments.append(settings);
        settings->show();
    } else {
        settings->activateWindow();
        settings->raise();
    }
}

void MainWindow::settingsChanged() {
    SaveLayout();
}

void MainWindow::widgetClosed(DocumentWidget *widget) {
    openDocuments.removeOne(widget);
}
