#include "boxes.h"
//Prywatne funkcje
void Boxes::initVariables(){
    this->can_move_bot = true;
    this->can_move_top = true;
    this->can_move_left = true;
    this->can_move_right = true;
}

void Boxes::BoundsCollision()
{
    //Top collision
    if(getGlobalBounds().top < 0){
        setPosition(getPosition().x,
                    0.f);
        this->can_move_top = false;
    }
    //Bottom Collision
    else if(getGlobalBounds().top+getGlobalBounds().height > 600){
        setPosition(getPosition().x,
                    600.f - getGlobalBounds().height);
        this->can_move_bot = false;
    }
    //Left collision
    if(getGlobalBounds().left < 0){
        setPosition(0.f,
                    getPosition().y);
        this->can_move_left = false;
    }
    //Right Collision
    else if(getGlobalBounds().left+getGlobalBounds().width > 1200){
        setPosition(1200.f - getGlobalBounds().width,
                    getPosition().y);
        this->can_move_right = false;
    }
}

//cons/des
Boxes::Boxes()
{
    this->initVariables();
}

Boxes::~Boxes(){

}

//accessors
const bool Boxes::getCanMoveBot() const{
    return this->can_move_bot;
}

const bool Boxes::getCanMoveTop() const{
    return this->can_move_top;
}

const bool Boxes::getCanMoveLeft() const{
    return this->can_move_left;
}

const bool Boxes::getCanMoveRight() const{
    return this->can_move_right;
}

void Boxes::setCanMove(sf::FloatRect wall){
    this->BoundsCollision();
    if(getGlobalBounds().intersects(wall)){
        //bottom collision
        if(getGlobalBounds().top < wall.top
           &&getGlobalBounds().top + getGlobalBounds().height<wall.top + wall.height
           &&getGlobalBounds().left < wall.left + wall.width
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left){
                setPosition(getGlobalBounds().left,
                            wall.top - getGlobalBounds().height);
                this->can_move_bot = false;
        }
        //top collision
        else if(getGlobalBounds().top > wall.top
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top+ wall.height
           &&getGlobalBounds().left < wall.left + wall.width
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left){
                setPosition(getGlobalBounds().left,
                            wall.top + wall.height);
                this->can_move_top = false;
        }
        //right collision
        if(getGlobalBounds().left < wall.left
           &&getGlobalBounds().left + getGlobalBounds().width<wall.left + wall.width
           &&getGlobalBounds().top < wall.top + wall.height
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top){
                setPosition(wall.left - getGlobalBounds().width,
                            getGlobalBounds().top);
                this->can_move_right = false;
        }
        //left collision
        else if(getGlobalBounds().left > wall.left
           &&getGlobalBounds().left + getGlobalBounds().width>wall.left + wall.width
           &&getGlobalBounds().top < wall.top + wall.height
           &&getGlobalBounds().top + getGlobalBounds().height>wall.top){
                setPosition(wall.left+wall.width,
                            getGlobalBounds().top);
                this->can_move_left = false;
        }
    }
}

void Boxes::reset(){
    this->can_move_bot = true;
    this->can_move_top = true;
    this->can_move_left = true;
    this->can_move_right = true;
}


