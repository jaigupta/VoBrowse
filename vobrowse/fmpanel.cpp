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

#include "fmpanel.h"
#include "mainwindow.h"
#include <QDirModel>
#include <QDir>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDebug>
#include <QToolTip>
#include <QTimer>
#include <QApplication>
#include <QDesktopServices>

FMPanel::FMPanel( MainWindow* aMainW, bool aLeft, QWidget * parent, Qt::WindowFlags f) : QWidget( parent, f ), left(aLeft)
{
    //setup variables
    mainW = aMainW;
    lastClick = QTime::currentTime ();
    noDrive = false;
    driveJustLoaded = false;
    //setup layouts and lists
    wholeLayout = new QVBoxLayout();
    tab = new QTabWidget();
    blist = new bookmarkListView();
    blist->setSelectionMode( QAbstractItemView::NoSelection );
    blist->setEditTriggers( QAbstractItemView::NoEditTriggers );
#if !defined(QEFEM_MAEMO_DEV)
    hlist = new historyListView( left );
    hlist->setSelectionMode( QAbstractItemView::NoSelection );
    hlist->setEditTriggers( QAbstractItemView::NoEditTriggers );
#endif
    foundList = new QListWidget( this );
    foundList->setSelectionMode( QAbstractItemView::NoSelection );
    foundList->setEditTriggers( QAbstractItemView::NoEditTriggers );    
#if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
    dlist = new driveListView();
#endif    
    dirList = new FMListView();
    tab->addTab(dirList,"Files");
#if !defined(QEFEM_MAEMO_DEV)
    tab->addTab(hlist,"History");
#endif
    tab->addTab(blist,"Bookmarks");
    tab->addTab(foundList,"Found");
#if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
    tab->addTab(dlist,"Drives");
#endif
    tab->setCurrentIndex(0);
    pathEdit = new QLineEdit();
    pathEdit->setFont(QFont("Courier", 15));
#if defined(QEFEM_MAEMO_DEV)
    pathEdit->setVisible( false );
#endif
    wholeLayout->setContentsMargins( 0, 0, 0, 0 );
    wholeLayout->setSpacing(0);
    wholeLayout->addWidget( tab );
    wholeLayout->addWidget( pathEdit );
    setLayout( wholeLayout );
    setVisible( true );
    setPathEditText( QDir::homePath());
    currentDir.clear();
    currentDir.append(QDir::homePath());
    currentFile.clear();
    currentFile.append(QDir::homePath());
#if !defined(QEFEM_MAEMO_DEV)
#if !defined(Q_OS_LINUX)
    //tab->setToolTip("Drive tab shows the drives. Files tab shows the files. History shows the last 128 visited directories. Bookmark tab shows bookmarks.");
#else
    //tab->setToolTip("Files tab shows the files. History shows the last 128 visited directories. Bookmark tab shows bookmarks.");
#endif
#endif
    //setup signals and slots
#if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
    connect(dlist, SIGNAL(clicked( const QModelIndex& )), this, SLOT( driveClicked( const QModelIndex & ) ));
    connect(dlist, SIGNAL(activated( const QModelIndex& )), this, SLOT( driveClicked( const QModelIndex & ) ));
    connect(hlist, SIGNAL(clicked( const QModelIndex& )), this, SLOT( listClicked( const QModelIndex & ) ));
    connect(hlist, SIGNAL(activated( const QModelIndex& )), this, SLOT( listClicked( const QModelIndex & ) ));
    connect(dirList, SIGNAL(clicked( const QModelIndex& )), this, SLOT( dirClicked( const QModelIndex & ) ));
    connect(dirList, SIGNAL(activated( const QModelIndex& )), this, SLOT( dirDoubleClicked( const QModelIndex & ) ));
    connect(dirList, SIGNAL(entered( const QModelIndex& )), this, SLOT( dirClicked( const QModelIndex & ) ));
#endif
    connect(blist, SIGNAL(clicked( const QModelIndex& )), this, SLOT( listClicked( const QModelIndex & ) ));
    connect(blist, SIGNAL(activated( const QModelIndex& )), this, SLOT( listClicked( const QModelIndex & ) ));
    connect(foundList, SIGNAL(itemDoubleClicked ( QListWidgetItem *)), this, SLOT( foundListClicked( QListWidgetItem * ) ));
    connect(foundList, SIGNAL(itemClicked ( QListWidgetItem *)), this, SLOT( foundListClicked( QListWidgetItem * ) ));
    connect(pathEdit, SIGNAL(editingFinished()),this,SLOT( editFinished() ));
    connect(dirList, SIGNAL(keyUpOrDownPressed()),this,SLOT( highlightMoved() ));
    connect(dirList, SIGNAL(copyFiles(const QStringList&)),this,SLOT( copy(const QStringList& ) ));
    connect(dirList, SIGNAL(focusGained()),this,SLOT( listGotFocus() ));
    //connect(dirList->model(), SIGNAL( rowChange()),this,SLOT(rowsChanged()));
    connect(dirList, SIGNAL( rootPathChanged ( const QString& )),this, SLOT( rootChanged ( const QString& ) ));
    foundList->clear();
    foundList->addItem("Clear list");
}

