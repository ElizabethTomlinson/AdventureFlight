//
// Created by elizabeth on 2/26/23.
//

#include "CoordinateManager.h"

CoordinateManager::CoordinateManager(int num_options) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);

        std::uniform_real_distribution<float> lat_distro(0.0, 90.0);
        std::uniform_real_distribution<float> lon_distro(0.0, 180.0);
        std::uniform_int_distribution prefix_distro(0, 1);
        for (int i = 0; i < num_options; ++i) {
            float lat_pre = prefix_distro(generator) == 0 ? -1.0f : 1.0f;
            float lon_pre = prefix_distro(generator) == 0 ? -1.0f : 1.0f;
            float lat = lat_pre * lat_distro(generator);
            float lon = lon_pre * lon_distro(generator);
            random_coords.emplace_back(lat, lon);
        }
}

std::vector<GeoCoordinate> CoordinateManager::getRandomCoords() {
    return this->random_coords;
}
