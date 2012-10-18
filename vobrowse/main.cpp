
#include <QtGui/QApplication>
#include <QDir>
#include <QFile>
#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include "ControlThread.h"
#include "Speech.h"

using namespace std;
#ifndef WIN32

#define HB_Q_WS_MAEMO
#endif
int main(int argc, char *argv[])
{
    Speech::visually_disabled = QFileInfo("visually_disabled").exists();
    QApplication a(argc, argv);
    a.setDoubleClickInterval(600);
    // Create browser instance
    MainWindow w;
    if(!Speech::visually_disabled)
        w.show();
    //main control thread for speech commands recognition, text file browsing and text-to-speech
    ControlThread t(&w);
    t.start();
    Speech::instance()->say("File Browser Started", 1);
    int ret = a.exec();
    return ret;
}
