#pragma once

#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "character.h"
#include "pacman.h"
#include "ghost.h"
#include "result.h"
#include "Board.h"

class Round
{
private:
    int m_level;
    Board m_board;
    Pacman m_pacman;
    std::vector<Ghost> m_ghosts;
    std::vector<Character *> m_characters;
    float m_cellSize;
    sf::Vector2f m_gridSize;
    sf::Vector2f m_gridOffset;
    sf::RenderWindow *m_window;
    int m_freezeRoundRemain;
    sf::Clock m_roundClock;
    Result m_result{};


    void handleEvents();

    std::string getStatisticalData() const;

    Ghost *getCollision();

    void handleCollision();

    void draw();

    Map getMap() const;

    
    const static std::map<char, std::tuple<int,const sf::SoundBuffer *, std::function<void(Round*)>>>
                          dataDict;

public:
    Round(const Map &map,
          sf::RenderWindow *window,
          const sf::Vector2f &gridOffset,
          const sf::Vector2f &gridSize,
          int level,
          int score);

    Result startRound();
};