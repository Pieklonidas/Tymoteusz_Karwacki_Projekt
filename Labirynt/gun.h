#ifndef GUN_H
#define GUN_H

#include "weapons.h"

class Gun : public Weapons
{
private:
    sf::Vector2f dir;
    float reloadTime;
    float reloadTimeMax;
    float bulletSpeed;
    bool isPicked_;
public:
    Gun(sf::Texture *texture);
    sf::Vector2f shoot();
    bool reload();
    void updateReload();
    void updateDirection();
    void pickUpWeapon(bool pickOrDrop);
    bool isPicked();
};

#endif // GUN_H
