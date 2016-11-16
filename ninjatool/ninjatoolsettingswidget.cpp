//
// Created by nbollom on 14/11/16.
//

#include "ninjatoolsettingswidget.h"

const QString NinjaToolSettingsWidget::DocumentType = QString("NinjaTool");
const QString NinjaToolSettingsWidget::DocumentName = QString("Settings");

NinjaToolSettingsWidget::NinjaToolSettingsWidget() {
}

QString NinjaToolSettingsWidget::GetDocumentType() {
    return NinjaToolSettingsWidget::DocumentType;
}

QString NinjaToolSettingsWidget::GetDocumentName() {
    return NinjaToolSettingsWidget::DocumentName;
}

bool NinjaToolSettingsWidget::SaveDocument() {
    return true;
}
