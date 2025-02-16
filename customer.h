#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "travel.h"
#include <vector>


class Customer
{
public:
    Customer(int id, std::string name);

    void addTravel(std::shared_ptr<Travel> travel);

    int getId(){return id;};

    std::vector<std::shared_ptr<Travel>> getTravelList(){return travelList;};

    void setTravelList(const std::vector<std::shared_ptr<Travel>> &newTravelList);

    std::string getName() const;

    void setTotalBookingsPreis(double newTotalBookingsPreis);

    double getTotalBookingsPreis() const;

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<Travel>> travelList;
    double totalBookingsPreis = 0;

};

#endif // CUSTOMER_H
