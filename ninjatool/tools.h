//
// Created by nbollom on 31/01/17.
//

#ifndef PROJECT_TOOLS_H
#define PROJECT_TOOLS_H

#include <string>
#include <stdlib.h>

inline std::string stringFromQString(QString value) {
    QByteArray ba = value.toLatin1();
    const char *bytes = ba;
    return std::string(bytes);
}

inline char* charStringFromQString(QString value) {
    QByteArray ba = value.toLatin1();
    const char *bytes = ba;
    size_t size = sizeof(char) * value.length();
    char *newValue = (char*)malloc(size);
    memcpy(newValue, bytes, size);
    return newValue;
}

#endif //PROJECT_TOOLS_H
