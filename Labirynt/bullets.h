#ifndef BULLETS_H
#define BULLETS_H

#include <SFML/Graphics.hpp>

class Bullets : public sf::Sprite
{
private:
    float speed;
    sf::Vector2f direction;
    sf::Vector2f position;
public:
    Bullets(sf::Texture* texture,float dirX, float dirY, float posX, float posY);
    ~Bullets();
    //functions
    void shoot();
};

#endif // BULLETS_H
