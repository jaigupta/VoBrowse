#include "bookmarklistview.h"
#include <QStandardItemModel>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QDebug>

bookmarkListView::bookmarkListView(QWidget *parent) :
    QListView(parent)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(2);
    setModel( model );
}

void bookmarkListView::addBookmark( const QString& path )
{
    QStandardItemModel* mod = qobject_cast<QStandardItemModel*>( model() );
    if( mod != NULL )
    {
        QStandardItem *item = new QStandardItem( style()->standardIcon( QStyle::SP_DirIcon ), path );
        mod->appendRow( item );
    }
}
