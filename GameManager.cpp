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
    std::string cmd;
    while (!this->game && cmd != "exit") {
        auto coord_manager = CoordinateManager(5);
        auto coords = coord_manager.getRandomCoords();
        std::cout << "Choose the coordinates:" << std::endl;
        for (int i = 0; i < coords.size(); ++i) {
            std::cout << i + 1 << ": " << std::fixed << std::setprecision(8) << coords[i].latitude() << " "
                      << coords[i].longitude() << std::endl;
        }

        cmd = readNextCommand();
        if (cmd == "none") {
            std::cout << "Printing new coordinates..." << std::endl;
            continue;
        }
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
 * @TODO: Clean this up some more.
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
    } else if (cmd == "load") {
        loadNewGame();
    } else if (this->game == nullptr) {
        this->next_action = START;
    } else if (processNextAction(cmd).first) {
        return cmd;
    } else if (processCommand(cmd)) {
        return cmd;
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
        std::cout << std::setprecision(8) << this->game->getGameStatus();
        next_action = CONTINUE;
    } else if (next_action == REMOVE_FUEL) {
        std::cout << "Enter the amount to remove. Current fuel: " << this->game->getCurrentFuel() << std::endl;
    } else if (next_action == ADD_FUEL) {
        std::cout << "Enter the amount to add" << std::endl;
    } else if (next_action == COMPLETE_LEG) {
        std::cout << "Enter Destination: (Planned Destination: " << tmp_dest << ")" << std::endl;
    } else if (next_action == PRINT_LEGS) {
        game->printAllLegs();
        next_action = CONTINUE;
    } else if (next_action == START_NEW_LEG) {
        std::cout << "Enter Planned Destination" << std::endl;
    } else {
        next_action = MAIN;
    }
}

void GameManager::save(const std::filesystem::path &path_) {
    nlohmann::json j = *game;
    std::ofstream of(path_);
    if (of.is_open()) {
        path = path_;
    }
    of << j.dump(4);
}

void GameManager::save() {
    if (!this->path.empty()) {
        this->save(this->path);
    }
}

void GameManager::load(const std::filesystem::path &path_) {
    this->path = path_;
    std::ifstream save_file(path);
    nlohmann::json loaded_game_data = nlohmann::json::parse(save_file);
    delete this->game;
    game = new AdventureFlightGame(loaded_game_data.get<AdventureFlightGame>());
}

GameManager::~GameManager() {
    delete this->game;
}

std::pair<bool, std::string> GameManager::processNextAction(const std::string &cmd) {
    bool processed = false;
    if (this->next_action == ADD_AIRCRAFT) {
        this->game->addAircraft(Aircraft(cmd));
        this->save();
        next_action = AIRCRAFT_CONFIRMATION;
        processed = true;
    } else if (next_action == SAVE) {
        this->save(cmd);
        next_action = MAIN;
        processed = true;
    } else if (next_action == LOAD) {
        this->load(cmd);
        next_action = MAIN;
        processed = true;
    } else if (next_action == REMOVE_FUEL) {
        double amount = std::stod(cmd);
        this->game->removeFuel(amount);
        this->save();
        printCurrentFuel();
        next_action = MAIN;
        processed = true;
    } else if (next_action == ADD_FUEL) {
        double amount = std::stod(cmd);
        this->game->addFuel(amount);
        this->save();
        printCurrentFuel();
        next_action = CONTINUE;
        processed = true;
    } else if (next_action == COMPLETE_LEG) {
        completeLeg(cmd);
        save();
        next_action = CONTINUE;
        processed = true;
    } else if (next_action == START_NEW_LEG) {
        startLeg(cmd);
        save();
        printCurrentFuel();
        next_action = MAIN;
        processed = true;
    }
    return {processed, cmd};
}

void GameManager::startLeg(const std::string &cmd) {
    tmp_dest = cmd;
    std::cout << "Enter planned distance: " << std::endl;
    tmp_dist = std::stoi(readNextCommand());
    std::cout << "Enter the amount to load. Current fuel: " << game->getCurrentFuel() << std::endl;
    double amount = std::stod(cmd);
    game->removeFuel(amount);
}

void GameManager::completeLeg(const std::string &cmd) {
    const std::string &dest = cmd;
    std::cout << "Enter Distance: (est. " << tmp_dist << ")" << std::endl;
    int dist = std::stoi(readNextCommand());
    std::cout << game->printAircraft();
    std::cout << "Enter Aircraft: " << std::endl;
    Aircraft aircraft(readNextCommand());
    std::cout << "Enter the amount of fuel remaining" << std::endl;
    double amount = std::stod(readNextCommand());
    game->addFuel(amount);
    std::string from = game->getLastLocation();
    game->addNewLeg(TripLeg(from, dest, dist, aircraft));
}

bool GameManager::processCommand(const std::string &cmd) {
    if (cmd == "get fuel") {
        printCurrentFuel();
        next_action = MAIN;
        return true;
    }
    if (cmd == "add aircraft") {
        this->next_action = ADD_AIRCRAFT;
        return true;
    }
    if (cmd == "status") {
        next_action = STATUS;
        return true;
    }
    if (cmd == "get coords") {
        auto coord_manager = CoordinateManager(3);
        auto coords = coord_manager.getRandomCoords();
        for (auto coord: coords) {
            std::cout << std::fixed << std::setprecision(8) << coord.latitude() << " " << coord.longitude()
                      << std::endl;
        }
        next_action = CONTINUE;
        return true;
    }
    if (cmd == "save") {
        next_action = SAVE;
        return true;
    }
    if (cmd == "load") {
        next_action = LOAD;
        return true;
    }
    if (cmd == "remove fuel") {
        next_action = REMOVE_FUEL;
        return true;
    }
    if (cmd == "start leg") {
        next_action = START_NEW_LEG;
        return true;
    }
    if (cmd == "add fuel") {
        next_action = ADD_FUEL;
        return true;
    }
    if (cmd == "complete leg") {
        next_action = COMPLETE_LEG;
        return true;
    }
    if (cmd == "print legs") {
        next_action = PRINT_LEGS;
        return true;
    }
    return false;
}

void GameManager::loadNewGame() {
    delete this->game;
    std::string cmd;
    while (!this->game && cmd != "exit") {
        std::cout << "Enter Filename:" << std::endl;
        cmd = readNextCommand();
        try {
            load(cmd);
            next_action = STATUS;
        } catch (...) {
            std::cout << "Could not load game" << std::endl;
        }

    }
}
