#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>


class Airport
{
public:
    Airport(std::string name, std::string iso_country, std::string municipality, std::string iata_code);


    std::string getIata_code() const;

    std::string getName() const;

private:
    std::string name;
    std::string iso_country;
    std::string municipality;
    std::string iata_code;

};

#endif // AIRPORT_H
