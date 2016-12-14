//
// Created by nbollom on 14/11/16.
//

#ifndef PROJECT_NINJATOOLSETTINGSWINDOW_H
#define PROJECT_NINJATOOLSETTINGSWINDOW_H

#include "documentwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>

class SettingsWidget : public DocumentWidget {
    Q_OBJECT

private:
    QGridLayout *layout;
    QLabel *rememberLayoutLabel;
    QCheckBox *rememberLayoutCheckbox;
    int changes;

protected:
    void RememberLayoutChecked(bool checked);

public:
    static const QString DocumentType;
    static const QString DocumentName;

    SettingsWidget();
    QString GetDocumentType() override;
    QString GetDocumentName() override;
    bool SaveDocument() override;

signals:
    void settingsChanged();

};

#endif //PROJECT_NINJATOOLSETTINGSWINDOW_H
