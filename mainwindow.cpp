#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorwindow.h"
#include "QTextBrowser"
#include "errorwindow.h"
#include <fstream>


#include <QDate>
#include <QInputDialog>
#include <QTableWidget>
#include <QDesktopServices>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);
    ui->BuchungAnlegen->setVisible(false);

    /*Tabs in Buchungsdetails*/
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);

    /*Flight Coordinates*/
    ui->label_FLightLongitudeToDest->setVisible(false);
    ui->label_FlightLatitudeToDest->setVisible(false);
    ui->label_FlightLongitudeFromDest->setVisible(false);
    ui->label_FlightLatitudeFromDest->setVisible(false);
    ui->FlightLatitudeToDest->setVisible(false);
    ui->FlightLongitueTODest->setVisible(false);
    ui->FlightLatitudeFromDest->setVisible(false);
    ui->FlightLongitudeFromDest->setVisible(false);

    /*Hotel Coordinates*/
    ui->label_HotelLatitude->setVisible(false);
    ui->label_HotelLongitude->setVisible(false);
    ui->HotelLatitude->setVisible(false);
    ui->HotelLongitude->setVisible(false);

    /*Car Coordinates*/
    ui->label_CarLantitudeFromDest->setVisible(false);
    ui->label_CarLongitudeFromDest->setVisible(false);
    ui->label_CarLantitudeToDest->setVisible(false);
    ui->label_CarLongitudeToDest->setVisible(false);
    ui->CarLantitudeFromDest->setVisible(false);
    ui->CarLongitudeFromDest->setVisible(false);
    ui->CarLantitudeToDest->setVisible(false);
    ui->CarLongitudeToDest->setVisible(false);

    /*Interface Init*/
    interface = std::make_shared<TravelAgency>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString currentFilename;
void MainWindow::on_actionEinlesen_triggered()
{
    currentFilename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All Files (*.*);;Text File(*.txt);;Json File(*.json)");

    try {
        interface->readFile(currentFilename.toStdString());

        QString info(interface->getInfo().c_str());

        QMessageBox::information(this, "Datei erfolgreich eingelesen!", info);

        QStringList bookingsList;

        for(auto booking: interface->getBookings()){
            bookingsList.push_back(booking->getDetails().c_str());
        }

       // ui->listWidget->addItems(bookingsList);

    } catch (std::exception& e) {
        //QMessageBox::warning(this, "Fehler beim Einlesen der Buchungen!", e.what());
        ErrorWindow errorWindow;
        errorWindow.setErrorText(e.what());
        errorWindow.setModal(true);
        errorWindow.exec();

    }
}

QString findLatestDate(const std::vector<QString>& dates) {
    if (dates.empty()) {
        // Wenn der Vektor leer ist
        return "";
    }

    QString latestDate = dates[0];

    for (const QString& date : dates) {
        if (date > latestDate) {
            latestDate = date;
        }
    }

    return latestDate;
}

QString findEarliestDate(const std::vector<QString>& dates) {
    if (dates.empty()) {
        // Wenn der Vektor leer ist
        return "";
    }

    QString earliestDate = dates[0];

    for (const QString& date : dates) {
        if (date < earliestDate) {
            earliestDate = date;
        }
    }

    return earliestDate;
}




void MainWindow::setCustomerInfo(std::shared_ptr<Customer> customer)
{
    std::vector<QString> fromDates;
    std::vector<QString> toDates;

    std::vector<QString> earliestFromDates;
    std::vector<QString> latestToDates;

    for(auto travel: customer->getTravelList()){
        fromDates.clear();
        toDates.clear();

        for(auto booking: travel->getTravelBookings()){
            fromDates.push_back(QString::fromStdString(booking->getFromDate()));
            toDates.push_back(QString::fromStdString(booking->getToDate()));
        }

        QString earliestFromDate = findEarliestDate(fromDates);
        earliestFromDates.push_back(earliestFromDate);

        QString latestToDate = findLatestDate(toDates);
        latestToDates.push_back(latestToDate);
    }

    int maxRow = customer->getTravelList().size();

    for(int row = 0; row < maxRow; row++){
        QTableWidgetItem* item;
        for(int column = 0; column <= 2; column++){

            item = new QTableWidgetItem;

            if(column == 0)
                item->setText(QString::number(customer->getTravelList()[row]->getId()));

            if(column == 1)
                item->setText(earliestFromDates[row]);

            if(column == 2)
                item->setText(latestToDates[row]);


            ui->tableWidget->setItem(row, column, item);
        }
    }

    ui->KundeID->setText(QString::number(customer->getId()));
    ui->KundeName->setText(QString::fromStdString(customer->getName()));
}



void MainWindow::on_actionKund_innensuche_triggered()
{
    //Alles reinigen, wenn man einen anderen Kunde sucht

    ui->tableWidget->clearContents();

    ui->tableWidget_2->clearContents();

    ui->BuchungsID->clear();
    ui->BuchungStart->clear();
    ui->BuchungEnde->clear();
    ui->BuchungPreis->clear();
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);


    int idCustomer = QInputDialog::getInt(this, "Kundensuche", "ID: ");

    std::shared_ptr<Customer> customer = interface->findCustomer(idCustomer);

    if(!customer){
        QMessageBox::warning(this, "Fehler!", "Es gibt keinen Kunde mit dem ID " + QString::number(idCustomer));
        return;
    }

    setCustomerInfo(customer);
}

