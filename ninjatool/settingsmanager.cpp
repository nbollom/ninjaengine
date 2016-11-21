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
    // Do I need to free anything?
    // Sync should not be called here because unsync changes are considered not wanted
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

QString SettingsManager::GetString(QString key, QString defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsString()) {
        return defaultValue;
    }
    else {
        return QString(v->GetString());
    }
}

void SettingsManager::SetString(QString key, QString value) {
    Value *v = processKeySections(key, true);
    string valueText = stringFromQString(value);
    SizeType length = (SizeType)valueText.length();
    v->SetString(valueText.c_str(), length, d.GetAllocator());
}

int SettingsManager::GetInt(QString key, int defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsInt()) {
        return defaultValue;
    }
    else {
        return v->GetInt();
    }
}

void SettingsManager::SetInt(QString key, int value) {
    Value *v = processKeySections(key, true);
    v->SetInt(value);
}

int64_t SettingsManager::GetInt64(QString key, int64_t defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsInt64()) {
        return defaultValue;
    }
    else {
        return v->GetInt64();
    }
}

void SettingsManager::SetInt64(QString key, int64_t value) {
    Value *v = processKeySections(key, true);
    v->SetInt64(value);
}

uint SettingsManager::GetUInt(QString key, uint defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsInt()) {
        return defaultValue;
    }
    else {
        return v->GetUint();
    }
}

void SettingsManager::SetUInt(QString key, uint value) {
    Value *v = processKeySections(key, true);
    v->SetUint(value);
}

uint64_t SettingsManager::GetUInt64(QString key, uint64_t defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsUint64()) {
        return defaultValue;
    }
    else {
        return v->GetUint64();
    }
}

void SettingsManager::SetUInt64(QString key, uint64_t value) {
    Value *v = processKeySections(key, true);
    v->SetUint64(value);
}

float SettingsManager::GetFloat(QString key, float defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsFloat()) {
        return defaultValue;
    }
    else {
        return v->GetFloat();
    }
}

void SettingsManager::SetFloat(QString key, float value) {
    Value *v = processKeySections(key, true);
    v->SetFloat(value);
}

double SettingsManager::GetDouble(QString key, double defaultValue) {
    Value *v = processKeySections(key);
    if (v == nullptr || !v->IsDouble()) {
        return defaultValue;
    }
    else {
        return v->GetDouble();
    }
}

void SettingsManager::SetDouble(QString key, double value) {
    Value *v = processKeySections(key);
    v->SetDouble(value);
}

void SettingsManager::DeleteKey(QString key) {
    if (!key.length()) {
        return;
    }
    QStringList parts = key.split(".");
    Value *v = &d;
    Value *p = nullptr;
    for (QStringList::iterator i = parts.begin(); i != parts.end(); ++i) {
        string part = stringFromQString(*i);
        if (!(v->IsObject() && v->HasMember(part.c_str()))) {
            v = nullptr;
            break;
        }
        p = v;
        v = &(*v)[part.c_str()];
    }
    if (v != nullptr && p != nullptr) { // p should never be nullptr but this check will silence the warning
        string lastKeyPath = stringFromQString(parts.last());
        p->RemoveMember(lastKeyPath.c_str());
    }
}
