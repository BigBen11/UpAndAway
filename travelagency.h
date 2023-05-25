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
#include "customer.h"


class TravelAgency
{
public:
    TravelAgency();

    void readFile(const std::string& filePath);

    std::string getInfo();

    void addBooking(Booking* pBooking);

    void addTravel(Travel* travel);

    void addCustomer(Customer* customer);


    std::vector<Booking*> getBookings();


    Booking* findBooking(std::string id);

    Travel* findTravel(int id);

    Customer* findCustomer(int id);


    ~TravelAgency();

private:
    std::vector<Booking*> allBookings;
    std::vector<Customer*> allCustomers;
    std::vector<Travel*> allTravels;
};

#endif // TRAVELAGENCY_H