QTableWidgetItem* sharedItem;
void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    sharedItem = item;

    ui->tableWidget_2->clearContents();


//        ui->BuchungsID->clear();
//        ui->BuchungStart->clear();
//        ui->BuchungEnde->clear();
//        ui->BuchungPreis->clear();
//        ui->tabWidget->setTabVisible(0,false);
//        ui->tabWidget->setTabVisible(1,false);
//        ui->tabWidget->setTabVisible(2,false);


    // Reise ID =>
    QString travelID = ui->tableWidget->item(item->row(), 0)->text();


    std::shared_ptr<Travel> travel = interface->findTravel(travelID.toInt());

    int maxRow = travel->getTravelBookings().size();

    for(int row = 0; row < maxRow; row++){
        QTableWidgetItem* item;
        for(int column = 0; column <= 3; column++){

            item = new QTableWidgetItem;

            if(column == 0){
                std::string bookingType = travel->getTravelBookings()[row]->getType();
                if(bookingType == "Flight"){
                    item->setText("✈️");
                }else if(bookingType == "Hotel"){
                    item->setText("🛏️");
                }else if(bookingType == "RentalCar"){
                    item->setText("🚘");
                }

            }

            if(column == 1)
                item->setText(QString::fromStdString(travel->getTravelBookings()[row]->getFromDate()));

            if(column == 2)
                item->setText(QString::fromStdString(travel->getTravelBookings()[row]->getToDate()));

            if(column == 3)
                item->setText(QString::number(travel->getTravelBookings()[row]->getPrice()));


            ui->tableWidget_2->setItem(row, column, item);
        }
    }

    ui->ReiseID->setText(travelID);


}


QTableWidgetItem* sharedItem_2;
void MainWindow::on_tableWidget_2_itemDoubleClicked(QTableWidgetItem *item)
{
    sharedItem_2 = item;

    ui->BuchungsID->clear();
    ui->BuchungStart->clear();
    ui->BuchungEnde->clear();
    ui->BuchungPreis->clear();
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);

    int bookingNum = item->row();
    int travelId = ui->ReiseID->toPlainText().toInt();

    std::shared_ptr<Booking> booking = interface->findTravel(travelId)->getTravelBookings()[bookingNum];


    ui->BuchungsID->setText(QString::fromStdString(booking->getId()));
    ui->BuchungStart->setValue(std::stoi(booking->getFromDate()));
    ui->BuchungEnde->setValue(std::stoi(booking->getToDate()));
    ui->BuchungPreis->setValue(booking->getPrice());


    if(booking->getType() == "Flight"){
        ui->tabWidget->setTabVisible(0, true);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,false);

        ui->Abreiseort->setText(QString::fromStdString(booking->getfromDestination()));
        ui->Ankunftsort->setText(QString::fromStdString(booking->getToDestination()));
        ui->Fluglinie->setText(QString::fromStdString(booking->getAirline()));

        QString nameFromDestination = QString::fromStdString(interface->findAirport(booking->getfromDestination())->getName());
        QString nameToDestination = QString::fromStdString(interface->findAirport(booking->getToDestination())->getName());

        ui->NameAbreiseort->setText(nameFromDestination);
        ui->NameAnkunftsort->setText(nameToDestination);


        std::string bookingClassFull;
        std::string bookingClass = booking->getBookingClass();

        if(bookingClass == "Y"){
            bookingClassFull = "Economy";
        }else if(bookingClass == "W"){
            bookingClassFull = "Premium Economy";
        }else if(bookingClass == "J"){
            bookingClassFull = "Business";
        }else if(bookingClass == "F"){
            bookingClassFull = "First";
        }else{
            bookingClassFull = "Falsche Eingabe!";
        }


        ui->Klasse->setText(QString::fromStdString(bookingClassFull));

    }else if(booking->getType() == "Hotel"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,true);
        ui->tabWidget->setTabVisible(2,false);

        ui->Hotel_2->setText(QString::fromStdString(booking->getHotel()));
        ui->Stadt->setText(QString::fromStdString(booking->getTown()));

        std::string roomTypeFull;
        std::string roomType = booking->getRoomType();
        if(roomType == "EZ"){
            roomTypeFull = "Einzelzimmer";
        }else if(roomType == "DZ"){
            roomTypeFull = "Doppelzimmer";
        }else if(roomType == "AP"){
            roomTypeFull = "Appartment";
        }else if(roomType == "SU"){
            roomTypeFull = "Suite";
        }else{
            roomTypeFull = "Falsche Eingabe!";
        }

        ui->Zimmertyp->setText(QString::fromStdString(roomTypeFull));

    }else if(booking->getType() == "RentalCar"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,true);

        ui->Abholort->setText(QString::fromStdString(booking->getPickupLocation()));
        ui->Fahrzeugklasse->setText(QString::fromStdString(booking->getVehicleClass()));
        ui->Firma->setText(QString::fromStdString(booking->getCompany()));
        ui->Rueckgabeort->setText(QString::fromStdString(booking->getReturnLocation()));
    }

    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);

}

