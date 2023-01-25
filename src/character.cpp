#include "character.h"

//------------------------------------------------------------------------------
Character::Character(sf::Vector2i pos, float charSize, sf::Vector2f gridOffset)
        : m_pos(pos),
          m_originalPos(pos),
          m_prevPos(pos),
          m_charSize(charSize),
          m_gridOffset(gridOffset)
{

}

//------------------------------------------------------------------------------
sf::Vector2i Character::getPos() const
{
    return m_pos;
}

//------------------------------------------------------------------------------
void Character::resetPos()
{
    m_pos = m_originalPos;
    m_prevPos = m_originalPos;
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
bool Character::isMoveValid(const Map &map, const sf::Vector2i &pos) const
{

    return pos.x >= 0 &&
           pos.x < map.getRowSize() &&
           pos.y >= 0 &&
           pos.y < map.getColSize() &&
           map[pos] != '#' &&
           (map[pos] != 'D' || getChar() == SUPER_PACMAN);
}

void Character::setInterval(float interval)
{
    this->m_interval = interval;
}

//------------------------------------------------------------------------------
void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    sf::Sprite sprite = getSprite();

    sprite.setScale(m_charSize / sprite.getTextureRect().width,
                    m_charSize / sprite.getTextureRect().height);


    sprite.setOrigin(sprite.getTextureRect().width / 2.f,
                     sprite.getTextureRect().height / 2.f);

    sf::Vector2f printPos = m_charSize * (((sf::Vector2f) (m_prevPos - m_pos)) *
                                          (float) m_interval +
                                          (sf::Vector2f) m_pos);
//
    sprite.setPosition(printPos + // pos on the grid
                       sf::Vector2f(m_charSize / 2, m_charSize / 2) + // center
                       m_gridOffset); // the grid playButtonFile position

    target.draw(sprite, states);
}

//------------------------------------------------------------------------------
int Character::getMovmentSpeed() const
{
    return m_movementSpeed;
}
//------------------------------------------------------------------------------
void Character::drawOnMap(Map &map) const
{
    map[m_pos] = getChar();
}
//------------------------------------------------------------------------------
sf::Vector2i Character::getPrevPos() const
{
    return m_prevPos;
}
//------------------------------------------------------------------------------