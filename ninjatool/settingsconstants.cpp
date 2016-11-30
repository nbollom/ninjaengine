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

QString BuildKey(int count, ...) {
    QString key;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        if (key.length()) {
            key += ".";
        }
        key += va_arg(args, QString);
    }
    va_end(args);
    return key;
}
