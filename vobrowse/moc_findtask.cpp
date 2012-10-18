/****************************************************************************
** Meta object code from reading C++ file 'findtask.h'
**
** Created: Thu Oct 18 13:43:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "findtask.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findtask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_findTask[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    9,    9,    9, 0x08,
      75,   63,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_findTask[] = {
    "findTask\0\0result\0getSearchResult(QStringList)\0"
    "readFindResult()\0exit,status\0"
    "findTaskFinished(int,QProcess::ExitStatus)\0"
};

void findTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        findTask *_t = static_cast<findTask *>(_o);
        switch (_id) {
        case 0: _t->getSearchResult((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->readFindResult(); break;
        case 2: _t->findTaskFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData findTask::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject findTask::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_findTask,
      qt_meta_data_findTask, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &findTask::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *findTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *findTask::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_findTask))
        return static_cast<void*>(const_cast< findTask*>(this));
    return QThread::qt_metacast(_clname);
}

int findTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void findTask::getSearchResult(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
