//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H
#define ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H


class AdventureFlightSettings {
public:
    AdventureFlightSettings(int number_of_aircraft, double starting_fuel);
    int getNumberOfAircraft() const;

    double getStartingFuel() const;
private:
    int number_of_aircraft;
    double starting_fuel;
};


#endif //ADVENTUREFLIGHT_ADVENTUREFLIGHTSETTINGS_H
