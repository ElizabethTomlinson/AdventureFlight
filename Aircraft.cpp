//
// Created by elizabeth on 2/26/23.
//

#include "Aircraft.h"

#include <utility>

Aircraft::Aircraft(std::string name): aircraft_name(std::move(name)), fuel(0){

};

std::string Aircraft::name() {
    return this->aircraft_name;
}
