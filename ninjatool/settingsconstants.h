//
// Created by nbollom on 28/11/16.
//

#ifndef PROJECT_SETTINGSCONSTANTS_H
#define PROJECT_SETTINGSCONSTANTS_H

#include <QString>

extern const QString REMEMBER_LAYOUT_KEY;
extern const bool REMEMBER_LAYOUT_DEFAULT;

extern const QString LAYOUT_KEY;

extern const QString X_KEY;
extern const QString Y_KEY;
extern const QString WIDTH_KEY;
extern const QString HEIGHT_KEY;

QString BuildKey(int count, ...);

#endif //PROJECT_SETTINGSCONSTANTS_H
