//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_GEOCOORDINATE_H
#define ADVENTUREFLIGHT_GEOCOORDINATE_H

#include <nlohmann/json.hpp>

class GeoCoordinate {
public:
    GeoCoordinate() : lat(0.0), lon(0.0) {};

    GeoCoordinate(double lat, double lon);

    [[nodiscard]] double latitude() const;

    [[nodiscard]] double longitude() const;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GeoCoordinate, lat, lon);
private:

    double lat, lon;
};


#endif //ADVENTUREFLIGHT_GEOCOORDINATE_H
