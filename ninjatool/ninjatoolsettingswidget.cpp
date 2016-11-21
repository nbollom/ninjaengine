//
// Created by nbollom on 14/11/16.
//

#include "ninjatoolsettingswidget.h"
#include "settingsmanager.h"

const QString NinjaToolSettingsWidget::DocumentType = QString("NinjaTool");
const QString NinjaToolSettingsWidget::DocumentName = QString("Settings");

NinjaToolSettingsWidget::NinjaToolSettingsWidget() {
    layout = new QGridLayout(this);
    this->setLayout(layout);
    rememberLayoutLabel = new QLabel("Remember Window Layout", this);
    layout->addWidget(rememberLayoutLabel, 0, 0);
    rememberLayoutCheckbox = new QCheckBox("", this);
    rememberLayoutCheckbox->setChecked(SettingsManager::GetBool("Settings.RememberWindowLayout", false));
    connect(rememberLayoutCheckbox, &QCheckBox::toggled, this, &NinjaToolSettingsWidget::RememberLayoutChecked);
    layout->addWidget(rememberLayoutCheckbox, 0, 1);
}

QString NinjaToolSettingsWidget::GetDocumentType() {
    return NinjaToolSettingsWidget::DocumentType;
}

QString NinjaToolSettingsWidget::GetDocumentName() {
    return NinjaToolSettingsWidget::DocumentName;
}

bool NinjaToolSettingsWidget::SaveDocument() {
    if (SettingsManager::GetBool("Settings.RememberWindowLayout", false)) {
        SettingsManager::DeleteKey("Layout");
    }
    SettingsManager::Sync();
    return true;
}

void NinjaToolSettingsWidget::RememberLayoutChecked(bool checked) {
    SettingsManager::SetBool("Settings.RememberWindowLayout", checked);
}
