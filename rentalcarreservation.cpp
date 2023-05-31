#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation(int travelId, std::string type, std::string pickupLocation, std::string returnLocation, std::string company,
                                           std::string id, double price, std::string fromDate, std::string toDate, std::string vehicleClass)
    :Booking(travelId, type, id, price, fromDate, toDate), pickupLocation(pickupLocation), returnLocation(returnLocation), company(company), vehicleClass(vehicleClass)
{

}

 std::string RentalCarReservation::getDetails() {
    std::string totalString = "ID: " + Booking::getId() + " Mietwagenreservierung mit " + company + ". Abholung am " + getFromDate() + " in " + pickupLocation
            + ".\nRueckgabe am " + getToDate() + " in " + returnLocation + ". Preis: " + doubleToString(getPrice()) + " Euro. Vehicle Class: " + vehicleClass;
     return totalString;
 }

 void RentalCarReservation::setPickupLocation(const std::string &newPickupLocation)
 {
     pickupLocation = newPickupLocation;
 }

 void RentalCarReservation::setReturnLocation(const std::string &newReturnLocation)
 {
     returnLocation = newReturnLocation;
 }

 void RentalCarReservation::setCompany(const std::string &newCompany)
 {
     company = newCompany;
 }

 void RentalCarReservation::setVehicleClass(const std::string &newVehicleClass)
 {
     vehicleClass = newVehicleClass;
 }
