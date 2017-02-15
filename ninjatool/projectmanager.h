//
// Created by nbollom on 31/01/17.
//

#ifndef PROJECT_PROJECTMANAGER_H
#define PROJECT_PROJECTMANAGER_H

#include <QList>
#include <QString>
#include <QDir>
#include <QStringListModel>
#include <functional>
#include <sqlite3.h>
#include "editors/newwidget.h"
#include "editors/documentwidget.h"

struct TypeRef {
    QStringListModel *model;
    std::function<NewWidget*()> GetNewDialog;
    std::function<DocumentWidget*(QString name)> GetEditor;
    TypeRef() {
            model = new QStringListModel();
    };
};

class ProjectManager {

private:
    static bool isOpen;
    static sqlite3 *db;
    static QHash<QString, TypeRef*> resources;
    static QHash<QString, TypeRef*> objects;
    ProjectManager() {};

public:
    static void Init();
    static void CloseProject();
    static bool LoadProject(QDir projectPath, QString projectName, std::function<bool(int, int)> upgradeCallback);
    static QStringList GetResourceTypes();
    static QStringListModel *GetResourceData(QString section);
    static QStringList GetObjectTypes();
    static QStringListModel *GetObjectData(QString section);
};

#endif //PROJECT_PROJECTMANAGER_H