void MainWindow::sortJson(QWidget* parent, nlohmann::json& json){
    QStringList items = {"Price" , "From Date", "To Date", "Travel ID"};
    QString item = QInputDialog::getItem(parent, "Sortieren...", "Wählen Sie das passende Sortierkriterium:", items);

    if(item == "Price"){
        std::sort(json.begin(), json.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
            return a["price"] < b["price"];
        });
    }else if(item == "From Date"){
        std::sort(json.begin(), json.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
            return a["fromDate"].get<std::string>() < b["fromDate"].get<std::string>();
        });
    }else if(item == "To Date"){
        std::sort(json.begin(), json.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
            return a["toDate"].get<std::string>() < b["toDate"].get<std::string>();
        });
    }else if(item == "Travel ID"){
        std::sort(json.begin(), json.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
            return a["travelId"] < b["travelId"];
        });
    }
}

void MainWindow::on_Speichern_clicked()
{
    // Laden der JSON-Datei
    std::ifstream jsonFileIn(currentFilename.toStdString());
    if (!jsonFileIn.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei.");
            return;
    }
    nlohmann::json json;
    jsonFileIn >> json;
    jsonFileIn.close();


    std::string fromDate = std::to_string(ui->BuchungStart->value());
    std::string toDate = std::to_string(ui->BuchungEnde->value());
    double price = ui->BuchungPreis->value();


    std::string idBooking = ui->BuchungsID->toPlainText().toStdString();
    int idTravel = ui->ReiseID->toPlainText().toInt();

    std::shared_ptr<Booking> bookingInTravel = interface->findTravel(idTravel)->findBookingInTravel(idBooking);
    std::shared_ptr<Booking> booking = interface->findBooking(idBooking);


    booking->setFromDate(fromDate);
    bookingInTravel->setFromDate(fromDate);
    booking->setToDate(toDate);
    bookingInTravel->setToDate(toDate);
    booking->setPrice(price);
    bookingInTravel->setPrice(price);

    std::string type = booking->getType();
    if(type == "Flight"){
        std::shared_ptr<FlightBooking> flight = std::dynamic_pointer_cast<FlightBooking> (booking);
        std::shared_ptr<FlightBooking> flightInTravel = std::dynamic_pointer_cast<FlightBooking> (bookingInTravel);

        std::string fromDestCode = ui->Abreiseort->text().toStdString();
        std::string toDestCode = ui->Ankunftsort->text().toStdString();

        if(interface->findAirport(fromDestCode)){
            flight->setFromDestination(fromDestCode);
            flightInTravel->setFromDestination(fromDestCode);

            ui->NameAbreiseort->setStyleSheet("color:Black;");
            ui->NameAbreiseort->setText(QString::fromStdString(interface->findAirport(fromDestCode)->getName()));
        }else{
            QMessageBox::warning(this, "Fehler", "Ungültiger Iata-Code in Abreiseort");
            ui->NameAbreiseort->setStyleSheet("color:Red;");
            ui->NameAbreiseort->setText("Ungültiger Iata-Code");
        }

        if(interface->findAirport(toDestCode)){
            flight->setToDestination(toDestCode);
            flightInTravel->setToDestination(toDestCode);

            ui->NameAnkunftsort->setStyleSheet("color:Black;");
            ui->NameAnkunftsort->setText(QString::fromStdString(interface->findAirport(toDestCode)->getName()));
        }else{
            QMessageBox::warning(this, "Fehler", "Ungültiger Iata-Code in Ankunftsort");
            ui->NameAnkunftsort->setStyleSheet("color:Red;");
            ui->NameAnkunftsort->setText("Ungültiger Iata-Code");
        }

        flight->setAirline(ui->Fluglinie->text().toStdString());
        flightInTravel->setAirline(ui->Fluglinie->text().toStdString());

        std::string bookingClass;
        std::string bookingClassFull = ui->Klasse->text().toStdString();

        if(bookingClassFull == "Economy"){
            bookingClass = "Y";
        }else if(bookingClassFull == "Premium Economy"){
            bookingClass = "W";
        }else if(bookingClassFull == "Business"){
            bookingClass = "J";
        }else if(bookingClassFull == "First"){
            bookingClass = "F";
        }else{
            bookingClass = "Falsche Eingabe!";
        }

        flight->setBookingClass(bookingClass);
        flightInTravel->setBookingClass(bookingClass);

        /*JSON*/
        for (auto& booking : json) {
            if (booking["id"] == ui->BuchungsID->toPlainText().toStdString()) {
                // Überschreiben Booking
                booking["airline"] = ui->Fluglinie->text().toStdString();
                booking["bookingClass"] = bookingClass;
                booking["fromDate"] = fromDate;
                booking["fromDest"] = fromDestCode;
                booking["price"] = price;
                booking["toDate"] = toDate;
                booking["toDest"] = toDestCode;
                break;
            }
        }



    }else if(type == "Hotel"){
        std::shared_ptr<HotelBooking> hotel = std::dynamic_pointer_cast<HotelBooking> (booking);
        std::shared_ptr<HotelBooking> hotelInTravel = std::dynamic_pointer_cast<HotelBooking> (bookingInTravel);

        hotel->setHotel(ui->Hotel_2->text().toStdString());
        hotelInTravel->setHotel(ui->Hotel_2->text().toStdString());
        hotel->setTown( ui->Stadt->text().toStdString());
        hotelInTravel->setTown( ui->Stadt->text().toStdString());

        std::string roomTypeFull = ui->Zimmertyp->text().toStdString();
        std::string roomType;
        if(roomTypeFull == "Einzelzimmer"){
            roomType = "EZ";
        }else if(roomTypeFull == "Doppelzimmer"){
            roomType = "DZ";
        }else if(roomTypeFull == "Appartment"){
            roomType = "AP";
        }else if(roomTypeFull == "Suite"){
            roomType = "SU";
        }else{
            roomType = "Falsche Eingabe!";
        }

        hotel->setRoomType(roomType);
        hotelInTravel->setRoomType(roomType);

        /*JSON*/
        for (auto& booking : json) {
            if (booking["id"] == ui->BuchungsID->toPlainText().toStdString()) {
                // Überschreiben Booking
                booking["fromDate"] = fromDate;
                booking["hotel"] = ui->Hotel_2->text().toStdString();
                booking["price"] = price;
                booking["roomType"] = roomType;
                booking["toDate"] = toDate;
                booking["town"] =  ui->Stadt->text().toStdString();
                break;
            }
        }

    }else if(type == "RentalCar"){
        std::shared_ptr<RentalCarReservation> car = std::dynamic_pointer_cast<RentalCarReservation> (booking);
        std::shared_ptr<RentalCarReservation> carInTravel = std::dynamic_pointer_cast<RentalCarReservation> (bookingInTravel);

        car->setPickupLocation(ui->Abholort->text().toStdString());
        carInTravel->setPickupLocation(ui->Abholort->text().toStdString());
        car->setReturnLocation(ui->Rueckgabeort->text().toStdString());
        carInTravel->setReturnLocation(ui->Rueckgabeort->text().toStdString());
        car->setCompany(ui->Firma->text().toStdString());
        carInTravel->setCompany(ui->Firma->text().toStdString());
        car->setVehicleClass(ui->Fahrzeugklasse->text().toStdString());
        carInTravel->setVehicleClass(ui->Fahrzeugklasse->text().toStdString());

        /*JSON*/
        for (auto& booking : json) {
            if (booking["id"] == ui->BuchungsID->toPlainText().toStdString()) {
                // Überschreiben Booking
                booking["company"] = ui->Firma->text().toStdString();
                booking["fromDate"] = fromDate;
                booking["pickupLocation"] = ui->Abholort->text().toStdString();
                booking["price"] = price;
                booking["returnLocation"] = ui->Rueckgabeort->text().toStdString();
                booking["toDate"] = toDate;
                booking["vehicleClass"] =  ui->Fahrzeugklasse->text().toStdString();
                break;
            }
        }
    }

    /***JSON Sortieren***/
    sortJson(this, json);

    /***Speichern in Json***/

    std::ofstream jsonFileOut(currentFilename.toStdString());
    if (!jsonFileOut.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei zum Schreiben.");
            return;
    }

    jsonFileOut << json.dump(4); // Optional: dump(4) für eine formatierte Ausgabe mit Einrückung von 4 Leerzeichen
    jsonFileOut.close();



    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);


    on_tableWidget_itemDoubleClicked(sharedItem);


}


