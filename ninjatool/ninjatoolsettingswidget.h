//
// Created by nbollom on 14/11/16.
//

#ifndef PROJECT_NINJATOOLSETTINGSWINDOW_H
#define PROJECT_NINJATOOLSETTINGSWINDOW_H

#include "documentwidget.h"

class NinjaToolSettingsWidget : public DocumentWidget {
    Q_OBJECT

public:
    static const QString DocumentType;
    static const QString DocumentName;

    NinjaToolSettingsWidget();
    QString GetDocumentType() override;
    QString GetDocumentName() override;
    bool SaveDocument() override;

};

#endif //PROJECT_NINJATOOLSETTINGSWINDOW_H
