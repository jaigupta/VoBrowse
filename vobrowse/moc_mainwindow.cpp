/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Oct 18 13:43:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   11,   11,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      54,   11,   11,   11, 0x0a,
      68,   11,   11,   11, 0x0a,
      82,   11,   11,   11, 0x0a,
      96,   11,   11,   11, 0x0a,
     110,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     138,   11,   11,   11, 0x0a,
     152,   11,   11,   11, 0x0a,
     172,   11,   11,   11, 0x0a,
     192,   11,   11,   11, 0x0a,
     202,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0pathChanged()\0alt1Pressed()\0"
    "alt2Pressed()\0alt3Pressed()\0alt4Pressed()\0"
    "alt5Pressed()\0alt6Pressed()\0alt7Pressed()\0"
    "alt8Pressed()\0helpPressed()\0"
    "notifySaid(QString)\0openByName(QString)\0"
    "backDir()\0forwardDir()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->pathChanged(); break;
        case 1: _t->alt1Pressed(); break;
        case 2: _t->alt2Pressed(); break;
        case 3: _t->alt3Pressed(); break;
        case 4: _t->alt4Pressed(); break;
        case 5: _t->alt5Pressed(); break;
        case 6: _t->alt6Pressed(); break;
        case 7: _t->alt7Pressed(); break;
        case 8: _t->alt8Pressed(); break;
        case 9: _t->helpPressed(); break;
        case 10: _t->notifySaid((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->openByName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->backDir(); break;
        case 13: _t->forwardDir(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::pathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
