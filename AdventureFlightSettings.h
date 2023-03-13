//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H
#define ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H

#include <nlohmann/json.hpp>

class AdventureFlightSettings {
public:
    AdventureFlightSettings() = default;
    AdventureFlightSettings(int number_of_aircraft, double starting_fuel);

    int getNumberOfAircraft() const;

    double getStartingFuel() const;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
            AdventureFlightSettings,
            number_of_aircraft,
            starting_fuel);
private:
    int number_of_aircraft;
    double starting_fuel;
};


#endif //ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H
