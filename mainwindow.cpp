#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorwindow.h"
#include "QTextBrowser"
#include "errorwindow.h"

#include <QDate>
#include <QInputDialog>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);
    interface = std::make_shared<TravelAgency>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEinlesen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All Files (*.*);;Text File(*.txt);;Json File(*.json)");

    try {
        interface->readFile(filename.toStdString());

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

void MainWindow::on_pushButton_clicked()
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

    ui->BuchungsID->clear();
    ui->BuchungStart->clear();
    ui->BuchungEnde->clear();
    ui->BuchungPreis->clear();
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);


    // Reise ID =>
    QString travelID = ui->tableWidget->item(item->row(), 0)->text();


    std::shared_ptr<Travel> travel = interface->findTravel(travelID.toInt());

    int maxRow = travel->getTravelBookings().size();

    for(int row = 0; row < maxRow; row++){
        QTableWidgetItem* item;
        for(int column = 0; column <= 3; column++){

            item = new QTableWidgetItem;

            if(column == 0)
                item->setText(QString::fromStdString(travel->getTravelBookings()[row]->getType()));

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


void MainWindow::on_Speichern_clicked()
{
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
    }

    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);


    on_tableWidget_itemDoubleClicked(sharedItem);


    //setCustomerInfo(interface->findCustomer((ui->KundeID->toPlainText().toInt())));

}


void MainWindow::on_Abbrechen_clicked()
{
    on_tableWidget_2_itemDoubleClicked(sharedItem_2);

    ui->Speichern->setDisabled(true);
    ui->Abbrechen->setDisabled(true);
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

