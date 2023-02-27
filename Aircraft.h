//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_AIRCRAFT_H
#define ADVENTUREFLIGHT_AIRCRAFT_H

#import <string>

class Aircraft {
public:
    explicit Aircraft(std::string name);

    std::string name();


private:
    float fuel;
    std::string aircraft_name;
};


#endif //ADVENTUREFLIGHT_AIRCRAFT_H
