/****************************************************************************
** Meta object code from reading C++ file 'fmlistview.h'
**
** Created: Thu Oct 18 13:43:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fmlistview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fmlistview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FMListView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      39,   33,   11,   11, 0x05,
      62,   11,   11,   11, 0x05,
      87,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,  101,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FMListView[] = {
    "FMListView\0\0keyUpOrDownPressed()\0files\0"
    "copyFiles(QStringList)\0rootPathChanged(QString)\0"
    "focusGained()\0path\0setRootPath(QString)\0"
};

void FMListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FMListView *_t = static_cast<FMListView *>(_o);
        switch (_id) {
        case 0: _t->keyUpOrDownPressed(); break;
        case 1: _t->copyFiles((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->rootPathChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->focusGained(); break;
        case 4: _t->setRootPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FMListView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FMListView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_FMListView,
      qt_meta_data_FMListView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FMListView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FMListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FMListView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FMListView))
        return static_cast<void*>(const_cast< FMListView*>(this));
    return QListView::qt_metacast(_clname);
}

int FMListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FMListView::keyUpOrDownPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FMListView::copyFiles(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FMListView::rootPathChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FMListView::focusGained()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
