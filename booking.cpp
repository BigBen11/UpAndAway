#include "booking.h"

Booking::Booking(int travelId, std::string type, std::string id, double price, std::string fromDate, std::string toDate)
    :id(id), price(price), fromDate(fromDate), toDate(toDate), type(type), travelId(travelId)
{

}

int Booking::getTravelId() const
{
    return travelId;
}

void Booking::setFromDate(const std::string &newFromDate)
{
    fromDate = newFromDate;
}

void Booking::setToDate(const std::string &newToDate)
{
    toDate = newToDate;
}

void Booking::setPrice(double newPrice)
{
    price = newPrice;
}

std::string doubleToString(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

