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

QString BuildKey(QString s1, QString s2, QString s3 = nullptr, QString s4 = nullptr, QString s5 = nullptr, QString s6 = nullptr);

#endif //PROJECT_SETTINGSCONSTANTS_H