FMPanel::~FMPanel()
{
    delete wholeLayout;
}

#if defined(QEFEM_MAEMO_DEV)
void FMPanel::openSelected()
{
    switch( tab->currentIndex() )
    {
    case 0://this is the directory list
        {
        QStringList list = dirList->selectedFiles();
        // for some reason the first .. are never returned in the list
        // TODO: fix this
        if( list.count() == 0 )
        {
            QDir dir(currentDir);
            dir.cdUp();
            currentFile.clear();
            currentDir.clear();
            currentDir.append( dir.absolutePath() );
            dirList->setRootPath( currentDir );
            return;
        }
        if( list.at(0).isEmpty() || list.at(0).at(0)=='/' )
        {
            return;
        }
        if( list.at(0).at(0)=='.' && list.at(0).at(1)=='.' )
        {
            QDir dir(currentDir);
            dir.cdUp();
            currentFile.clear();
            currentDir.clear();
            currentDir.append( dir.absolutePath() );
            dirList->setRootPath( currentDir );
            return;
        }
        QString selectedFile( currentDir );
        selectedFile.append("/");
        selectedFile.append( list.at(0) );
        QFileInfo inf( selectedFile ) ;
        //isAbsolute()
        //isBundle()
        if( inf.isDir() )
        {
            //mainW->startAnimation();
            currentFile.clear();
            //TODO check the size
            currentDir.clear();
            currentDir.append( inf.absoluteFilePath() );
            dirList->setRootPath( currentDir );
            return;
        }
        if( inf.isExecutable() )
        {
            QProcess::startDetached( inf.absoluteFilePath() );
        }
        if( inf.isFile() )
        {
            QString url("file:///");
            url.append( inf.filePath() );
            //qDebug()<<url;
            QDesktopServices::openUrl( url );
        }
        currentDir.clear();
        currentDir.append( inf.absolutePath() );
        dirList->setRootPath( currentDir );
        break;
        }
    case 1://bookmark tab
        {
        break;
        }
    case 2://found tab
        {
        break;
        }
    default:
        {
        }
    }
}
#endif    

void FMPanel::listGotFocus()
{
    lastClick = QTime::currentTime();
}

void FMPanel::listClicked( const QModelIndex &index )
{
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    tab->setCurrentIndex(0);
#else
    tab->setCurrentIndex(1);
#endif    
    if( noDrive )
        return;
    const QStandardItemModel* model = 
        qobject_cast<const QStandardItemModel*>( index.model() );
    if( model != 0 )
    {
        lastClick = QTime::currentTime ();
        QStandardItem* item = model->itemFromIndex(index);
        //qDebug()<<item->text();
        //setPathEditText( item->text() );
        currentDir.clear();
        currentDir.append( item->text() );
        dirList->setRootPath( currentDir );
        //setPathEditText( currentDir );
    }
}

void FMPanel::openByName(QString &fileName)
{
    if(fileName.size() == 0){
        editFinished();
        return;
    }
    QDir curDir(currentDir);
    QString path = curDir.absoluteFilePath(fileName);
    QDir check(path);
    QDir act(path);
    QString upath = act.canonicalPath();
    QFileInfo f(upath);
    if(f.isDir())
    {
        //dirList->setRootPath(path);
        mode = None;
        setPathEditText(upath);
    }
    editFinished();
}

QStringList FMPanel::getFileList()
{
    QStringList res;
    QString DirPath = this->currentDir;
    QDir curDir(DirPath);
    return curDir.entryList();
}

void FMPanel::foundListClicked( QListWidgetItem *item )
{
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    tab->setCurrentIndex(0);
#else
    tab->setCurrentIndex(1);
#endif
    if( noDrive )
        return;
    if( item != NULL )
    {
        lastClick = QTime::currentTime ();
        if( item->text() == "Clear list")
        {
            foundList->clear();
            foundList->addItem("Clear list");
        #if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
            tab->setTabText( 4, "Found");
        #else
            #ifdef QEFEM_MAEMO_DEV
            tab->setTabText( 2, "Found");
            #else
            tab->setTabText( 3, "Found");
            #endif
        #endif
        }
        else
        {
            QFileInfo inf(item->text());
            qDebug()<<item->text();
            setPathEditText( item->text() );
            currentDir.clear();
            currentDir.append( inf.absoluteDir().absolutePath() );
            dirList->setRootPath( inf.absoluteDir().absolutePath() );
        }
        //setPathEditText( currentDir );
    }
}

