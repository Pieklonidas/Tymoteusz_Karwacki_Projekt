#ifndef BOSSBULLET_H
#define BOSSBULLET_H

#include <SFML/Graphics.hpp>

class BossBullet
{
public:
    sf::CircleShape shape;
    sf::Vector2f currVelocity;
    float maxSpeed;

    BossBullet(float radius = 15.f);

};

#endif // BOSSBULLET_H
