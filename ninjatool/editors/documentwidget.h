//
// Created by nbollom on 14/11/16.
//

#ifndef PROJECT_DOCUMENTWIDGET_H
#define PROJECT_DOCUMENTWIDGET_H

#include <QWidget>

class DocumentWidget : public QWidget {
    Q_OBJECT

public:
    virtual QString GetDocumentType() = 0;
    virtual QString GetDocumentName() = 0;
    virtual bool SaveDocument() = 0;

signals:
    void widgetClosed(DocumentWidget *widget);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE {
        SaveDocument();
        emit widgetClosed(this);
    }

};

#endif //PROJECT_DOCUMENTWIDGET_H
