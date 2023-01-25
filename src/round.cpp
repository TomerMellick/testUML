#include <sstream>
#include <iomanip>
#include <SFML/Audio.hpp>
#include "round.h"
#include "resources.h"

//a map that attach score, sound, function to each char in the map
const std::map<char, std::tuple<int, const sf::SoundBuffer *, std::function<void(
        Round *)>>> Round::dataDict = {
        {COOKIE,        {2, (const sf::SoundBuffer *) Resources::loadResources(
                Resources::COOKIE_S), [](Round *round) {}}},

        {GIFT_SUPER,    {5, (const sf::SoundBuffer *) Resources::loadResources(
                Resources::GIFT_S),   [](
                Round *round) { round->m_pacman.setSuper(); }}},
        {GIFT_FREEZE,   {5, (const sf::SoundBuffer *) Resources::loadResources(
                Resources::GIFT_S),   [](
                Round *round) { round->m_freezeRoundRemain = 10; }}},
        {GIFT_ADD_TIME, {5, (const sf::SoundBuffer *) Resources::loadResources(
                Resources::GIFT_S),   [](Round *round)
                                      {
                                          round->m_board.addTime(
                                                  sf::seconds(10));
                                      }}},
        {GIFT_ADD_LIFE, {5, (const sf::SoundBuffer *) Resources::loadResources(
                Resources::GIFT_S),   [](
                Round *round) { round->m_pacman.incLife(); }}},

        {KEY,           {7, nullptr,  [](Round *round) {}}},
        {DOOR,          {0, nullptr,  [](Round *round) {}}},
        {' ',           {0, nullptr,  [](Round *round) {}}}
};

//------------------------------------------------------------------------------
Round::Round(const Map &map,
             sf::RenderWindow *window,
             const sf::Vector2f &gridOffset,
             const sf::Vector2f &gridSize,
             int level,
             int score) :
        m_board(map, gridSize, gridOffset),
        m_cellSize(std::min(gridSize.x / map.getColSize(),
                            gridSize.y / map.getRowSize())),
        m_pacman(sf::Vector2i(0, 0), m_cellSize, gridOffset),
        m_window(window),
        m_gridOffset(gridOffset),
        m_gridSize(gridSize),
        m_freezeRoundRemain(0),
        m_level(level),
        m_result{true, score}
{
    for (int i = 0; i < map.getRowSize(); ++i)
    {
        for (int j = 0; j < map.getColSize(); ++j)
        {
            if (map(i, j) == GHOST)
            {
                m_ghosts.emplace_back(sf::Vector2i(i, j), m_cellSize,
                                      gridOffset);
            }
            else if (map(i, j) == PACMAN)
            {
                m_pacman = Pacman(sf::Vector2i(i, j), m_cellSize, gridOffset);
            }
        }
    }

    m_characters.push_back(&m_pacman);
    for (auto &ghost: m_ghosts)
    {
        m_characters.push_back(&ghost);
    }

}

//------------------------------------------------------------------------------
void Round::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            m_pacman.setDirection(event.key.code);
        }
    }
}