void MainWindow::on_Abbrechen_clicked()
{
    on_tableWidget_2_itemDoubleClicked(sharedItem_2);

    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);
}


void MainWindow::on_button_gps_clicked()
{

    int travelId = ui->ReiseID->toPlainText().toInt();

    std::shared_ptr<Travel> travel = interface->findTravel(travelId);

    if (travel == nullptr) {
        // Reise nicht gefunden
        return;
    }

    std::vector<std::shared_ptr<Booking>> bookings = travel->getTravelBookings();

    // Sammlung für GeoJSON-Features erstellen
    QString featureCollection = "{\"type\":\"FeatureCollection\",\"features\":[";
    QString coordinates;
    QString feature;

    for (auto booking: bookings) {

        if (booking->getType() == "Hotel") {
            std::shared_ptr<HotelBooking> hotelBooking = std::dynamic_pointer_cast<HotelBooking>(booking);
            QString hotelLatitude = QString::fromStdString(hotelBooking->getHotelLatitude());
            QString hotelLongitude = QString::fromStdString(hotelBooking->getHotelLongitude());
            coordinates = QString("[%1,%2]").arg(hotelLongitude, hotelLatitude);

            // GeoJSON-Feature für die Buchung erstellen
            feature = QString("{\"type\":\"Feature\",\"geometry\":{\"type\":\"Point\",\"coordinates\":%1},\"properties\":{\"Hotel\":\"%2\"}}")
                          .arg(coordinates, QString::fromStdString(booking->getHotel()));

        } else if (booking->getType() == "RentalCar") {
            std::shared_ptr<RentalCarReservation> carBooking = std::dynamic_pointer_cast<RentalCarReservation>(booking);
            QString pickupLatitude = QString::fromStdString(carBooking->getPickupLatitude());
            QString pickupLongitude = QString::fromStdString(carBooking->getPickupLongitude());
            QString returnLatitude = QString::fromStdString(carBooking->getReturnLatitude());
            QString returnLongitude = QString::fromStdString(carBooking->getReturnLongitude());

            if(pickupLatitude == returnLatitude && pickupLongitude == returnLongitude){
                coordinates = QString("[%1,%2]").arg(pickupLongitude, pickupLatitude);
                // GeoJSON-Feature für die Buchung erstellen
                feature = QString("{\"type\":\"Feature\",\"geometry\":{\"type\":\"Point\",\"coordinates\":%1},\"properties\":{\"PickupStation\":\"%2\",\"ReturnStation\":\"%3\",\"Company\":\"%4\"}}")
                              .arg(coordinates, QString::fromStdString(carBooking->getPickupLocation()), QString::fromStdString(carBooking->getReturnLocation()), QString::fromStdString(carBooking->getCompany()));

            }else{
                coordinates = QString("[%1,%2],[%3,%4]").arg(pickupLongitude, pickupLatitude, returnLongitude, returnLatitude);

                // GeoJSON-Feature für die Buchung erstellen
                feature = QString("{\"type\":\"Feature\",\"geometry\":{\"type\":\"LineString\",\"coordinates\":[%1]},\"properties\":{\"PickupStation\":\"%2\",\"ReturnStation\":\"%3\",\"Company\":\"%4\"}}")
                              .arg(coordinates, QString::fromStdString(carBooking->getPickupLocation()), QString::fromStdString(carBooking->getReturnLocation()), QString::fromStdString(carBooking->getCompany()));
            }



        } else if (booking->getType() == "Flight") {
            std::shared_ptr<FlightBooking> flightBooking = std::dynamic_pointer_cast<FlightBooking>(booking);
            QString startLatitude = QString::fromStdString(flightBooking->getFromDestLatitude());
            QString startLongitude = QString::fromStdString(flightBooking->getFromDestLongitude());
            QString endLatitude = QString::fromStdString(flightBooking->getToDestLatitude());
            QString endLongitude = QString::fromStdString(flightBooking->getToDestLongitude());
            coordinates = QString("[%1,%2],[%3,%4]").arg(startLongitude, startLatitude, endLongitude, endLatitude);

            // GeoJSON-Feature für die Buchung erstellen
            feature = QString("{\"type\":\"Feature\",\"geometry\":{\"type\":\"LineString\",\"coordinates\":[%1]},\"properties\":{\"From Destination\":\"%2\",\"To Destination\":\"%3\"}}")
                          .arg(coordinates, QString::fromStdString(flightBooking->getfromDestination()), QString::fromStdString(flightBooking->getToDestination()));
        }



        // Feature zur Sammlung hinzufügen
        featureCollection += feature + ",";
    }


    featureCollection.chop(1);
    featureCollection += "]}";


    QString mapUrl = "http://townsendjennings.com/geo/?geojson=" + QUrl::toPercentEncoding(featureCollection);


    QDesktopServices::openUrl(QUrl(mapUrl));
}




