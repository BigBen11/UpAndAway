#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation(int travelId, std::string type, std::string pickupLocation, std::string returnLocation, std::string company,
                                           std::string id, double price, std::string fromDate, std::string toDate, std::string vehicleClass,
                                           std::string pickupLatitude, std::string pickupLongitude, std::string returnLatitude, std::string returnLongitude)
    :Booking(travelId, type, id, price, fromDate, toDate), pickupLocation(pickupLocation), returnLocation(returnLocation),
    company(company), vehicleClass(vehicleClass),
    pickupLatitude(pickupLatitude), pickupLongitude(pickupLongitude), returnLatitude(returnLatitude), returnLongitude(returnLongitude)
{

}

 std::string RentalCarReservation::getDetails() {
    std::string totalString = "ID: " + Booking::getId() + " Mietwagenreservierung mit " + company + ". Abholung am " + getFromDate() + " in " + pickupLocation
                               + ".\nRueckgabe am " + getToDate() + " in " + returnLocation + ". Preis: " + std::to_string(getPrice()) + " Euro. Vehicle Class: " + vehicleClass;
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

 std::string RentalCarReservation::getPickupLatitude() const
 {
     return pickupLatitude;
 }

 std::string RentalCarReservation::getPickupLongitude() const
 {
     return pickupLongitude;
 }

 std::string RentalCarReservation::getReturnLatitude() const
 {
     return returnLatitude;
 }

 std::string RentalCarReservation::getReturnLongitude() const
 {
     return returnLongitude;
 }
