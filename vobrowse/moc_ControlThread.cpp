/****************************************************************************
** Meta object code from reading C++ file 'ControlThread.h'
**
** Created: Thu Oct 18 13:43:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ControlThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      33,   14,   14,   14, 0x05,
      40,   14,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      70,   14,   14,   14, 0x05,
      83,   14,   14,   14, 0x05,
      93,   14,   14,   14, 0x05,
     112,   14,   14,   14, 0x05,
     135,   14,   14,   14, 0x05,
     153,   14,   14,   14, 0x05,
     174,   14,   14,   14, 0x05,
     195,   14,   14,   14, 0x05,
     217,   14,   14,   14, 0x05,
     239,   14,   14,   14, 0x05,
     257,   14,   14,   14, 0x05,
     277,   14,   14,   14, 0x05,
     292,   14,   14,   14, 0x05,
     313,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     335,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ControlThread[] = {
    "ControlThread\0\0openFile(QString)\0"
    "back()\0forward()\0notifySaid(QString)\0"
    "forwardDir()\0backDir()\0searchSpoken(bool)\0"
    "spokeSearchAlpha(char)\0setActiveTab(int)\0"
    "linuxSearch(QString)\0openNotepad(QString)\0"
    "notepadIncreaseFont()\0notepadDecreaseFont()\0"
    "notepadScrollUp()\0notepadScrollDown()\0"
    "notepadClose()\0changeDrive(QString)\0"
    "bookmarkthis(QString)\0pathChanged()\0"
};

void ControlThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControlThread *_t = static_cast<ControlThread *>(_o);
        switch (_id) {
        case 0: _t->openFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->back(); break;
        case 2: _t->forward(); break;
        case 3: _t->notifySaid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->forwardDir(); break;
        case 5: _t->backDir(); break;
        case 6: _t->searchSpoken((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->spokeSearchAlpha((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 8: _t->setActiveTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->linuxSearch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->openNotepad((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->notepadIncreaseFont(); break;
        case 12: _t->notepadDecreaseFont(); break;
        case 13: _t->notepadScrollUp(); break;
        case 14: _t->notepadScrollDown(); break;
        case 15: _t->notepadClose(); break;
        case 16: _t->changeDrive((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->bookmarkthis((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->pathChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ControlThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ControlThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ControlThread,
      qt_meta_data_ControlThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlThread))
        return static_cast<void*>(const_cast< ControlThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ControlThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void ControlThread::openFile(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlThread::back()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ControlThread::forward()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ControlThread::notifySaid(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControlThread::forwardDir()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ControlThread::backDir()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ControlThread::searchSpoken(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ControlThread::spokeSearchAlpha(char _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ControlThread::setActiveTab(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ControlThread::linuxSearch(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ControlThread::openNotepad(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ControlThread::notepadIncreaseFont()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void ControlThread::notepadDecreaseFont()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void ControlThread::notepadScrollUp()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void ControlThread::notepadScrollDown()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void ControlThread::notepadClose()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void ControlThread::changeDrive(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ControlThread::bookmarkthis(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_END_MOC_NAMESPACE