void MainWindow::on_BuchungStart_valueChanged(int arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_BuchungEnde_valueChanged(int arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_BuchungPreis_valueChanged(double arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Abreiseort_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Ankunftsort_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Fluglinie_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Klasse_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Hotel_2_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Stadt_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Zimmertyp_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Abholort_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Rueckgabeort_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Firma_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}


void MainWindow::on_Fahrzeugklasse_textChanged(const QString &arg1)
{
    ui->Speichern->setEnabled(true);
    ui->Abbrechen->setEnabled(true);
}





void MainWindow::on_actionNeue_Kunde_anlegen_triggered()
{
    int maxId = 0;
    for(auto customer: interface->getAllCustomers()){
        if(customer->getId() > maxId){
            maxId = customer->getId();
        }
    }

    int newId = ++maxId;

    QString newName = QInputDialog::getText(this, "Neue Kunde anlegen...", "Geben Sie bitte die Name ein:");

    std::shared_ptr<Customer> newCustomer = std::make_shared<Customer>(Customer(newId, newName.toStdString()));

    interface->addCustomer(newCustomer);

    QMessageBox::information(this, "Erflogreich!", newName + " ist erfolgreich mit ID " + QString::number(newId) + " angelegt!");
}


void MainWindow::on_actionNeue_Buchung_anlegen_triggered()
{
    ui->groupBox->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_3->setEnabled(true);

    ui->Speichern->setVisible(false);
    ui->Abbrechen->setVisible(false);
    ui->BuchungAnlegen->setVisible(true);



    QStringList items = {"Flugbuchung", "Hotelbuchung", "Mietwagenreservierung"};

    QString bookingType = QInputDialog::getItem(this, "Buchungstyp", "Wählen Sie bitte den Buchungstyp: ", items);

    if(bookingType == "Flugbuchung"){
        ui->tabWidget->setTabVisible(0,true);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,false);

        /*Flight Coordinates*/
        ui->label_FLightLongitudeToDest->setVisible(true);
        ui->label_FlightLatitudeToDest->setVisible(true);
        ui->label_FlightLongitudeFromDest->setVisible(true);
        ui->label_FlightLatitudeFromDest->setVisible(true);
        ui->FlightLatitudeToDest->setVisible(true);
        ui->FlightLongitueTODest->setVisible(true);
        ui->FlightLatitudeFromDest->setVisible(true);
        ui->FlightLongitudeFromDest->setVisible(true);

    }else if(bookingType == "Hotelbuchung"){
        ui->tabWidget->setTabVisible(0,false);
        ui->tabWidget->setTabVisible(1,true);
        ui->tabWidget->setTabVisible(2,false);

        /*Hotel Coordinates*/
        ui->label_HotelLatitude->setVisible(true);
        ui->label_HotelLongitude->setVisible(true);
        ui->HotelLatitude->setVisible(true);
        ui->HotelLongitude->setVisible(true);

    }else if(bookingType == "Mietwagenreservierung"){
        ui->tabWidget->setTabVisible(0,false);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,true);

        /*Car Coordinates*/
        ui->label_CarLantitudeFromDest->setVisible(true);
        ui->label_CarLongitudeFromDest->setVisible(true);
        ui->label_CarLantitudeToDest->setVisible(true);
        ui->label_CarLongitudeToDest->setVisible(true);
        ui->CarLantitudeFromDest->setVisible(true);
        ui->CarLongitudeFromDest->setVisible(true);
        ui->CarLantitudeToDest->setVisible(true);
        ui->CarLongitudeToDest->setVisible(true);

    }
}





