#ifndef WALLS_H
#define WALLS_H

#include <SFML/Graphics.hpp>

class Walls : public sf::Sprite
{
private:

public:
    Walls();
    ~Walls();
    void reMove(const float X, const float Y);
};

#endif // WALLS_H
