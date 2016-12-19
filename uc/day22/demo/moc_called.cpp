/****************************************************************************
** Meta object code from reading C++ file 'called.h'
**
** Created: Fri Apr 29 01:44:02 2011
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "called.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'called.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Called[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Called[] = {
    "Called\0\0bizlog()\0"
};

const QMetaObject Called::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Called,
      qt_meta_data_Called, 0 }
};

const QMetaObject *Called::metaObject() const
{
    return &staticMetaObject;
}

void *Called::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Called))
        return static_cast<void*>(const_cast< Called*>(this));
    return QObject::qt_metacast(_clname);
}

int Called::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: bizlog(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
