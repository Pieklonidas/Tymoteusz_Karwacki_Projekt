#include "sagittarius.h"

//Cons/des
Sagittarius::Sagittarius(){
    this->dirX = 0;
    this->dirY = 0;
}

Sagittarius::~Sagittarius(){

}
//Modifiers
void Sagittarius::setStartingMove(const float X, const float Y){
    this->dirX = X;
    this->dirY = Y;
}

void Sagittarius::setVision(){
    if(this->dirX < 0){
        this->vision.left = 0;
        this->vision.top = getGlobalBounds().top;
        this->vision.width = getGlobalBounds().left;
        this->vision.height = getGlobalBounds().height;
    }
    else if(this->dirX>0){
        this->vision.left = getGlobalBounds().left + getGlobalBounds().width;
        this->vision.top = getGlobalBounds().top;
        this->vision.width = 1200 - getGlobalBounds().left - getGlobalBounds().width;
        this->vision.height = getGlobalBounds().height;
    }

    if(this->dirY < 0){
        this->vision.left = getGlobalBounds().left;
        this->vision.top = 0;
        this->vision.width = getGlobalBounds().width;
        this->vision.height = getGlobalBounds().top;
    }
    else if(this->dirY>0){
        this->vision.left = getGlobalBounds().left;
        this->vision.top = getGlobalBounds().top;
        this->vision.width = getGlobalBounds().width;
        this->vision.height = 600 - getGlobalBounds().top - getGlobalBounds().width;
    }
}

void Sagittarius::setVision(sf::FloatRect wall){
    if(this->dirX < 0){
        if(vision.intersects(wall)){
            this->vision.left = wall.left+wall.width;
            this->vision.width = getGlobalBounds().left - wall.left - wall.width;
        }
    }
    else if(this->dirX>0){
        if(vision.intersects(wall)){
            this->vision.width = wall.left - getGlobalBounds().left - getGlobalBounds().width;
        }
    }

    if(this->dirY < 0){
        if(vision.intersects(wall)){
            this->vision.top = wall.top+wall.height;
            this->vision.height = getGlobalBounds().top - wall.top - wall.height;
        }
    }
    else if(this->dirY>0){
        if(vision.intersects(wall)){
            this->vision.height = wall.top - getGlobalBounds().top - getGlobalBounds().height;
        }
    }
}
//Accessors
const sf::FloatRect Sagittarius::getVision() const{
    return this->vision;
}
//Functions
void Sagittarius::checkCollision(sf::FloatRect wall, int wallDir){
    sf::FloatRect nextPos = getGlobalBounds();
    nextPos.left += dirX;
    nextPos.top += dirY;
    if(wall.intersects(nextPos)){
        //bottom collision
        if(getGlobalBounds().top < wall.top
           &&getGlobalBounds().top + getGlobalBounds().height<wall.top + wall.height
           &&getGlobalBounds().left < wall.left + wall.width
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left
           &&dirY!=0){

                setPosition(getGlobalBounds().left,
                            wall.top - getGlobalBounds().height);

                this->dirX = this->dirY*wallDir;
                this->dirY = 0;
        }
        //top collision
        else if(getGlobalBounds().top > wall.top
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top+ wall.height
           &&getGlobalBounds().left < wall.left + wall.width
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left
           &&dirY!=0){

                setPosition(getGlobalBounds().left,
                            wall.top + wall.height);

                this->dirX = this->dirY*wallDir;
                this->dirY = 0;
        }
        //right collision
        if(getGlobalBounds().left < wall.left
           &&getGlobalBounds().left + getGlobalBounds().width<wall.left + wall.width
           &&getGlobalBounds().top < wall.top + wall.height
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top
           &&dirX!=0){

                setPosition(wall.left - getGlobalBounds().width,
                            getGlobalBounds().top);

                this->dirY = this->dirX*wallDir;
                this->dirX = 0;
        }
        //left collision
        else if(getGlobalBounds().left > wall.left
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left + wall.width
           &&getGlobalBounds().top < wall.top + wall.height
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top
           &&dirX!=0){

                setPosition(wall.left+wall.width,
                            getGlobalBounds().top);

                this->dirY = this->dirX*wallDir;
                this->dirX = 0;
        }
    }
}

void Sagittarius::update(){
    move(dirX,dirY);
}














