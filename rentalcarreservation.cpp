#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation(std::string type, std::string pickupLocation, std::string returnLocation, std::string company,
                                           std::string id, double price, std::string fromDate, std::string toDate, std::string vehicleClass)
    :Booking(type, id, price, fromDate, toDate), pickupLocation(pickupLocation), returnLocation(returnLocation), company(company), vehicleClass(vehicleClass)
{

}

 std::string RentalCarReservation::getDetails() {
    std::string totalString = "ID: " + Booking::getId() + " Mietwagenreservierung mit " + company + ". Abholung am " + getFromDate() + " in " + pickupLocation
            + ".\nRueckgabe am " + getToDate() + " in " + returnLocation + ". Preis: " + doubleToString(getPrice()) + " Euro. Vehicle Class: " + vehicleClass;
    return totalString;
}
