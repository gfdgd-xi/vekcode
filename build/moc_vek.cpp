/****************************************************************************
** Meta object code from reading C++ file 'vek.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/vek.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vek.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vek_t {
    QByteArrayData data[18];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vek_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vek_t qt_meta_stringdata_vek = {
    {
QT_MOC_LITERAL(0, 0, 3), // "vek"
QT_MOC_LITERAL(1, 4, 9), // "startTray"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 8), // "exitTray"
QT_MOC_LITERAL(4, 24, 25), // "on_action_About_triggered"
QT_MOC_LITERAL(5, 50, 9), // "vekAddApp"
QT_MOC_LITERAL(6, 60, 9), // "vekRunApp"
QT_MOC_LITERAL(7, 70, 26), // "on_action_AddApp_triggered"
QT_MOC_LITERAL(8, 97, 24), // "on_action_Exit_triggered"
QT_MOC_LITERAL(9, 122, 31), // "on_action_WineInstall_triggered"
QT_MOC_LITERAL(10, 154, 30), // "on_action_EditSource_triggered"
QT_MOC_LITERAL(11, 185, 16), // "unInitWineOption"
QT_MOC_LITERAL(12, 202, 10), // "unVekAbout"
QT_MOC_LITERAL(13, 213, 10), // "installApp"
QT_MOC_LITERAL(14, 224, 12), // "unSourceEdit"
QT_MOC_LITERAL(15, 237, 10), // "setAppSize"
QT_MOC_LITERAL(16, 248, 8), // "vekStyle"
QT_MOC_LITERAL(17, 257, 11) // "vekLanguage"

    },
    "vek\0startTray\0\0exitTray\0"
    "on_action_About_triggered\0vekAddApp\0"
    "vekRunApp\0on_action_AddApp_triggered\0"
    "on_action_Exit_triggered\0"
    "on_action_WineInstall_triggered\0"
    "on_action_EditSource_triggered\0"
    "unInitWineOption\0unVekAbout\0installApp\0"
    "unSourceEdit\0setAppSize\0vekStyle\0"
    "vekLanguage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vek[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    1,   95,    2, 0x0a /* Public */,
       4,    0,   98,    2, 0x0a /* Public */,
       5,    0,   99,    2, 0x08 /* Private */,
       6,    0,  100,    2, 0x08 /* Private */,
       7,    0,  101,    2, 0x08 /* Private */,
       8,    0,  102,    2, 0x08 /* Private */,
       9,    0,  103,    2, 0x08 /* Private */,
      10,    0,  104,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vek::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vek *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startTray(); break;
        case 1: _t->exitTray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_action_About_triggered(); break;
        case 3: _t->vekAddApp(); break;
        case 4: _t->vekRunApp(); break;
        case 5: _t->on_action_AddApp_triggered(); break;
        case 6: _t->on_action_Exit_triggered(); break;
        case 7: _t->on_action_WineInstall_triggered(); break;
        case 8: _t->on_action_EditSource_triggered(); break;
        case 9: _t->unInitWineOption(); break;
        case 10: _t->unVekAbout(); break;
        case 11: _t->installApp(); break;
        case 12: _t->unSourceEdit(); break;
        case 13: _t->setAppSize(); break;
        case 14: _t->vekStyle(); break;
        case 15: _t->vekLanguage(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vek::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_vek.data,
    qt_meta_data_vek,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vek::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vek::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vek.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vek::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
