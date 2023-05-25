#include "customer.h"

Customer::Customer(int id, std::string name)
    :id(id), name(name)
{

}

void Customer::addTravel(Travel* travel){
    travelList.push_back(travel);
}

void Customer::setTravelList(const std::vector<Travel *> &newTravelList)
{
    travelList = newTravelList;
}
