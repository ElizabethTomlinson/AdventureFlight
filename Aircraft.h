//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_AIRCRAFT_H
#define ADVENTUREFLIGHT_AIRCRAFT_H

#include <string>
#include <nlohmann/json.hpp>

class Aircraft {
public:
    Aircraft() = default;
    explicit Aircraft(std::string name);

    Aircraft(const Aircraft &) = default;

    std::string name();

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Aircraft, aircraft_name, fuel);
private:
    float fuel;
    std::string aircraft_name;
};


#endif //ADVENTUREFLIGHT_AIRCRAFT_H
