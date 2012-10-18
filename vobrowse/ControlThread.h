#ifndef CONTROL_THREAD_H
#define CONTROL_THREAD_H

#pragma once
#include <QThread>
#include "mainwindow.h"
#include <string>
#include "VoiceBase.h"
#include <QtGui>
#include <QtGui/QMessageBox>
#include "importinbuf.h"
#include "utils.h"
#include "Speech.h"
class ControlThread :
    public QThread
{
    Q_OBJECT
public:
    ControlThread(MainWindow *window);
    ~ControlThread(void);
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
    Speech sp;
    void reloadFiles();
signals:
    void openFile(QString);
    void back();
    void forward();
    void notifySaid(QString);
    void forwardDir();
    void backDir();
    void searchSpoken(bool);
    void spokeSearchAlpha(char);
    void setActiveTab(int);
    void linuxSearch(QString);
    void openNotepad(QString);
    void notepadIncreaseFont();
    void notepadDecreaseFont();
    void notepadScrollUp();
    void notepadScrollDown();
    void notepadClose();
    void changeDrive(const QString&);
    void bookmarkthis(const QString&);
public slots:
    void pathChanged();
    
private:
    MainWindow *w;
    VoiceBase *vBase;
    
protected:
    void run();

};

#endif
