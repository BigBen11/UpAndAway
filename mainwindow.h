#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QTableWidgetItem>

#include <iostream>
#include <fstream>
#include "./json.hpp"
#include <vector>

#include "travelagency.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCustomerInfo(std::shared_ptr<Customer> customer);

private slots:
    void on_actionEinlesen_triggered();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_tableWidget_2_itemDoubleClicked(QTableWidgetItem *item);

    void on_Speichern_clicked();

    void on_Abbrechen_clicked();

    void on_BuchungStart_valueChanged(int arg1);

    void on_BuchungEnde_valueChanged(int arg1);

    void on_BuchungPreis_valueChanged(double arg1);

    void on_Abreiseort_textChanged(const QString &arg1);

    void on_Ankunftsort_textChanged(const QString &arg1);

    void on_Fluglinie_textChanged(const QString &arg1);

    void on_Klasse_textChanged(const QString &arg1);

    void on_Hotel_2_textChanged(const QString &arg1);

    void on_Stadt_textChanged(const QString &arg1);

    void on_Zimmertyp_textChanged(const QString &arg1);

    void on_Abholort_textChanged(const QString &arg1);

    void on_Rueckgabeort_textChanged(const QString &arg1);

    void on_Firma_textChanged(const QString &arg1);

    void on_Fahrzeugklasse_textChanged(const QString &arg1);

    void on_button_gps_clicked();

    void on_actionNeue_Kunde_anlegen_triggered();

    void on_actionNeue_Buchung_anlegen_triggered();

    void on_actionKund_innensuche_triggered();

    void on_BuchungAnlegen_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<TravelAgency> interface;
};
#endif // MAINWINDOW_H
