 #include "travelagency.h"

TravelAgency::TravelAgency()
{

}

TravelAgency::~TravelAgency()
{
    for (auto booking: allBookings) {
        delete booking;
    }
    for(auto travel: allTravels){
        delete travel;
    }
    for(auto customer: allCustomers){
        delete customer;
    }
}

std::vector<Booking*> TravelAgency::getBookings(){
    return allBookings;
}

void TravelAgency::addBooking(Booking* pBooking){
    allBookings.push_back(pBooking);
}

void TravelAgency::addTraevel(Travel* travel){
    allTravels.push_back(travel);
}

void TravelAgency::addCustomer(Customer* customer){
    allCustomers.push_back(customer);
}






void chekJsonObjekt(std::string const attributName, nlohmann::json const fileJson, int const objectNumber){
    if(fileJson.find(attributName) == fileJson.end() || fileJson[attributName].get<std::string>().empty()) {
        throw std::runtime_error("Error: " + attributName + " attribute is missing or empty in object " + std::to_string(objectNumber));
    }
}


void chekJsonObjektPrice(std::string attributName, nlohmann::json fileJson, int objectNumber){
    if(fileJson.find(attributName) == fileJson.end() || !fileJson[attributName].is_number() || fileJson[attributName] == 0) {
        throw std::runtime_error("Error: " + attributName + " attribute is missing or empty in object " + std::to_string(objectNumber));
    }
}

void chekJsonObjektFlight(std::string attributName, nlohmann::json fileJson, int objectNumber){
    if(fileJson.find(attributName) == fileJson.end() || fileJson[attributName].get<std::string>().empty() || fileJson[attributName].get<std::string>().size() != 3 ) {
        throw std::runtime_error("Error: " + attributName + " attribute is missing or empty or !=3 letter in object " + std::to_string(objectNumber));
    }
}

bool isTravelIdExistent(std::vector<int> travelIdAll, nlohmann::json object){
    for(auto travelId: travelIdAll){
        if(object["travelId"] == travelId){
            return true;
        }
    }
    return false;
}

bool isCustomerIdExistent(std::vector<int> customerIdAll, nlohmann::json object){
    for(auto customerId: customerIdAll){
        if(object["customerId"] == customerId){
            return true;
        }
    }
    return false;
}



void TravelAgency::readFile(std::string filePath){

        nlohmann::json fileJson;

        std::fstream fileInput(filePath);

        if (!fileInput.is_open()) {
               std::cerr << "Failed to open file\n";
               exit(-1);
        }

        fileInput >> fileJson;

        int objectNumber = 0;

        for (const auto& booking : fileJson) {
            objectNumber++;

            //Allgemeine pruefung fuer Klasse Booking
            chekJsonObjekt("type", booking, objectNumber);
            chekJsonObjekt("id", booking, objectNumber);
            chekJsonObjektPrice("price", booking, objectNumber);
            chekJsonObjekt("fromDate", booking, objectNumber);
            chekJsonObjekt("toDate", booking, objectNumber);

            //Genaue Pruefung fuer verschiedene Kindklassen mit verschiedenen Attributen
            if(booking["type"] == "Flight"){
                chekJsonObjektFlight("fromDest", booking, objectNumber);
                chekJsonObjektFlight("toDest", booking, objectNumber);
                chekJsonObjekt("airline", booking, objectNumber);

            }else if(booking["type"] == "Hotel"){
                chekJsonObjekt("hotel", booking, objectNumber);
                chekJsonObjekt("town", booking, objectNumber);

            }else if(booking["type"] == "RentalCar"){
                chekJsonObjekt("pickupLocation", booking, objectNumber);
                chekJsonObjekt("returnLocation", booking, objectNumber);
                chekJsonObjekt("company", booking, objectNumber);
            }
        }



        std::vector<Booking*> travelBookings;
        std::vector<Travel*> customerTravels;

        std::vector<int> travelIdAll;

        std::vector<int> customerIdAll;


        std::vector<Booking*> tmpTravelBookings;
        std::vector<Travel*> tmpTravelList;



        for (auto object : fileJson) {
            /*Speichern von Bookings*/
            if (object["type"] == "Flight") {
                Booking* pFlightBooking = new FlightBooking(object["type"], object["fromDest"], object["toDest"],
                    object["airline"], object["id"], object["price"],
                    object["fromDate"], object["toDate"], object["bookingClass"]);

                this->addBooking(pFlightBooking);

            } else if (object["type"] == "RentalCar") {
                Booking* pRentalCarReservation = new RentalCarReservation(object["type"], object["pickupLocation"], object["returnLocation"],
                    object["company"], object["id"], object["price"],
                    object["fromDate"], object["toDate"], object["vehicleClass"]);

                this->addBooking(pRentalCarReservation);

            } else if (object["type"] == "Hotel") {
                Booking* pHotelBooking = new HotelBooking(object["type"], object["hotel"], object["town"],
                    object["id"], object["price"], object["fromDate"], object["toDate"], object["roomType"]);

                this->addBooking(pHotelBooking);
            }

            /*Speichern von Travels*/
            tmpTravelBookings.clear();
            for (auto tmpObject : fileJson){
                if(tmpObject["travelId"] == object["travelId"]){
                    tmpTravelBookings.push_back(this->allBookings.back());
                }
            }
            if(!this->findTravel(object["travelId"])){
                Travel* pTravel = new Travel(object["travelId"], object["customerId"], tmpTravelBookings);
                allTravels.push_back(pTravel);
            }

            /*Speichern von Customers*/
            tmpTravelList.clear();
            for (auto travel: allTravels){
                if(travel->getCustomerId() == object["customerId"]){
                    tmpTravelList.push_back(travel);
                }
            }
            if(!this->findCustomer(object["customerId"])){
                Customer* pCustomer = new Customer(object["customerId"], object["customerName"], tmpTravelList);
                allCustomers.push_back(pCustomer);

            }
        }


        fileInput.close();
}



