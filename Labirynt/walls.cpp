#include "walls.h"

//cons/des
Walls::Walls()
{
    this->canBeClosestToEnemy = false;
}
Walls::~Walls(){

}
//Metody klasy
void Walls::reMove(const float X, const float Y){
        move(X,Y);
}

//Modifiers
void Walls::setDirectionForEnemy(const bool dir){
    if(dir){
        this->directionForEnemy = 1;
    }else this->directionForEnemy = -1;

}

void Walls::setCanBeClosest(bool close){
    this->canBeClosestToEnemy = close;
}
//Accessors
int Walls::giveDirectionToEnemy(){
    return this->directionForEnemy;
}

bool Walls::getCanBeClosest(){
    return this->canBeClosestToEnemy;
}