void MainWindow::on_BuchungAnlegen_clicked()
{

    // Laden der JSON-Datei
    std::ifstream jsonFileIn(currentFilename.toStdString());
    if (!jsonFileIn.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei.");
            return;
    }

    nlohmann::json allBookingsJson;
    jsonFileIn >> allBookingsJson;
    jsonFileIn.close();

    nlohmann::json newBookingJson;


    /*Customer eingeben*/
    QString tmp1 = QInputDialog::getText(this, "Speichern unter...", "Kunde ID: ");
    int customerId = tmp1.toInt();

    if(not interface->findCustomer(customerId)){
        QMessageBox::warning(this, "Fehler!", "Es gibt keinen Kunde mit ID " + tmp1);
        return;
    }

    /*Travel eingeben*/
    QStringList items;
    for(auto travel: interface->findCustomer(customerId)->getTravelList()){
        items.push_back(QString::number(travel->getId()));
    }
    items.push_back("Neue Reise...");

    QString item = QInputDialog::getItem(this, "Speichern unter...", "Reise ID: ", items);
    int travelId;
    if(item == "Neue Reise..."){
        int maxId = 0;
        for(auto travel: interface->getAllTravels()){
            if(travel->getId() > maxId){
                maxId = travel->getId();
            }
        }
        travelId = ++maxId;
    }else{
        travelId = item.toInt();
    }


    /*Attributen fuer Booking speichern*/
    QString newId = QUuid::createUuid().toString();
    ui->BuchungsID->setText(newId);

    std::string fromDate = std::to_string(ui->BuchungStart->value());
    std::string toDate = std::to_string(ui->BuchungEnde->value());
    double price = ui->BuchungPreis->value();

    std::shared_ptr<Booking> pBooking = nullptr;

    if(ui->tabWidget->isTabVisible(0)/*Flight*/){

        std::string fromDestCode = ui->Abreiseort->text().toStdString();
        std::string toDestCode = ui->Ankunftsort->text().toStdString();

        if(interface->findAirport(fromDestCode)){
            std::string fromDestName = interface->findAirport(fromDestCode)->getName();
            ui->NameAbreiseort->setStyleSheet("color:Black;");
            ui->NameAbreiseort->setText(QString::fromStdString(fromDestName));
        }else{
            QMessageBox::warning(this, "Fehler", "Ungültiger Iata-Code in Abreiseort");
            ui->NameAbreiseort->setStyleSheet("color:Red;");
            ui->NameAbreiseort->setText("Ungültiger Iata-Code");
            return;
        }

        if(interface->findAirport(toDestCode)){
            std::string toDestName = interface->findAirport(toDestCode)->getName();
            ui->NameAnkunftsort->setStyleSheet("color:Black;");
            ui->NameAnkunftsort->setText(QString::fromStdString(toDestName));
        }else{
            QMessageBox::warning(this, "Fehler", "Ungültiger Iata-Code in Ankunftsort");
            ui->NameAnkunftsort->setStyleSheet("color:Red;");
            ui->NameAnkunftsort->setText("Ungültiger Iata-Code");
            return;
        }

        std::string airline = ui->Fluglinie->text().toStdString();

        std::string bookingClass;
        std::string bookingClassFull = ui->Klasse->text().toStdString();
        if(bookingClassFull == "Economy"){
            bookingClass = "Y";
        }else if(bookingClassFull == "Premium Economy"){
            bookingClass = "W";
        }else if(bookingClassFull == "Business"){
            bookingClass = "J";
        }else if(bookingClassFull == "First"){
            bookingClass = "F";
        }else{
            bookingClass = "Falsche Eingabe!";
        }

        std::string fromDestLatitude = ui->FlightLatitudeFromDest->text().toStdString();
        std::string fromDestLongitude = ui->FlightLongitudeFromDest->text().toStdString();
        std::string toDestLatitude = ui->FlightLatitudeToDest->text().toStdString();
        std::string toDestLongitude = ui->FlightLongitueTODest->text().toStdString();

        pBooking = std::make_shared<FlightBooking>(FlightBooking(travelId, "Flight", fromDestCode, toDestCode,"","", airline,
                                                                 newId.toStdString(), price, fromDate, toDate, bookingClass,
                                                                 fromDestLatitude, fromDestLongitude, toDestLatitude, toDestLongitude));


        newBookingJson = {
                {"airline", airline},
                {"bookingClass", bookingClass},
                {"customerId", customerId},
                {"customerName", interface->findCustomer(customerId)->getName()},
                {"fromDate", fromDate},
                {"fromDest", fromDestCode},
                {"fromDestLatitude", fromDestLatitude},
                {"fromDestLongitude", fromDestLongitude},
                {"id", newId.toStdString()},
                {"price", price},
                {"toDate", toDate},
                {"toDest", toDestCode},
                {"toDestLatitude", toDestLatitude},
                {"toDestLongitude", toDestLongitude},
                {"travelId", travelId},
                {"type", "Flight"}
        };


    }else if(ui->tabWidget->isTabVisible(1)/*Hotel*/){
        std::string hotel = ui->Hotel_2->text().toStdString();
        std::string hotelLatitude = ui->HotelLatitude->text().toStdString();
        std::string hotelLongitude = ui->HotelLongitude->text().toStdString();

        std::string town = ui->Stadt->text().toStdString();

        std::string roomTypeFull = ui->Zimmertyp->text().toStdString();
        std::string roomType;
        if(roomTypeFull == "Einzelzimmer"){
            roomType = "EZ";
        }else if(roomTypeFull == "Doppelzimmer"){
            roomType = "DZ";
        }else if(roomTypeFull == "Appartment"){
            roomType = "AP";
        }else if(roomTypeFull == "Suite"){
            roomType = "SU";
        }else{
            roomType = "Falsche Eingabe!";
        }

        pBooking = std::make_shared<HotelBooking>(HotelBooking(travelId, "Hotel","","", hotel, town, newId.toStdString(), price, fromDate, toDate,
                                                               roomType, hotelLatitude, hotelLongitude));


        newBookingJson = {
            {"customerId", customerId},
            {"customerName", interface->findCustomer(customerId)->getName()},
            {"fromDate", fromDate},
            {"hotel", hotel},
            {"hotelLatitude", hotelLatitude},
            {"hotelLongitude", hotelLongitude},
            {"id", newId.toStdString()},
            {"price", price},
            {"roomType", roomType},
            {"toDate", toDate},
            {"town", town},
            {"travelId", travelId},
            {"type", "Hotel"}
        };

    }else if(ui->tabWidget->isTabVisible(2)/*Car*/){
        std::string pickupLocation = ui->Abholort->text().toStdString();
        std::string pickupLatitude = ui->CarLantitudeFromDest->text().toStdString();
        std::string pickupLongitude =  ui->CarLongitudeFromDest->text().toStdString();;

        std::string returnLocation = ui->Rueckgabeort->text().toStdString();
        std::string returnLatitude =  ui->CarLantitudeToDest->text().toStdString();;
        std::string returnLongitude =  ui->CarLongitudeToDest->text().toStdString();;

        std::string company = ui->Firma->text().toStdString();
        std::string vehicleClass = ui->Fahrzeugklasse->text().toStdString();

        pBooking = std::make_shared<RentalCarReservation>(RentalCarReservation(travelId, "RentalCar","","", pickupLocation, returnLocation, company,
                                                                               newId.toStdString(), price, fromDate, toDate, vehicleClass,
                                                                               pickupLatitude, pickupLongitude, returnLatitude, returnLongitude));

        newBookingJson = {
            {"company", company},
            {"customerId", customerId},
            {"customerName", interface->findCustomer(customerId)->getName()},
            {"fromDate", fromDate},
            {"id", newId.toStdString()},
            {"pickupLatitude", pickupLatitude},
            {"pickupLocation", pickupLocation},
            {"pickupLongitude", pickupLongitude},
            {"price", price},
            {"returnLatitude", returnLatitude},
            {"returnLocation", returnLocation},
            {"returnLongitude", returnLongitude},
            {"toDate", toDate},
            {"travelId", travelId},
            {"type", "RentalCar"},
            {"vehicleClass", vehicleClass}
        };
    }

    /*Eingegebene Reise schon bereits existiert*/
    if(interface->findTravel(travelId)){
        interface->addBooking(pBooking);
        interface->findTravel(travelId)->addBooking(pBooking);

    }else{
        interface->addBooking(pBooking);

        std::shared_ptr<Travel> newTravel = std::make_shared<Travel>(Travel(travelId,customerId));
        newTravel->addBooking(pBooking);
        interface->addTravel(newTravel);

        interface->findCustomer(customerId)->addTravel(newTravel);
    }

    // Hinzufügen des neuen Objekts zum Array
    allBookingsJson.push_back(newBookingJson);

    //Sortieren
    sortJson(this, allBookingsJson);


    // Speichern des aktualisierten Arrays in die JSON-Datei
    std::ofstream jsonFileOut(currentFilename.toStdString());
    if (!jsonFileOut.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei zum Schreiben.");
            return;
    }

    jsonFileOut << allBookingsJson.dump(4); // Optional: dump(4) für eine formatierte Ausgabe mit Einrückung von 4 Leerzeichen
    jsonFileOut.close();


    /*Alle GroupBoxes einblenden*/
    ui->groupBox->setVisible(true);
    ui->groupBox_2->setVisible(true);
    ui->groupBox_3->setEnabled(true);

    /*Knopf wechseln*/
    ui->Speichern->setVisible(true);
    ui->Abbrechen->setVisible(true);
    ui->BuchungAnlegen->setVisible(false);

    /*Buchungsdeails aufraeumen*/
    ui->BuchungsID->clear();
    ui->BuchungStart->clear();
    ui->BuchungEnde->clear();
    ui->BuchungPreis->clear();

        /*Flight Coordinates*/
    ui->label_FLightLongitudeToDest->setVisible(false);
    ui->label_FlightLatitudeToDest->setVisible(false);
    ui->label_FlightLongitudeFromDest->setVisible(false);
    ui->label_FlightLatitudeFromDest->setVisible(false);
    ui->FlightLatitudeToDest->setVisible(false);
    ui->FlightLongitueTODest->setVisible(false);
    ui->FlightLatitudeFromDest->setVisible(false);
    ui->FlightLongitudeFromDest->setVisible(false);

        /*Hotel Coordinates*/
    ui->label_HotelLatitude->setVisible(false);
    ui->label_HotelLongitude->setVisible(false);
    ui->HotelLatitude->setVisible(false);
    ui->HotelLongitude->setVisible(false);

        /*Car Coordinates*/
    ui->label_CarLantitudeFromDest->setVisible(false);
    ui->label_CarLongitudeFromDest->setVisible(false);
    ui->label_CarLantitudeToDest->setVisible(false);
    ui->label_CarLongitudeToDest->setVisible(false);
    ui->CarLantitudeFromDest->setVisible(false);
    ui->CarLongitudeFromDest->setVisible(false);
    ui->CarLantitudeToDest->setVisible(false);
    ui->CarLongitudeToDest->setVisible(false);

    /*Buchungsdetails*/
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);

    QMessageBox::information(this, "Erfolgreich!", "Neue Buchung ist erfolgreich gespeichert!");
}


