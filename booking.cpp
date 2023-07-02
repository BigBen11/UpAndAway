#include "booking.h"

Booking::Booking(int travelId, std::string type, std::string id, double price, std::string fromDate, std::string toDate, std::string predecessor1, std::string predecessor2)
    :id(id), price(price), fromDate(fromDate), toDate(toDate), type(type), travelId(travelId), predecessor1(predecessor1), predecessor2(predecessor2)
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

std::string Booking::getPredecessor1() const
{
    return predecessor1;
}

std::string Booking::getPredecessor2() const
{
    return predecessor2;
}

