#include "historylistview.h"
#include <QStandardItemModel>
#include <QDir>
#include <QTimer>
using namespace std;

historyListView::historyListView( bool left, QWidget *parent) :
    QListView(parent), mleft(left)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(1);
    setModel( model );
}

historyListView::~historyListView()
{
}

void historyListView::addHistoryItem(const QString &path)
{
#ifdef Q_WS_WIN
    QString temp( path );
    temp.replace( QString("/"), QString("\\"));
#endif
    QStandardItemModel* mod = qobject_cast<QStandardItemModel*>( model() );
    if( mod != NULL )
    {
#ifdef Q_WS_WIN
        QStandardItem *item = new QStandardItem( style()->standardIcon( QStyle::SP_DirIcon ), temp );
#else
        QStandardItem *item = new QStandardItem( style()->standardIcon( QStyle::SP_DirIcon ), path );
#endif
        mod->insertRow( 0, item);
        if( mod->rowCount() > 128 )
        {
            mod->removeRow( 128 );
        }
    }
}

QString historyListView::getTop()
{
    QString path = "";
    QStandardItemModel* mod = qobject_cast<QStandardItemModel*>( model() );
    if( mod != NULL && mod->rowCount() > 0)
    {
        path = mod->item(0)->text();
        mod->removeRow(0);
    }
    return path;
}

void historyListView::back()
{
    QString path = "";
    QStandardItemModel* mod = qobject_cast<QStandardItemModel*>( model() );
    if(mod->rowCount() == 0)
        return;
    if( mod != NULL )
    {
        path = mod->item(0)->text();
        mod->removeRow(0);
    }
    this->forwardStack.push(path);
}

void historyListView::forward()
{
    if(forwardStack.size() <= 0)
        return;
    QString path = forwardStack.top();
    forwardStack.pop();
    QStandardItemModel* mod = qobject_cast<QStandardItemModel*>( model() );
    if( mod != NULL )
    {
        QStandardItem *item = new QStandardItem( style()->standardIcon( QStyle::SP_DirIcon ), path );
        mod->insertRow( 0, item);
        if( mod->rowCount() > 128 )
        {
            mod->removeRow( 128 );
        }
    }
}