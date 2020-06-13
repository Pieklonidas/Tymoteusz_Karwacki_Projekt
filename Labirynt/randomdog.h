#ifndef RANDOMDOG_H
#define RANDOMDOG_H

#include "walls.h"
#include <memory>

class RandomDog : public sf::Sprite
{
private:
    bool top;
    bool bottom;
    bool left;
    bool right;
    bool zmiana;
    sf::Vector2f velocity;
public:
    RandomDog(sf::Texture* texture);
    sf::Vector2f getDirection();
    void setPossibleTrack(std::vector<std::unique_ptr<Walls>>& walls);
    void updateSurroundings();
    void updatePossibleWay();
    void setMovementSpeed(float dirX,float dirY);
    void update();
};

#endif // RANDOMDOG_H
