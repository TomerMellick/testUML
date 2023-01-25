#pragma once

#include <SFML/Graphics.hpp>
#include "character.h"



class Ghost : public Character
{
private:
    static int m_lastGhostColor;
    int m_color;
    sf::Texture m_ghostTexture;

    /**
     * get the shortest trail to the pacman
     * @param ghost_wall is a ghost consider as wall 
     * @param map the map to check on
     * @return the position near to the that in the shortest trail to the pacman
     */
    sf::Vector2i fastestToPacman(bool ghost_wall, const Map &map) const;

    /**
     * get a random (and valid) move
     * @param map the map to check a valid move from
     * @return the valid move
     */
    sf::Vector2i getRandomMove(const Map &map) const;


public:
    Ghost(sf::Vector2i pos, float charSize, sf::Vector2f gridOffset);

    /**
     * move the character
     * @param map move the character by the map 
     */
    void move(const Map &map) override;

    /**
     * get the char (`&`)
     * @return always a '&'
     */
    char getChar() const override;


    sf::Sprite getSprite() const override;

    void dontMove();
};