#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QTest>
#include "travelagency.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

private:
    TravelAgency travelAgency;
private slots:
    void testReantalCarReservation();
    void testFlightBooking();
    void testHotelBooking();

};

#endif // TEST_H
