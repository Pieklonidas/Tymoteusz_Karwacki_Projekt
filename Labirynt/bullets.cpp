#include "bullets.h"
//cons/des
Bullets::Bullets(sf::Texture* texture, float dirX, float dirY, float posX, float posY)
{
    this->speed = 20.f;
    this->direction.x = dirX;
    this->direction.y = dirY;
    this->position.x = posX;
    this->position.y = posY;
    setPosition(position);
    setTexture(*texture);
}

Bullets::~Bullets(){

}
//Functions
void Bullets::shoot(){
    move(this->speed*this->direction.x,this->speed*this->direction.y);
}
