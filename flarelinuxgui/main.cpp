/*
Flare Linux GUI Client, version 1.0.0
flarelinuxgui.exe
©2021, Foreach Code Factory. All Rights Reserved.
*/

#include <QApplication>
#include <QPixmap>

#include "mainwindow.h"

int main(int ARGC, char *ARGV[]) {
    QApplication mainApp(ARGC, ARGV);

    mainWindow window;

    QPixmap pPm("favicon.png");

    window.setWindowTitle("Flare Linux GUI Client - v1.0.0");

    window.setWindowIcon(pPm);

    window.show();

    return mainApp.exec();
}
