#include "finish.h"

Finish::Finish(){
    this->followBoss_ = false;
}

Finish::~Finish(){

}

void Finish::follow(bool f)
{
    this->followBoss_ = f;
}

void Finish::followBoss(Boss &boss)
{
    if(this->followBoss_){
        setPosition(boss.getPos().x + boss.getBounds().width/2.f,
                    boss.getPos().y + boss.getBounds().height/2.f);
    }
}
