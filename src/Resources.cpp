#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "resources.h"

std::map<std::string, void *> resources;

const void *Resources::loadResources(std::string path)
{
    if (resources.find(path) == resources.end())
    {
        if (path.ends_with(".png"))
        {
            sf::Texture *t = new sf::Texture();
            t->loadFromFile(path);
            resources[path] = t;
        }
        else if (path.ends_with(".ogg") || 
                 path.ends_with(".wav"))
        {
            sf::SoundBuffer *s = new sf::SoundBuffer();
            s->loadFromFile(path);

            resources[path] = s;
        }
        else if (path.ends_with(".ttf") || 
                 path.ends_with(".TTF") ||
                 path.ends_with(".otf"))
        {
            sf::Font *f = new sf::Font();
            f->loadFromFile(path);
            resources[path] = f;
        }
    }
    return resources[path];
}
