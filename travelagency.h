#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <vector>
#include "booking.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"



class TravelAgency
{
public:
    TravelAgency();

    void readFile(std::string filePath);

    std::string getInfo();

    void addBooking(Booking* pBooking);

    std::vector<Booking*> getBookings();

    Booking* getBooking(std::string id);

    ~TravelAgency();

private:
    std::vector<Booking*> bookings;
};

#endif // TRAVELAGENCY_H
