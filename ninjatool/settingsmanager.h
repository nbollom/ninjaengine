//
// Created by nbollom on 15/11/16.
//

#ifndef PROJECT_SETTINGSMANAGER_H
#define PROJECT_SETTINGSMANAGER_H

#include <rapidjson/document.h>
#include <QString>
#include <list>
#include <string>

#define DEFINE_GET_SET(type, get_name, set_name) static type get_name(QString key, type defaultValue); static void set_name(QString key, type value);

class SettingsManager {

private:
    SettingsManager() {};
    static rapidjson::Document d;
    static std::string filePath;
    static rapidjson::Value* processKeySections(QString key, bool create = false);

public:
    static void Init(QString file);
    static void Free();
    static bool Sync();
    DEFINE_GET_SET(bool, GetBool, SetBool)
    DEFINE_GET_SET(QString, GetString, SetString)
    DEFINE_GET_SET(int, GetInt, SetInt)
    DEFINE_GET_SET(int64_t, GetInt64, SetInt64)
    DEFINE_GET_SET(uint, GetUInt, SetUInt)
    DEFINE_GET_SET(uint64_t , GetUInt64, SetUInt64)
    DEFINE_GET_SET(float, GetFloat, SetFloat)
    DEFINE_GET_SET(double, GetDouble, SetDouble)
    static void DeleteKey(QString key);
};

#endif //PROJECT_SETTINGSMANAGER_H
