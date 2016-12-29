//
// Created by nbollom on 14/12/16.
//

#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include "newwidget.h"

NewWidget::NewWidget() {
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    contentWidget = new QWidget(this);
    layout->addWidget(contentWidget);
    layout->addStretch(1);
    buttonsWidget = new QWidget(this);
    layout->addWidget(buttonsWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonsWidget->setLayout(buttonLayout);
    okButton = new QPushButton("OK", this);
    okButton->setAutoDefault(true);
    okButton->setDefault(true);
    connect(okButton, &QPushButton::pressed, this, &NewWidget::onOKPressed);
    buttonLayout->addWidget(okButton);
    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::pressed, this, &NewWidget::onCancelledPressed);
    buttonLayout->addWidget(cancelButton);
    setModal(true);
}

void NewWidget::onOKPressed() {
    qDebug() << "OK pressed";
    accept();
}

void NewWidget::onCancelledPressed() {
    qDebug() << "Cancel pressed";
    reject();
}
