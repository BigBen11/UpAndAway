#include "travel.h"

Travel::Travel(int id, int customerId)
    :id(id), customerId(customerId)
{

}

void Travel::addBooking(Booking* booking){
    travelBookings.push_back(booking);
}

void Travel::setTravelBookings(const std::vector<Booking *> &newTravelBookings)
{
    travelBookings = newTravelBookings;
}