void MainWindow::on_actionBuchungen_sortieren_triggered()
{
    // Laden der JSON-Datei
    std::ifstream jsonFileIn(currentFilename.toStdString());
    if (!jsonFileIn.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei.");
        return;
    }
    nlohmann::json json;
    jsonFileIn >> json;
    jsonFileIn.close();

    //Sortieren
    sortJson(this, json);

    /***Speichern in Json***/
    std::ofstream jsonFileOut(currentFilename.toStdString());
    if (!jsonFileOut.is_open()) {
        QMessageBox::critical(this, "Fehler!", "Fehler beim Öffnen der JSON-Datei zum Schreiben.");
            return;
    }

    jsonFileOut << json.dump(4); // Optional: dump(4) für eine formatierte Ausgabe mit Einrückung von 4 Leerzeichen
    jsonFileOut.close();
}


void MainWindow::on_actionReisen_pr_fen_triggered()
{
    QStringList items;

    for(auto travel: interface->getAllTravels()){
            items.push_back(QString::number(travel->getId()));
    }

    QString item = QInputDialog::getItem(this, "Prüfen...", "Wählen Sie die zu prüfende Reise: ", items);

    auto travel = interface->findTravel(item.toInt());

    QString roundTrip = "No Data";
    QString enoughHotels = "No Data";
    QString noUselessHotels = "No Data";
    QString noUselessRentalCars = "No Data";

    if(travel->checkRoundtrip()){
        roundTrip = "✅";
    }else{
        roundTrip = "❌";
    }

    if(travel->checkEnoughHotels()){
        enoughHotels = "✅";
    }else{
        enoughHotels = "❌";
    }

    if(travel->checkNoUselessHotels()){
        noUselessHotels = "✅";
    }else{
        noUselessHotels = "❌";
    }

    if(travel->checkNoUselessRentalCars()){
        noUselessRentalCars = "✅";
    }else{
        noUselessRentalCars = "❌";
    }

    QMessageBox::information(this, "Ergebnisse für die Reise " + item,
                              "Rundreise: " + roundTrip + "\n"
                            + "Genug Hotels: " + enoughHotels + "\n"
                            + "Kein überflüssiges Hotel: " + noUselessHotels + "\n"
                            + "Kein überflüssiger Mietwagen: " + noUselessRentalCars);
}


void MainWindow::on_actionABC_Analyse_triggered()
{
    QMessageBox::information(this, "ABC-Analyse", QString::fromStdString(interface->abcAnalyse()));
}

