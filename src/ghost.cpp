#include "ghost.h"
#include "resources.h"
#include <queue>
#include <random>
#include <algorithm>

int Ghost::m_lastGhostColor = -1;

//------------------------------------------------------------------------------
char Ghost::getChar() const
{

    return GHOST;
}

//------------------------------------------------------------------------------
Ghost::Ghost(sf::Vector2i pos, float charSize, sf::Vector2f gridOffset)
        : Character(pos, charSize, gridOffset)
{
    m_color = (m_lastGhostColor + 1) % 4;
    m_lastGhostColor = m_color;
    m_movementSpeed = 1;

}

//------------------------------------------------------------------------------
void Ghost::move(const Map &map)
{
    // go to the fastest that not move in other ghosts
    sf::Vector2i pos = fastestToPacman(true, map);
    m_prevPos = m_pos;
    if (pos != sf::Vector2i{-1, -1})
    {
        this->m_pos = pos;
        return;
    }
    // go to the fastest that move in other ghosts
    pos = fastestToPacman(false, map);
    if (pos != sf::Vector2i{-1, -1})
    {

        this->m_pos = pos;
        return;
    }
    this->m_pos = getRandomMove(map);
}

//------------------------------------------------------------------------------
sf::Vector2i Ghost::getRandomMove(const Map &map) const
{
    //for randomness
    std::random_device rd;
    std::mt19937 g(rd());
    sf::Vector2i new_poses[] = {this->m_pos + sf::Vector2i{0, 1},
                                this->m_pos + sf::Vector2i{0, -1},
                                this->m_pos + sf::Vector2i{1, 0},
                                this->m_pos + sf::Vector2i{-1, 0}};

    std::shuffle(new_poses, new_poses + 4, g);
    for (const sf::Vector2i &new_pos: new_poses)
    {
        if (isMoveValid(map, new_pos))
        {
            return new_pos;
        }
    }
    return {0, 0};
}

//------------------------------------------------------------------------------
sf::Vector2i Ghost::fastestToPacman(bool ghost_wall, const Map &map) const
{
    //for randomness
    std::random_device rd;
    std::mt19937 g(rd());

    //create 2D array of cells that not needed to be checked
    bool **ratingTrail = new bool *[map.getColSize() * sizeof(bool *)];
    for (int i = 0; i < map.getRowSize(); ++i)
    {
        ratingTrail[i] = new bool[map.getRowSize() * sizeof(bool)];
    }
    //create a queue of the closest pos to the pacman
    // first one that enter is the closest to the pacman (the pacman itself) and
    // the last one is the rarest that ever enter to the queue
    std::queue<sf::Vector2i> posToCheck;

    //fill the table and add to the queue the pos of the pacman
    for (int i = 0; i < map.getColSize(); ++i)
    {
        for (int j = 0; j < map.getRowSize(); ++j)
        {
            ratingTrail[i][j] =
                    isMoveValid(map, {j, i}) &&
                    (!ghost_wall || map[{j, i}] != GHOST);
            if (map[{j, i}] == SUPER_PACMAN ||
                map[{j, i}] == PACMAN)
            {
                posToCheck.push(sf::Vector2i{j, i});

            }
        }
    }
    // search for the first in the queue that are valid move for the ghost
    while (!posToCheck.empty())
    {
        sf::Vector2i pos = posToCheck.front();
        posToCheck.pop();
        sf::Vector2i new_poses[] = {pos + sf::Vector2i{0, 1},
                                    pos + sf::Vector2i{0, -1},
                                    pos + sf::Vector2i{1, 0},
                                    pos + sf::Vector2i{-1, 0}};

        //shuffle the list for fun (and get random from the fastests)
        std::shuffle(new_poses, new_poses + 4, g);

        for (const sf::Vector2i &new_pos: new_poses)
        {
            if (new_pos == getPos())
            {
                for (int i = 0; i < map.getRowSize(); ++i)
                {
                    delete[] ratingTrail[i];
                }
                delete[] ratingTrail;
                return pos;
            }

            if (isMoveValid(map, new_pos) &&
                ratingTrail[new_pos.y][new_pos.x])
            {
                ratingTrail[new_pos.y][new_pos.x] = false;
                posToCheck.push(new_pos);
            }
        }
    }

    for (int i = 0; i < map.getRowSize(); ++i)
    {
        delete[] ratingTrail[i];
    }
    delete[] ratingTrail;

    return {-1, -1};
}

//------------------------------------------------------------------------------
sf::Sprite Ghost::getSprite() const
{
    sf::Sprite sprite;
    sprite.setTexture(*(const sf::Texture *) Resources::loadResources(Resources::GHOSTS_T));

    // direction of the ghost by the texture (please look at `ghosts.png`)
    int dir = 2;
    if (m_prevPos.y < m_pos.y)
    {
        dir = 1;
    }
    else if (m_prevPos.y > m_pos.y)
    {
        dir = 3;
    }
    else if (m_prevPos.x < m_pos.x)
    {
        dir = 0;
    }
    // look at `ghosts.png` to understand the magic numbers
    sprite.setTextureRect(sf::IntRect(((dir * 2) +((int)(m_interval * 2)))* Resources::GHOST_TS ,m_color * Resources::GHOST_TS, Resources::GHOST_TS, Resources::GHOST_TS));


    return sprite;
}

void Ghost::dontMove()
{
    m_prevPos = m_pos;
}
