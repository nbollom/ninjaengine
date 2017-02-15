//
// Created by nbollom on 31/01/17.
//

#include "projectmanager.h"
#include "tools.h"
#include "editors/newproject.h"

static int DATA_VERSION = 1;

bool ProjectManager::isOpen = false;
sqlite3 *ProjectManager::db = nullptr;

static const QHash<int, QStringList> UPGRADE_SQL = {
        {
                1,
                {
                        "CREATE TABLE Images(Name PRIMARY KEY UNIQUE, Path VARCHAR);"
                }
        }
};

void ProjectManager::Init() {
    { //Image Resource Type
        TypeRef *images = new TypeRef();
        images->model->setStringList({"Test1", "Test2", "Test3"});
        images->GetNewDialog = []() {
            return new NewProjectWidget(); //TODO: change to correct new dialog
        };
        images->GetEditor = [](QString name) {
            return nullptr; //TODO: change to correct editor
        };
        resources["Images"] = images;
    }
    { //Animation Resource Type
        TypeRef *animations = new TypeRef();
        //TODO: new dialog
        resources["Animations"] = animations;
    }
    { //Sprite Object Type
        TypeRef *sprites = new TypeRef();
        //TODO: new dialog
        objects["Sprites"] = sprites;
    }
}

QHash<QString, TypeRef*> ProjectManager::resources = {};
QHash<QString, TypeRef*> ProjectManager::objects = {};

void ProjectManager::CloseProject() {
    if (isOpen) {
        sqlite3_close(db);
    }
}

bool ProjectManager::LoadProject(QDir projectPath, QString projectName, std::function<bool(int, int)> upgradeCallback) {
    CloseProject();
    projectPath.cd(projectName);
    QString fullPath = projectPath.absoluteFilePath(projectName + ".dat");
    char *charPath = charStringFromQString(fullPath);
    int ret = sqlite3_open(charPath, &db);
    free(charPath);
    if (ret == SQLITE_OK) {
        isOpen = true;
        const char versionSQL[] = "PRAGMA user_version;";
        sqlite3_stmt *versionStatement;
        ret = sqlite3_prepare_v2(db, versionSQL, (int)strlen(versionSQL), &versionStatement, nullptr);
        int dbVersion = 0;
        if(ret == SQLITE_OK) {
            sqlite3_step(versionStatement);
            dbVersion = sqlite3_column_int(versionStatement, 0);
            sqlite3_finalize(versionStatement);
        }
        else {
            isOpen = false;
            return isOpen;
        }
        if (dbVersion < DATA_VERSION) {
            if(dbVersion != 0 && !upgradeCallback(dbVersion, DATA_VERSION)) {
                isOpen = false;
                return isOpen;
            }
            for (int ver = dbVersion + 1; ver <= DATA_VERSION; ++ver) {
                QStringList versionUpgradeSQL = UPGRADE_SQL[ver];
                //TODO: upgrade
                for (QStringList::iterator i = versionUpgradeSQL.begin(); i != versionUpgradeSQL.end(); ++i) {
                    QString sql = *i;
                    sqlite3_stmt *stmt;
                    char *charSQL = charStringFromQString(sql);
                    ret = sqlite3_prepare_v2(db, charSQL, sql.length(), &stmt, nullptr);
                    free(charSQL);
                    if(ret == SQLITE_OK) {
                        sqlite3_step(stmt);
                        int x = sqlite3_column_int(stmt, 0);
                        printf("response: %d", x);
                        sqlite3_finalize(stmt);
                    }
                }
            }
        }
        //TODO: load and populate item lists
    }
    return isOpen;
}

QStringList ProjectManager::GetResourceTypes() {
    QStringList types = resources.keys();
    qSort(types);
    return types;
}

QStringListModel* ProjectManager::GetResourceData(QString section) {
    return resources[section]->model;
}

QStringList ProjectManager::GetObjectTypes() {
    QStringList types = objects.keys();
    qSort(types);
    return types;
}

QStringListModel* ProjectManager::GetObjectData(QString section) {
    return objects[section]->model;
}