//------------------------------------------------------------------------------
Result Round::startRound()
{
    sf::Sound sound;
    m_roundClock.restart();
    sf::Clock clockForDeltaTime;

    sf::Time elapsedRoundTime = sf::seconds(m_board.getMap().getTime());
    while (m_window->isOpen())
    {
        // get delta time
        sf::Time deltaTime = clockForDeltaTime.restart();
        handleEvents();

        //time over 
        if (m_board.getNumOfCookies() == 0)
        {
            m_result.m_win = true;
            m_result.m_score += 50 + m_ghosts.size() * 2;
            break;
        }
        else if (m_roundClock.getElapsedTime() > elapsedRoundTime ||
                 m_pacman.getHealth() == 0)
        {
            m_result.m_win = false;
            break;
        }

        // move pacman and ghosts
        if ((int) (m_roundClock.getElapsedTime().asSeconds() *
                   (float) m_pacman.getMovmentSpeed()) !=
            (int) ((m_roundClock.getElapsedTime().asSeconds() -
                    deltaTime.asSeconds()) *
                   (float) m_pacman.getMovmentSpeed()))
        {
            if (m_freezeRoundRemain == 0)
            {
                for (auto &ghost: m_ghosts)
                {
                    ghost.move(getMap());
                }
            }
            else
            {
                // freeze round
                m_freezeRoundRemain--;
                for (auto &ghost: m_ghosts)
                {
                    // prevent error with the interval calculation
                    ghost.dontMove();
                }
            }
            m_pacman.move(getMap());


        }

        // check if pacman collide with ghost
        handleCollision();


        // update board according to the pacman position 
        char eat = m_board.updateBoard(m_pacman.getPos());

        // use the score, the sound and the function of the eaten object
        auto [score, soundBuffer, func] = dataDict.at(eat);
        m_result.m_score += score;
        func(this);
        if (soundBuffer)
        {
            sound.setBuffer(*soundBuffer);
            sound.play();
        }

        // set the interval for the characters
        //by claculating the time that passed from the last move between 2 cells
        float interval = 1 -
                         (m_roundClock.getElapsedTime().asSeconds() *
                          m_pacman.getMovmentSpeed()
                          -
                          (int) (m_roundClock.getElapsedTime().asSeconds() *
                                 m_pacman.getMovmentSpeed()));
        for (auto &character: m_characters)
        {
            character->setInterval(interval);
        }
        // draw
        draw();
    }
    return m_result;
}

//------------------------------------------------------------------------------
Map Round::getMap() const
{
    Map map = m_board.getMap();
    for (const Character *character: m_characters)
    {
        character->drawOnMap(map);
    }
    return map;
}

//------------------------------------------------------------------------------
Ghost *Round::getCollision()
{
    for (Ghost &ghost: m_ghosts)
    {
        sf::Vector2i ghostDirection = ghost.getPos() - ghost.getPrevPos();
        sf::Vector2i pacmanDirection =
                m_pacman.getPos() - m_pacman.getPrevPos();
        if (ghost.getPos() == m_pacman.getPos())
        {
            return &ghost;
        }
        // harder but more realistic
        //if(ghost.getPos() == m_pacman.getPrevPos() && ghostDirection != pacmanDirection)

        if (ghost.getPos() == m_pacman.getPrevPos() &&
            ghostDirection == -pacmanDirection)
        {
            return &ghost;
        }
    }

    return nullptr;
}

//------------------------------------------------------------------------------
void Round::handleCollision()
{
    Ghost *ghost = getCollision();
    if (ghost)
    {
        if (m_pacman.isSuper())
        {
            ghost->resetPos();
        }
        else
        {
            m_pacman.decHealth();
            for (auto &character: m_characters)
            {
                character->resetPos();
            }
        }
    }
}

//------------------------------------------------------------------------------
std::string Round::getStatisticalData() const
{
    std::ostringstream oss;
    int seconds = m_board.getMap().getTime() -
                  (int) m_roundClock.getElapsedTime().asSeconds();
    oss << "Time: "
        << std::setw(2) << std::setfill('0') << seconds / 60 << ":"
        << std::setw(2) << std::setfill('0') << seconds % 60 <<
        ", Score: " <<  m_result.m_score <<
        ", Round: " << std::setw(2) << std::setfill('0') << m_level <<
        ", Health: " << std::setw(2) << std::setfill('0')
        << m_pacman.getHealth();
    return oss.str();
}
//------------------------------------------------------------------------------

void Round::draw()
{
    m_window->clear();
    // draw the map
    m_window->draw(m_board);
    // draw the characters
    for (auto &character: m_characters)
    {
        m_window->draw(*character);
    }

    // draw the time + score + life
    sf::Text text;
    const sf::Font *font = (const sf::Font *) Resources::loadResources(
            Resources::KARMA_F);
    text.setFillColor(sf::Color::Yellow);


    text.setFont(*font);
    text.setString(getStatisticalData());

    text.setCharacterSize(30);
    text.setPosition(((float) m_window->getSize().x / 2) -
                     text.getLocalBounds().width / 2, 50);
    m_window->draw(text);
    m_window->display();


}
 