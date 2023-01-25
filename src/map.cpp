#include "map.h"

//------------------------------------------------------------------------------
Map::Map(int rowSize, int colSize,int time,char fill): m_rowSize(rowSize), m_colSize(colSize),m_time(time)
{

    this->m_map = new char *[colSize];
    for (int i = 0; i < colSize; ++i)
    {
        this->m_map[i] = new char[rowSize];
        for (int j = 0; j < rowSize; ++j)
        {
            this->m_map[i][j] = fill;
        }
    }
}

//------------------------------------------------------------------------------
int Map::getRowSize() const
{
    return this->m_rowSize;
}

//------------------------------------------------------------------------------
int Map::getColSize() const
{
    return this->m_colSize;
}

//------------------------------------------------------------------------------
void Map::print() const
{
    for (int i = 0; i < this->m_colSize; ++i)
    {
        for (int j = 0; j < this->m_rowSize; ++j)
        {
            std::cout << this->m_map[i][j];
        }
        std::cout << std::endl;
    }
}

//------------------------------------------------------------------------------
char &Map::operator[](const sf::Vector2i &pos)
{
    return this->m_map[pos.y][pos.x];
}

//------------------------------------------------------------------------------
char Map::operator[](const sf::Vector2i &pos) const
{
    return this->m_map[pos.y][pos.x];
}

//------------------------------------------------------------------------------
Map::~Map()
{
    for (int i = 0; i < this->m_colSize; ++i)
    {
        delete[] this->m_map[i];
    }
    delete[] this->m_map;
}

//------------------------------------------------------------------------------
Map::Map(const Map &src) : m_colSize(src.m_colSize), m_rowSize(src.m_rowSize), m_time(src.m_time)
{
    this->m_map = new char *[src.m_colSize];
    for (int i = 0; i < src.m_colSize; ++i)
    {
        this->m_map[i] = new char[this->m_rowSize];
        for (int j = 0; j < src.m_rowSize; ++j)
        {
            this->m_map[i][j] = src.m_map[i][j];
        }
    }
}

//------------------------------------------------------------------------------
Map &Map::operator=(const Map &src)
{
    if (this == &src)
    {
        return *this;
    }
    m_time= src.m_time;
    //when it's important to alloc from playButtonFile?
    bool new_alloc = src.m_colSize != this->m_colSize ||
                     src.m_rowSize != this->m_rowSize;
    if (new_alloc)
    {
        for (int i = 0; i < m_colSize; ++i)
        {
            delete[] this->m_map[i];
        }
        delete[] this->m_map;
        this->m_map = new char *[src.m_colSize];

    }
    for (int i = 0; i < src.m_colSize; ++i)
    {
        if (new_alloc)
        {
            this->m_map[i] = new char[src.m_rowSize];
        }
        for (int j = 0; j < src.m_rowSize; ++j)
        {
            this->m_map[i][j] = src.m_map[i][j];
        }
    }
    this->m_colSize = src.m_colSize;
    this->m_rowSize = src.m_rowSize;
    return *this;
}
//------------------------------------------------------------------------------
char &Map::operator()(int row, int col)
{
    return this->m_map[col][row];
}
//------------------------------------------------------------------------------
char Map::operator()(int row, int col) const
{
    return this->m_map[col][row];
}
//------------------------------------------------------------------------------
int Map::getTime() const
{
    return this->m_time;
}

void Map::addTime(sf::Time time)
{
    this->m_time += time.asSeconds();
}
