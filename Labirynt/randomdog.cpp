#include "randomdog.h"
#include <iostream>

//cons/des
RandomDog::RandomDog(sf::Texture* texture)
{
    setTexture(*texture);
    this->top = true;
    this->bottom = true;
    this->left = true;
    this->right = true;
    this->zmiana = true;
    velocity.x = 0.f;
    velocity.y = 0.f;

}
//Metody klasy
void RandomDog::setPossibleTrack(std::vector<std::unique_ptr<Walls> > &walls){
    this->updateSurroundings();
    for(auto &w : walls){
        sf::FloatRect wallBounds = w->getGlobalBounds();
        sf::FloatRect dogBounds = getGlobalBounds();

        if(dogBounds.intersects(wallBounds)){

            //bottom collision
            if(dogBounds.top < wallBounds.top
               &&dogBounds.top + dogBounds.height<wallBounds.top + wallBounds.height
               &&dogBounds.left < wallBounds.left + wallBounds.width
               &&dogBounds.left + dogBounds.width>wallBounds.left){
                    this->bottom = false;
                    setPosition(dogBounds.left,wallBounds.top-dogBounds.height);
            }
            //top collision
            else if(dogBounds.top > wallBounds.top
               &&dogBounds.top + dogBounds.height>wallBounds.top+ wallBounds.height
               &&dogBounds.left < wallBounds.left + wallBounds.width
               &&dogBounds.left + dogBounds.width>wallBounds.left){
                    this->top = false;
                    setPosition(dogBounds.left, wallBounds.top + wallBounds.height);
            }
            //right collision
            if(dogBounds.left < wallBounds.left
               &&dogBounds.left + dogBounds.width<wallBounds.left + wallBounds.width
               &&dogBounds.top < wallBounds.top + wallBounds.height
               &&dogBounds.top + dogBounds.height>wallBounds.top){
                    this->right = false;
                    setPosition(wallBounds.left - dogBounds.width,dogBounds.top);
            }
            //left collision
            else if(dogBounds.left > wallBounds.left
               &&dogBounds.left + dogBounds.width>wallBounds.left + wallBounds.width
               &&dogBounds.top < wallBounds.top + wallBounds.height
               &&dogBounds.top + dogBounds.height>wallBounds.top){
                    this->left = false;
                    setPosition(wallBounds.left + wallBounds.width,dogBounds.top);
            }
        }
    }
}

void RandomDog::updateSurroundings(){
    this->top = true;
    this->bottom = true;
    this->left = true;
    this->right = true;
}

void RandomDog::updatePossibleWay(){
    //Top/bot
    if(!bottom && velocity.y >= 0){
        velocity.y = -2.f;
    }else if(!top && velocity.y <= 0){
        velocity.y = 2.f;
    }
    //left/right
    if(!right && velocity.x >= 0){
        velocity.x = -2.f;
    }else if(!left && velocity.x <= 0){
        velocity.x = 2.f;
    }

}

void RandomDog::setMovementSpeed(float dirX, float dirY){
    this->velocity.x = dirX;
    this->velocity.y = dirY;
}

void RandomDog::update(){
    this->updatePossibleWay();
    move(velocity);
}

sf::Vector2f RandomDog::getDirection(){
    return velocity;
}