void FMPanel::driveClicked( const QModelIndex &index )
{
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>( index.model() );
    if( model == NULL )
        return;
    QStandardItem* item = model->itemFromIndex(index);
#ifdef Q_WS_MAC
    QString path( item->whatsThis() );
#else
    QString path( item->text() );
#endif
    QDir dir( path );
    currentFile.clear();
    if( dir.entryInfoList().count()!=0 )
    {
        lastClick = QTime::currentTime ();
        currentDir.clear();
        currentDir.append( path );
        dirList->setRootPath( currentDir );
        setPathEditText( currentDir );
        driveJustLoaded = true;
        noDrive = false;
        QString empty = "";
        openByName(empty);
    }
    else
    {
        //TODO: check this out on win
        QStandardItemModel* model = new QStandardItemModel( 1, 1 );
        QStandardItem* empty = new QStandardItem("No drive available.");
        currentDir.clear();
        model->insertRow( 0, empty );
        dirList->setModel( model );
        setPathEditText( "No drive available." );
        noDrive = true;
        mainW->stopAnimation();
    }
    tab->setCurrentIndex(1);
    return;
}

void FMPanel::driveOpened( const QString &path )
{
    QDir dir( path );
    currentFile.clear();
    if( dir.entryInfoList().count()!=0 )
    {
        lastClick = QTime::currentTime ();
        currentDir.clear();
        currentDir.append( path );
        dirList->setRootPath( currentDir );
        setPathEditText( currentDir );
        driveJustLoaded = true;
        noDrive = false;
    }
    else
    {
        //TODO: check this out on win
        QStandardItemModel* model = new QStandardItemModel( 1, 1 );
        QStandardItem* empty = new QStandardItem("No drive available.");
        currentDir.clear();
        model->insertRow( 0, empty );
        dirList->setModel( model );
        setPathEditText( "No drive available." );
        noDrive = true;
        mainW->stopAnimation();
    }
    tab->setCurrentIndex(0);
    editFinished();
    return;
}

void FMPanel::dirClicked( const QModelIndex &  index )
{
    if( noDrive )
        return;
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>( index.model() );
    if( model != 0 )
    {
        lastClick = QTime::currentTime ();
        QStandardItem* item = model->itemFromIndex( index );
        QString path( dirList->getRootDir() );
        if( path.at(path.size()-1)!='/')
        {
            path.append("/");
        }
        if( index.row() == 0 )
        {
            path.append( ".." );
        }
        else
        {
            path.append( item->data(Qt::DisplayRole ).toString());
        }
        setPathEditText( path );
        currentFile.clear();
        currentFile.append( path );
    }
    mainW->notifyPathChanged();
}

void FMPanel::dirDoubleClicked( const QModelIndex &  index )
{
    if( noDrive )
        return;
    const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>( index.model() );
    if( model != 0 )
    {
        lastClick = QTime::currentTime ();
        QStandardItem* item = model->itemFromIndex( index );
        QString path( dirList->getRootDir() );
        if( path.at(path.size()-1)!='/')
        {
            path.append("/");
        }
        QString dirs( item->data(Qt::DisplayRole ).toString() );
        if(( dirs[0] == '.' )&&( dirs[1] == '.' )&&( dirs[2] == '\t' ))
        {
            QDir dir( path);
            if( dir.cdUp() )
            {
                path.clear();
                path.append( dir.canonicalPath () );
                currentDir.clear();
                currentDir.append( path  );
                dirList->setRootPath( currentDir );
                setPathEditText( currentDir );
                return;
            }
            else
            {
                return;
            }
        }
        path.append(dirs);
        QFileInfo inf( path ) ;
        //isAbsolute()
        //isBundle()
        if( inf.isDir() )
        {
            //mainW->startAnimation();
            currentFile.clear();
            //TODO check the size
            currentDir.clear();
            currentDir.append( path );
            dirList->setRootPath( currentDir );
            setPathEditText( currentDir );
            return;
        }
        if( inf.isExecutable() )
        {
            QProcess::startDetached( inf.absoluteFilePath() );
        }
        if( inf.isFile() )
        {
            QString url("file:///");
            url.append( inf.filePath() );
            //qDebug()<<url;
            QDesktopServices::openUrl( url );
        }
        //if( isFile() )
        //isHidden()
        //isReadable()
        //isRelative()
        //isRoot()
        //isSymLink()
        //isWritable()
        //setPathEditText( model->filePath(index) );
    }
}

