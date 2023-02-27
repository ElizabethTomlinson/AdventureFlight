//
// Created by elizabeth on 2/26/23.
//

#include "FuelGenerator.h"

FuelGenerator::FuelGenerator(double fuel_generation_rate):
last(std::chrono::system_clock::now()),
fuel_generation_rate(fuel_generation_rate),
fuel_reserves(0.0) {
}

FuelGenerator::FuelGenerator(double fuel_generation_rate, std::chrono::time_point<std::chrono::system_clock> start):
        fuel_generation_rate(fuel_generation_rate), last(start), fuel_reserves(0){

}

void FuelGenerator::updateFuel() {
    auto curr = std::chrono::system_clock::now();
    std::chrono::duration<double> duration =  curr - last;
    fuel_reserves += fuel_generation_rate * duration.count();
    last = curr;
}

double FuelGenerator::emptyReserves() {
    this->updateFuel();
    double reserves = this->fuel_reserves;
    this->fuel_reserves = 0;
    return reserves;
}


