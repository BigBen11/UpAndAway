#include "travelagency.h"
#include <QDebug>

TravelAgency::TravelAgency()
{
    nlohmann::json fileJson;

    std::ifstream fileInput("C:/ProjectsQt/UpAndAway/upandaway/iatacodes.json");

    if (!fileInput.is_open()) {
        std::cerr << "Failed to open iatacodes.json\n";
        exit(-1);
    }

    fileInput >> fileJson;

    fileInput.close();

    std::shared_ptr<Airport> pAirport = NULL;
    for(const auto& airport: fileJson){
        pAirport = std::make_shared<Airport>(Airport(airport["name"], airport["iso_country"], airport["municipality"], airport["iata_code"]));
        addAirport(pAirport);
    }


}

TravelAgency::~TravelAgency()
{

}

std::vector<std::shared_ptr<Airport>> TravelAgency::getAllAirports() const
{
    return allAirports;
}

std::vector<std::shared_ptr<Booking>> TravelAgency::getBookings(){
    return allBookings;
}

void TravelAgency::addBooking(std::shared_ptr<Booking> pBooking){
    allBookings.push_back(pBooking);
}

void TravelAgency::addTravel(std::shared_ptr<Travel> travel){
    allTravels.push_back(travel);
}

void TravelAgency::addCustomer(std::shared_ptr<Customer> customer){
    allCustomers.push_back(customer);
}

void TravelAgency::addAirport(std::shared_ptr<Airport> airport){
    allAirports.push_back(airport);
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
            std::shared_ptr<Booking> pBooking = nullptr;

            std::string predecessor1 = "";
            std::string predecessor2 = "";

            if(booking.find("predecessor1") != booking.end()){
                predecessor1 = booking["predecessor1"];
            }
            if(booking.find("predecessor2") != booking.end()){
                predecessor2 = booking["predecessor2"];
            }

            if (booking["type"] == "Flight") {
                pBooking = std::make_shared<FlightBooking> (FlightBooking(booking["travelId"], booking["type"], booking["fromDest"], booking["toDest"],
                    predecessor1, predecessor2,
                    booking["airline"], booking["id"], booking["price"],
                    booking["fromDate"], booking["toDate"], booking["bookingClass"],
                    booking["fromDestLatitude"], booking["fromDestLongitude"],
                    booking["toDestLatitude"], booking["toDestLongitude"]));

            } else if (booking["type"] == "RentalCar") {
                pBooking = std::make_shared<RentalCarReservation>(RentalCarReservation(booking["travelId"], booking["type"], predecessor1, predecessor2,
                    booking["pickupLocation"], booking["returnLocation"],
                    booking["company"], booking["id"], booking["price"],
                    booking["fromDate"], booking["toDate"], booking["vehicleClass"],
                    booking["pickupLatitude"], booking["pickupLongitude"],
                    booking["returnLatitude"], booking["returnLongitude"]));

            } else if (booking["type"] == "Hotel") {
                pBooking = std::make_shared<HotelBooking>(HotelBooking(booking["travelId"], booking["type"], predecessor1, predecessor2,
                    booking["hotel"], booking["town"],
                    booking["id"], booking["price"], booking["fromDate"], booking["toDate"], booking["roomType"],
                    booking["hotelLatitude"], booking["hotelLongitude"]));
            }

            allBookings.push_back(pBooking);
    }

    /*TRAVELS*/
    for (const auto& objJson : fileJson){
        if(!findTravel(objJson["travelId"])){
            std::shared_ptr<Travel> pTravel = std::make_shared<Travel>(Travel(objJson["travelId"],objJson["customerId"]));
            addTravel(pTravel);
        }
    }

     /*CUSTOMERS*/
    for (const auto& objJson : fileJson){
        if(!findCustomer(objJson["customerId"])){
            std::shared_ptr<Customer> pCustomer = std::make_shared<Customer>(Customer(objJson["customerId"], objJson["customerName"]));
            addCustomer(pCustomer);
        }
    }


    //std::cout << "TOTAL:  "<< "\t" << allBookings.size() << "\t"<< allTravels.size() << "\t"<< allCustomers.size() << std::endl<< std::endl;


    /*BOOKINGS FÜR TRAVELS*/
    for (const auto& travel: allTravels){
        std::vector <std::shared_ptr<Booking>> tmpBookings;

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
        std::vector <std::shared_ptr<Travel>> tmpTravels;
        double totalSum = 0;

        for(const auto& travel: allTravels){
            if(travel->getCustomerId() == customer->getId()){
                tmpTravels.push_back(travel);


            }
        }

        customer->setTravelList(tmpTravels);

        tmpTravels.clear();
    }

}

