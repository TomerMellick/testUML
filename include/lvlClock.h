#include <sfml/Graphics.hpp>
#pragma once
class LvlClock
{
private:
    sf::Clock m_clock;
    sf::Time m_maxTime;
    sf::Time m_lastWaitTime;
public:
    LvlClock(int maxTime);

    void start();

    void pause();

    void wait(double seconds);

    bool isOver();

    int getTimeLeft();
};