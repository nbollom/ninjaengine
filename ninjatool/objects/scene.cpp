//
// Created by nbollom on 10/11/16.
//

#include "scene.h"

Scene::Scene() : ObjectType() {
    _list << "Test";
    _list << "Test2";
    _list << "Test3";
    _model->setStringList(_list);
}

QString Scene::GetTitle() {
    return "Scene";
}

QWidget* Scene::GetAddNewItemForm() {
    return nullptr;
}

QWidget* Scene::GetEditor(QString item) {
    return nullptr;
}
