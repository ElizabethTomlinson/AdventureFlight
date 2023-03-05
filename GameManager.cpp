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

    auto coord_manager = CoordinateManager(3);
    auto coords = coord_manager.getRandomCoords();
    std::cout << "Choose the coordinates:" << std::endl;
    for (int i = 0; i < coords.size(); ++i) {
        std::cout << i + 1 << ": " << coords[i].latitude() << " " << coords[i].longitude() << std::endl;
    }
    std::string cmd;
    while (!this->game && cmd != "exit") {
        cmd = readNextCommand();
        if (cmd != "exit") {
            int num = std::stoi(cmd);
            this->game = new AdventureFlightGame(AdventureFlightSettings(
                                                         AIRCRAFT_NUM,
                                                         DEFAULT_INITIAL_FUEL),
                                                 coords.at(num - 1));
            this->next_action = STATUS;
        } else {
            exit(0);
        }
    }
}

void GameManager::runGame() {
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
 * @TODO: Don't have this nastiness here. Implement better state machine.
 */
std::string GameManager::updateGameState() {
    if (this->next_action == CONTINUE) {
        this->next_action = MAIN;
        std::cout << std::endl;
        return "continue";
    }
    std::string cmd = readNextCommand();
    if (cmd == "start") {
        startNewGame();
    } else if (this->game == nullptr) {
        this->next_action = START;
    } else if (this->next_action == ADD_AIRCRAFT) {
        this->game->addAircraft(Aircraft(cmd));
        this->save();
        next_action = AIRCRAFT_CONFIRMATION;
    } else if (next_action == SAVE) {
        this->save(cmd);
        next_action = MAIN;
    } else if (next_action == LOAD) {
        this->load(cmd);
        next_action = MAIN;
    } else if (next_action == REMOVE_FUEL) {
        double amount = std::stod(cmd);
        this->game->removeFuel(amount);
        this->save();
        printCurrentFuel();
        next_action = MAIN;
    } else if (next_action == ADD_FUEL) {
        double amount = std::stod(cmd);
        this->game->addFuel(amount);
        this->save();
        printCurrentFuel();
        next_action = CONTINUE;
    } else if (cmd == "get fuel") {
        printCurrentFuel();
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
        next_action = CONTINUE;
    } else if (cmd == "save") {
        next_action = SAVE;
    } else if (cmd == "load") {
        next_action = LOAD;
    } else if (cmd == "remove fuel") {
        next_action = REMOVE_FUEL;
    } else if (cmd == "add fuel") {
        next_action = ADD_FUEL;
    }
    return cmd;
}

void GameManager::printCurrentFuel() { std::cout << "Current Fuel: " << game->getCurrentFuel() << std::endl; }

void GameManager::printStateOutput() {
    if (next_action == START) {
        std::cout << "Welcome to AdventureFlight! No game is loaded. To start a new game, type start" << std::endl;
    } else if (next_action == ADD_AIRCRAFT) {
        std::cout << "Which aircraft would you like to add?" << std::endl;
    } else if (next_action == MAIN) {
        std::cout << "Please Enter Command:" << std::endl;
    } else if (next_action == AIRCRAFT_CONFIRMATION) {
        std::cout << game->printAircraft();
        next_action = CONTINUE;
    } else if (next_action == SAVE) {
        std::cout << "Enter file name" << std::endl;
    } else if (next_action == LOAD) {
        std::cout << "Please enter file name" << std::endl;
    } else if (next_action == STATUS) {
        std::cout << this->game->getGameStatus();
        next_action = CONTINUE;
    } else if (next_action == REMOVE_FUEL) {
        std::cout << "Enter the amount to remove" << std::endl;
    } else if (next_action == ADD_FUEL) {
        std::cout << "Enter the amount to add" << std::endl;
    } else {
        next_action = MAIN;
    }
}

void GameManager::save(const std::filesystem::path &path) {
    this->path = path;
    std::ofstream save_file(path);
    save_file << game->printAircraft();
    save_file << game->getCurrentFuel() << std::endl;
    save_file << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    save_file << game->outputBareCoords() << std::endl;
    save_file.close();
}

void GameManager::save() {
    if (!this->path.empty()) {
        this->save(this->path);
    }
}

void GameManager::load(const std::filesystem::path &path) {
    this->path = path;
    std::ifstream save_file(path);
    std::string line;
    bool aircraft = false;
    bool fuel = false;
    double fuel_val = 0;
    bool time = false;
    GeoCoordinate coordinate;
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
        } else if (!time) {
            long num = std::stol(line);
            dur = std::chrono::duration<long>(num);
            time = true;
        } else {
            std::stringstream ss;
            ss << line;
            std::string lat_string, lon_string;
            ss >> lat_string;
            ss >> lon_string;
            double lat = std::stod(lat_string);
            double lon = std::stod(lon_string);
            coordinate = GeoCoordinate(lat, lon);
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
            fuel_val,
            coordinate);
    for (const auto &ac: aircraft_vector) {
        this->game->addAircraft(ac);
    }
}

GameManager::~GameManager() {
    delete this->game;
}
