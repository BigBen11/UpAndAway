#include "test.h"


Test::Test(QObject *parent)
    : QObject{parent}
{
    travelAgency.readFile("C:/Users/User/Desktop/BookingsPraktikum4.json");
}

void Test::testReantalCarReservation(){
    int cnt = 0;

    for(auto booking: travelAgency.getBookings()){
        if(booking->getCompany() == "Europcar"){
            cnt++;
        }
    }

    QCOMPARE(cnt, 7);

}

void Test::testFlightBooking(){
    int cnt = 0;

    for(auto booking: travelAgency.getBookings()){
        if(booking->getAirline() == "Air France"){
            cnt++;
        }
    }

    QCOMPARE(cnt, 3);

}

void Test::testHotelBooking(){
    int cnt = 0;

    for(auto booking: travelAgency.getBookings()){
        if((booking->getRoomType() == "SU") || (booking->getRoomType() == "AP")){
            cnt++;
        }
    }

    QCOMPARE(cnt, 14);
}
