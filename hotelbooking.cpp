#include "hotelbooking.h"

HotelBooking::HotelBooking(std::string type, std::string hotel, std::string town,
                           std::string id, double price, std::string fromDate, std::string toDate, std::string roomType)
    :Booking(type, id, price, fromDate, toDate), hotel(hotel), town(town), roomType(roomType)
{

}

std::string HotelBooking::getDetails(){

    std::string roomTypeFull;
    if(roomType == "EZ"){
        roomTypeFull = "Einzelzimmer";
    }else if(roomType == "DZ"){
        roomTypeFull = "Doppelzimmer";
    }else if(roomType == "AP"){
        roomTypeFull = "Appartment";
    }else if(roomType == "SU"){
        roomTypeFull = "Suite";
    }else{
        roomTypeFull = "keine Angabe";
    }
    std::string totalString = "ID: " + Booking::getId() + " Hotelreservierung in " + hotel + " in " + town + ".\nVom " + getFromDate() + " bis zum " + getToDate()
            + ".Preis: " + doubleToString(getPrice()) + " Euro. Wohnung Typ: " + roomTypeFull;
    return totalString;
}
