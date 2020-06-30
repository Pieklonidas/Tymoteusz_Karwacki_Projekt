#include "bossbullet.h"

BossBullet::BossBullet(float radius)
    : currVelocity(0.f,0.f), maxSpeed(10.f)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
};
