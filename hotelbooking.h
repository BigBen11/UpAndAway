#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include "booking.h"

class HotelBooking : public Booking
{
public:
    HotelBooking(int travelId, std::string type, std::string hotel, std::string town,
                 std::string id, double price, std::string fromDate, std::string toDate, std::string roomType,
                 std::string hotelLatitude, std::string hotelLongitude);

    std::string getDetails() override;

    std::string getHotel() override {return hotel;};
    std::string getTown() override {return town;};
    std::string getRoomType() override {return roomType;};

    void setHotel(const std::string &newHotel);
    void setTown(const std::string &newTown);
    void setRoomType(const std::string &newRoomType);

    std::string getHotelLatitude() const;

    std::string getHotelLongitude() const;

private:
    std::string hotel;
    std::string town;
    std::string roomType;

    std::string hotelLatitude;
    std::string hotelLongitude;
};

#endif // HOTELBOOKING_H
