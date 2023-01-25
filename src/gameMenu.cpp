#include "gameMenu.h"
#include "game.h"
#include "GameEditor.h"
#include "scoreBoard.h"
#include "resources.h"


//------------------------------------------------------------------------------
GameMenu::GameMenu(sf::Vector2u windowSize)
{
    // Create the window
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Pac-Man Menu");
    m_window.setFramerateLimit(60);
    m_buffer = (sf::SoundBuffer *) Resources::loadResources(
            Resources::SOUNDTRACK_S);
    //set music
    m_music = new sf::Sound(*m_buffer);
    m_music->setLoop(true);

    // Create the buttons
    m_playButton = new MenuButton(Resources::PLAY_BUTTON_T,
                                  std::bind(&GameMenu::startGame, this));

    m_exitButton = new MenuButton(Resources::EXIT_BUTTON_T,
                                  std::bind(&GameMenu::exitGame, this));
    m_helpButton = new MenuButton(Resources::HELP_BUTTON_T,
                                  std::bind(&GameMenu::showHelp, this));
    m_editorButton = new MenuButton(Resources::EDITOR_BUTTON_T,
                                    std::bind(&GameMenu::openEditor, this));

    m_highScoreButton = new MenuButton(Resources::HIGHSCORE_BUTTON_T,
                                       std::bind(&GameMenu::showHighScores,
                                                 this));
    m_buttons = {m_playButton,
                 m_helpButton, m_editorButton,
                 m_highScoreButton, m_exitButton};

    // Set the button positions
    for (int i = 0; i < m_buttons.size(); i++)
    {
        m_buttons[i]->setPosition(sf::Vector2f(
                0.5f * windowSize.x - 0.5f * m_buttons[i]->getSize().x,
                (1.f / (m_buttons.size() + 1.f) * (i + 1.f)) * windowSize.y -
                0.5f * m_buttons[i]->getSize().y));
    }
    m_backgroundTexture = (sf::Texture *) Resources::loadResources(
            Resources::BACKGROUND_T);
    m_background.setTexture(*m_backgroundTexture);


}

//------------------------------------------------------------------------------
void GameMenu::run()
{
    m_music->play();
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (auto &m_button: m_buttons)
                    {

                        m_button->handleClick(event.mouseButton.x,
                                              event.mouseButton.y);
                    }
                    m_window.create(sf::VideoMode(400, 600), "Pac-Man Menu");
                    m_window.setFramerateLimit(60);
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                for (auto &m_button: m_buttons)
                {
                    m_button->handleHover(event.mouseMove.x,
                                          event.mouseMove.y);
                }
            }
        }

        m_window.clear();
        m_window.draw(m_background);
        for (auto &m_button: m_buttons)
        {
            m_window.draw(*m_button);
        }

        m_window.display();
    }

}

//------------------------------------------------------------------------------
void GameMenu::startGame()
{
    m_window.close();

    Game game("my_map.txt");
    int currentScore = game.startGame().m_score;

    std::string name = ScoreBoard::getName();

    if (!name.empty())
    {
        ScoreBoard::getInstance().writeToFile({name, currentScore});
    }


}

//------------------------------------------------------------------------------
void GameMenu::showHighScores()
{

    m_window.create(sf::VideoMode(m_window.getSize().x, m_window.getSize().y), "High Scores");


    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }
        m_window.clear();
        m_window.draw(m_background);
        m_window.draw(ScoreBoard::getInstance());

        m_window.display();
    }

}

//------------------------------------------------------------------------------
void GameMenu::exitGame()
{

    m_window.close();
    exit(0);
}

//------------------------------------------------------------------------------
void GameMenu::openEditor()
{
    m_window.close();
    GameEditor editor = GameEditor();
    editor.run();
}

//------------------------------------------------------------------------------
void GameMenu::showHelp()
{

    m_window.create(sf::VideoMode(400, 600), "Help");
    m_window.setFramerateLimit(60);
    sf::Texture *helpTexture = (sf::Texture *) Resources::loadResources(
            Resources::HELP_SCREEN_T);


    sf::Sprite helpSprite;
    helpSprite.setTexture(*helpTexture);
    helpSprite.setPosition(0, 0);
    helpSprite.setScale(
            m_window.getSize().x / helpTexture->getSize().x,
            m_window.getSize().y / helpTexture->getSize().y);
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_window.close();
                }
            }
        }
        m_window.clear();
        m_window.draw(helpSprite);
        m_window.display();
    }
}

//------------------------------------------------------------------------------
GameMenu::~GameMenu()
{
    for (int i = 0; i < m_buttons.size(); ++i)
    {
        delete m_buttons[i];
    }
}