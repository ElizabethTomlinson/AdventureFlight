//
// Created by elizabeth on 2/26/23.
//

#include <iostream>
#include "AdventureFlightGame.h"

AdventureFlightGame::AdventureFlightGame(AdventureFlightSettings adventure_flight_settings) :
        settings((adventure_flight_settings)), fuelGenerator(FuelGenerator()) {
}

AdventureFlightGame::AdventureFlightGame(AdventureFlightSettings adventure_flight_settings, FuelGenerator fuelGenerator,
                                         double fuel) :
        settings(adventure_flight_settings),
        fuelGenerator(fuelGenerator),
        fuel(fuel) {

}

void AdventureFlightGame::addAircraft(Aircraft ac) {
    if (this->aircraft.size() < settings.getNumberOfAircraft()) {
        this->aircraft.push_back(ac);
    }
}

std::string AdventureFlightGame::printAircraft() {
    std::string return_val;
    if (this->aircraft.empty()) {
        return "no aircraft added\n";
    }
    return_val +=  "Current Aircraft: \n";
    for (auto ac: this->aircraft) {
        return_val += ac.name() + "\n";
    }
    return_val += "end of list\n";
    return return_val;
}

double AdventureFlightGame::getCurrentFuel() {
    this->fuel += fuelGenerator.emptyReserves();
    return this->fuel;
}

void AdventureFlightGame::removeFuel(double amount) {
    double current_amount = this->getCurrentFuel();
    if (amount > current_amount) {
        std::cout << "Cannot remove that much fuel" << std::endl;
        return;
    }
    this->fuel -= amount;
}

void AdventureFlightGame::addFuel(double amount) {
    this->fuel += amount;
}



