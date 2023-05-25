#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "travel.h"
#include <vector>


class Customer
{
public:
    Customer(int id, std::string name);

    void addTravel(Travel* travel);

    int getId(){return id;};

    std::vector<Travel*> getTravelList(){return travelList;};

    void setTravelList(const std::vector<Travel *> &newTravelList);

private:
    int id;
    std::string name;
    std::vector<Travel*> travelList;

};

#endif // CUSTOMER_H
