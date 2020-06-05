#ifndef RIFLE_H
#define RIFLE_H

#include "weapons.h"

class Rifle : public Weapons
{
private:
    sf::Vector2f dir;
    float reloadTime;
    float reloadTimeMax;
    float bulletSpeed;
    bool isPicked_;
public:
    Rifle(sf::Texture* texture);
    sf::Vector2f shoot();
    bool reload();
    void updateReload();
    void updateDirection();
    void pickUpWeapon(bool pickOrDrop);
    bool isPicked();
};

#endif // RIFLE_H
