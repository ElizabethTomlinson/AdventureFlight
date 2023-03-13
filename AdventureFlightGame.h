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
#include <nlohmann/json.hpp>
#include "JSONConverters.h"
#include "TripLeg.h"

class AdventureFlightGame {
public:
    AdventureFlightGame() = default;

    explicit AdventureFlightGame(AdventureFlightSettings adventure_flight_settings, GeoCoordinate input_coords);

    AdventureFlightGame(
            AdventureFlightSettings adventure_flight_settings,
            FuelGenerator fuel_generator,
            double fuel,
            GeoCoordinate input_coords);

    void addAircraft(const Aircraft &ac);

    std::string printAircraft();

    double getCurrentFuel();

    void removeFuel(double amount);

    void addFuel(double amount);

    std::string getGameStatus();

    std::string outputBareCoords();

    void addNewLeg(const TripLeg &leg);

    std::string getOrigin();

    std::string getLastLocation();

    void printLastLeg();

    void printAllLegs();

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AdventureFlightGame,
                                   aircraft,
                                   settings,
                                   fuel,
                                   fuel_generator,
                                   coords,
                                   legs);

private:
    std::vector<Aircraft> aircraft;
    AdventureFlightSettings settings;
    double fuel;
    FuelGenerator fuel_generator;
    GeoCoordinate coords;
    std::vector<TripLeg> legs;
};


#endif //ADVENTUREFLIGHT_ADVENTUREFLIGHTGAME_H
