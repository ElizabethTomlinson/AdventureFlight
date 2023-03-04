//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H
#define ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H


#include <vector>
#include "Aircraft.h"
#include "AdventureFlightSettings.h"
#include "FuelGenerator.h"
#include "GeoCoordinate.h"

class AdventureFlightGame {
public:
    explicit AdventureFlightGame(AdventureFlightSettings adventure_flight_settings, GeoCoordinate input_coords);

    AdventureFlightGame(
            AdventureFlightSettings adventure_flight_settings,
            FuelGenerator fuelGenerator,
            double fuel,
            GeoCoordinate input_coords);

    void addAircraft(const Aircraft &ac);

    std::string printAircraft();

    double getCurrentFuel();

    void removeFuel(double amount);

    void addFuel(double amount);

    std::string getGameStatus();

    std::string outputBareCoords();

private:
    std::vector<Aircraft> aircraft;
    AdventureFlightSettings settings;
    double fuel;
    FuelGenerator fuelGenerator;
    GeoCoordinate coords;
};


#endif //ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H
