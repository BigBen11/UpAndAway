#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <vector>
#include "booking.h"
#include <iostream>
#include <fstream>
#include "C:\ProjectsQt\UpAndAway\upandaway\json.hpp"
#include <list>

#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "customer.h"
#include "airport.h"


class TravelAgency
{
public:
    TravelAgency();

    void readFile(const std::string& filePath);

    std::string getInfo();

    void addBooking(std::shared_ptr<Booking> pBooking);

    void addTravel(std::shared_ptr<Travel> travel);

    void addCustomer(std::shared_ptr<Customer> customer);

    void addAirport(std::shared_ptr<Airport> airport);


    std::vector<std::shared_ptr<Booking>> getBookings();


    std::shared_ptr<Booking> findBooking(std::string id);

    std::shared_ptr<Travel> findTravel(int id);

    std::shared_ptr<Customer> findCustomer(int id);


    ~TravelAgency();

    std::vector<std::shared_ptr<Airport>> getAllAirports() const;

    std::shared_ptr<Airport> findAirport(std::string iata_code);

    std::vector<std::shared_ptr<Customer> > getAllCustomers() const;

    std::vector<std::shared_ptr<Travel> > getAllTravels() const;

private:
    std::vector<std::shared_ptr<Booking>> allBookings;
    std::vector<std::shared_ptr<Customer>> allCustomers;
    std::vector<std::shared_ptr<Travel>> allTravels;

    std::vector<std::shared_ptr<Airport>> allAirports;
};

#endif // TRAVELAGENCY_H
