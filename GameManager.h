//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_GAMEMANAGER_H
#define ADVENTUREFLIGHT_GAMEMANAGER_H


#include <filesystem>
#include "AdventureFlightGame.h"

class GameManager {
    enum Action {
        ADD_AIRCRAFT,
        START,
        STATUS,
        MAIN,
        AIRCRAFT_CONFIRMATION,
        SAVE,
        LOAD,
        REMOVE_FUEL,
        ADD_FUEL,
        CONTINUE
    };
public:
    GameManager() : game(nullptr), next_action(START) {};

    ~GameManager();

    void startNewGame();

    void runGame();

    std::string updateGameState();

    void printStateOutput();

    static std::string readNextCommand();

    void save(const std::filesystem::path &path);

    void save();

    void load(const std::filesystem::path &path);

private:
    Action next_action;
    AdventureFlightGame *game;
    std::filesystem::path path;

    void printCurrentFuel();
};

#endif //ADVENTUREFLIGHT_GAMEMANAGER_H
