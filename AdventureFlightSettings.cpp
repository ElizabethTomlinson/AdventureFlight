//
// Created by elizabeth on 2/26/23.
//

#include "AdventureFlightSettings.h"

AdventureFlightSettings::AdventureFlightSettings(int number_of_aircraft, double starting_fuel) :
        number_of_aircraft(number_of_aircraft),
        starting_fuel(starting_fuel) {
}

int AdventureFlightSettings::getNumberOfAircraft() const {
    return number_of_aircraft;
}

double AdventureFlightSettings::getStartingFuel() const {
    return starting_fuel;
}


