#ifndef TRAVEL_H
#define TRAVEL_H

#include "booking.h"
#include <vector>
#include <memory>
#include "algorithmen.cpp"

class Travel
{
public:
    Travel(int id, int customerId);

    void addBooking(std::shared_ptr<Booking> booking);

    int getId(){return id;};

    int getCustomerId(){return customerId;};

    std::vector<std::shared_ptr<Booking>> getTravelBookings(){return travelBookings;};

    void setTravelBookings(std::vector<std::shared_ptr<Booking>> &newTravelBookings);

    std::shared_ptr<Booking> findBookingInTravel(std::string idBooking);

    int getBookingsNumber();

    bool checkRoundtrip();
    bool checkEnoughHotels();
    bool checkNoUselessHotels();
    bool checkNoUselessRentalCars();

    std::vector<std::shared_ptr<Booking>> topologicalSort(std::vector<std::shared_ptr<Booking>> &bookings);

private:
    int id;
    int customerId;
    std::vector<std::shared_ptr<Booking>> travelBookings;
    std::shared_ptr<Graph <std::shared_ptr<Booking>, 20>> graph = std::make_shared<Graph<std::shared_ptr<Booking>, 20>>();

};

#endif // TRAVEL_H