QString FMPanel::selectedFile()
{
    return pathEdit->text();
}

QStringList FMPanel::selectedFiles()
{
    QStringList list = dirList->selectedFiles();
    QStringList res;
    QString fileName;
    QString full;
    foreach( fileName, list)
    {
        full.clear();
        full.append( currentDir );
        full.append("/");
        full.append( fileName );
        res.append( full );
    }
    return res;
}


QTime FMPanel::lastFocus()
{
    return lastClick;
}

QLineEdit* FMPanel::getPathEdit()
{
    return pathEdit;
}

void FMPanel::setEditMode( EditMode emode )
{
    if( noDrive )
        return;
    mode = emode;
    switch( mode )
    {
        case None:
        {
            return;
        }
        case Search:
        {
            //TODO generate dir names
            pathEdit->setText("*.*");
            pathEdit->setFocus();
            pathEdit->selectAll();
            break;
        }
        default:
            return;
    }
    return;
}

void FMPanel::editFinished()
{
#if defined(QEFEM_MAEMO_DEV)
    hidePathEdit();
#endif
    switch( mode )
    {
        case None:
        {
            QString dirName( pathEdit->text() );
            QFileInfo finfo( dirName );
            if( finfo.exists() && finfo.isDir() )
            {
                currentFile.clear();
                currentFile.append( dirName );
                currentDir.clear();
                currentDir.append( dirName );
                dirList->setRootPath( dirName );
            }
            else
            {
                setPathEditText( currentDir );
            }
            dirList->setFocus();
            return;
        }
        case Search:
        {
            mode = None;
            findTask* ftask = new findTask( currentDir,pathEdit->text() );
            findVector.append(QPair<findTask *,QPair<QString, bool> >( ftask, QPair<QString, bool>( pathEdit->text(), true)) );
            connect( ftask, SIGNAL( finished() ), this, SLOT( findTaskFinished() ));
            connect( ftask, SIGNAL( getSearchResult( const QStringList& ) ), this, SLOT( readFindResult( const QStringList& ) ));
            ftask->run();
            setPathEditText( currentDir );
            dirList->setFocus();
            //mainW->updateStatus();
            break;
        }
    }
    mode = None;
    return;
}

void FMPanel::readFindResult( const QStringList& result )
{
    foundList->addItems( result );
    QString tabText("Found(");
    tabText.append( QString().setNum( foundList->count()-1 ) );
    tabText.append(")");
    if(result.size() > 0)
    {
        Speech::instance()->stop();
        std::vector<std::string > names;
        for(int i=0; i<result.size(); i++)
        {
            names.push_back(std::string(result[i].toLocal8Bit().data()));
        }
        Speech::instance()->sayList(names, 1);
    }
#if !defined(Q_OS_LINUX)
    tab->setTabText( 3, tabText);
#else
#ifdef QEFEM_MAEMO_DEV
    tab->setTabText( 3, tabText);
#else
    tab->setTabText( 3, tabText);
#endif
#endif
    return;
}

void FMPanel::reload()
{
    //QDirModel* model = qobject_cast<QDirModel*>( dirList->model() );
    //if( model != NULL )
    //    model->refresh( model->index( currentDir ) );
    ////qDebug()<<"reload "<<left<<" "<<currentDir;
    //dirList->setRootPath(currentDir );
    //dirList->update();
}

void FMPanel::driveReload()
{
    ////qDebug()<<"driveReload";
#ifdef Q_WS_MAC
    QFileInfoList list = QDir("/Volumes/").entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );
#else
    QFileInfoList list = QDir::drives();
#endif
    if( list != drives )
    {
        //qDebug()<<"drives changed.";
        drives.clear();
        driveList->clear();
        for( int i=0; i<list.count(); i++ )
        {
            drives.append( list[i] );
#ifdef Q_WS_MAC
            QListWidgetItem* item = new QListWidgetItem( list[i].fileName(), driveList );
            item->setWhatsThis( list[i].filePath () );
            item->setToolTip( list[i].fileName() );
            driveList->addItem( item );
#else
            driveList->addItem( list[i].absolutePath() );
#endif
        }
    }
}


QString FMPanel::getCurrentDir()
{
    return currentDir;
}

void FMPanel::findTaskFinished( )
{
    for(int i=0; i < findVector.size(); i++ )
    {    
        if( !findVector[i].first->isRunning() )
        {
            delete findVector[i].first;
            findVector.remove(i);
            i--;
        }
    }
    //mainW->updateStatus();
}

