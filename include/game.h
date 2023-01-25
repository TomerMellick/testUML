#pragma once

#include "result.h"
#include "map.h"
#include <map>
#include "pacman.h"
#include "ghost.h"
#include "board.h"
#include <vector>

class Game
{
private:
   
    /**
     * the size of the map of the game
     */
    unsigned int m_gridSize;
    
    /**
     * the maps (from the file)
     */
    std::vector<Map> m_maps;


    /**
     * the result of the game
     */
    Result m_res;

    /**
     * map of the score for each char that can be eat
     */
    static const std::map<char, int> SCORE_DICT;
    
    sf::RenderWindow m_window;
    
    /**
     * print the game status when end and wait for `esc` key
     */


public:
    Game(const char *mapName);

    /**
     * start a game
     * @return the result of the game
     */
    Result startGame();

};