std::string TravelAgency::getInfo(){
    int cnt_FlightBookings = 0;
    int cnt_HotelBookings = 0;
    int cnt_RentalCars = 0;

    double sum_FlightBookings = 0;
    double sum_HotelBookings = 0;
    double sum_RentalCars = 0;

    for(auto booking: allBookings){
        if(booking->getType() == "Flight"){
            cnt_FlightBookings++;
            sum_FlightBookings += booking->getPrice();
        }else if(booking->getType() == "RentalCar"){
            cnt_RentalCars++;
            sum_RentalCars += booking->getPrice();
        }else if(booking->getType() == "Hotel"){
            cnt_HotelBookings++;
            sum_HotelBookings += booking->getPrice();
        }
    }

    std::string cnt_FlightBookings_str = std::to_string(cnt_FlightBookings);
    std::string cnt_HotelBookings_str = std::to_string(cnt_HotelBookings);
    std::string cnt_RentalCars_str = std::to_string(cnt_RentalCars);

    std::string sum_FlightBookings_str = std::to_string(sum_FlightBookings);
    std::string sum_HotelBookings_str = std::to_string(sum_HotelBookings);
    std::string sum_RentalCars_str = std::to_string(sum_RentalCars);




    std::string total = "Es wurden " + cnt_FlightBookings_str + " Flugbuchungen im Wert von " + sum_FlightBookings_str + " Euro,                                     "
                                     + cnt_RentalCars_str + " Mietwagenbuchungen im Wert von " + sum_RentalCars_str + " Euro,                                        "
                                     + cnt_HotelBookings_str + " Hotelreservierungen im Wert von " + sum_HotelBookings_str + " Euro angelegt.                        "
                      + "Es wurden " + std::to_string(allTravels.size()) + "Reisen und " + std::to_string(allCustomers.size())
                                     + " Kunden angelegt. Der Kunde mit der ID 1 hat " + std::to_string(findCustomer(1)->getTravelList().size())
                                     + " Reisen gebucht. Zur Reise mit der ID 17 gehören " + std::to_string(findTravel(17)->getTravelBookings().size()) + " Buchungen.";

    return total;

}

Booking* TravelAgency::findBooking(std::string id){
    for(auto booking: allBookings){
        if(id == booking->getId()){
            return booking;
        }
    }
    return NULL;
}


Travel* TravelAgency::findTravel(int id){
    for(auto travel: allTravels){
        if(id == travel->getId()){
            return travel;
        }
    }
    return NULL;
}

Customer* TravelAgency::findCustomer(int id){
    for(auto customer: allCustomers){
        if(id == customer->getId()){
            return customer;
        }
    }
    return NULL;
}

