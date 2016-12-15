//
// Created by nbollom on 14/12/16.
//

#include <QtWidgets/QVBoxLayout>
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
    cancelButton = new QPushButton("Cancel", this);
    buttonLayout->addWidget(cancelButton);
    okButton = new QPushButton("OK", this);
    buttonLayout->addWidget(okButton);
    setWindowModality(Qt::ApplicationModal);
}
