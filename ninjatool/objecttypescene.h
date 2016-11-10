//
// Created by nbollom on 10/11/16.
//

#ifndef PROJECT_OBJECTTYPESCENE_H
#define PROJECT_OBJECTTYPESCENE_H

#include "objecttype.h"

class ObjectTypeScene : public ObjectType {
    Q_OBJECT

private:
    QStringList _list;

public:
    ObjectTypeScene();
    QString GetTitle() override;
    QWidget* GetAddNewItemForm() override;
    QWidget* GetEditor(QString item) override;
};

#endif //PROJECT_OBJECTTYPESCENE_H
