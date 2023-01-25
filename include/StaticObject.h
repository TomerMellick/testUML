#include <SFML/Graphics.hpp>

const char WALL = '#';
const char DOOR = 'D';
const char KEY = '%';
const char COOKIE = '*';
const char GIFT_SUPER = '1';
const char GIFT_FREEZE = '2';
const char GIFT_ADD_TIME = '3';
const char GIFT_ADD_LIFE = '4';
const int NUM_OF_STATIC_OBJECTS = 9;

struct StaticObject
{
    char m_char;
    sf::Texture m_texture;

    StaticObject(char c, const std::string &texture_path)
            : m_char(c)
    {
        m_texture.loadFromFile(texture_path);
    }
};