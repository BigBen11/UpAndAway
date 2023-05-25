#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include "booking.h"

class HotelBooking : public Booking
{
public:
    HotelBooking(int travelId, std::string type, std::string hotel, std::string town,
                 std::string id, double price, std::string fromDate, std::string toDate, std::string roomType);
    std::string getDetails() override;

    std::string getHotel() override {return hotel;};
    std::string getTown() override {return town;};
    std::string getRoomType() override {return roomType;};
private:
    std::string hotel;
    std::string town;
    std::string roomType;
};

#endif // HOTELBOOKING_H
