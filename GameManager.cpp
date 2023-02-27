//
// Created by elizabeth on 2/26/23.
//

#include <string>
#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "CoordinateManager.h"

void GameManager::startNewGame() {
    delete this->game;
    this->game = new AdventureFlightGame(AdventureFlightSettings(5, 100));
}

void GameManager::runGame() {
    if (this->game == nullptr) {
        std::cout << "No game has been started" << std::endl;
        exit(1);
    }
    std::string cmd;
    while (cmd != "exit") {
        printStateOutput();
        cmd = updateGameState();
    }
}

std::string GameManager::readNextCommand() {
    std::string cmd;
    getline(std::cin, cmd);
    return cmd;
}

/**
 * @TODO: Don't have this nastyness here
 * @param cmd
 */
std::string GameManager::updateGameState() {
    std::string cmd = readNextCommand();
    if (this->next_action == ADD_AIRCRAFT) {
        this->game->addAircraft(Aircraft(cmd));
        next_action = AIRCRAFT_CONFIRMATION;
    } else if (next_action == SAVE) {
        this->save(cmd);
        next_action = MAIN;
    } else if (next_action == LOAD) {
        this->load(cmd);
        next_action = MAIN;
    } else if (cmd == "get fuel") {
        std::cout << "current Fuel: " << game->getCurrentFuel() << std::endl;
        next_action = MAIN;
    } else if (cmd == "add aircraft") {
        this->next_action = ADD_AIRCRAFT;
    } else if (cmd == "status") {
        next_action = STATUS;
    } else if (cmd == "get coords") {
        auto coord_manager = CoordinateManager(3);
        auto coords = coord_manager.getRandomCoords();
        for (auto coord: coords) {
            std::cout << coord.latitude() << " " << coord.longitude() << std::endl;
        }
        next_action = MAIN;
    } else if (cmd == "save") {
        next_action = SAVE;
    } else if (cmd == "load") {
        next_action = LOAD;
    }
    return cmd;
}

void GameManager::printStateOutput() {
    if (next_action == START) {
        std::cout << "Welcome to AdventureFlight! Please enter command:" << std::endl;
    } else if (next_action == ADD_AIRCRAFT) {
        std::cout << "which aircraft would you like to add?" << std::endl;
    } else if (next_action == MAIN) {
        std::cout << "Please Enter Command:" << std::endl;
    } else if (next_action == AIRCRAFT_CONFIRMATION) {
        std::cout << game->printAircraft();
        next_action = MAIN;
    } else if (next_action == SAVE) {
        std::cout << "Enter file name" << std::endl;
    } else if (next_action == LOAD) {
        std::cout << "Please enter file name" << std::endl;
    } else if (next_action == STATUS) {
        std::cout << "Current Fuel is" << std::endl;
        std::cout << this->game->getCurrentFuel() << std::endl;
        std::cout << this->game->printAircraft() << std::endl;
        next_action = MAIN;
    } else {
        next_action = MAIN;
    }
}

void GameManager::save(const std::filesystem::path &path) {
    std::ofstream save_file(path);
    save_file << game->printAircraft();
    save_file << game->getCurrentFuel() << std::endl;
    save_file << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    save_file.close();
}

void GameManager::load(const std::filesystem::path &path) {
    std::ifstream save_file(path);
    std::string line;
    bool aircraft = false;
    bool fuel = false;
    double fuel_val = 0;
    std::vector<Aircraft> aircraft_vector;
    std::chrono::duration<int> dur{};
    while (getline(save_file, line)) {
        if (line == "Current Aircraft: ") {
            continue;
        } else if (line == "end of list") {
            aircraft = true;
        } else if (!aircraft) {
            aircraft_vector.emplace_back(line);
        } else if (!fuel) {
            fuel_val = std::stod(line);
            fuel = true;
        } else {
            long num = std::stol(line);
            dur = std::chrono::duration<long>(num);
        }
    }
    delete this->game;
    this->game = new AdventureFlightGame(
            AdventureFlightSettings(
                    5,
                    0),
            FuelGenerator(
                    DEFAULT_FUEL_GENERATION_RATE,
                    std::chrono::time_point<std::chrono::system_clock>(dur)),
            fuel_val);
    for (auto ac: aircraft_vector) {
        this->game->addAircraft(ac);
    }
}

GameManager::~GameManager() {
    delete this->game;
}
