//
// Created by nbollom on 14/12/16.
//

#include "newproject.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>

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

NewProjectWidget::~NewProjectWidget() {
    delete nameLabel;
    delete nameText;
    delete pathLabel;
    delete pathText;
    delete pathSelectorButton;
    delete pathBrowser;
}

QString NewProjectWidget::GetProjectName() {
    return projectName;
}

QDir NewProjectWidget::GetProjectPath() {
    return projectPath;
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
    pathBrowser->exec();
}

void NewProjectWidget::PathSelectorOK() {
    pathText->setText(pathBrowser->directory().path());
}

void NewProjectWidget::onOKPressed() {
    if (nameText->text().length() == 0) {
        QMessageBox::critical(this, "Error", "Name cannot be empty");
        return;
    }
    projectName = nameText->text();
    if (pathText->text().length() == 0) {
        QMessageBox::critical(this, "Error", "Path cannot be empty");
        return;
    }
    projectPath = QDir(pathText->text());
    if (!projectPath.exists()) {
        QMessageBox::critical(this, "Error", "Path must exist");
        return;
    }
    QFileInfoList entryList = projectPath.entryInfoList(QDir::NoFilter, QDir::DirsFirst);
    for (QFileInfoList::iterator i = entryList.begin(); i != entryList.end(); ++i) {
        QFileInfo fileInfo = *i;
        if (fileInfo.fileName() == projectName && fileInfo.isDir()) {
            if (fileInfo.dir().exists(projectName + ".dat")) {
                if (QMessageBox::question(this, "Warning", "A project already exists at this location\nDo you wish to overwrite?") == QMessageBox::No) {
                    return;
                }
            }
            break;
        }
        else if (fileInfo.fileName() == projectName && fileInfo.isFile()) {
            // the filesystem might allow files and directories with the same name, try to create the directory before erroring
            if (!projectPath.mkdir(projectName)) {
                QMessageBox::critical(this, "Error", "Cannot create a project with the name " + projectName + " in " + projectPath.absolutePath());
                return;
            }
            break;
        }
        else {
            if (!projectPath.mkdir(projectName)) {
                QMessageBox::critical(this, "Error", "Cannot create a project with the name " + projectName + " in " + projectPath.absolutePath());
                return;
            }
        }
    }
    NewWidget::onOKPressed();
}
