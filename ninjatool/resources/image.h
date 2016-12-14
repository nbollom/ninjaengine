//
// Created by nbollom on 14/12/16.
//

#ifndef PROJECT_RESOURCETYPESCENE_H
#define PROJECT_RESOURCETYPESCENE_H

#include "../objecttype.h"

class Image : public ObjectType {
    Q_OBJECT

private:
    QStringList _list;

public:
    Image();
    QString GetTitle() override;
    QWidget* GetAddNewItemForm() override;
    QWidget* GetEditor(QString item) override;
};

#endif //PROJECT_RESOURCETYPESCENE_H