std::string TravelAgency::abcAnalyse()
{

    for(const auto& customer: allCustomers){
        double totalSumCustomer = 0;

        for(const auto& travel: customer->getTravelList()){
            for(const auto& booking: travel->getTravelBookings()){
                totalSumCustomer += booking->getPrice();
            }
        }

        customer->setTotalBookingsPreis(totalSumCustomer);
    }

    std::sort(allCustomers.begin(), allCustomers.end(), [](std::shared_ptr<Customer> a, std::shared_ptr<Customer> b){
        return a->getTotalBookingsPreis() <= b->getTotalBookingsPreis();
    });

    int customersNum = allCustomers.size();
    int customerNum_A = customersNum * 0.8;// 80%
    int customerNum_B = customersNum * 0.1;// 10%
    int customerNum_C = customersNum * 0.1;// 10%

    if(customerNum_A+customerNum_B+customerNum_C != customersNum){
        customerNum_A++;
    }

    double totalSum_A = 0;
    double totalSum_B = 0;
    double totalSum_C = 0;

    int i = 0;
    for(i; i < customerNum_A; i++){
        totalSum_A += allCustomers[i]->getTotalBookingsPreis();
    }
    for(i; i < customerNum_A + customerNum_B; i++){
        totalSum_B += allCustomers[i]->getTotalBookingsPreis();
    }
    for(i; i < customerNum_A + customerNum_B + customerNum_C; i++){
        totalSum_C += allCustomers[i]->getTotalBookingsPreis();
    }

    double averageSumCustomer_A = totalSum_A / customerNum_A;
    double averageSumCustomer_B = totalSum_B / customerNum_B;
    double averageSumCustomer_C = totalSum_C / customerNum_C;


    std::string abc = "Kategorie A (Top 80% der Kunden, 80% des Umsatzes):\n";
    abc += "\tKundenanzahl: " + std::to_string(customerNum_A) + "\n";
    abc += "\tGesamtumsatz dieser Kunden: " + std::to_string(totalSum_A) + " €\n";
    abc += "\tDurchschnittlicher Umsatz pro Kunde: " + std::to_string(averageSumCustomer_A) + " €\n";
    abc += "Kategorie B (Mittlere 10% der Kunden, 10% des Umsatzes):\n";
    abc += "\tKundenanzahl: " + std::to_string(customerNum_B) + "\n";
    abc += "\tGesamtumsatz dieser Kunden: " + std::to_string(totalSum_B) + " €\n";
    abc += "\tDurchschnittlicher Umsatz pro Kunde: " + std::to_string(averageSumCustomer_B) + " €\n";
    abc += "Kategorie C (Untere 10% der Kunden, 10% des Umsatzes):\n";
    abc += "\tKundenanzahl: " + std::to_string(customerNum_C) + "\n";
    abc += "\tGesamtumsatz dieser Kunden: " + std::to_string(totalSum_C) + " €\n";
    abc += "\tDurchschnittlicher Umsatz pro Kunde: " + std::to_string(averageSumCustomer_C) + " €\n";


    return abc;
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

std::shared_ptr<Booking> TravelAgency::findBooking(std::string id){
    for(auto booking: allBookings){
        if(id == booking->getId()){
            return booking;
        }
    }
    return nullptr;
}


std::shared_ptr<Travel> TravelAgency::findTravel(int id){
    for(auto travel: allTravels){
        if(id == travel->getId()){
            return travel;
        }
    }
    return nullptr;
}

std::shared_ptr<Customer> TravelAgency::findCustomer(int id){
    for(auto customer: allCustomers){
        if(id == customer->getId()){
            return customer;
        }
    }
    return nullptr;
}

std::shared_ptr<Airport> TravelAgency::findAirport(std::string iata_code){
    for(auto airport: allAirports){
        if(iata_code == airport->getIata_code()){
            return airport;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Customer> > TravelAgency::getAllCustomers() const
{
    return allCustomers;
}

std::vector<std::shared_ptr<Travel> > TravelAgency::getAllTravels() const
{
    return allTravels;
}

