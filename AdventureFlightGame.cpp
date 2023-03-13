//
// Created by elizabeth on 2/26/23.
//

#include <iostream>
#include <sstream>
#include "AdventureFlightGame.h"

AdventureFlightGame::AdventureFlightGame(
        AdventureFlightSettings adventure_flight_settings,
        GeoCoordinate input_coordinates) :
        settings((adventure_flight_settings)), fuel_generator(FuelGenerator()), coords(input_coordinates) {
    this->fuel = settings.getStartingFuel();
}

AdventureFlightGame::AdventureFlightGame(
        AdventureFlightSettings adventure_flight_settings,
        FuelGenerator fuel_generator,
        double fuel,
        GeoCoordinate input_coordinates) :
        settings(adventure_flight_settings),
        fuel_generator(fuel_generator),
        fuel(fuel),
        coords(input_coordinates) {

}

void AdventureFlightGame::addAircraft(const Aircraft &ac) {
    if (this->aircraft.size() < settings.getNumberOfAircraft()) {
        this->aircraft.push_back(ac);
    }
}

std::string AdventureFlightGame::printAircraft() {
    std::string return_val;
    if (this->aircraft.empty()) {
        return "no aircraft added\n";
    }
    return_val += "Current Aircraft: \n";
    for (auto ac: this->aircraft) {
        return_val += ac.name() + "\n";
    }
    return_val += "end of list\n";
    return return_val;
}

double AdventureFlightGame::getCurrentFuel() {
    this->fuel += fuel_generator.emptyReserves();
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

std::string AdventureFlightGame::getGameStatus() {
    std::stringstream buf;
    buf << "Current Fuel is" << std::endl;
    buf << this->getCurrentFuel() << std::endl;
    buf << this->printAircraft() << std::endl;
    buf << "Goal Coordinates are: " << std::endl;
    buf << this->coords.latitude() << " " << this->coords.longitude() << std::endl;
    return buf.str();
}

std::string AdventureFlightGame::outputBareCoords() {
    std::stringstream buf;
    buf << this->coords.latitude() << " " << this->coords.longitude() << std::endl;
    return buf.str();
}

void AdventureFlightGame::addNewLeg(const TripLeg &leg) {
    legs.push_back(leg);
}

std::string AdventureFlightGame::getOrigin() {
    if (legs.empty()) {
        return ORIGIN_SEATTLE;
    } else {
        return legs.at(0).getFrom();
    }
}

std::string AdventureFlightGame::getLastLocation() {
    if (legs.empty()) {
        return ORIGIN_SEATTLE;
    } else {
        return legs.at(legs.size() - 1).getTo();
    }
}

void AdventureFlightGame::printLastLeg() {
    if (!legs.empty()) {
        legs.at(legs.size() - 1).printLeg(legs.size());
    }
}

void AdventureFlightGame::printAllLegs() {
    TripLeg::printHeader();
    for (int i = 0; i < legs.size(); ++i) {
        legs.at(i).printLeg(i + 1);
    }
}
