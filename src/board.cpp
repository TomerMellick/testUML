#include <SFML/Graphics.hpp>
#include "resources.h"
#include "board.h"

const StaticObject Board::MAP_CHARS[NUM_OF_STATIC_OBJECTS] = {
        {WALL,           Resources::WALL_T},
        {DOOR,           Resources::DOOR_T},
        {KEY,            Resources::KEY_T},
        {COOKIE,         Resources::COOKIE_T},
        {GIFT_ADD_LIFE,  Resources::GIFT_ADD_LIFE_T},
        {GIFT_ADD_TIME,  Resources::GIFT_ADD_TIME_T},
        {GIFT_FREEZE,    Resources::GIFT_FREEZE_T},
        {GIFT_SUPER,     Resources::GIFT_SUPER_T},
        {' ',            Resources::EMPTY_T}
};

//------------------------------------------------------------------------------
Board::Board(const Map &startingMap, sf::Vector2f gridSize, sf::Vector2f gridOffset)
        : m_map(startingMap),
          m_numOfCookies(0),
          m_gridSize(gridSize),
          m_gridOffset(gridOffset)
{
    for (int i = 0; i < this->m_map.getColSize(); ++i)
    {
        for (int j = 0; j < this->m_map.getRowSize(); ++j)
        {
            if (!isMapChar(this->m_map(j, i)))
            {
                this->m_map(j, i) = ' ';
            }
            if (this->m_map(j, i) == COOKIE)
            {
                m_numOfCookies++;
            }
        }
    }

}

//------------------------------------------------------------------------------
char Board::updateBoard(const sf::Vector2i &pacmanPos)
{
    char c = this->m_map(pacmanPos.x, pacmanPos.y);
    if (c == KEY)
    {
        this->openClosestDoor(pacmanPos);
    }
    if (c == COOKIE)
    {
        this->m_numOfCookies--;
    }

    this->m_map(pacmanPos.x, pacmanPos.y) = ' ';
    return c;
}

//------------------------------------------------------------------------------
Map Board::getMap() const
{
    Map tmp = this->m_map;
    return tmp;

}

//------------------------------------------------------------------------------
bool Board::isMapChar(char c) const
{
    for (int i = 0; i < NUM_OF_STATIC_OBJECTS; ++i)
    {
        if (c == MAP_CHARS[i].m_char)
        {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
void Board::openClosestDoor(sf::Vector2i pos)
{
    int minDistanceSquare = -1;
    sf::Vector2i bestDoorPos;
    for (int i = 0; i < this->m_map.getRowSize(); ++i)
    {
        for (int j = 0; j < this->m_map.getColSize(); ++j)
        {
            if (this->m_map(i, j) == DOOR)
            {
                int distanceSquare = (pos.x - i) * (pos.x - i) +
                                     (pos.y - j) * (pos.y - j);

                if (minDistanceSquare == -1 ||
                    distanceSquare < minDistanceSquare)
                {
                    minDistanceSquare = distanceSquare;
                    bestDoorPos = {i, j};
                }
            }

        }
    }
    this->m_map[bestDoorPos] = ' ';
}

//------------------------------------------------------------------------------
int Board::getNumOfCookies() const
{
    return this->m_numOfCookies;
}
//------------------------------------------------------------------------------
void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    float cell_size = std::min((float) (m_gridSize.y /
                                       this->m_map.getRowSize()),
                              (float) (m_gridSize.x /
                                       this->m_map.getColSize()));

    for (int i = 0; i < this->m_map.getRowSize(); ++i)
    {
        for (int j = 0; j < this->m_map.getColSize(); ++j)
        {
            if (this->m_map[{i, j}] == ' ')
            {
                // continue;
            }
            sf::Sprite sprite;
            for (int k = 0; k < NUM_OF_STATIC_OBJECTS; ++k)
            {
                if (this->m_map[{i, j}] == MAP_CHARS[k].m_char)
                {
                    sprite.setTexture(MAP_CHARS[k].m_texture);
                    break;
                }
            }
            sprite.setPosition(i * cell_size + m_gridOffset.x, j * cell_size + m_gridOffset.y);
            sprite.setScale(cell_size / sprite.getTexture()->getSize().x,
                            cell_size / sprite.getTexture()->getSize().y);

            target.draw(sprite, states);
        }
    }
}

void Board::addTime(sf::Time time)
{
    m_map.addTime(time);

}
//------------------------------------------------------------------------------