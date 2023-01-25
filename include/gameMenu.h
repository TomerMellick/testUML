#pragma once

#include"menuButton.h"
#include <SFML/Audio.hpp>
#include "scoreBoard.h"

class GameMenu
{
public:
    /***
     * constructor
     * @param windowSize
     */
    GameMenu(sf::Vector2u windowSize);

    /***
     * run the menu
     */
    void run();
    ~GameMenu();
private:
    /***
     * func to use when the play button is pressed
     */
    void startGame();

    /***
     * func to use when the highscore button is pressed
     */
    void showHighScores();

    /***
     * func to use when the exit button is pressed
     */
    void exitGame();

    /***
     * func to use when the editor button is pressed
     */
    void openEditor();

    /***
     * func to use when the help button is pressed
     */
    void showHelp();



    const sf::Texture *m_backgroundTexture;
    sf::Sprite m_background;

    const sf::SoundBuffer *m_buffer;

    sf::RenderWindow m_window;

    MenuButton *m_playButton;
    MenuButton *m_highScoreButton;
    MenuButton *m_editorButton;
    MenuButton *m_helpButton;
    MenuButton *m_exitButton;

    std::vector<MenuButton *> m_buttons;
    sf::Sound *m_music;
    ScoreBoard *m_scoreBoard = nullptr;


};
