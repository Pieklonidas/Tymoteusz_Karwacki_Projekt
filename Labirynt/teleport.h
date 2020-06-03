#ifndef TELEPORT_H
#define TELEPORT_H

#include "player.h"


class Teleport : public sf::Sprite
{
private:
    sf::FloatRect exitBounds;
    float exitX;
    float exitY;
public:
    Teleport();
    ~Teleport();
    //modifiers
    void setExitBounds(sf::FloatRect exit);
    void setDirection(const float X, const float Y);
    //metody klasy
    void teleportPlayer(Player &player);
};

#endif // TELEPORT_H
