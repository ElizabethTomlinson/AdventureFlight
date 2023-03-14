//
// Created by elizabeth on 3/12/23.
//

#ifndef ADVENTUREFLIGHT_JSONCONVERTERS_H
#define ADVENTUREFLIGHT_JSONCONVERTERS_H

#include <nlohmann/json.hpp>

namespace nlohmann {
    template<>
    struct adl_serializer<std::chrono::time_point<std::chrono::system_clock> > {
        static void to_json(json &j, const std::chrono::time_point<std::chrono::system_clock> &timePoint) {
            j = std::chrono::system_clock::to_time_t(timePoint);
        }

        static void from_json(const json &j, std::chrono::time_point<std::chrono::system_clock> &timePoint) {
            timePoint = std::chrono::time_point<std::chrono::system_clock>(std::chrono::duration<long>(j.get<long>()));

        }
    };
}
#endif //ADVENTUREFLIGHT_JSONCONVERTERS_H
