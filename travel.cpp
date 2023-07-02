#include "travel.h"
#include <algorithm>
#include <array>

Travel::Travel(int id, int customerId)
    :id(id), customerId(customerId)
{

}

void Travel::addBooking(std::shared_ptr<Booking> booking){
    travelBookings.push_back(booking);
}

std::shared_ptr<Booking> Travel::findBookingInTravel(std::string idBooking)
{
    for(auto booking: travelBookings){
        if(idBooking == booking->getId()){
            return booking;
        }
    }
    return nullptr;
}

int Travel::getBookingsNumber(){
    return travelBookings.size();
}

void Travel::setTravelBookings(std::vector<std::shared_ptr<Booking>> &newTravelBookings)
{
    travelBookings = topologicalSort(newTravelBookings);
}

std::vector<std::shared_ptr<Booking> > Travel::topologicalSort(std::vector<std::shared_ptr<Booking> > &bookings)
{
    struct VertexData {
        int vertexNumber;
        std::shared_ptr<Booking> vertexValue;
        int endTime;
    };

    int i = 0;
    for(const auto &booking : bookings){
        graph->insertVertex(i, booking);
        i++;
    }

    std::string pre1Id = "";
    std::string pre2Id = "";
    int pre1 = -1;
    int pre2 = -1;
    for(int i = 0; i < bookings.size(); i++){

        if(not graph->getVertexValue(i)->getPredecessor1().empty()){
            pre1Id = graph->getVertexValue(i)->getPredecessor1();

            for(int j = 0; j < bookings.size(); j++){
                if(pre1Id == bookings[j]->getId()){
                    pre1 = j;
                    break;
                }
            }
            graph->insertEdge(pre1, i);
        }

        if(not graph->getVertexValue(i)->getPredecessor2().empty()){
            pre2Id = graph->getVertexValue(i)->getPredecessor2();

            for(int j = 0; j < bookings.size(); j++){
                if(pre2Id == bookings[j]->getId()){
                    pre2 = j;
                    break;
                }
            }
            graph->insertEdge(pre2, i);
        }
    }

    DepthFirstSearch(*graph);

    std::vector<VertexData> toBeSorted;
    VertexData vertexData;

    for (int k = 0; k < bookings.size(); k++) {
        vertexData.vertexNumber = k;
        vertexData.vertexValue = graph->getVertexValue(k);
        vertexData.endTime = graph->getEnd(k);

        toBeSorted.push_back(vertexData);
    }

    std::sort(toBeSorted.begin(), toBeSorted.end(), [](const VertexData &a, const VertexData &b){
        return a.endTime > b.endTime;
    } );

    std::vector<std::shared_ptr<Booking>> tmp;
    for(const auto& vertex: toBeSorted){
        tmp.push_back(vertex.vertexValue);
    }

    return tmp;

}

bool Travel::checkRoundtrip(){
    if(travelBookings.front()->getfromDestination() == travelBookings.back()->getToDestination())
        return true;
    else
        return false;
}

bool Travel::checkEnoughHotels(){

    for(int i = 0; i < travelBookings.size(); i++){
        if(travelBookings[i]->getType() == "RentalCar")
            continue;

        if(i == (travelBookings.size() - 1))
            return true;

        if(travelBookings[i+1]->getType() != "RentalCar"){
            if(not (travelBookings[i]->getToDate() >= travelBookings[i+1]->getFromDate()))
                return false;
        }else{
            if(not (travelBookings[i]->getToDate() >= travelBookings[i+2]->getFromDate()))
                return false;
        }

    }

    return true;
}

bool Travel::checkNoUselessHotels(){

    for(int i = 0; i < travelBookings.size(); i++){
        if(travelBookings[i]->getType() == "RentalCar")
            continue;

        if(i == (travelBookings.size() - 1))
            return true;

        if(travelBookings[i+1]->getType() != "RentalCar"){//wenn next booking ist RentalCar, nehmen wir übernächste
            if(not (travelBookings[i]->getToDate() <= travelBookings[i+1]->getFromDate()))
                return false;
        }else{
            if(not (travelBookings[i]->getToDate() <= travelBookings[i+2]->getFromDate()))
                return false;
        }

    }

    return true;
}

bool Travel::checkNoUselessRentalCars(){

    for(int i = 0; i < travelBookings.size(); i++){
        if(travelBookings[i]->getType() == "Hotel")
            continue;

        if(i == (travelBookings.size() - 1))
            return true;

        if(travelBookings[i+1]->getType() != "Hotel"){//wenn next booking ist Hotel, nehmen wir übernächste
            if(not (travelBookings[i]->getToDate() <= travelBookings[i+1]->getFromDate()))
                return false;
        }else{
            if(not (travelBookings[i]->getToDate() <= travelBookings[i+2]->getFromDate()))
                return false;
        }

    }

    return true;
}
