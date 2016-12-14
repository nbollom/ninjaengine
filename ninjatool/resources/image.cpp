//
// Created by nbollom on 14/12/16.
//

#include "image.h"

Image::Image() : ObjectType() {
    _list << "Test";
    _list << "Test2";
    _list << "Test3";
    _model->setStringList(_list);
}

QString Image::GetTitle() {
    return "Image";
}

QWidget* Image::GetAddNewItemForm() {
    return nullptr;
}

QWidget* Image::GetEditor(QString item) {
    return nullptr;
}
