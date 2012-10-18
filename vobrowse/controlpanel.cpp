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

#include "controlpanel.h"
#include "mainwindow.h"
#include <QDir>
#include <QProcess>
#include <QDebug>
#include <QThreadPool>
#include <QToolTip>
#include <QApplication>
#include <QMessageBox>

ControlPanel::ControlPanel( MainWindow* aMainW, FMPanel* aLeftPanel, 
                           FMPanel* aRightPanel )
{
    mainW = aMainW;
    leftPanel = aLeftPanel;
    rightPanel = aRightPanel;
    commandLayout = new QHBoxLayout();
    commandLayout->setContentsMargins( 2, 2, 2, 2 );
    commandLayout->setSpacing(1);
    searchButton = new QPushButton( "&Find" );
    searchButton->hide();
#if defined(QEFEM_MAEMO_DEV)
    bookmarkButton = new QPushButton( "&Bmark" );
#else    
    bookmarkButton = new QPushButton( "&Bookmark" );
    bookmarkButton->hide();
#endif  
#if !defined(QEFEM_MAEMO_DEV)
    //animation->setToolTip("When this animation is rotating its indicating that some file operation is going on.");
    bookmarkButton->setToolTip("This bookmarks the selected directory or the current directory. Those can be activeted through the bookmarks tab. The bookmarks are stored in home dir/.Qefem/.bookmarks text file.");
    //animation->setWhatsThis("When this animation is rotating its indicating that some file operation is going on.");
    bookmarkButton->setWhatsThis("This bookmarks the selected directory or the current directory. Those can be activeted through the bookmarks tab. The bookmarks are stored in home dir/.Qefem/.bookmarks text file.");
    searchButton->setWhatsThis("This starts a search in the current folder, wildcharacters can be used. The result is listed in found tab");
#endif
    animation = new QLabel();
    movie = new QMovie(":/images/spiral.gif");
    animation->setMinimumSize( 30, 30);
    animation->setMaximumSize( 30, 30);
    animation->setMovie(movie);
    movie->setScaledSize( QSize(30,30) );
    movie->start();
    commandLayout->addWidget( animation );
    commandLayout->addWidget( bookmarkButton );
    commandLayout->addWidget( searchButton );
#if defined(QEFEM_MAEMO_DEV)
    openButton = new QPushButton( "O&pen" );
    commandLayout->addWidget( openButton );
    exitButton = new QPushButton( "E&xit" );
    commandLayout->addWidget( exitButton );
#endif    
    //add events
    connect(bookmarkButton, SIGNAL(clicked( bool )), this, SLOT( bookmarkButtonClicked( bool ) ));
    connect(searchButton, SIGNAL(clicked( bool )), this, SLOT( searchButtonClicked( bool ) ));
#if defined(QEFEM_MAEMO_DEV)
    connect(openButton, SIGNAL(clicked( bool )), this, SLOT( openButtonClicked( bool ) ));
    connect(exitButton, SIGNAL(clicked( bool )), this, SLOT( exitButtonClicked( bool ) ));
#endif
    setLayout( commandLayout );
    setVisible( true );
    statusOn = false;
    movie->stop();
}

ControlPanel::~ControlPanel()
{
    delete commandLayout;
}

void ControlPanel::bookmarkButtonClicked( bool /*checked*/ )
{
    QString path;
    if( leftPanel->lastFocus() > rightPanel->lastFocus() )
    {
        if( leftPanel->curFile().isEmpty() || QFileInfo( leftPanel->curFile() ).isFile() )
        {
            path.append( leftPanel->curDir() );
            leftPanel->addBookmark( path);
            rightPanel->addBookmark( path );
        }
        else
        {
            path.append( leftPanel->curFile() );
            leftPanel->addBookmark( path );
            rightPanel->addBookmark( path );
        }
    }
    else
    {
        if( rightPanel->curFile().isEmpty() || QFileInfo( rightPanel->curFile() ).isFile() )
        {
            path.append( rightPanel->curDir() );
            leftPanel->addBookmark( rightPanel->curDir() );
            rightPanel->addBookmark( rightPanel->curDir() );
        }
        else
        {
            path.append( rightPanel->curFile() );
            leftPanel->addBookmark( path );
            rightPanel->addBookmark( path );
        }
    }
}

void ControlPanel::searchButtonClicked( bool checked )
{
    if(checked)
    {
        movie->start();
        #if defined(QEFEM_MAEMO_DEV)
        rightPanel->showPathEdit();
        #endif
        leftPanel->setEditMode( Search );
    }else
    {
        movie->stop();
        leftPanel->setEditMode(None);
    }
}
#if defined(QEFEM_MAEMO_DEV)
void ControlPanel::openButtonClicked( bool /*checked*/ )
{
    if( leftPanel->lastFocus() > rightPanel->lastFocus() )
    {
        leftPanel->openSelected();
    }
    else
    {
        rightPanel->openSelected();
    }
}

void ControlPanel::exitButtonClicked( bool /*checked*/ )
{
    QCoreApplication::exit(0);
}
#endif

QStringList ControlPanel::getStatus()
{
    QStringList list;
    /*for(int i=0; i < copyVector.size(); i++ )
    {
        if( copyVector[i].first->isRunning() )
        {
            QString text("Copy of ");
            text.append( copyVector[i].second.first );
            text.append(" is running.");
            list << text;
        }
    }
    for(int i=0; i < delVector.size(); i++ )
    {
        if( delVector[i].first->isRunning() )
        {
            QString text("Deletion of ");
            text.append( delVector[i].second.first );
            text.append(" is running.");
            list << text;
        }
    }*/
    return list;
}

void ControlPanel::disableButtons()
{
    bookmarkButton->setDisabled( true );
    searchButton->setDisabled( true );
#if defined(QEFEM_MAEMO_DEV)
    openButton->setDisabled( true );
#endif
}

void ControlPanel::enableButtons()
{
    bookmarkButton->setEnabled( true );
    searchButton->setEnabled( true );
#if defined(QEFEM_MAEMO_DEV)
    openButton->setEnabled( true );
#endif
}

void ControlPanel::stopAnimation()
{
    movie->stop();
}

void ControlPanel::startAnimation()
{
    if( movie->state() != QMovie::Running )
    {
        movie->start();
    }
}
