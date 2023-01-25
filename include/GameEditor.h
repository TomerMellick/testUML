#pragma once

#include "GameObject.h"
#include "CharMatrix.h"
#include "MainWindow.h"
#include <fstream>

/***
 * GameEditor class is the main class of the game editor
 * it is responsible for the main loop of the game editor
 * and for the saving and loading of the board
 */
class GameEditor
{
public:
    GameEditor();

    void run();

private:
    //vector of all the game objects in the game
    std::vector<GameObject> m_game_objects;

    //function to save the game objects to a file
    void save(const CharMatrix &matrix);

    //function to restart editing the board
    void start_new();

    bool m_re_run;

};



