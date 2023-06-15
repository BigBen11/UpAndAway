#ifndef TRAVEL_H
#define TRAVEL_H

#include "booking.h"
#include <vector>
#include <memory>

class Travel
{
public:
    Travel(int id, int customerId);

    void addBooking(std::shared_ptr<Booking> booking);

    int getId(){return id;};

    int getCustomerId(){return customerId;};

    std::vector<std::shared_ptr<Booking>> getTravelBookings(){return travelBookings;};

    void setTravelBookings(const std::vector<std::shared_ptr<Booking>> &newTravelBookings);

    std::shared_ptr<Booking> findBookingInTravel(std::string idBooking);

private:
    int id;
    int customerId;
    std::vector<std::shared_ptr<Booking>> travelBookings;
};

#endif // TRAVEL_H
