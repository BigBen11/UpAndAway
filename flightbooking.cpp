#include "flightbooking.h"

FlightBooking::FlightBooking(std::string type, std::string fromDestination, std::string toDestination, std::string airline,
                             std::string id, double price, std::string fromDate, std::string toDate, std::string bookingClass)
    :Booking(type, id, price, fromDate, toDate), fromDestination(fromDestination), toDestination(toDestination), airline(airline), bookingClass(bookingClass)
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
            " am " + getFromDate() + ". Preis: " + doubleToString(getPrice()) + " Euro. Klasse: " + bookingClassFull;
    return totalString;
}

