/****************************************************************************
** Meta object code from reading C++ file 'keyFrameInterpolator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../keyFrameInterpolator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyFrameInterpolator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qglviewer__KeyFrameInterpolator_t {
    const uint offsetsAndSize[56];
    char stringdata0[370];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_qglviewer__KeyFrameInterpolator_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_qglviewer__KeyFrameInterpolator_t qt_meta_stringdata_qglviewer__KeyFrameInterpolator = {
    {
QT_MOC_LITERAL(0, 31), // "qglviewer::KeyFrameInterpolator"
QT_MOC_LITERAL(32, 12), // "interpolated"
QT_MOC_LITERAL(45, 0), // ""
QT_MOC_LITERAL(46, 10), // "endReached"
QT_MOC_LITERAL(57, 11), // "addKeyFrame"
QT_MOC_LITERAL(69, 5), // "Frame"
QT_MOC_LITERAL(75, 5), // "frame"
QT_MOC_LITERAL(81, 4), // "time"
QT_MOC_LITERAL(86, 12), // "const Frame*"
QT_MOC_LITERAL(99, 10), // "deletePath"
QT_MOC_LITERAL(110, 8), // "setFrame"
QT_MOC_LITERAL(119, 6), // "Frame*"
QT_MOC_LITERAL(126, 20), // "setInterpolationTime"
QT_MOC_LITERAL(147, 21), // "setInterpolationSpeed"
QT_MOC_LITERAL(169, 5), // "speed"
QT_MOC_LITERAL(175, 22), // "setInterpolationPeriod"
QT_MOC_LITERAL(198, 6), // "period"
QT_MOC_LITERAL(205, 20), // "setLoopInterpolation"
QT_MOC_LITERAL(226, 4), // "loop"
QT_MOC_LITERAL(231, 13), // "setClosedPath"
QT_MOC_LITERAL(245, 6), // "closed"
QT_MOC_LITERAL(252, 18), // "startInterpolation"
QT_MOC_LITERAL(271, 17), // "stopInterpolation"
QT_MOC_LITERAL(289, 18), // "resetInterpolation"
QT_MOC_LITERAL(308, 19), // "toggleInterpolation"
QT_MOC_LITERAL(328, 17), // "interpolateAtTime"
QT_MOC_LITERAL(346, 6), // "update"
QT_MOC_LITERAL(353, 16) // "invalidateValues"

    },
    "qglviewer::KeyFrameInterpolator\0"
    "interpolated\0\0endReached\0addKeyFrame\0"
    "Frame\0frame\0time\0const Frame*\0deletePath\0"
    "setFrame\0Frame*\0setInterpolationTime\0"
    "setInterpolationSpeed\0speed\0"
    "setInterpolationPeriod\0period\0"
    "setLoopInterpolation\0loop\0setClosedPath\0"
    "closed\0startInterpolation\0stopInterpolation\0"
    "resetInterpolation\0toggleInterpolation\0"
    "interpolateAtTime\0update\0invalidateValues"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qglviewer__KeyFrameInterpolator[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x06,    1 /* Public */,
       3,    0,  153,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,  154,    2, 0x0a,    3 /* Public */,
       4,    2,  157,    2, 0x0a,    5 /* Public */,
       4,    1,  162,    2, 0x0a,    8 /* Public */,
       4,    2,  165,    2, 0x0a,   10 /* Public */,
       9,    0,  170,    2, 0x0a,   13 /* Public */,
      10,    1,  171,    2, 0x0a,   14 /* Public */,
      12,    1,  174,    2, 0x0a,   16 /* Public */,
      13,    1,  177,    2, 0x0a,   18 /* Public */,
      15,    1,  180,    2, 0x0a,   20 /* Public */,
      17,    1,  183,    2, 0x0a,   22 /* Public */,
      17,    0,  186,    2, 0x2a,   24 /* Public | MethodCloned */,
      19,    1,  187,    2, 0x0a,   25 /* Public */,
      19,    0,  190,    2, 0x2a,   27 /* Public | MethodCloned */,
      21,    1,  191,    2, 0x0a,   28 /* Public */,
      21,    0,  194,    2, 0x2a,   30 /* Public | MethodCloned */,
      22,    0,  195,    2, 0x0a,   31 /* Public */,
      23,    0,  196,    2, 0x0a,   32 /* Public */,
      24,    0,  197,    2, 0x0a,   33 /* Public */,
      25,    1,  198,    2, 0x0a,   34 /* Public */,
      26,    0,  201,    2, 0x08,   36 /* Private */,
      27,    0,  202,    2, 0x08,   37 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QReal,    6,    7,
    QMetaType::Void, 0x80000000 | 8,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QReal,    6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    6,
    QMetaType::Void, QMetaType::QReal,    7,
    QMetaType::Void, QMetaType::QReal,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void qglviewer::KeyFrameInterpolator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KeyFrameInterpolator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->interpolated(); break;
        case 1: _t->endReached(); break;
        case 2: _t->addKeyFrame((*reinterpret_cast< std::add_pointer_t<Frame>>(_a[1]))); break;
        case 3: _t->addKeyFrame((*reinterpret_cast< std::add_pointer_t<Frame>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 4: _t->addKeyFrame((*reinterpret_cast< std::add_pointer_t<const Frame*>>(_a[1]))); break;
        case 5: _t->addKeyFrame((*reinterpret_cast< std::add_pointer_t<const Frame*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qreal>>(_a[2]))); break;
        case 6: _t->deletePath(); break;
        case 7: _t->setFrame((*reinterpret_cast< std::add_pointer_t<Frame*>>(_a[1]))); break;
        case 8: _t->setInterpolationTime((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 9: _t->setInterpolationSpeed((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 10: _t->setInterpolationPeriod((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->setLoopInterpolation((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->setLoopInterpolation(); break;
        case 13: _t->setClosedPath((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->setClosedPath(); break;
        case 15: _t->startInterpolation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->startInterpolation(); break;
        case 17: _t->stopInterpolation(); break;
        case 18: _t->resetInterpolation(); break;
        case 19: _t->toggleInterpolation(); break;
        case 20: _t->interpolateAtTime((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 21: _t->update(); break;
        case 22: _t->invalidateValues(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Frame* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KeyFrameInterpolator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyFrameInterpolator::interpolated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KeyFrameInterpolator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyFrameInterpolator::endReached)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject qglviewer::KeyFrameInterpolator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_qglviewer__KeyFrameInterpolator.offsetsAndSize,
    qt_meta_data_qglviewer__KeyFrameInterpolator,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_qglviewer__KeyFrameInterpolator_t
, QtPrivate::TypeAndForceComplete<KeyFrameInterpolator, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Frame &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Frame &, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Frame * const, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Frame * const, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Frame * const, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *qglviewer::KeyFrameInterpolator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qglviewer::KeyFrameInterpolator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qglviewer__KeyFrameInterpolator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qglviewer::KeyFrameInterpolator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void qglviewer::KeyFrameInterpolator::interpolated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void qglviewer::KeyFrameInterpolator::endReached()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
