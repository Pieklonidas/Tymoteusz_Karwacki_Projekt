#include "rifle.h"
Rifle::Rifle(sf::Texture* texture) : Weapons(texture){
    this->dir = sf::Vector2f(0.f,0.f);
    this->reloadTimeMax = 10.f;
    this->reloadTime = this->reloadTimeMax;
    this->bulletSpeed = 30.f;
}


//Functions
sf::Vector2f Rifle::shoot(){
    return this->dir;
}

bool Rifle::reload(){
    if(this->reloadTime == this->reloadTimeMax){
        this->reloadTime = 0;
        return true;
    }
    else {
        return false;
    }
}

void Rifle::updateReload(){
    if(this->reloadTime<this->reloadTimeMax){
        this->reloadTime += 1;
    }
}

void Rifle::updateDirection(){
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

void Rifle::pickUpWeapon(bool pickOrDrop){
    this->isPicked_ = pickOrDrop;
}

bool Rifle::isPicked(){
    return this->isPicked_;
}


















