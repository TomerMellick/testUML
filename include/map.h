#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Map
{
private:

    int m_rowSize; // width
    int m_colSize; // height
    char **m_map;
    int m_time;
public:
    /**
     * crate a 2D array of chars
     * @param rowSize width
     * @param colSize height
     * @param fill what char to fill with the 2D array
     */
    Map(int rowSize, int colSize,int time = 0 ,char fill = '\0' );

    /**
     * create deep copy of other map
     * @param src the other map
     */
    Map(const Map &src);

    /**
     * deep copy of the other map
     * @param src the other map
     * @return reference to self
     */
    Map &operator=(const Map &src);

    /**
     * get width
     * @return the width
     */
    int getRowSize() const;


    /**
     * get width
     * @return the height
     */
    int getColSize() const;

    /**
     * print the map to the console
     */
    void print() const;

    /**
     * get the char at the position
     * @param pos the 
     * @return the char at the pos (as reference)
     */
    char &operator[](const sf::Vector2i &pos);
    
    /**
     * get the char at the position
     * @param row the row
     * @param col the col
     * @return the char at the pos (as const reference)
     */
    char &operator()(int row, int col);

    /**
     * get the char at the position
     * @param pos the 
     * @return the char at the pos
     */
    char operator[](const sf::Vector2i &pos) const;
    
    /**
     * get the char at the position
     * @param row the row
     * @param col the col
     * @return the char at the pos
     */
    char operator()(int row, int col) const;


    ~Map();

    int getTime() const;

    void addTime(sf::Time time);
};