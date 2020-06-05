#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>

class Weapons : public sf::Sprite
{
private:

public:
    Weapons(sf::Texture* texture);
    virtual ~Weapons() = default;
    virtual bool reload() = 0;
    virtual void updateReload() = 0;
    virtual sf::Vector2f shoot() = 0;
    virtual void updateDirection() = 0;
    virtual void pickUpWeapon(bool pickOrDrop) = 0;
    virtual bool isPicked() = 0;

};

#endif // WEAPONS_H
