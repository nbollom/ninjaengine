//
// Created by nbollom on 10/11/16.
//

#include "objecttypescene.h"

ObjectTypeScene::ObjectTypeScene() : ObjectType() {
    _list << "Test";
    _list << "Test2";
    _list << "Test3";
    _model->setStringList(_list);
}

QString ObjectTypeScene::GetTitle() {
    return "Scene";
}

QWidget* ObjectTypeScene::GetAddNewItemForm() {
    return nullptr;
}

QWidget* ObjectTypeScene::GetEditor(QString item) {
    return nullptr;
}
