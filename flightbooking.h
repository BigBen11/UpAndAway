#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H

#include "booking.h"

class FlightBooking : public Booking
{
public:
    FlightBooking(int travelId, std::string type, std::string fromDestination, std::string toDestination, std::string airline,
                  std::string id, double price, std::string fromDate, std::string toDate, std::string bookingClass);
    std::string getDetails() override;

    std::string getfromDestination() override{return fromDestination;};
    std::string getToDestination() override{return toDestination;};
    std::string getAirline() override{return airline;};
    std::string getBookingClass() override{return bookingClass;};
private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
    std::string bookingClass;
};

#endif // FLIGHTBOOKING_H
