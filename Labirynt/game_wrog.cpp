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

void Game::updateRandDogs(){
    for(auto &d : randDogs){
        d->setPossibleTrack(this->walls);
        d->updatePossibleWay();
        d->update();
    }
}

void Game::dogChangeDir(){
    for(auto &d : this->randDogs){
        for(size_t i = 0; i<this->changeDirection.size(); i++){
            if(d->getGlobalBounds().intersects(this->changeDirection[i].getGlobalBounds())){
                    if(firstTime[i]){
                            if(d->getDirection().y > 0){
                                int dir2 = rand()%3;
                                if(dir2 == 0){
                                    d->setMovementSpeed(3.f,0.f);
                                }
                                else if(dir2 == 1){
                                    d->setMovementSpeed(0.f,3.f);
                                }
                                else if(dir2 == 2){
                                    d->setMovementSpeed(-3.f,0.f);
                                }
                            }
                            else if(d->getDirection().y < 0){
                                int dir2 = rand()%3;
                                if(dir2 == 0){
                                    d->setMovementSpeed(3.f,0.f);
                                }
                                else if(dir2 == 1){
                                    d->setMovementSpeed(0.f,-3.f);
                                }
                                else if(dir2 == 2){
                                    d->setMovementSpeed(-3.f,0.f);
                                }
                            }
                            else if(d->getDirection().x > 0){
                                int dir2 = rand()%3;
                                if(dir2 == 0){
                                    d->setMovementSpeed(0.f,-3.f);
                                }
                                else if(dir2 == 1){
                                    d->setMovementSpeed(3.f,0.f);
                                }
                                else if(dir2 == 2){
                                    d->setMovementSpeed(0.f,3.f);
                                }
                            }
                            else if(d->getDirection().x < 0){
                                int dir2 = rand()%3;
                                if(dir2 == 0){
                                    d->setMovementSpeed(-3.f,0.f);
                                }
                                else if(dir2 == 1){
                                    d->setMovementSpeed(0.f,-3.f);
                                }
                                else if(dir2 == 2){
                                    d->setMovementSpeed(0.f,3.f);
                                }
                            }
                        firstTime[i] = false;
                    }
                }else firstTime[i] = true;
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
            this->endgame = true;
        }
        counter++;
    }
    for(auto &dog : this->randDogs){
        if(dog->getGlobalBounds().intersects(this->player->getBounds())){
            this->endgame = true;
        }
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

void Game::updateBoss()
{
    if(this->boss.size()>0)
    {
        this->finish->followBoss(*this->boss[0]);
        for(size_t i = 0; i<this->boss.size(); i++){
            this->boss[i]->updateGui();
            this->boss[i]->die();
            this->boss[i]->move();
            this->boss[i]->airAttack(*this->player);
            this->boss[i]->shoot(*this->player);
            this->boss[i]->closeHit(*this->player);
            if(this->boss[i]->endGame()){
                this->endgame = true;
            }
            if(this->boss[i]->isDead()){
                this->boss.erase(this->boss.begin() + i);
            }
        }
    }
}














