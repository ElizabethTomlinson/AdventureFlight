//
// Created by elizabeth on 3/12/23.
//

#ifndef ADVENTUREFLIGHT_TRIPLEG_H
#define ADVENTUREFLIGHT_TRIPLEG_H


#include <string>
#include <chrono>
#include "Aircraft.h"
#include "JSONConverters.h"

class TripLeg {
public:
    TripLeg() = default;

    TripLeg(std::string from, std::string to, int dist, const Aircraft &aircraft);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TripLeg, from, to, dist, completed_on, aircraft)

    [[nodiscard]] const std::string &getFrom() const {
        return from;
    }

    [[nodiscard]] const std::string &getTo() const {
        return to;
    }

    [[nodiscard]] int getDist() const {
        return dist;
    }

    [[nodiscard]] const std::chrono::time_point<std::chrono::system_clock> &getCompletedOn() const {
        return completed_on;
    }

    [[nodiscard]] const Aircraft &getAircraft() const {
        return aircraft;
    };

    void printLeg(int leg_num);

    static void printHeader();

private:
    std::string from;
    std::string to;
    int dist{};
    std::chrono::time_point<std::chrono::system_clock> completed_on;
    Aircraft aircraft;

};


#endif //ADVENTUREFLIGHT_TRIPLEG_H
