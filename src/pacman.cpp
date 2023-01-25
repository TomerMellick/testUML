#include "pacman.h"
#include <cmath>
#include "resources.h"

//#define _USE_MATH_DEFINES
const double PI = 3.14159265358979323846;



//------------------------------------------------------------------------------
Pacman::Pacman(sf::Vector2i position, float charSize, sf::Vector2f gridOffset)
        : Character(position, charSize, gridOffset),
          m_super(0),
          m_health(3),
          m_direction(0, 0)
{
    sf::Texture texture;// = new sf::Texture();

    m_movementSpeed = 5;
}

//------------------------------------------------------------------------------
int Pacman::getHealth() const
{
    return m_health;
}

//------------------------------------------------------------------------------
void Pacman::decHealth()
{
    m_health--;
}

//------------------------------------------------------------------------------
char Pacman::getChar() const
{
    return m_super > 0 ? SUPER_PACMAN : PACMAN;
}

//------------------------------------------------------------------------------
void Pacman::setDirection(sf::Keyboard::Key key)
{

    sf::Vector2i to_move = sf::Vector2i{0, 0};
    if (key == sf::Keyboard::Up)
    {
        to_move = sf::Vector2i{0, -1};
    }
    else if (key == sf::Keyboard::Down)
    {
        to_move = sf::Vector2i{0, 1};
    }
    else if (key == sf::Keyboard::Left)
    {
        to_move = sf::Vector2i{-1, 0};
    }
    else if (key == sf::Keyboard::Right)
    {
        to_move = sf::Vector2i{1, 0};
    }
    this->m_direction = to_move;


}

//------------------------------------------------------------------------------
void Pacman::setSuper()
{
    this->m_super = 20;
}

//------------------------------------------------------------------------------
void Pacman::move(const Map &map)
{
    if (m_super > 0)
    {
        m_super--;
    }
    if (isMoveValid(map, m_pos + m_direction))
    {
        m_prevPos = m_pos;
        m_pos += m_direction;
    }
    else
    {
        m_prevPos = m_pos;
        //m_direction = sf::Vector2i{0, 0};
    }


}
//------------------------------------------------------------------------------

sf::Sprite Pacman::getSprite() const
{
    sf::Vector2i diff = m_pos - m_prevPos;
    sf::Sprite sprite;
    sprite.setTexture(*(sf::Texture *)Resources::loadResources(Resources::PACMAN_GAME_T));

    //look at `Resources::PACMAN_GAME_T` file to understand the next line
    sprite.setTextureRect(sf::IntRect((int)(m_interval * 4)* Resources::PACMAN_GAME_TS ,(m_super>0) * Resources::PACMAN_GAME_TS, Resources::PACMAN_GAME_TS, Resources::PACMAN_GAME_TS));
    //rotate the sprite according to the direction of the pacman
    double angle = atan2(diff.y, diff.x) / PI * 180;
    sprite.setRotation((float) angle);
    return sprite;
}
//------------------------------------------------------------------------------
bool Pacman::isSuper() const
{
    if (m_super > 0)
    {
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
void Pacman::incLife()
{
    m_health++;

}
