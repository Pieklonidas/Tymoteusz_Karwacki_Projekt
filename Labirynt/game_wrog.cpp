#include "game.h"
#include <iostream>

void Game::updateSagittarius(){
    for(auto &sag : this->sagittariuses){
        for(auto &wall : this->walls){
            sag->checkCollision(wall->getGlobalBounds(),wall->giveDirectionToEnemy());
        }
        sag->update();
    }
    for(auto &sag : this->sagittariuses){
        sag->setVision();
        for(auto &wall : this->walls){
            if(wall->getCanBeClosest()
            &&wall->getGlobalBounds().intersects(sag->getVision())){
                sag->setVision(wall->getGlobalBounds());
            }
        }
    }
}

void Game::doesEnemySeePlayer(){
    for(auto &sag : this->sagittariuses){
        if(this->player->getBounds().intersects(sag->getVision())&&sag->startShooting()){
            this->enemyBullets.push_back(new Bullets(
                                             this->textures_["BULLET"],
                                             sag->shootDirection().x,
                                             sag->shootDirection().y,
                                             sag->getGlobalBounds().left,
                                             sag->getGlobalBounds().top+sag->getGlobalBounds().height/2
                                             ));
        }
    }
}

void Game::updateCombat(){
    unsigned counter = 0;
    for(auto *bul : this->enemyBullets){
        if(bul->getGlobalBounds().intersects(this->player->getBounds())){
            delete this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter--;
            endgame = true;
        }
        counter++;
    }
}

void Game::updateBullets(){
    /*
        - Sprawdzanie, czy pociski nie wychodza poza okno
        - Usuwanie pociskow, ktore wyszly poza okno
    */
    unsigned counter = 0;
    for(auto *bul : this->enemyBullets){
        bul->shoot();
        //Right border
        if(bul->getGlobalBounds().left > this->window_->getSize().x){
            delete this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter--;
        }
        //Left border
        else if(bul->getGlobalBounds().left+bul->getGlobalBounds().width < 0){
            delete this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter --;
        }
        //Bottom border
        if(bul->getGlobalBounds().top > this->window_->getSize().y){
            delete this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter --;
        }
        //Top border
        else if(bul->getGlobalBounds().top + bul->getGlobalBounds().height < 0){
            delete this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter --;
        }
        counter++;
    }
    unsigned counter2 = 0;
    for(auto *bul : this->enemyBullets){
        for(auto &w : this->walls){
            if(bul->getGlobalBounds().intersects(w->getGlobalBounds())){
                delete this->enemyBullets.at(counter2);
                this->enemyBullets.erase(this->enemyBullets.begin() + counter2);
                counter2--;
            }
        }
        counter2++;
    }
}
