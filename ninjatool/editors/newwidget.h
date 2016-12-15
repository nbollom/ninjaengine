//
// Created by nbollom on 14/12/16.
//

#ifndef PROJECT_NEWWIDGET_H
#define PROJECT_NEWWIDGET_H

#include <QWidget>
#include <QtWidgets/QPushButton>

class NewWidget : public QWidget {
    Q_OBJECT

public:
    NewWidget();

protected:
    QWidget *contentWidget;
    QWidget *buttonsWidget;
    QPushButton *okButton;
    QPushButton *cancelButton;

signals:
    void dialogOk();
    void dialogCancel();

};

#endif //PROJECT_NEWWIDGET_H
