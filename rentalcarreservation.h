#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include "booking.h"

class RentalCarReservation : public Booking
{
public:
    RentalCarReservation(int travelId, std::string type, std::string pickupLocation, std::string returnLocation, std::string company,
                         std::string id, double price, std::string fromDate, std::string toDate, std::string vehicleClass);
    std::string getDetails() override;

    std::string getPickupLocation() override {return pickupLocation;};
    std::string getReturnLocation() override {return returnLocation;};
    std::string getCompany() override {return company;};
    std::string getVehicleClass() override {return vehicleClass;};
private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;
    std::string vehicleClass;
};

#endif // RENTALCARRESERVATION_H
