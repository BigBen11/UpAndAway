QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airport.cpp \
    booking.cpp \
    customer.cpp \
    errorwindow.cpp \
    flightbooking.cpp \
    hotelbooking.cpp \
    main.cpp \
    mainwindow.cpp \
    rentalcarreservation.cpp \
    test.cpp \
    travel.cpp \
    travelagency.cpp \
    travelagencyui.cpp \
    algorithmen.cpp

HEADERS += \
    airport.h \
    booking.h \
    customer.h \
    errorwindow.h \
    flightbooking.h \
    hotelbooking.h \
    mainwindow.h \
    rentalcarreservation.h \
    test.h \
    travel.h \
    travelagency.h \
    travelagencyui.h \
    graph.h

FORMS += \
    errorwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../Users/User/Desktop/bookingsPraktikum3.json \
    ../../../Users/User/Desktop/bookingsPraktikum4.json \
    ../../Users/User/Desktop/bookingsPraktikum2.json \
    bookingsPraktikum5.json \
    iatacodes.json
