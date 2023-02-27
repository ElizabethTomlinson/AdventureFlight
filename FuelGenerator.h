//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_FUELGENERATOR_H
#define ADVENTUREFLIGHT_FUELGENERATOR_H

#include <chrono>
#include "Constants.h"

class FuelGenerator {
public:
    explicit FuelGenerator(double fuel_generation_rate);
    FuelGenerator(double fuel_generation_rate, std::chrono::time_point<std::chrono::system_clock> start);
    FuelGenerator() : FuelGenerator(DEFAULT_FUEL_GENERATION_RATE){}
    void updateFuel();
    double emptyReserves();
private:
    double fuel_reserves;
    std::chrono::time_point<std::chrono::system_clock> last;
    double fuel_generation_rate;
};


#endif //ADVENTUREFLIGHT_FUELGENERATOR_H
