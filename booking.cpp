#include "booking.h"

Booking::Booking(std::string type, std::string id, double price, std::string fromDate, std::string toDate)
    :id(id), price(price), fromDate(fromDate), toDate(toDate), type(type)
{

}

std::string doubleToString(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

