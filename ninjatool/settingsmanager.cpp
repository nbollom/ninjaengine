//
// Created by nbollom on 15/11/16.
//

#include "settingsmanager.h"
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <QtCore/QtCore>

using namespace rapidjson;
using namespace std;

string SettingsManager::filePath = "";
Document SettingsManager::d;

inline string stringFromQString(QString value) {
    QByteArray ba = value.toLatin1();
    const char *bytes = ba;
    return string(bytes);
}

void SettingsManager::Init(QString file) {
    filePath = stringFromQString(file);
    FILE* fp = fopen(filePath.c_str(), "r");
    if (fp) {
        char readBuffer[512];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        d.ParseStream(is);
        fclose(fp);
    }
    else {
        d.SetObject(); //initialize a default settings object and persist
//        Sync();
    }
}

void SettingsManager::Free() {
    Sync();
}

bool SettingsManager::Sync() {
    FILE* fp = fopen(filePath.c_str(), "w+");
    if (fp) {
        char writeBuffer[512];
        FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        d.Accept(writer);
        fclose(fp);
        return true;
    }
    return false;
}

Value* SettingsManager::processKeySections(QString key, bool create) {
    if (!key.length()) {
        return nullptr;
    }
    QStringList parts = key.split(".");
    Value *v = &d;
    for (QStringList::iterator i = parts.begin(); i != parts.end(); ++i) {
        string part = stringFromQString(*i);
        if (!(v->IsObject() && v->HasMember(part.c_str()))) {
            if (create) {
                if (!v->IsObject()) {
                    v->SetObject(); // Make sure its an object so we can create a member on it
                }
                Value k(part.c_str(), (int)part.length(), d.GetAllocator());
                Value nv;
                v->AddMember(k, nv, d.GetAllocator());
            }
            else {
                v = nullptr;
                break;
            }
        }
        v = &(*v)[part.c_str()];
    }
    return v;
}

bool SettingsManager::GetBool(QString key, bool defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsBool()) {
        return defaultValue;
    }
    else {
        return v->GetBool();
    }
}

void SettingsManager::SetBool(QString key, bool value) {
    Value *v = processKeySections(key, true);
    v->SetBool(value);
}

string SettingsManager::GetString(QString key, string defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsString()) {
        return defaultValue;
    }
    else {
        return v->GetString();
    }
}

void SettingsManager::SetString(QString key, std::string value) {
    Value *v = processKeySections(key, true);
    v->SetString(value.c_str(), (int)value.length(), d.GetAllocator());
}
