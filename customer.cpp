#include "customer.h"

Customer::Customer(int id, std::string name, std::vector<Travel*> travelList)
    :id(id), name(name), travelList(travelList)
{

}

void Customer::addTravel(Travel* travel){
    travelList.push_back(travel);
}
