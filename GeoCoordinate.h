//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_GEOCOORDINATE_H
#define ADVENTUREFLIGHT_GEOCOORDINATE_H


class GeoCoordinate {
public:
    GeoCoordinate() : lat(0.0), lon(0.0) {};

    GeoCoordinate(double lat, double lon);

    [[nodiscard]] double latitude() const;

    [[nodiscard]] double longitude() const;

private:

    double lat, lon;
};


#endif //ADVENTUREFLIGHT_GEOCOORDINATE_H
