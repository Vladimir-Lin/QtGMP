NAME         = QtGMP
TARGET       = $${NAME}
QT           = core
QT          -= gui
QT          -= script

load(qt_module)

win32 {
INCLUDEPATH += $${PWD}/../../include/$${NAME}/mpir
INCLUDEPATH += $${PWD}/../../include/$${NAME}/mpfr
} else {
INCLUDEPATH += $${PWD}/../../include/$${NAME}/gmp
INCLUDEPATH += $${PWD}/../../include/$${NAME}/mpfr
}
INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtgmp.h

# Multiple Precision Integers, Floating-point and Rationals Supports

SOURCES += $${PWD}/vrandom.cpp
SOURCES += $${PWD}/vlong.cpp
SOURCES += $${PWD}/vdouble.cpp
SOURCES += $${PWD}/vrational.cpp
SOURCES += $${PWD}/vprecision.cpp

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)

win32 {

CONFIG(release,debug|release) {
  LIBS      += -lmpir
  LIBS      += -lmpfr
  LIBS      += -lmpirxx
} else {
  LIBS      += -lmpird
  LIBS      += -lmpfrd
  LIBS      += -lmpirxxd
}

} else {

CONFIG(release,debug|release) {
  LIBS      += -lgmp
  LIBS      += -lmpfr
} else {
  LIBS      += -lgmpd
  LIBS      += -lmpfrd
}

}
