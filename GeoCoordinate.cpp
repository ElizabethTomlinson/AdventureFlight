//
// Created by elizabeth on 2/26/23.
//
#include <stdexcept>
#include "GeoCoordinate.h"

GeoCoordinate::GeoCoordinate(float lat, float lon) : lat(lat), lon(lon) {
    if (lat > 90.0f || lat < -90.0f) {
        throw std::invalid_argument("Latitude must be between -90 and 90");
    }
    if (lon > 180.0f || lon < -180.0f) {
        throw std::invalid_argument("Longitude must be between -180 and 180");
    }
}

double GeoCoordinate::latitude() const {
    return this->lat;
}

double GeoCoordinate::longitude() const {
    return this->lon;
}
