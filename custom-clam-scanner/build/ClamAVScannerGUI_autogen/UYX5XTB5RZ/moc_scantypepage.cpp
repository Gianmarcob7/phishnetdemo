/****************************************************************************
** Meta object code from reading C++ file 'scantypepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ui/scantypepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scantypepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanTypePage_t {
    QByteArrayData data[17];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanTypePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanTypePage_t qt_meta_stringdata_ScanTypePage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ScanTypePage"
QT_MOC_LITERAL(1, 13, 17), // "backButtonClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "startScan"
QT_MOC_LITERAL(4, 42, 19), // "onBackButtonClicked"
QT_MOC_LITERAL(5, 62, 17), // "onScanTypeChanged"
QT_MOC_LITERAL(6, 80, 5), // "index"
QT_MOC_LITERAL(7, 86, 21), // "onBrowseButtonClicked"
QT_MOC_LITERAL(8, 108, 25), // "onCustomScanButtonClicked"
QT_MOC_LITERAL(9, 134, 14), // "startQuickScan"
QT_MOC_LITERAL(10, 149, 15), // "startSystemScan"
QT_MOC_LITERAL(11, 165, 15), // "startCustomScan"
QT_MOC_LITERAL(12, 181, 18), // "handleScanComplete"
QT_MOC_LITERAL(13, 200, 12), // "filesScanned"
QT_MOC_LITERAL(14, 213, 12), // "threatsFound"
QT_MOC_LITERAL(15, 226, 18), // "updateScanProgress"
QT_MOC_LITERAL(16, 245, 19) // "checkScheduledScans"

    },
    "ScanTypePage\0backButtonClicked\0\0"
    "startScan\0onBackButtonClicked\0"
    "onScanTypeChanged\0index\0onBrowseButtonClicked\0"
    "onCustomScanButtonClicked\0startQuickScan\0"
    "startSystemScan\0startCustomScan\0"
    "handleScanComplete\0filesScanned\0"
    "threatsFound\0updateScanProgress\0"
    "checkScheduledScans"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanTypePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   76,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    2,   85,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void ScanTypePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanTypePage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backButtonClicked(); break;
        case 1: _t->startScan(); break;
        case 2: _t->onBackButtonClicked(); break;
        case 3: _t->onScanTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onBrowseButtonClicked(); break;
        case 5: _t->onCustomScanButtonClicked(); break;
        case 6: _t->startQuickScan(); break;
        case 7: _t->startSystemScan(); break;
        case 8: _t->startCustomScan(); break;
        case 9: _t->handleScanComplete((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->updateScanProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->checkScheduledScans(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanTypePage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanTypePage::backButtonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScanTypePage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanTypePage::startScan)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanTypePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ScanTypePage.data,
    qt_meta_data_ScanTypePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanTypePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanTypePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanTypePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ScanTypePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ScanTypePage::backButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ScanTypePage::startScan()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
