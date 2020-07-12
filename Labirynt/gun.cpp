#include "gun.h"

Gun::Gun(sf::Texture* texture) : Weapons(texture)
{
    this->dir = sf::Vector2f(0.f,0.f);
    this->reloadTimeMax = 25.f;
    this->reloadTime = this->reloadTimeMax;
    this->bulletSpeed = 20.f;
    this->isPicked_ = false;
}

sf::Vector2f Gun::shoot(){
    return this->dir;
}

bool Gun::reload(){
    if(this->reloadTime == this->reloadTimeMax){
        this->reloadTime = 0;
        return true;
    }
    else {
        return false;
    }
}

void Gun::updateReload(){
    if(this->reloadTime<this->reloadTimeMax){
        this->reloadTime += 1;
    }
}

void Gun::updateDirection(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->dir.x = -1;
        this->dir.y = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->dir.x = 1;
        this->dir.y = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->dir.y = -1;
        this->dir.x = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->dir.y = 1;
        this->dir.x = 0;
    }
}

void Gun::pickUpWeapon(bool pickOrDrop){
    this->isPicked_ = pickOrDrop;
}

bool Gun::isPicked(){
    return this->isPicked_;
}
