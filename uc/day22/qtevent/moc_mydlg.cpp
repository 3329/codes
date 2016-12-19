/****************************************************************************
** Meta object code from reading C++ file 'mydlg.h'
**
** Created: Fri Apr 29 23:51:19 2011
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mydlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mydlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyDlg[] = {
    "MyDlg\0\0showM()\0"
};

const QMetaObject MyDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyDlg,
      qt_meta_data_MyDlg, 0 }
};

const QMetaObject *MyDlg::metaObject() const
{
    return &staticMetaObject;
}

void *MyDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDlg))
        return static_cast<void*>(const_cast< MyDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showM(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
