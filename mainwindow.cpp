#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorwindow.h"
#include "QTextBrowser"
#include "errorwindow.h"

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
        instanz.readFile(filename.toStdString());

        QString info(instanz.getInfo().c_str());

        QMessageBox::information(this, "Datei erfolgreich eingelesen!", info);

        QStringList bookingsList;

        for(auto booking: instanz.getBookings()){
            bookingsList.push_back(booking->getDetails().c_str());
        }

        ui->listWidget->addItems(bookingsList);

    } catch (std::exception& e) {
        //QMessageBox::warning(this, "Fehler beim Einlesen der Buchungen!", e.what());
        ErrorWindow errorWindow;
        errorWindow.setErrorText(e.what());
        errorWindow.setModal(true);
        errorWindow.exec();

    }
}

std::string doubleToStr(double value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


QString dateUpgrade(std::string date){
    std::string year_str;
    std::string month_str;
    std::string day_str;

    for(int i = 0; i <= 3; i++)
         year_str += date.at(i);
    for(int i = 4; i <= 5; i++)
        month_str += date.at(i);
    for(int i = 6; i < 8; i++)
        day_str += date.at(i);

    std::string total_str = day_str + "." + month_str + "." + year_str;

    QString total(total_str.c_str());

    return total;
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->textBrowserType->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getType()));
    ui->textBrowserId->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getId()));
    ui->textBrowserPreis->setText(QString::number(instanz.getBookings()[currentRow]->getPrice()));

    //Datum
    std::string toDate = instanz.getBookings()[currentRow]->getToDate();
    std::string fromDate = instanz.getBookings()[currentRow]->getFromDate();
    ui->textBrowserAnDatum->setText(dateUpgrade(toDate));
    ui->textBrowserAbDatum->setText(dateUpgrade(fromDate));

    if(instanz.getBookings()[currentRow]->getType() == "Flight"){
        ui->tabWidget->setTabVisible(0, true);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,false);

        ui->textBrowserTypeAbreiseort->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getfromDestination()));
        ui->textBrowserTypeAnkunftsort->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getToDestination()));
        ui->textBrowserTypeFluglinie->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getAirline()));


        std::string bookingClassFull;
        std::string bookingClass = instanz.getBookings()[currentRow]->getBookingClass();

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

    }else if(instanz.getBookings()[currentRow]->getType() == "Hotel"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,true);
        ui->tabWidget->setTabVisible(2,false);

        ui->textBrowserTypeHotel->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getHotel()));
        ui->textBrowserTypeStadt->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getTown()));

        std::string roomTypeFull;
        std::string roomType = instanz.getBookings()[currentRow]->getRoomType();
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

    }else if(instanz.getBookings()[currentRow]->getType() == "RentalCar"){
        ui->tabWidget->setTabVisible(0, false);
        ui->tabWidget->setTabVisible(1,false);
        ui->tabWidget->setTabVisible(2,true);

        ui->textBrowserTypeAbholort->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getPickupLocation()));
        ui->textBrowserTypeFahrzeugklasse->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getVehicleClass()));
        ui->textBrowserTypeFirma->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getCompany()));
        ui->textBrowserTypeRueckgabeort->setText(QString::fromStdString(instanz.getBookings()[currentRow]->getReturnLocation()));
    }

}


void MainWindow::on_actionAusw_hlen_triggered()
{

}

