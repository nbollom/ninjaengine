//
// Created by nbollom on 10/11/16.
//

#include "objecttype.h"
#include "objects/scene.h"
#include "resources/image.h"

QList<ObjectType*> objectTypes = {
    new Scene()
};

QList<ObjectType*> resourceTypes = {
    new Image()
};

ObjectType::ObjectType() {
    _model = new QStringListModel();
}

QStringListModel *ObjectType::GetModel() {
    return _model;
}