QStringList FMPanel::getStatus()
{
    QStringList list;
    for(int i=0; i < findVector.size(); i++ )
    {
        if( !findVector[i].first->isFinished() )
        {
            qDebug()<<__FILE__<<__LINE__;
            QString text("Search for ");
            text.append( findVector[i].second.first );
            text.append(" is running.");
            list << text;
        }
    }
    return list;
}

QString FMPanel::curDir()
{
    return currentDir;
}

QString FMPanel::curFile()
{
    return currentFile;
}

void FMPanel::setDirListFocus()
{
    dirList->setFocus(Qt::ShortcutFocusReason);
    lastClick = QTime::currentTime();
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    tab->setCurrentIndex(0);
#else
    tab->setCurrentIndex(1);
#endif
}

void FMPanel::setDriveListFocus()
{
#if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
    dirList->setFocus(Qt::ShortcutFocusReason);
    lastClick = QTime::currentTime();
    tab->setCurrentIndex(0);
#endif
}

void FMPanel::setHistoryFocus()
{
    dirList->setFocus(Qt::ShortcutFocusReason);
    lastClick = QTime::currentTime();
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    tab->setCurrentIndex(1);
#else
    tab->setCurrentIndex(2);
#endif
}

void FMPanel::setBookmarkFocus()
{
    dirList->setFocus(Qt::ShortcutFocusReason);
    lastClick = QTime::currentTime();
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    tab->setCurrentIndex(2);
#else
    tab->setCurrentIndex(3);
#endif
}

void FMPanel::selectionChanged()
{
    ////qDebug()<<"selection changed.";
    dirClicked( dirList->currentIndex() );
}

void FMPanel::highlightMoved()
{
    ////qDebug()<<"HL moved.";
    dirClicked( dirList->currentIndex() );
}

void FMPanel::rowsChanged()
{
    /*if( driveJustLoaded )
    {
        driveJustLoaded = false;
        return;
    }
    if( dirList->hasFocus() )
    {
        dirList->selectionModel()->select(dirList->currentIndex(), QItemSelectionModel::Select);
    }
    else
    {
        dirClicked( dirList->currentIndex() );
    }*/
}

void FMPanel::setPathEditText(QString text)
{
#ifdef Q_WS_WIN
    text.replace( QString("/"), QString("\\"));
    pathEdit->setText( text );
#else
    pathEdit->setText( text );
#endif
}

void FMPanel::copy( const QStringList& files )
{
    emit copyFiles( files, currentDir, left );
}

void FMPanel::focusInEvent( QFocusEvent * /*event*/ )
{
    //qDebug()<<"focusInEvent";
    lastClick = QTime::currentTime ();
}

void FMPanel::rootChanged ( const QString & newPath )
{
    //qDebug()<<"root changed "<<newPath;

    mainW->stopAnimation();

#ifndef QEFEM_MAEMO_DEV
    hlist->addHistoryItem( newPath );
#endif
    currentDir.clear();
    currentDir.append( newPath );
    currentFile.clear();
    currentFile.append( newPath );

    setPathEditText( newPath );
}

void FMPanel::addBookmark( const QString& path )
{
    #ifdef Q_WS_WIN
    QString temp( path );
    temp.replace( QString("/"), QString("\\"));
    blist->addBookmark( temp );
    #else
    blist->addBookmark( path );
    #endif
}

#if defined(QEFEM_MAEMO_DEV)
void FMPanel::showPathEdit()
{
    pathEdit->setVisible( true );
}

void FMPanel::hidePathEdit()
{
    pathEdit->setVisible( false );
}

#endif

void FMPanel::back()
{
    hlist->back();
    QString topname = hlist->getTop();
    openByName(topname);
}

void FMPanel::forward()
{
    hlist->forward();
    QString pathname = hlist->getTop();
    openByName(pathname);
}

void FMPanel::addSearchAlpha(char c)
{
    if(pathEdit->text() == "*.*"){
        pathEdit->setText("");
    }
    if(c==1)
    {
        pathEdit->setText("");
        return;
    }
    if(c==0)
    {
        QString w = pathEdit->text();
        w.chop(1);
        pathEdit->setText(w);
        return;
    }
    if(c==2)
    {
        editFinished();
        return;
    }
    QString w = pathEdit->text() + QString(c);
    pathEdit->setText(w);
}

void FMPanel::startSearch()
{
    editFinished();
}

void FMPanel::setActiveTab(int ind)
{
    tab->setCurrentIndex(ind);
}
