cmake_minimum_required(VERSION 3.24)
project(AdventureFlight)

set(CMAKE_CXX_STANDARD 17)

add_executable(AdventureFlight main.cpp CoordinateManager.cpp CoordinateManager.h GeoCoordinate.cpp GeoCoordinate.h Aircraft.cpp Aircraft.h FuelGenerator.cpp FuelGenerator.h Constants.h AdventureFlightGame.cpp AdventureFlightGame.h GameManager.cpp GameManager.h AdventureFlightSettings.cpp AdventureFlightSettings.h)
