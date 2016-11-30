//
// Created by nbollom on 14/11/16.
//

#include "ninjatoolsettingswidget.h"
#include "settingsmanager.h"
#include "settingsconstants.h"

const QString NinjaToolSettingsWidget::DocumentType = QString("NinjaTool");
const QString NinjaToolSettingsWidget::DocumentName = QString("Settings");

NinjaToolSettingsWidget::NinjaToolSettingsWidget() {
    layout = new QGridLayout(this);
    this->setLayout(layout);
    rememberLayoutLabel = new QLabel("Remember Window Layout", this);
    layout->addWidget(rememberLayoutLabel, 0, 0);
    rememberLayoutCheckbox = new QCheckBox("", this);
    rememberLayoutCheckbox->setChecked(SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT));
    connect(rememberLayoutCheckbox, &QCheckBox::toggled, this, &NinjaToolSettingsWidget::RememberLayoutChecked);
    layout->addWidget(rememberLayoutCheckbox, 0, 1);
    changes = 0;
}

QString NinjaToolSettingsWidget::GetDocumentType() {
    return NinjaToolSettingsWidget::DocumentType;
}

QString NinjaToolSettingsWidget::GetDocumentName() {
    return NinjaToolSettingsWidget::DocumentName;
}

bool NinjaToolSettingsWidget::SaveDocument() {
    if (SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT)) {
        SettingsManager::DeleteKey(LAYOUT_KEY);
    }
    SettingsManager::Sync();
    if (changes > 0) {
        emit settingsChanged();
    }
    return true;
}

void NinjaToolSettingsWidget::RememberLayoutChecked(bool checked) {
    changes += (SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT) == checked ? -1 : 1);
    SettingsManager::SetBool(REMEMBER_LAYOUT_KEY, checked);
}
