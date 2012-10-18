/****************************************************************************
** Meta object code from reading C++ file 'fmpanel.h'
**
** Created: Thu Oct 18 13:43:29 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fmpanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fmpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FMPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,    8,    8,    8, 0x0a,
      68,    8,    8,    8, 0x0a,
      78,    8,    8,    8, 0x0a,
      87,    8,    8,    8, 0x0a,
     101,    8,    8,    8, 0x0a,
     120,    8,    8,    8, 0x0a,
     139,    8,    8,    8, 0x0a,
     158,  153,    8,    8, 0x0a,
     185,  179,    8,    8, 0x0a,
     211,  203,    8,    8, 0x0a,
     232,    8,    8,    8, 0x0a,
     260,  253,    8,    8, 0x0a,
     297,  288,    8,    8, 0x0a,
     320,  318,    8,    8, 0x0a,
     341,    8,    8,    8, 0x0a,
     355,    8,    8,    8, 0x0a,
     379,  373,    8,    8, 0x08,
     409,  404,    8,    8, 0x08,
     444,  373,    8,    8, 0x08,
     470,  373,    8,    8, 0x08,
     494,  373,    8,    8, 0x08,
     524,    8,    8,    8, 0x08,
     539,    8,    8,    8, 0x08,
     556,    8,    8,    8, 0x08,

 // enums: name, flags, count, data

 // enum data: key, value

       0        // eod
};

static const char qt_meta_stringdata_FMPanel[] = {
    "FMPanel\0\0files,dest,left\0"
    "copyFiles(QStringList,QString,bool)\0"
    "back()\0forward()\0reload()\0driveReload()\0"
    "findTaskFinished()\0selectionChanged()\0"
    "rowsChanged()\0path\0addBookmark(QString)\0"
    "files\0copy(QStringList)\0newPath\0"
    "rootChanged(QString)\0driveOpened(QString)\0"
    "result\0readFindResult(QStringList)\0"
    "fileName\0openByName(QString&)\0c\0"
    "addSearchAlpha(char)\0startSearch()\0"
    "setActiveTab(int)\0index\0"
    "listClicked(QModelIndex)\0item\0"
    "foundListClicked(QListWidgetItem*)\0"
    "driveClicked(QModelIndex)\0"
    "dirClicked(QModelIndex)\0"
    "dirDoubleClicked(QModelIndex)\0"
    "editFinished()\0highlightMoved()\0"
    "listGotFocus()\0"
};

void FMPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FMPanel *_t = static_cast<FMPanel *>(_o);
        switch (_id) {
        case 0: _t->copyFiles((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->back(); break;
        case 2: _t->forward(); break;
        case 3: _t->reload(); break;
        case 4: _t->driveReload(); break;
        case 5: _t->findTaskFinished(); break;
        case 6: _t->selectionChanged(); break;
        case 7: _t->rowsChanged(); break;
        case 8: _t->addBookmark((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->copy((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 10: _t->rootChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->driveOpened((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->readFindResult((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 13: _t->openByName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->addSearchAlpha((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 15: _t->startSearch(); break;
        case 16: _t->setActiveTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->listClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 18: _t->foundListClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 19: _t->driveClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 20: _t->dirClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 21: _t->dirDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 22: _t->editFinished(); break;
        case 23: _t->highlightMoved(); break;
        case 24: _t->listGotFocus(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FMPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FMPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FMPanel,
      qt_meta_data_FMPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FMPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FMPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FMPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FMPanel))
        return static_cast<void*>(const_cast< FMPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int FMPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void FMPanel::copyFiles(const QStringList & _t1, const QString & _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
