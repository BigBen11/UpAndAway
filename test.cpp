#include "test.h"
#include "travelagency.h"

Test::Test(QObject *parent)
    : QObject{parent}
{

}

void Test::test(){
    TravelAgency travelAgency;
    travelAgency.readFile("C:/Users/User/Desktop/BookingsPraktikum4.json");

    int cnt = 0;

    for(auto booking: travelAgency.getBookings()){
        if(booking->getCompany() == "Europcar"){
            cnt++;
        }
    }

    QCOMPARE(cnt, 7);

}
