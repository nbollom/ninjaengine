//
// Created by nbollom on 28/11/16.
//

#include "settingsconstants.h"

const QString REMEMBER_LAYOUT_KEY = "Settings.RememberWindowLayout";
const bool REMEMBER_LAYOUT_DEFAULT = false;

const QString LAYOUT_KEY = "Layout";

const QString X_KEY = "X";
const QString Y_KEY = "Y";
const QString WIDTH_KEY = "Width";
const QString HEIGHT_KEY = "Height";

QString BuildKey(QString s1, QString s2, QString s3, QString s4, QString s5, QString s6) {
    QString key = s1 + "." + s2;
    if (s3 != nullptr) {
        key += "." + s3;
    }
    if (s4 != nullptr) {
        key += "." + s4;
    }
    if (s5 != nullptr) {
        key += "." + s5;
    }
    if (s6 != nullptr) {
        key += "." + s6;
    }
    return key;
}
