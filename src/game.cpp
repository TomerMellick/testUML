#include <iostream>
#include <fstream>
#include "map.h"
#include "game.h"
#include "board.h"
#include "io.h"
#include "round.h"


//------------------------------------------------------------------------------
Game::Game(const char *mapName) : m_res({false, 0})
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    m_gridSize = desktop.height - 250;
    m_window.create({m_gridSize, desktop.height - 150}, "SuperPacman",
                    sf::Style::Titlebar | sf::Style::Close);
    std::ifstream map_file(mapName);
    int width, height;
    int time;

    while (map_file >> time >> width >> height)
    {
        m_maps.emplace_back(width, height, time);
        Map &map = m_maps[m_maps.size() - 1];
        for (int i = 0; i < map.getColSize(); ++i)
        {
            for (int j = 0; j < map.getRowSize(); ++j)
            {
                char c;
                do
                {
                    c = (char) map_file.get();
                } while (c == '\n' || c == '\r');
                map(j, i) = c;
            }
        }
    }
    m_window.setFramerateLimit(60);

}

//------------------------------------------------------------------------------
Result Game::startGame()
{
    m_res.m_win = true;
    for (size_t i = 0; i < m_maps.size(); ++i)
    {
        Round r(m_maps[i], &m_window, {0, 150},
                {(float) m_gridSize, (float) m_gridSize}, (int) i + 1,
                m_res.m_score);

        m_res = r.startRound();

        if (!m_res.m_win)
        {
            break;
        }
    }

    return m_res;
}

//------------------------------------------------------------------------------

