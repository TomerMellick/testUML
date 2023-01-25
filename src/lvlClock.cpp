#include "lvlClock.h"

LvlClock::LvlClock(int maxTime)
{
    m_clock.restart();
    sf::Time time = sf::seconds(m_clock.getElapsedTime().asSeconds());
    m_maxTime = sf::seconds(maxTime);


}

void LvlClock::start()
{
    m_clock.restart();
}

void LvlClock::pause()
{
    m_lastWaitTime = m_clock.getElapsedTime();
}

void LvlClock::wait(double seconds)
{
    m_lastWaitTime = this->m_clock.getElapsedTime();
    sf::sleep(sf::seconds(seconds));
    
}

bool LvlClock::isOver()
{

    return m_clock.getElapsedTime() > m_maxTime;
}
int LvlClock::getTimeLeft()
{
    return m_maxTime.asSeconds() - m_clock.getElapsedTime().asSeconds();
}