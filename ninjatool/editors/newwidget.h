//
// Created by nbollom on 14/12/16.
//

#ifndef PROJECT_NEWWIDGET_H
#define PROJECT_NEWWIDGET_H

#include <QDialog>
#include <QPushButton>

class NewWidget : public QDialog {
    Q_OBJECT

public:
    NewWidget();

protected:
    QWidget *contentWidget;
    QWidget *buttonsWidget;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void onOKPressed();
    void onCancelledPressed();

};

#endif //PROJECT_NEWWIDGET_H
