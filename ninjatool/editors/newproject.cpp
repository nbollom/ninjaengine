//
// Created by nbollom on 14/12/16.
//

#include "newproject.h"
#include <QGridLayout>

NewProjectWidget::NewProjectWidget() : NewWidget() {
    QGridLayout *layout = new QGridLayout();
    contentWidget->setLayout(layout);
    QString nameHelp = "The name of the project\nThis will also be the name of the directory created for the project";
    nameLabel = new QLabel("Name", this);
    nameLabel->setToolTip(nameHelp);
    layout->addWidget(nameLabel, 0, 0);
    nameText = new QLineEdit(this);
    nameText->setToolTip(nameHelp);
    layout->addWidget(nameText, 0, 1, 1, 2);
    QString pathHelp = "The directory to create the project in\nA new directory will be created at this path with the project name";
    pathLabel = new QLabel("Path", this);
    pathLabel->setToolTip(pathHelp);
    layout->addWidget(pathLabel, 1, 0);
    pathText = new QLineEdit(this);
    pathText->setToolTip(pathHelp);
    layout->addWidget(pathText, 1, 1);
    pathSelectorButton = new QPushButton("Browse", this);
    pathSelectorButton->setAutoDefault(true);
    pathSelectorButton->setToolTip("Browse for a directory");
    connect(pathSelectorButton, &QPushButton::pressed, this, &NewProjectWidget::PathSelectorClicked);
    layout->addWidget(pathSelectorButton, 1, 2);
}

void NewProjectWidget::PathSelectorClicked() {
    if (pathBrowser == nullptr) {
        pathBrowser = new QFileDialog(this, "Select Project Path");
        connect(pathBrowser, &QFileDialog::accepted, this, &NewProjectWidget::PathSelectorOK);
    }
    pathBrowser->setFileMode(QFileDialog::DirectoryOnly);
    if (pathText->text().length()) {
        pathBrowser->setDirectory(pathText->text());
    }
    pathBrowser->show();
}

void NewProjectWidget::PathSelectorOK() {
    pathText->setText(pathBrowser->directory().path());
}
