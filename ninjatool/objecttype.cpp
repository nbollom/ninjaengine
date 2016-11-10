//
// Created by nbollom on 10/11/16.
//

#include "objecttype.h"
#include "objecttypescene.h"

QList<ObjectType*> objectTypes = {
        new ObjectTypeScene()
};

ObjectType::ObjectType() {
    _model = new QStringListModel();
}

QStringListModel *ObjectType::GetModel() {
    return _model;
}
