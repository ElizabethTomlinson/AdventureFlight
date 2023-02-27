//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_GEOCOORDINATE_H
#define ADVENTUREFLIGHT_GEOCOORDINATE_H


class GeoCoordinate {
public:
    GeoCoordinate(float lat, float lon);

    double latitude() const;

    double longitude() const;

private:
    GeoCoordinate() : lat(0.0), lon(0.0) {};
    double lat, lon;
};


#endif //ADVENTUREFLIGHT_GEOCOORDINATE_H
