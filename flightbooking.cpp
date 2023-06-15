#include "flightbooking.h"

FlightBooking::FlightBooking(int travelId, std::string type, std::string fromDestination, std::string toDestination, std::string airline,
                             std::string id, double price, std::string fromDate, std::string toDate, std::string bookingClass,
                             std::string fromDestLatitude, std::string fromDestLongitude, std::string toDestLatitude, std::string toDestLongitude)
    :Booking(travelId, type, id, price, fromDate, toDate), fromDestination(fromDestination), toDestination(toDestination),
    airline(airline), bookingClass(bookingClass), fromDestLatitude(fromDestLatitude), fromDestLongitude(fromDestLongitude),
    toDestLatitude(toDestLatitude),  toDestLongitude(toDestLongitude)
{

}

std::string FlightBooking::getDetails() {

    std::string bookingClassFull;
    if(bookingClass == "Y"){
        bookingClassFull = "Economy";
    }else if(bookingClass == "W"){
        bookingClassFull = "Premium Economy";
    }else if(bookingClass == "J"){
        bookingClassFull = "Business";
    }else if(bookingClass == "F"){
        bookingClassFull = "First";
    }else{
        bookingClassFull = "keine Angabe";
    }
    std::string totalString = "ID: " + Booking::getId() + " Flugbuchung von " + fromDestination + " nach " + toDestination + ".\nMit " + airline +
                              " am " + getFromDate() + ". Preis: " + std::to_string(getPrice()) + " Euro. Klasse: " + bookingClassFull;
    return totalString;
}

void FlightBooking::setFromDestination(const std::string &newFromDestination)
{
    fromDestination = newFromDestination;
}

void FlightBooking::setToDestination(const std::string &newToDestination)
{
    toDestination = newToDestination;
}

void FlightBooking::setAirline(const std::string &newAirline)
{
    airline = newAirline;
}

void FlightBooking::setBookingClass(const std::string &newBookingClass)
{
    bookingClass = newBookingClass;
}

