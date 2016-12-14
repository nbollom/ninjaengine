//
// Created by nbollom on 14/11/16.
//

#include "settingswidget.h"
#include "../settingsmanager.h"
#include "../settingsconstants.h"

const QString SettingsWidget::DocumentType = QString("NinjaTool");
const QString SettingsWidget::DocumentName = QString("Settings");

SettingsWidget::SettingsWidget() {
    layout = new QGridLayout(this);
    this->setLayout(layout);
    rememberLayoutLabel = new QLabel("Remember Window Layout", this);
    layout->addWidget(rememberLayoutLabel, 0, 0);
    rememberLayoutCheckbox = new QCheckBox("", this);
    rememberLayoutCheckbox->setChecked(SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT));
    connect(rememberLayoutCheckbox, &QCheckBox::toggled, this, &SettingsWidget::RememberLayoutChecked);
    layout->addWidget(rememberLayoutCheckbox, 0, 1);
    changes = 0;
}

QString SettingsWidget::GetDocumentType() {
    return SettingsWidget::DocumentType;
}

QString SettingsWidget::GetDocumentName() {
    return SettingsWidget::DocumentName;
}

bool SettingsWidget::SaveDocument() {
    if (SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT)) {
        SettingsManager::DeleteKey(LAYOUT_KEY);
    }
    SettingsManager::Sync();
    if (changes > 0) {
        emit settingsChanged();
    }
    return true;
}

void SettingsWidget::RememberLayoutChecked(bool checked) {
    changes += (SettingsManager::GetBool(REMEMBER_LAYOUT_KEY, REMEMBER_LAYOUT_DEFAULT) == checked ? -1 : 1);
    SettingsManager::SetBool(REMEMBER_LAYOUT_KEY, checked);
}
