#pragma once

#include <SFML/Graphics.hpp>
/***
 * @brief A class that represents a game object on the board
 */
struct GameObject
{   //single texture constructor
    GameObject(char symbol, const char *filename) :
            m_symbol(symbol)
    {
        m_texture_board.loadFromFile(filename);
        m_texture_tool = m_texture_board;
    }
    //two textures constructor for objects that have different textures for the board and the tool
    GameObject(char symbol, const char *filename_board, const char *filename_preview) :
            m_symbol(symbol)
    {
        m_texture_board.loadFromFile(filename_board);
        m_texture_tool.loadFromFile(filename_preview);
    }

    char m_symbol;
    sf::Texture m_texture_tool;
    sf::Texture m_texture_board;
};