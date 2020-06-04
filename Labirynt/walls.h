#ifndef WALLS_H
#define WALLS_H

#include <SFML/Graphics.hpp>

class Walls : public sf::Sprite
{
private:
    int directionForEnemy;
    bool canBeClosestToEnemy;
public:
    Walls();
    ~Walls();
    void reMove(const float X, const float Y);
    //modifiers
    void setDirectionForEnemy(const bool dir);
    void setCanBeClosest(bool close);
    //Accessors
    int giveDirectionToEnemy();
    bool getCanBeClosest();
};

#endif // WALLS_H
