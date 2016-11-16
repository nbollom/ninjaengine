//
// Created by nbollom on 15/11/16.
//

#ifndef PROJECT_SETTINGSMANAGER_H
#define PROJECT_SETTINGSMANAGER_H

#include <rapidjson/document.h>

class SettingsManager {

private:
    SettingsManager();
    static SettingsManager *instance;
    rapidjson::Document d;

public:
    static SettingsManager* GetInstance();


};

#endif //PROJECT_SETTINGSMANAGER_H
