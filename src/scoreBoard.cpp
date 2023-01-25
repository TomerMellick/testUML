#include "scoreBoard.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "resources.h"

const std::string SCOREFILE = "highscores.txt";
ScoreBoard* ScoreBoard::instance = nullptr;
//------------------------------------------------------------------------------
ScoreBoard::ScoreBoard()
{
    std::ifstream file(SCOREFILE);
    m_font = (sf::Font *) Resources::loadResources(Resources::KARMA_F);
    std::string name;
    int score;

    while (file >> name >> score)
    {
        m_scores.emplace_back(Score{name, score});
    }

    file.close();


}

//------------------------------------------------------------------------------
void ScoreBoard::readFromFile()
{
    std::ifstream file(SCOREFILE);
    std::string name;
    int score;
    while (file >> name >> score)
    {
        m_scores.emplace_back(Score{name, score});
    }
    file.close();

}

//------------------------------------------------------------------------------
void ScoreBoard::writeToFile(const Score &input)
{
    std::ofstream file(SCOREFILE);
    bool isHighScore = false;
    for (int i = 0;i<m_scores.size();i++)
    {
        if (input.m_score>=m_scores[i].m_score&&!isHighScore)
        {
            isHighScore = true;
            m_scores.insert(m_scores.begin() + i, input);
            break;

        }
    }
    if (m_scores.size()<10&&!isHighScore)
    {
        m_scores.insert(m_scores.end(),input);
    }

    for (auto &i: m_scores)
    {
        file << i.m_name << " " << i.m_score << std::endl;
    }

    file.close();
}

//------------------------------------------------------------------------------
void ScoreBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Text text, text2;

    text.setFont(*m_font);

    text.setCharacterSize(24);


    text.setFillColor(sf::Color::Yellow);


    for (int i = 0; i < 10 && i < m_scores.size(); ++i)
    {
        std::string str =
                std::to_string(i + 1) + "  " + m_scores[i].m_name + " " +
                std::to_string(m_scores[i].m_score);
        text.setString(str);
        text.setPosition(150, 50 + (i * 50));
        target.draw(text, states);

    }
}

//------------------------------------------------------------------------------
std::string ScoreBoard::getName()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(500, 50), "Enter your name: ");
    window.setFramerateLimit(60);
    sf::Font *font = (sf::Font *) Resources::loadResources(Resources::KARMA_F);

    sf::Text text;
    text.setFont(*font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(0, 0);
    std::string name;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.key.code == sf::Keyboard::Enter)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (name.size() > 0)
                    {
                        name.pop_back();
                    }
                }
                else if (event.text.unicode == 13)
                {
                    window.close();
                }
                else if (event.text.unicode < 128)
                {
                    name += static_cast<char>(event.text.unicode);
                }
            }
        }
        text.setString(name);
        window.clear();
        window.draw(text);
        window.display();
    }
    return name;
}
//------------------------------------------------------------------------------
ScoreBoard& ScoreBoard::getInstance()
{
    if(instance == nullptr)
        instance = new ScoreBoard();
    return *instance;
}