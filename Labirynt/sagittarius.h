#ifndef SAGITTARIUS_H
#define SAGITTARIUS_H

#include <SFML/Graphics.hpp>

class Sagittarius : public sf::Sprite
{
private:
    float dirX;
    float dirY;
    sf::FloatRect vision;
    float relodeTime;
    float relodeTimeMax;
public:
    Sagittarius();
    ~Sagittarius();
    //Modifiers
    void setStartingMove(const float X, const float Y);
    void setVision();
    void setVision(sf::FloatRect wall);
    //Accessors
    const sf::FloatRect getVision() const;

    //Functions
    void checkCollision(sf::FloatRect wall, int wallDir);
    void update();
    sf::Vector2f shootDirection();
    bool startShooting();
};

#endif // SAGITTARIUS_H
