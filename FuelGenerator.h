//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_FUELGENERATOR_H
#define ADVENTUREFLIGHT_FUELGENERATOR_H

#include <chrono>
#include "Constants.h"
#include <nlohmann/json.hpp>
#include "JSONConverters.h"

class FuelGenerator {
public:
    explicit FuelGenerator(double fuel_generation_rate);
    FuelGenerator(double fuel_generation_rate, std::chrono::time_point<std::chrono::system_clock> start);
    FuelGenerator() : FuelGenerator(DEFAULT_FUEL_GENERATION_RATE){}
    void updateFuel();
    double emptyReserves();
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FuelGenerator, fuel_reserves, last, fuel_generation_rate, points);
private:
    double fuel_reserves;
    std::chrono::time_point<std::chrono::system_clock> last;
    double fuel_generation_rate;
    std::vector<std::chrono::time_point<std::chrono::system_clock>> points;
};


#endif //ADVENTUREFLIGHT_FUELGENERATOR_H
