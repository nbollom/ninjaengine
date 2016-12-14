//
// Created by nbollom on 10/11/16.
//

#ifndef PROJECT_OBJECTTYPE_H
#define PROJECT_OBJECTTYPE_H

#include <QObject>
#include <QString>
#include <QStringListModel>

class ObjectType : public QObject {
    Q_OBJECT

protected:
    QStringListModel *_model;

public:
    ObjectType();
    virtual QString GetTitle() = 0;
    QStringListModel* GetModel();
    virtual QWidget* GetAddNewItemForm() = 0;
    virtual QWidget* GetEditor(QString item) = 0;

};

extern QList<ObjectType*> objectTypes;
extern QList<ObjectType*> resourceTypes;

#endif //PROJECT_OBJECTTYPE_H
