#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H

#include "booking.h"

class FlightBooking : public Booking
{
public:
    FlightBooking(int travelId, std::string type, std::string fromDestination, std::string toDestination, std::string airline,
                  std::string id, double price, std::string fromDate, std::string toDate, std::string bookingClass,
                  std::string fromDestLatitude, std::string fromDestLongitude, std::string toDestLatitude, std::string toDestLongitude);

    std::string getDetails() override;

    std::string getfromDestination() override{return fromDestination;};
    std::string getToDestination() override{return toDestination;};
    std::string getAirline() override{return airline;};
    std::string getBookingClass() override{return bookingClass;};
    void setFromDestination(const std::string &newFromDestination);

    void setToDestination(const std::string &newToDestination);

    void setAirline(const std::string &newAirline);

    void setBookingClass(const std::string &newBookingClass);

    std::string getFromDestLatitude() const;

    std::string getFromDestLongitude() const;

    std::string getToDestLatitude() const;

    std::string getToDestLongitude() const;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
    std::string bookingClass;

    std::string fromDestLatitude;
    std::string fromDestLongitude;
    std::string toDestLatitude;
    std::string toDestLongitude;
};

#endif // FLIGHTBOOKING_H
