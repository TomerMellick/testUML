#include <SFML/Graphics.hpp>

#pragma once
//a struct to hold the score and the name of the player
struct Score
{
    std::string m_name = "no_name";
    int m_score = 0;
};

/***
 * a singleton class to handle the scoreboard
 */
class ScoreBoard : public sf::Drawable
{

public:
    /***
     * get the instance of the scoreboard
     * @return the instance of the scoreboard
     */
    static ScoreBoard &getInstance();

    void readFromFile();

    /***
     * add a score to the scoreboard
     * @param score the score to add
     */
    void writeToFile(const Score &score);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /***
     * get from the user the name of the player
     * @return the scores
     */
    static std::string getName();

private:
    ScoreBoard();

    //the scores in the score board
    std::vector<Score> m_scores;
    const sf::Font *m_font;
    sf::Text m_text;
    static ScoreBoard *instance;


};
