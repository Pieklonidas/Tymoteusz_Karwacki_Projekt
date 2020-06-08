#include "game.h"
#include <iostream>
/*
    Funkcje wplywajace na ruch gracza oraz broni
*/
void Game::updateInput(){
    /*
        - Wczytywanie odpowiednich przyciskow z klawiatury i wykonywanie odpowiednich akcji
        - Ustawienie predkosci gracza, kierunku w jaki ma sie poruszac
        - Strzelanie z broni
    */
    this->velocity_.y = 0.f;
    this->velocity_.x = 0.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->velocity_.x += -this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->velocity_.x += this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->velocity_.y += -this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->velocity_.y += this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        for(auto &w : this->weapons){
            if(w->isPicked()&&w->reload()){
                this->playerBullets.push_back(new Bullets(
                                                 this->textures_["BULLET"],
                                                 w->shoot().x,
                                                 w->shoot().y,
                                                 w->getGlobalBounds().left,
                                                 w->getGlobalBounds().top+w->getGlobalBounds().height/2
                                                 ));
            }
        }
    }
}

void Game::teleportPlayer(){
    /*
        - Wykrywanie kolizji gracza z teleportem
        - Przenoszenie gracza w odpowienie miejsce
    */
    for(auto &teleport : this->teleports){
        if(this->player->getBounds().intersects(teleport->getGlobalBounds())){
            teleport->teleportPlayer(*this->player);
        }
    }
}

void Game::updatePlayer(){
    /*
        - Poruszanie gracza
    */
    this->player->update();
    this->player->move(this->velocity_.x,this->velocity_.y);
}

void Game::weaponPicked(){
    /*
        - Ustawianie podniesionej broni w odpowiednim miejsu (tak jakby to gracz ja nosil)
    */
    for(auto &w : this->weapons){
        if(w->isPicked()){
            w->setPosition(this->player->getBounds().left,
                           this->player->getBounds().top + this->player->getBounds().height/2);
        }
    }
}

void Game::updateWeaponsReload(){
    /*
        - Aktualizowanie czasu do wystrzelenia nastepnego pocisku
        - Aktualizowanie kierunku w ktorym aktualnie ma wystrzelic bron
    */
    for(auto &w : this->weapons){
        w->updateReload();
        w->updateDirection();
    }
}

void Game::updatePlayerBullets(){
    /*
        - Sprawdzanie czy kule wystrzelone przez gracza wyszly poza okno
        - Usuwanie pociskow, ktore wyszly poza okno
    */
    unsigned counter = 0;
    for(auto *bul : this->playerBullets){
        bul->shoot();
        //Right border
        if(bul->getGlobalBounds().left > this->window_->getSize().x){
            delete this->playerBullets.at(counter);
            this->playerBullets.erase(this->playerBullets.begin() + counter);
            counter--;
        }
        //Left border
        else if(bul->getGlobalBounds().left+bul->getGlobalBounds().width < 0){
            delete this->playerBullets.at(counter);
            this->playerBullets.erase(this->playerBullets.begin() + counter);
            counter --;
        }
        //Bottom border
        if(bul->getGlobalBounds().top > this->window_->getSize().y){
            delete this->playerBullets.at(counter);
            this->playerBullets.erase(this->playerBullets.begin() + counter);
            counter --;
        }
        //Top border
        else if(bul->getGlobalBounds().top + bul->getGlobalBounds().height < 0){
            delete this->playerBullets.at(counter);
            this->playerBullets.erase(this->playerBullets.begin() + counter);
            counter --;
        }
        counter++;
    }
    unsigned counter2 = 0;
    for(auto *bul : this->playerBullets){
        for(auto &w : this->walls){
            if(bul->getGlobalBounds().intersects(w->getGlobalBounds())){
                delete this->playerBullets.at(counter2);
                this->playerBullets.erase(this->playerBullets.begin() + counter2);
                counter2--;
            }
        }
        counter2++;
    }
}

void Game::updateCombatPlayer(){
    /*
        - Wykrywanie kolizji pociskow gracza z wrogiem
    */
    unsigned counter = 0;
    for(auto *bul : this->playerBullets){
        for(auto &e : this->sagittariuses){
            if(bul->getGlobalBounds().intersects(e->getGlobalBounds())){
                delete this->playerBullets.at(counter);
                this->playerBullets.erase(this->playerBullets.begin() + counter);
                counter--;
            }
        }
        counter++;
    }
}





