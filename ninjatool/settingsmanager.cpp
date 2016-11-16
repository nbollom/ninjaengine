//
// Created by nbollom on 15/11/16.
//

#include "settingsmanager.h"
#include <rapidjson/filereadstream.h>

using namespace rapidjson;
using namespace std;

SettingsManager::SettingsManager() {
    FILE* fp = fopen("settings.json", "r");
    char readBuffer[512];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    d.ParseStream(is);
}

SettingsManager *SettingsManager::instance = nullptr;

SettingsManager* SettingsManager::GetInstance() {
    if (instance == nullptr) {
        instance = new SettingsManager();
    }
    return instance;
}
