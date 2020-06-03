#include "teleport.h"
//cons/des
Teleport::Teleport()
{

}
Teleport::~Teleport(){

}
//Modifiers
void Teleport::setExitBounds(sf::FloatRect exit){
    this->exitBounds = exit;
}

void Teleport::setDirection(const float X, const float Y){
    this->exitX = X;
    this->exitY = Y;
}
//Metody klasy
void Teleport::teleportPlayer(Player &player){
    if(exitY > 0){
        player.setPosition(this->exitBounds.left,
                            this->exitBounds.top + this->exitBounds.height);
    }
    else if(exitY < 0){
        player.setPosition(this->exitBounds.left,
                            this->exitBounds.top - player.getBounds().height);
    }
    if(exitX > 0){
        player.setPosition(this->exitBounds.left + this->exitBounds.width,
                            this->exitBounds.top);
    }
    else if(exitX < 0){
        player.setPosition(this->exitBounds.left - player.getBounds().width,
                            this->exitBounds.top);
    }
}
