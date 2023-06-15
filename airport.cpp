#include "airport.h"

Airport::Airport(std::string name, std::string iso_country, std::string municipality, std::string iata_code)
    :name(name), iso_country(iso_country), municipality(municipality), iata_code(iata_code)
{

}

std::string Airport::getIata_code() const
{
    return iata_code;
}

std::string Airport::getName() const
{
    return name;
}
