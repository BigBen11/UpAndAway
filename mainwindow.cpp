#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorwindow.h"
#include "QTextBrowser"
#include "errorwindow.h"

#include <QDate>
#include <QInputDialog>
#include <QTableWidget>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEinlesen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All Files (*.*);;Text File(*.txt);;Json File(*.json)");

    try {
        interface.readFile(filename.toStdString());

        QString info(interface.getInfo().c_str());

        QMessageBox::information(this, "Datei erfolgreich eingelesen!", info);

        QStringList bookingsList;

        for(auto booking: interface.getBookings()){
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

//std::string doubleToStr(double value)
//{
//    std::ostringstream oss;
//    oss << value;
//    return oss.str();
//}


//QString dateUpgrade(std::string date){
//    std::string year_str;
//    std::string month_str;
//    std::string day_str;

//    for(int i = 0; i <= 3; i++)
//         year_str += date.at(i);
//    for(int i = 4; i <= 5; i++)
//        month_str += date.at(i);
//    for(int i = 6; i < 8; i++)
//        day_str += date.at(i);

//    std::string total_str = day_str + "." + month_str + "." + year_str;

//    QString total(total_str.c_str());

//    return total;
//}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    /*ui->textBrowserType->setText(QString::fromStdString(interface.getBookings()[currentRow]->getType()));
    ui->textBrowserId->setText(QString::fromStdString(interface.getBookings()[currentRow]->getId()));
    ui->textBrowserPreis->setText(QString::number(interface.getBookings()[currentRow]->getPrice()));

    //Datum
    std::string toDate = interface.getBookings()[currentRow]->getToDate();
    std::string fromDate = interface.getBookings()[currentRow]->getFromDate();

    QDate QtoDate = QDate::fromString(QString::fromStdString(toDate), "yyyymmdd");
    QDate QfromDate = QDate::fromString(QString::fromStdString(fromDate), "yyyymmdd");

    ui->textBrowserAnDatum->setText(dateUpgrade(toDate));
    ui->textBrowserAbDatum->setText(dateUpgrade(fromDate));

    if(interface.getBookings()[currentRow]->getType() == "Flight"){
        ui->tabWidget->setTabVisible(0, true);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,false);

        ui->textBrowserTypeAbreiseort->setText(QString::fromStdString(interface.getBookings()[currentRow]->getfromDestination()));
        ui->textBrowserTypeAnkunftsort->setText(QString::fromStdString(interface.getBookings()[currentRow]->getToDestination()));
        ui->textBrowserTypeFluglinie->setText(QString::fromStdString(interface.getBookings()[currentRow]->getAirline()));


        std::string bookingClassFull;
        std::string bookingClass = interface.getBookings()[currentRow]->getBookingClass();

        if(bookingClass == "Y"){
            bookingClassFull = "Economy";
        }else if(bookingClass == "W"){
            bookingClassFull = "Premium Economy";
        }else if(bookingClass == "J"){
            bookingClassFull = "Business";
        }else if(bookingClass == "F"){
            bookingClassFull = "First";
        }else{
            bookingClassFull = "keine Angabe";
        }


        ui->textBrowserTypeKlasse->setText(QString::fromStdString(bookingClassFull));

    }else if(interface.getBookings()[currentRow]->getType() == "Hotel"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,true);
        ui->tabWidget->setTabVisible(2,false);

        ui->textBrowserTypeHotel->setText(QString::fromStdString(interface.getBookings()[currentRow]->getHotel()));
        ui->textBrowserTypeStadt->setText(QString::fromStdString(interface.getBookings()[currentRow]->getTown()));

        std::string roomTypeFull;
        std::string roomType = interface.getBookings()[currentRow]->getRoomType();
        if(roomType == "EZ"){
            roomTypeFull = "Einzelzimmer";
        }else if(roomType == "DZ"){
            roomTypeFull = "Doppelzimmer";
        }else if(roomType == "AP"){
            roomTypeFull = "Appartment";
        }else if(roomType == "SU"){
            roomTypeFull = "Suite";
        }else{
            roomTypeFull = "keine Angabe";
        }

        ui->textBrowserTypeZimmertyp->setText(QString::fromStdString(roomTypeFull));

    }else if(interface.getBookings()[currentRow]->getType() == "RentalCar"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,true);

        ui->textBrowserTypeAbholort->setText(QString::fromStdString(interface.getBookings()[currentRow]->getPickupLocation()));
        ui->textBrowserTypeFahrzeugklasse->setText(QString::fromStdString(interface.getBookings()[currentRow]->getVehicleClass()));
        ui->textBrowserTypeFirma->setText(QString::fromStdString(interface.getBookings()[currentRow]->getCompany()));
        ui->textBrowserTypeRueckgabeort->setText(QString::fromStdString(interface.getBookings()[currentRow]->getReturnLocation()));
    }*/

}

QString findLatestDate(const std::vector<QString>& dates) {
    if (dates.empty()) {
        // Wenn der Vektor leer ist, gibt es kein spätestes Datum.
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
        // Wenn der Vektor leer ist, gibt es kein spätestes Datum.
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

    Customer* customer = interface.findCustomer(idCustomer);

    if(!customer){
        QMessageBox::warning(this, "Fehler!", "Es gibt keinen Kunde mit dem ID " + QString::number(idCustomer));
        return;
    }

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




void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
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


    Travel* travel = interface.findTravel(travelID.toInt());

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


void MainWindow::on_tableWidget_2_itemDoubleClicked(QTableWidgetItem *item)
{
    ui->BuchungsID->clear();
    ui->BuchungStart->clear();
    ui->BuchungEnde->clear();
    ui->BuchungPreis->clear();
    ui->tabWidget->setTabVisible(0,false);
    ui->tabWidget->setTabVisible(1,false);
    ui->tabWidget->setTabVisible(2,false);

    int bookingNum = item->row();
    int travelId = ui->ReiseID->toPlainText().toInt();

    Booking* booking = interface.findTravel(travelId)->getTravelBookings()[bookingNum];


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
            bookingClassFull = "keine Angabe";
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
            roomTypeFull = "keine Angabe";
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





}

