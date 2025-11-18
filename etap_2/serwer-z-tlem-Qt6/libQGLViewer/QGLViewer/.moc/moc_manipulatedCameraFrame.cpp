/****************************************************************************
** Meta object code from reading C++ file 'manipulatedCameraFrame.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../manipulatedCameraFrame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manipulatedCameraFrame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qglviewer__ManipulatedCameraFrame_t {
    const uint offsetsAndSize[24];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_qglviewer__ManipulatedCameraFrame_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_qglviewer__ManipulatedCameraFrame_t qt_meta_stringdata_qglviewer__ManipulatedCameraFrame = {
    {
QT_MOC_LITERAL(0, 33), // "qglviewer::ManipulatedCameraF..."
QT_MOC_LITERAL(34, 11), // "setFlySpeed"
QT_MOC_LITERAL(46, 0), // ""
QT_MOC_LITERAL(47, 5), // "speed"
QT_MOC_LITERAL(53, 16), // "setSceneUpVector"
QT_MOC_LITERAL(70, 3), // "Vec"
QT_MOC_LITERAL(74, 2), // "up"
QT_MOC_LITERAL(77, 4), // "spin"
QT_MOC_LITERAL(82, 18), // "initFromDOMElement"
QT_MOC_LITERAL(101, 11), // "QDomElement"
QT_MOC_LITERAL(113, 7), // "element"
QT_MOC_LITERAL(121, 9) // "flyUpdate"

    },
    "qglviewer::ManipulatedCameraFrame\0"
    "setFlySpeed\0\0speed\0setSceneUpVector\0"
    "Vec\0up\0spin\0initFromDOMElement\0"
    "QDomElement\0element\0flyUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qglviewer__ManipulatedCameraFrame[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x0a,    1 /* Public */,
       4,    1,   47,    2, 0x0a,    3 /* Public */,
       7,    0,   50,    2, 0x09,    5 /* Protected */,
       8,    1,   51,    2, 0x0a,    6 /* Public */,
      11,    0,   54,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,

       0        // eod
};

void qglviewer::ManipulatedCameraFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManipulatedCameraFrame *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setFlySpeed((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 1: _t->setSceneUpVector((*reinterpret_cast< std::add_pointer_t<Vec>>(_a[1]))); break;
        case 2: _t->spin(); break;
        case 3: _t->initFromDOMElement((*reinterpret_cast< std::add_pointer_t<QDomElement>>(_a[1]))); break;
        case 4: _t->flyUpdate(); break;
        default: ;
        }
    }
}

const QMetaObject qglviewer::ManipulatedCameraFrame::staticMetaObject = { {
    QMetaObject::SuperData::link<ManipulatedFrame::staticMetaObject>(),
    qt_meta_stringdata_qglviewer__ManipulatedCameraFrame.offsetsAndSize,
    qt_meta_data_qglviewer__ManipulatedCameraFrame,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_qglviewer__ManipulatedCameraFrame_t
, QtPrivate::TypeAndForceComplete<ManipulatedCameraFrame, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Vec &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QDomElement &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *qglviewer::ManipulatedCameraFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qglviewer::ManipulatedCameraFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qglviewer__ManipulatedCameraFrame.stringdata0))
        return static_cast<void*>(this);
    return ManipulatedFrame::qt_metacast(_clname);
}

int qglviewer::ManipulatedCameraFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ManipulatedFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
