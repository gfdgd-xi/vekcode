/****************************************************************************
** Meta object code from reading C++ file 'vekAppPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/view/aview/vekAppPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vekAppPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vekAppPanel_t {
    QByteArrayData data[13];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vekAppPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vekAppPanel_t qt_meta_stringdata_vekAppPanel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "vekAppPanel"
QT_MOC_LITERAL(1, 12, 17), // "toObjAutoArgs_ptr"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "addAppSlot"
QT_MOC_LITERAL(4, 42, 12), // "addGroupSlot"
QT_MOC_LITERAL(5, 55, 13), // "BaseDockData*"
QT_MOC_LITERAL(6, 69, 8), // "dcokData"
QT_MOC_LITERAL(7, 78, 12), // "addAppObject"
QT_MOC_LITERAL(8, 91, 12), // "BaseAppData*"
QT_MOC_LITERAL(9, 104, 7), // "appData"
QT_MOC_LITERAL(10, 112, 8), // "upTabIco"
QT_MOC_LITERAL(11, 121, 12), // "objectRunApp"
QT_MOC_LITERAL(12, 134, 13) // "objAppInstall"

    },
    "vekAppPanel\0toObjAutoArgs_ptr\0\0"
    "addAppSlot\0addGroupSlot\0BaseDockData*\0"
    "dcokData\0addAppObject\0BaseAppData*\0"
    "appData\0upTabIco\0objectRunApp\0"
    "objAppInstall"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vekAppPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    1,   51,    2, 0x0a /* Public */,
       7,    2,   54,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,
      11,    0,   60,    2, 0x0a /* Public */,
      12,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 8,    6,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vekAppPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vekAppPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toObjAutoArgs_ptr(); break;
        case 1: _t->addAppSlot(); break;
        case 2: _t->addGroupSlot((*reinterpret_cast< BaseDockData*(*)>(_a[1]))); break;
        case 3: _t->addAppObject((*reinterpret_cast< BaseDockData*(*)>(_a[1])),(*reinterpret_cast< BaseAppData*(*)>(_a[2]))); break;
        case 4: _t->upTabIco(); break;
        case 5: _t->objectRunApp(); break;
        case 6: _t->objAppInstall(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vekAppPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vekAppPanel::toObjAutoArgs_ptr)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vekAppPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_vekAppPanel.data,
    qt_meta_data_vekAppPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vekAppPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vekAppPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vekAppPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vekAppPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void vekAppPanel::toObjAutoArgs_ptr()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
