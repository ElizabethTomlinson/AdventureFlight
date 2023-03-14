//
// Created by elizabeth on 2/26/23.
//

#ifndef ADVENTUREFLIGHT_GAMEMANAGER_H
#define ADVENTUREFLIGHT_GAMEMANAGER_H


#include <filesystem>
#include "AdventureFlightGame.h"
#include <nlohmann/json.hpp>

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
        CONTINUE,
        COMPLETE_LEG,
        START_NEW_LEG,
        PRINT_LEGS
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

    void loadNewGame();

private:
    Action next_action;
    AdventureFlightGame *game;
    std::filesystem::path path;
    std::string tmp_dest;
    int tmp_dist;

    void printCurrentFuel();

    std::pair<bool, std::string> processNextAction(const std::string &cmd);

    bool processCommand(const std::string &cmd);

    void completeLeg(const std::string &cmd);


    void startLeg(const std::string &cmd);
};

#endif //ADVENTUREFLIGHT_GAMEMANAGER_H
