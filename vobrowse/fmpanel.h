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

#ifndef FMPANEL_H
#define FMPANEL_H

#include "fmlistview.h"
#include "bookmarklistview.h"
#include "historylistview.h"
#include "drivelistview.h"
#include "findtask.h"
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTime>
#include <QFileInfo>
#include <QProcess>
#include <QShortcut>
#include <QFileSystemModel>
#include "utils.h"
#include "Speech.h"
#include <vector>
#include <string>

class MainWindow;

class FMPanel : public QWidget
{
Q_OBJECT
Q_ENUMS(EditMode)
public:
    FMPanel( MainWindow* aMainW, bool aLeft, QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~FMPanel();
    QStringList getStatus();
    void setDirListFocus();
    void setDriveListFocus();
    void setBookmarkFocus();
    void setHistoryFocus();
public:
public:
    //TODO: later multiply selection
    QString selectedFile();
    QStringList selectedFiles();
    QString getCurrentDir();
    QTime lastFocus();
    QLineEdit* getPathEdit();
    void setEditMode( EditMode emode );
    QString curDir();
    QString curFile();
    QStringList getFileList();
#if defined(QEFEM_MAEMO_DEV)
    void showPathEdit();
    void hidePathEdit();
#endif
public slots:
#if defined(QEFEM_MAEMO_DEV) || defined(Q_OS_LINUX)
    void openSelected();
#endif
    void back();
    void forward();
    void reload();
    void driveReload();
    void findTaskFinished( );
    void selectionChanged();
    void rowsChanged();
    void addBookmark( const QString& path );
    void copy( const QStringList& files );
    void rootChanged( const QString & newPath );
    void driveOpened( const QString&);
    void readFindResult( const QStringList& result );
    void openByName(QString &fileName);
    void addSearchAlpha(char c);
    void startSearch();
    void setActiveTab(int);
signals:
    void copyFiles( const QStringList& files, const QString& dest, bool left );
private slots:
    void listClicked( const QModelIndex &index );
    void foundListClicked( QListWidgetItem *item );
    void driveClicked( const QModelIndex &index);
    void dirClicked( const QModelIndex &  index );
    void dirDoubleClicked( const QModelIndex &  index );
    void editFinished();
    void highlightMoved();
    void listGotFocus();
private:
    void setPathEditText(const QString text);
    void focusInEvent ( QFocusEvent * event );
private:
    QListWidget *driveList;
    FMListView *dirList;
    bookmarkListView *blist;
    historyListView *hlist;
    QListWidget *foundList;
#if !defined(QEFEM_MAEMO_DEV) && !defined(Q_OS_LINUX)
    driveListView *dlist;
#endif
    QHBoxLayout *listLayout;
    QVBoxLayout *wholeLayout;
    QVBoxLayout *leftLayout;
    QLineEdit* pathEdit;
    QString currentDir;
    QString currentFile;
    QTime lastClick;
    EditMode mode;
    bool noDrive;
    QFileInfoList drives;
    QVector<QPair<findTask*,QPair<QString, bool > > > findVector;//find process,path,left or right panel
    MainWindow* mainW;
    bool left;
    bool driveJustLoaded;
    QTabWidget* tab;
};

#endif // FMPANEL_H
