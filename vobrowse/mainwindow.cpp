/*
The QeFeM project.
Copyright (C) 2010  Karim Pinter

This code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <QtGlobal>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QLibraryInfo>
#include <QDesktopServices>

#include "mainwindow.h"

using namespace std;

#ifdef Q_WS_MAC
extern void qt_set_sequence_auto_mnemonic(bool b);
#endif

// MainWindow constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    
#ifdef Q_WS_MAC
    qt_set_sequence_auto_mnemonic( true );
#endif
    // setting up Window settings and layout
    this->setWindowTitle("VoBrowse - Voice Controlled File Browser");
    this->setWindowIcon(QIcon("icon.png"));
    contentWidget = QPointer<QWidget>(new QWidget(this));
    contentWidget->setWindowFlags( Qt::SubWindow );
    wholeLayout = QSharedPointer<QVBoxLayout>(new QVBoxLayout());
    listLayout = QPointer<QHBoxLayout>(new QHBoxLayout());
    wholeLayout->setContentsMargins( 2, 2, 2, 2 );
    listLayout->setContentsMargins( 2, 2, 2, 2 );
    wholeLayout->setSpacing(2);
    listLayout->setSpacing(2);
    // Panel for listing browser contents
    rightPanel = QPointer<FMPanel>(new FMPanel( this, false, contentWidget.data() ));
    leftPanel = QPointer<FMPanel>(new FMPanel( this, true, contentWidget.data() ));
    rightPanel->hide();          // right panel only for testing purposes

    alt1 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1),
                              this));
    connect( alt1.data(), SIGNAL(activated()), this, SLOT(alt1Pressed()));
    alt2 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2),
                              this));
    connect( alt2.data(), SIGNAL(activated()), this, SLOT(alt2Pressed()));
    alt3 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_3),
                              this));
    connect( alt3.data(), SIGNAL(activated()), this, SLOT(alt3Pressed()));
    alt4 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_4),
                              this));
    connect( alt4.data(), SIGNAL(activated()), this, SLOT(alt4Pressed()));
    alt5 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_5),
                              this));
    connect( alt5.data(), SIGNAL(activated()), this, SLOT(alt5Pressed()));
    alt6 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_6),
                              this));
    connect( alt6.data(), SIGNAL(activated()), this, SLOT(alt6Pressed()));
    alt7 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_7),
                              this));
    connect( alt7.data(), SIGNAL(activated()), this, SLOT(alt7Pressed()));
    alt8 = QSharedPointer<QShortcut>(new QShortcut(QKeySequence(Qt::ALT + Qt::Key_8),
                              this));
    connect( alt8.data(), SIGNAL(activated()), this, SLOT(alt8Pressed()));
    
    listLayout->addWidget( leftPanel.data() );
    listLayout->addWidget( rightPanel.data() );
    controlPanel = QPointer<ControlPanel>(new ControlPanel(this,leftPanel.data(),rightPanel.data()));
    wholeLayout->addLayout( listLayout.data() );
    wholeLayout->addWidget( controlPanel.data() );
    contentWidget->setLayout( wholeLayout.data() );
#if defined(Q_WS_WIN)||defined(Q_WS_MAC)||defined(Q_WS_X11)
    contentWidget->setMinimumSize(300,320);
    setMinimumSize(300,320);
    setGeometry(100,100,500,480);    
#endif
#if defined(QEFEM_MAEMO_DEV)
    setWindowState(Qt::WindowFullScreen);
    contentWidget->setMinimumSize(800,480);
    setMinimumSize(800,480);
    setGeometry(0,0,800,480);    
#endif               
    rightPanel->setDirListFocus();
    // initialise the text pad for text file browsing
    mypad = new Notepad();
    // for mutual exclusion purposes between different files
    mutex.tryLock();
    mutex.unlock();
}
// destructor
MainWindow::~MainWindow()
{
}
// handler for window resize
void MainWindow::resizeEvent ( QResizeEvent * /*event*/ )
{
    contentWidget->resize( size() );
}

// handler for stopping animation
void MainWindow::stopAnimation()
{
    controlPanel->stopAnimation();
}

// handler for starting animation
void MainWindow::startAnimation()
{
    controlPanel->startAnimation();
}

// get current directory of left browser panel
QString MainWindow::leftCurrentDir()
{
    return leftPanel->curDir();
}

QString MainWindow::rightCurrentDir()
{
    return rightPanel->curDir();
}
// get current file for left browser panel
QString MainWindow::leftCurrentFile()
{
    return leftPanel->curFile();
}

QString MainWindow::rightCurrentFile()
{
    return rightPanel->curFile();
}

// handling keypress events

// setting focus to directory lists of left browser panel
void MainWindow::alt3Pressed()
{
    leftPanel->setDirListFocus();
}


void MainWindow::alt4Pressed()
{
    rightPanel->setDirListFocus();
}

// setting focus to history of left browser panel
void MainWindow::alt5Pressed()
{
    leftPanel->setHistoryFocus();
}

void MainWindow::alt6Pressed()
{
    rightPanel->setHistoryFocus();
}

// setting focus to directory lists of left browser panel
void MainWindow::alt7Pressed()
{
    leftPanel->setBookmarkFocus();
}

void MainWindow::alt8Pressed()
{
    rightPanel->setBookmarkFocus();
}

void MainWindow::alt1Pressed()
{
    leftPanel->setDriveListFocus();
}

void MainWindow::alt2Pressed()
{
    rightPanel->setDriveListFocus();
}



void  MainWindow::helpPressed()
{
    /*QString url("file:///");
    QString fileName(QDir::homePath());
    fileName.append("/.Qefem/qefem_help.html");
    if(!QFile::exists(fileName))
    {
        QFile::copy(":/help/qefem_help.html",fileName);
    }
    url.append(fileName);
    QDesktopServices::openUrl( url );*/
}

void MainWindow::notifySaid(QString words)
{
    QMessageBox msgBox;
    msgBox.setText(words);
    msgBox.exec();
}

void MainWindow::openByName(QString fileName)
{
    leftPanel->openByName(fileName);
    emit pathChanged();
}

QStringList MainWindow::getFileList()
{
    return leftPanel->getFileList();
}

void MainWindow::notifyPathChanged()
{
    emit pathChanged();
}

void MainWindow::forwardDir()
{
    leftPanel->back();
}

void MainWindow::backDir()
{
    leftPanel->forward();
}

void MainWindow::setWorking(bool working)
{
    mutex.lock();
    this->working = working;
    mutex.unlock();
}

bool MainWindow::isWorking()
{
    return this->working;
}

