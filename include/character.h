#pragma once


#include "map.h"
#include <sfml/Graphics.hpp>


class Character : public sf::Drawable
{
protected:

    sf::Vector2i m_pos;
    sf::Vector2i m_prevPos;
    sf::Vector2i m_originalPos;
    float m_charSize;
    double m_interval;
    sf::Vector2f m_gridOffset;
    int m_movementSpeed = 1;

    virtual sf::Sprite getSprite() const =0 ;

public:
    Character(sf::Vector2i pos,float charSize, sf::Vector2f gridOffset);

    void drawOnMap(Map &map) const;

    /**
     * the character move algorithm
     * need to be implemented in sub-classes
     * @param map the algorithm may need the map
     */
    virtual void move(const Map &map) = 0;

    /**
     * draw the character on a map
     * @param map the map to draw on
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * get the character position
     * @return the character position
     */
    sf::Vector2i getPos() const;

    /**
     * get the character last (before the one its go into) position
     * @return the character position
     */
     sf::Vector2i getPrevPos() const;

    /**
     * reset the position of the character
     * (for example when the pacman interact with the ghosts)
     */
    void resetPos();

    /**
     * get the char of the character
     * need to be implemented in sub-classes
     * @return the char of the character
     */
    virtual char getChar() const = 0;

    /**
     * check if the move valid (for all character also checks for super)
     * @param map the map to check if the move valid
     * @param pos the position to check if its valid on the map
     * @return is the pos is a move that a regular character can do
     */
    bool isMoveValid(const Map &map, const sf::Vector2i &pos) const;

    void setInterval(float interval);

    int getMovmentSpeed() const;
};

const char GHOST = '&';
const char PACMAN = 'a';
const char SUPER_PACMAN = '@';
