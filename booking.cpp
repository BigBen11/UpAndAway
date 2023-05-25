#include "booking.h"

Booking::Booking(int travelId, std::string type, std::string id, double price, std::string fromDate, std::string toDate)
    :id(id), price(price), fromDate(fromDate), toDate(toDate), type(type), travelId(travelId)
{

}

int Booking::getTravelId() const
{
    return travelId;
}

std::string doubleToString(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

