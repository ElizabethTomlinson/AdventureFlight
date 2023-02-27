//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H
#define ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H


#include <vector>
#include "Aircraft.h"
#include "AdventureFlightSettings.h"
#include "FuelGenerator.h"

class AdventureFlightGame {
public:
    explicit AdventureFlightGame(AdventureFlightSettings adventure_flight_settings);
    AdventureFlightGame(AdventureFlightSettings adventure_flight_settings, FuelGenerator fuelGenerator, double fuel);

    void addAircraft(Aircraft ac);

    std::string printAircraft();

    double getCurrentFuel();

    void removeFuel(double amount);

    void addFuel(double amount);

private:
    std::vector<Aircraft> aircraft;
    AdventureFlightSettings settings;
    double fuel;
    FuelGenerator fuelGenerator;
};


#endif //ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H
