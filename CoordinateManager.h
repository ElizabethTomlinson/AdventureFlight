//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_COORDINATEMANAGER_H
#define ADVENTUREFLIGHT_COORDINATEMANAGER_H

#include <vector>
#include <array>
#include "GeoCoordinate.h"
#include <random>
#include <chrono>

class CoordinateManager {
public:
    explicit CoordinateManager(int num_options);

    std::vector<GeoCoordinate> getRandomCoords();

private:
    std::vector<GeoCoordinate> random_coords;
};

#endif //ADVENTUREFLIGHT_COORDINATEMANAGER_H
