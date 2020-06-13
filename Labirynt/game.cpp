#include "game.h"
#include <iostream>
/*
    Funkcje wykonujace inne funkcje
*/
//Cons/des
Game::Game()
{
    /*
        - Funkcje inicjalizujace
    */
    this->initWindow();
    this->initGui();
    this->initTime();
    this->initVariables();
    this->initTextures();
}

Game::~Game()
{
    /*
        - Usuwanie wszystkich wskaźników
    */
    delete this->window_;

    for(auto &i : textures_){
        delete i.second;
    }

    for(auto *i : this->enemyBullets){
        delete i;
    }

    for(auto *bul : this->playerBullets){
        delete bul;
    }

    delete this->clock;
}

//Metody klasy
void Game::run(){
    /*
        -
    */
    while (this->window_->isOpen()) {
        if(this->level == this->nextLevel){
            this->createLevel(this->level);
            this->nextLevel++;
        }
        updatePollEvents();
        if(!this->endgame){
            update();
        }
        render();
        this->endLevel();
    }
}

void Game::updateTime(){
    /*
        - Pobranie czasu miedzy kolejnymi klatkami
    */
    this->elapsed = this->clock->restart();
}

void Game::updatePollEvents(){
    /*
        - Zdarzenia
    */
    while (this->window_->pollEvent(this->ev_)) {
        if(this->ev_.type == sf::Event::Closed){
            this->window_->close();
        }
        if(this->ev_.key.code == sf::Keyboard::Escape){
            this->window_->close();
        }
        if(this->ev_.key.code == sf::Keyboard::R){
            this->endgame = false;
            this->nextLevel = this->level;
            this->walls.clear();
            this->boxes.clear();
            this->buttons.clear();
            this->removableWalls.clear();
            this->teleports.clear();
            this->sagittariuses.clear();
            this->dirX.clear();
            this->dirY.clear();
            this->distance.clear();
            this->enemyBullets.clear();
            this->counterRemoveWall.clear();
            this->weapons.clear();
            for(auto *bul : this->enemyBullets){
                delete bul;
            }
            this->enemyBullets.clear();
            for(auto *bul : this->playerBullets){
                delete bul;
            }
            this->playerBullets.clear();
        }
        if(this->ev_.key.code == sf::Keyboard::E){
            for(auto &w : this->weapons){
                if(this->player->getBounds().intersects(w->getGlobalBounds())){
                    w->pickUpWeapon(true);
                }
            }
        }
        if(this->ev_.key.code == sf::Keyboard::Q){
            for(auto &w : this->weapons){
                if(this->player->getBounds().intersects(w->getGlobalBounds())){
                    w->pickUpWeapon(false);
                }
            }
        }
    }
}

void Game::update(){
    /*
        - Funkcje aktualizujace gre
    */
    this->updateTime();
    this->updateInput();
    this->updateWallCollision();
    this->updateRemovableWallCollision();
    this->updateBoxCollision();
    this->updateBoxWallCollsion();
    this->updateBoxRemovableWallCollision();
    this->updateBoxPlayerCollision();
    this->updatePlayer();
    this->weaponPicked();
    this->updateWeaponsReload();
    this->updateSagittarius();
    this->dogChangeDir();
    this->updateRandDogs();
    this->updateBullets();
    this->updatePlayerBullets();
    this->updateCombatPlayer();
    this->updateCombat();
    this->doesEnemySeePlayer();
    this->teleportPlayer();
    this->updateCollision();
    this->updateButtonBox();
    this->removeWalls();
    this->resetBoxes();
}

void Game::render(){
    /*
        - Tworzenie kolejnych klatek gry
    */
    this->window_->clear(sf::Color::White);

    //render staff
    if(this->buttons.size()>0){
        for(auto &button : this->buttons){
            this->window_->draw(*button);
        }
    }

    if(this->walls.size()>0){
        for(auto &wall : this->walls){
            this->window_->draw(*wall);
        }
    }

    if(this->boxes.size()>0){
        for(auto &box : this->boxes){
            this->window_->draw(*box);
        }
    }

    if(this->removableWalls.size()>0){
        for(auto &wall : this->removableWalls){
            this->window_->draw(*wall);
        }
    }

    this->window_->draw(*this->finish);
    /*
    if(this->changeDirection.size()>0){
        for(auto &rect : this->changeDirection){
            this->window_->draw(rect);
        }
    }*/

    if(this->teleports.size()>0){
        for(auto &tp : this->teleports){
            this->window_->draw(*tp);
        }
    }

    if(this->sagittariuses.size()>0){
        for(auto &sg : this->sagittariuses){
            this->window_->draw(*sg);
        }
    }

    if(this->randDogs.size()>0){
        for(auto &dog : this->randDogs){
            this->window_->draw(*dog);
        }
    }

    if(this->enemyBullets.size()>0){
        for(auto *bul : this->enemyBullets){
            this->window_->draw(*bul);
        }
    }

    if(this->playerBullets.size()>0){
        for(auto *bul : this->playerBullets){
            this->window_->draw(*bul);
        }
    }

    this->player->render(*this->window_);

    if(this->weapons.size()>0){
        for(auto &w : this->weapons){
            this->window_->draw(*w);
        }
    }


    //endgame screen
    if(this->endgame){
        this->window_->draw(this->endgameText);
    }

    this->window_->display();
}






















