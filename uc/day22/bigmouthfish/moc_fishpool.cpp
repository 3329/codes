/****************************************************************************
** Meta object code from reading C++ file 'fishpool.h'
**
** Created: Mon May 31 17:01:00 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fishpool.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fishpool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FishPool[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,
      29,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FishPool[] = {
    "FishPool\0\0dir\0changeDir(int)\0move()\0"
    "openmouth()\0"
};

const QMetaObject FishPool::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FishPool,
      qt_meta_data_FishPool, 0 }
};

const QMetaObject *FishPool::metaObject() const
{
    return &staticMetaObject;
}

void *FishPool::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FishPool))
        return static_cast<void*>(const_cast< FishPool*>(this));
    return QWidget::qt_metacast(_clname);
}

int FishPool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeDir((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: move(); break;
        case 2: openmouth(); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FishPool::changeDir(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FishPool::move()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
