/****************************************************************************
** Meta object code from reading C++ file 'jfqdlg.h'
**
** Created: Fri Apr 29 19:56:57 2011
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "jfqdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jfqdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QJfqDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QJfqDlg[] = {
    "QJfqDlg\0\0GetResult()\0"
};

const QMetaObject QJfqDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QJfqDlg,
      qt_meta_data_QJfqDlg, 0 }
};

const QMetaObject *QJfqDlg::metaObject() const
{
    return &staticMetaObject;
}

void *QJfqDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QJfqDlg))
        return static_cast<void*>(const_cast< QJfqDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int QJfqDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: GetResult(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
