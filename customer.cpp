#include "customer.h"

Customer::Customer(int id, std::string name)
    :id(id), name(name)
{

}

void Customer::addTravel(std::shared_ptr<Travel> travel){
    travelList.push_back(travel);
}

void Customer::setTravelList(const std::vector<std::shared_ptr<Travel>> &newTravelList)
{
    travelList = newTravelList;
}

std::string Customer::getName() const
{
    return name;
}
