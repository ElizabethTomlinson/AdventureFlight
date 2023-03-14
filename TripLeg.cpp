//
// Created by elizabeth on 3/12/23.
//

#include "TripLeg.h"

#include <utility>
#include <iostream>

TripLeg::TripLeg(std::string from, std::string to, int dist, const Aircraft &aircraft) :
        from(std::move(from)),
        to(std::move(to)),
        dist(dist),
        aircraft(aircraft),
        completed_on(std::chrono::system_clock::now()) {
}

void TripLeg::printLeg(int leg_num) {
    auto comp_time = std::chrono::system_clock::to_time_t(completed_on);
    auto time = std::localtime(&comp_time);
    printf("%3d | %s -> %s | %4d | %02d/%02d/%02d | %s\n",
           leg_num,
           from.c_str(),
           to.c_str(),
           dist,
           time->tm_mon + 1,
           time->tm_mday,
           time->tm_year - 100,
           aircraft.name().c_str());
}

void TripLeg::printHeader() {
    std::cout << "Leg | From -> To   | Dist | Comp. On | Aircraft" << std::endl;
}
