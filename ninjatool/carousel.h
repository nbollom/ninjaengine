//
// Created by nbollom on 14/12/16.
//

#ifndef PROJECT_CAROUSEL_H
#define PROJECT_CAROUSEL_H

#include "objecttype.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QListView>

class Carousel : public QWidget {
    Q_OBJECT

private:
    int selectedIndex;
    QList<QPushButton*> buttons;
    QList<QListView*> lists;

protected:
    // Carousel slots
    void buttonPressed();

public:
    Carousel(QList<ObjectType*> source);
    ~Carousel();
};

#endif //PROJECT_CAROUSEL_H
