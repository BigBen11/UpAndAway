 #include "travelagency.h"
#include <QDebug>

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

void TravelAgency::addTravel(Travel* travel){
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



void TravelAgency::readFile(const std::string& filePath) {
    nlohmann::json fileJson;

    std::ifstream fileInput(filePath);

    if (!fileInput.is_open()) {
        std::cerr << "Failed to open file\n";
        exit(-1);
    }

    fileInput >> fileJson;

    fileInput.close();

    for (const auto& booking : fileJson){
        // Allgemeine Prüfung für Klasse Booking
        chekJsonObjekt("type", booking, 0);
        chekJsonObjekt("id", booking, 0);
        chekJsonObjektPrice("price", booking, 0);
        chekJsonObjekt("fromDate", booking, 0);
        chekJsonObjekt("toDate", booking, 0);

        // Genaue Prüfung für verschiedene Kindklassen mit verschiedenen Attributen
        if (booking["type"] == "Flight") {
            chekJsonObjektFlight("fromDest", booking, 0);
            chekJsonObjektFlight("toDest", booking, 0);
            chekJsonObjekt("airline", booking, 0);

        } else if (booking["type"] == "Hotel") {
            chekJsonObjekt("hotel", booking, 0);
            chekJsonObjekt("town", booking, 0);

        } else if (booking["type"] == "RentalCar") {
            chekJsonObjekt("pickupLocation", booking, 0);
            chekJsonObjekt("returnLocation", booking, 0);
            chekJsonObjekt("company", booking, 0);
        }
    }

    /*BOOKINGS SPEICHERN*/
    for (const auto& booking : fileJson) {
        if (findBooking(booking["id"].get<std::string>()) == nullptr) {
            Booking* pBooking = nullptr;

            if (booking["type"] == "Flight") {
                pBooking = new FlightBooking(booking["travelId"], booking["type"], booking["fromDest"], booking["toDest"],
                    booking["airline"], booking["id"], booking["price"],
                    booking["fromDate"], booking["toDate"], booking["bookingClass"]);

            } else if (booking["type"] == "RentalCar") {
                pBooking = new RentalCarReservation(booking["travelId"], booking["type"], booking["pickupLocation"], booking["returnLocation"],
                    booking["company"], booking["id"], booking["price"],
                    booking["fromDate"], booking["toDate"], booking["vehicleClass"]);

            } else if (booking["type"] == "Hotel") {
                pBooking = new HotelBooking(booking["travelId"], booking["type"], booking["hotel"], booking["town"],
                    booking["id"], booking["price"], booking["fromDate"], booking["toDate"], booking["roomType"]);
            }

            if (pBooking != nullptr) {
                addBooking(pBooking);
            }
        }
    }

    /*TRAVELS*/
    for (const auto& objJson : fileJson){
        if(!findTravel(objJson["travelId"])){
            Travel* pTravel = new Travel(objJson["travelId"],objJson["customerId"]);
            addTravel(pTravel);
        }
    }

     /*CUSTOMERS*/
    for (const auto& objJson : fileJson){
        if(!findCustomer(objJson["customerId"])){
            Customer* pCustomer = new Customer(objJson["customerId"], objJson["customerName"]);
            addCustomer(pCustomer);
        }
    }


    //std::cout << "TOTAL:  "<< "\t" << allBookings.size() << "\t"<< allTravels.size() << "\t"<< allCustomers.size() << std::endl<< std::endl;


    /*BOOKINGS FÜR TRAVELS*/
    for (const auto& travel: allTravels){
        std::vector <Booking*> tmpBookings;

        for(const auto& booking : allBookings){


            if(booking->getTravelId() == travel->getId()){
                tmpBookings.push_back(booking);
            }
        }

        travel->setTravelBookings(tmpBookings);

        tmpBookings.clear();

       // std::cout << travel->getTravelBookings().size() << std::endl;
    }


    /*TRAVELS FÜR CUSTOMERS*/
    for (const auto& customer: allCustomers){
        std::vector <Travel*> tmpTravels;

        for(const auto& travel: allTravels){


            if(travel->getCustomerId() == customer->getId()){
                tmpTravels.push_back(travel);
            }
        }

        customer->setTravelList(tmpTravels);

        tmpTravels.clear();

        //std::cout << customer->getTravelList().size() << std::endl;
    }
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

