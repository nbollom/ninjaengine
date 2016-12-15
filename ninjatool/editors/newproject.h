//
// Created by nbollom on 14/12/16.
//

#ifndef PROJECT_NEWPROJECT_H
#define PROJECT_NEWPROJECT_H

#include "newwidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

class NewProjectWidget : public NewWidget {
    Q_OBJECT

public:
    NewProjectWidget();

private:
    QLabel *nameLabel;
    QLineEdit *nameText;
    QLabel *pathLabel;
    QLineEdit *pathText;
    QPushButton *pathSelectorButton;
    QFileDialog *pathBrowser = nullptr;

    void PathSelectorClicked();
    void PathSelectorOK();
};

#endif //PROJECT_NEWPROJECT_H
