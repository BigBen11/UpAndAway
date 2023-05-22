#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include "travelagency.h"
#include <QMainWindow>

class TravelAgencyUI : public QMainWindow
{
public:
    TravelAgencyUI( TravelAgency* pTravelAgency, QWidget *parent = nullptr);

private:
    TravelAgency* pTravelAgency;

};

#endif // TRAVELAGENCYUI_H
