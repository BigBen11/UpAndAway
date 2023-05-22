#include "travel.h"

Travel::Travel(int id, int customerId, std::vector<Booking*> travelBookings)
    :id(id), customerId(customerId), travelBookings(travelBookings)
{

}

void Travel::addBooking(Booking* booking){
    travelBookings.push_back(booking);
}
