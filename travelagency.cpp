 #include "travelagency.h"

TravelAgency::TravelAgency()
{

}

TravelAgency::~TravelAgency()
{
    for (auto booking: bookings) {
        delete booking;
    }
    bookings.clear();
}

std::vector<Booking*> TravelAgency::getBookings(){
    return bookings;
}

void TravelAgency::addBooking(Booking* pBooking){
    bookings.push_back(pBooking);
}

Booking* TravelAgency::getBooking(std::string id){
    for(auto booking: bookings){
        if(id == booking->getId()){
            return booking;
        }
    }
    return NULL;
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



        for(int i = 0; i < 87; i++){
           if(fileJson[i]["type"] == "Flight"){
                Booking* pFlightBooking = new FlightBooking(fileJson[i]["type"], fileJson[i]["fromDest"], fileJson[i]["toDest"],
                        fileJson[i]["airline"], fileJson[i]["id"], fileJson[i]["price"],
                        fileJson[i]["fromDate"], fileJson[i]["toDate"], fileJson[i]["bookingClass"]);
                this->addBooking(pFlightBooking);

           }else if(fileJson[i]["type"] == "RentalCar"){
               Booking* pRentalCarReservation = new RentalCarReservation(fileJson[i]["type"], fileJson[i]["pickupLocation"], fileJson[i]["returnLocation"],
                       fileJson[i]["company"], fileJson[i]["id"], fileJson[i]["price"],
                       fileJson[i]["fromDate"], fileJson[i]["toDate"], fileJson[i]["vehicleClass"]);
               this->addBooking(pRentalCarReservation);

           }else if(fileJson[i]["type"] == "Hotel"){
                Booking* pHotelBooking = new HotelBooking(fileJson[i]["type"], fileJson[i]["hotel"], fileJson[i]["town"],
                        fileJson[i]["id"], fileJson[i]["price"],fileJson[i]["fromDate"], fileJson[i]["toDate"], fileJson[i]["roomType"]);
                this->addBooking(pHotelBooking);
           }
        }

        fileInput.close();


    /*catch (std::exception& e) {
        std::cout << e.what() << std::endl << "Haben Sie die Datei korrigiert? (j/n)\n";

        char isFileCorrected;
        std::cin >> isFileCorrected;

        if(isFileCorrected == 'j'){
            std::cout << "Dann noch mal...\n";

        }else if(isFileCorrected == 'n'){
            std::cout << "Tschuess dann :(\n";
            exit(1);
        }else{
            std::cout << "Falsche Eingabe!\n";
        }


    }*/

}

std::string TravelAgency::getInfo(){
    int cnt_FlightBookings = 0;
    int cnt_HotelBookings = 0;
    int cnt_RentalCars = 0;

    double sum_FlightBookings = 0;
    double sum_HotelBookings = 0;
    double sum_RentalCars = 0;



    for(auto booking: bookings){
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
                                     + cnt_HotelBookings_str + " Hotelreservierungen im Wert von " + sum_HotelBookings_str + " Euro angelegt.";

    return total;

}

