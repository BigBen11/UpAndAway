#ifndef TRAVEL_H
#define TRAVEL_H

#include "booking.h"
#include <vector>

class Travel
{
public:
    Travel(int id, int customerId, std::vector<Booking*> travelBookings);

    void addBooking(Booking* booking);

    int getId(){return id;};

    int getCustomerId(){return customerId;};

    std::vector<Booking*> getTravelBookings(){return travelBookings;};

private:
    int id;
    int customerId;
    std::vector<Booking*> travelBookings;
};

#endif // TRAVEL_H
