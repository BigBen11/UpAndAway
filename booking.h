#ifndef BOOKING_H
#define BOOKING_H
#include <string>
#include <sstream>

class Booking
{
public:
    Booking(int travelId, std::string type, std::string id, double price, std::string fromDate, std::string toDate, std::string predecessor1, std::string predecessor2);
    virtual ~Booking() = default;
    virtual std::string getDetails() = 0;
    std::string getId(){return id;};
    std::string getFromDate(){return fromDate;};
    std::string getToDate(){return toDate;};
    double getPrice(){return price;};
    std::string getType(){return type;};

    //Flight
    virtual std::string getfromDestination(){return "";};
    virtual std::string getToDestination(){return "";};
    virtual std::string getAirline(){return "";};
    virtual std::string getBookingClass(){return "";};

    //Hotel
    virtual std::string getHotel(){return "";};
    virtual std::string getTown(){return "";};
    virtual std::string getRoomType(){return "";};

    //RentalCar
    virtual std::string getPickupLocation(){return "";};
    virtual std::string getReturnLocation(){return "";};
    virtual std::string getCompany(){return "";};
    virtual std::string getVehicleClass(){return "";};

    int getTravelId() const;

    void setFromDate(const std::string &newFromDate);

    void setToDate(const std::string &newToDate);

    void setPrice(double newPrice);

    std::string getPredecessor1() const;

    std::string getPredecessor2() const;

private:
    std::string id;
    double price;
    std::string fromDate;
    std::string toDate;
    std::string type;
    int travelId;
    std::string predecessor1;
    std::string predecessor2;
};


#endif // BOOKING_H
