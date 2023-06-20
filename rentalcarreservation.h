#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include "booking.h"

class RentalCarReservation : public Booking
{
public:
    RentalCarReservation(int travelId, std::string type, std::string pickupLocation, std::string returnLocation, std::string company,
                         std::string id, double price, std::string fromDate, std::string toDate, std::string vehicleClass,
                         std::string pickupLatitude, std::string pickupLongitude, std::string returnLatitude, std::string returnLongitude);

    std::string getDetails() override;

    std::string getPickupLocation() override {return pickupLocation;};
    std::string getReturnLocation() override {return returnLocation;};
    std::string getCompany() override {return company;};
    std::string getVehicleClass() override {return vehicleClass;};
    void setPickupLocation(const std::string &newPickupLocation);

    void setReturnLocation(const std::string &newReturnLocation);

    void setCompany(const std::string &newCompany);

    void setVehicleClass(const std::string &newVehicleClass);

    std::string getPickupLatitude() const;

    std::string getPickupLongitude() const;

    std::string getReturnLatitude() const;

    std::string getReturnLongitude() const;

private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;
    std::string vehicleClass;

    std::string pickupLatitude;
    std::string pickupLongitude;
    std::string returnLatitude;
    std::string returnLongitude;
};

#endif // RENTALCARRESERVATION_H
