//
// Created by nbollom on 12/10/16.
//

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.show();
    return app.exec();
}