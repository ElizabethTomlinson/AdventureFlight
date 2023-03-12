cmake_minimum_required(VERSION 3.24)
project(AdventureFlight)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(AdventureFlight main.cpp CoordinateManager.cpp CoordinateManager.h GeoCoordinate.cpp GeoCoordinate.h Aircraft.cpp Aircraft.h FuelGenerator.cpp FuelGenerator.h Constants.h AdventureFlightGame.cpp AdventureFlightGame.h GameManager.cpp GameManager.h AdventureFlightSettings.cpp AdventureFlightSettings.h)
target_link_libraries(AdventureFlight PRIVATE nlohmann_json::nlohmann_json)
