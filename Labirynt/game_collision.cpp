#include "game.h"
#include <iostream>
/*
    Funkcje wykrywajace kolizje miedzy graczem, bramami
*/
void Game::updateCollision(){
    /*
        - Sprawdzanie, czy gracz nie wychodzi poza granice okna
        - Ustawianie gracza na granicy w prypadku jej przekroczenia
    */
    //left
    if(this->player->getBounds().left<= 0.f){
        this->player->setPosition(0.f,this->player->getBounds().top);
    }
    //right
    else if(this->player->getBounds().left + this->player->getBounds().width >= this->window_->getSize().x){
        this->player->setPosition(this->window_->getSize().x - this->player->getBounds().width
                                  ,this->player->getBounds().top);
    }
    //top
    if(this->player->getBounds().top<= 0.f){
        this->player->setPosition(this->player->getBounds().left,0.f);
    }
    //bottom
    else if(this->player->getBounds().top + this->player->getBounds().height>= this->window_->getSize().y){
        this->player->setPosition(this->player->getBounds().left
                                  ,this->window_->getSize().y - this->player->getBounds().height);
    }
}

void Game::updateWallCollision(){
    /*
        - Sprawdzanie kolizji gracza ze zwykłymi scianami
        - Nie pozwala graczowi wejsc w sciane/przejsc przez nia
        - Na ten moment nie dziala poprawinie (dziala poprawnie tylko w przypadku uzywania tylko jednego przycisku
        ruchu w tym samym momencie
        !!!POPRAWIC
    */
    for(auto &wall : this->walls){
        sf::FloatRect playerBounds = this->player->getBounds();
        sf::FloatRect wallBounds = wall->getGlobalBounds();
        this->nextPos_ = playerBounds;
        this->nextPos_.left += this->velocity_.x;
        this->nextPos_.top += this->velocity_.y;

        if(wallBounds.intersects(nextPos_)){
            //bottom collision
            if(playerBounds.top < wallBounds.top
               &&playerBounds.top + playerBounds.height<wallBounds.top + wallBounds.height
               &&playerBounds.left < wallBounds.left + wallBounds.width
               &&playerBounds.left + playerBounds.width>wallBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                this->velocity_.y = 0.f;
                this->player->setPosition(playerBounds.left,wallBounds.top-playerBounds.height);

            }
            //top collision
            else if(playerBounds.top > wallBounds.top
               &&playerBounds.top + playerBounds.height>wallBounds.top+ wallBounds.height
               &&playerBounds.left < wallBounds.left + wallBounds.width
               &&playerBounds.left + playerBounds.width>wallBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                this->velocity_.y=0.f;
                this->player->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
            }
            //right collision
            if(playerBounds.left < wallBounds.left
               &&playerBounds.left + playerBounds.width<wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left - playerBounds.width,playerBounds.top);
            }
            //left collision
            else if(playerBounds.left > wallBounds.left
               &&playerBounds.left + playerBounds.width>wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left + wallBounds.width,playerBounds.top);
            }
        }
    }
}

void Game::updateRemovableWallCollision(){
    /*
        - Wykrywanie kolizji z bramami, czyli ze scianami ktore sie przesuwaja, gdy wcisniemy przycisk
        - Nie pozwala graczowi wejsc w brame/przejsc przez nia
        - Na ten moment nie dziala poprawinie (dziala poprawnie tylko w przypadku uzywania tylko jednego przycisku
        ruchu w tym samym momencie jednak w tym przypadku jest to bardzo malo przeszkadzajace
        !!!POPRAWIC
    */
    for(auto &wall : this->removableWalls){
        sf::FloatRect playerBounds = this->player->getBounds();
        sf::FloatRect wallBounds = wall->getGlobalBounds();
        this->nextPos_ = playerBounds;
        this->nextPos_.left += this->velocity_.x;
        this->nextPos_.top += this->velocity_.y;

        if(wallBounds.intersects(nextPos_)){
            //bottom collision
            if(playerBounds.top < wallBounds.top
               &&playerBounds.top + playerBounds.height<wallBounds.top + wallBounds.height
               &&playerBounds.left < wallBounds.left + wallBounds.width
               &&playerBounds.left + playerBounds.width>wallBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                this->velocity_.y = 0.f;
                this->player->setPosition(playerBounds.left,wallBounds.top-playerBounds.height);

            }
            //top collision
            else if(playerBounds.top > wallBounds.top
               &&playerBounds.top + playerBounds.height>wallBounds.top+ wallBounds.height
               &&playerBounds.left < wallBounds.left + wallBounds.width
               &&playerBounds.left + playerBounds.width>wallBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                this->velocity_.y=0.f;
                this->player->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
            }
            //right collision
            if(playerBounds.left < wallBounds.left
               &&playerBounds.left + playerBounds.width<wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left - playerBounds.width,playerBounds.top);
            }
            //left collision
            else if(playerBounds.left > wallBounds.left
               &&playerBounds.left + playerBounds.width>wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left + wallBounds.width,playerBounds.top);
            }
        }
    }
}

void Game::updateBoxCollision(){
    /*
        - Wykrywanie kolizji gracza z pudelkami
        - W przypadku wykrycia kolizji, pudelko przesuwa sie razem synchronicznie tak jak gracz
        - Na razie gracz moze jednak wejsc swoja tekstura w pudelko przy duzej szybkosci
        - Jezeli wcisniemy dwa przyciski ruchu na raz (np. "D" i "S") to pudelko prawdopodobnie przemiesci sie na
        naroznik tekstury gracza
        !!!POPRAWIC
    */
    for(auto &box : this->boxes){
        sf::FloatRect playerBounds = this->player->getBounds();
        sf::FloatRect boxBounds = box->getGlobalBounds();

        if(boxBounds.intersects(playerBounds)){
            //bottom collision
            if(playerBounds.top < boxBounds.top
               &&playerBounds.top + playerBounds.height<boxBounds.top + boxBounds.height
               &&playerBounds.left < boxBounds.left + boxBounds.width
               &&playerBounds.left + playerBounds.width>boxBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

                    box->setPosition(box->getGlobalBounds().left,
                                     this->player->getBounds().top+this->player->getBounds().height);
            }
            //top collision
            else if(playerBounds.top > boxBounds.top
               &&playerBounds.top + playerBounds.height>boxBounds.top+ boxBounds.height
               &&playerBounds.left < boxBounds.left + boxBounds.width
               &&playerBounds.left + playerBounds.width>boxBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

                box->setPosition(box->getGlobalBounds().left,
                                 this->player->getBounds().top - box->getGlobalBounds().height);
            }
            //right collision
            if(playerBounds.left < boxBounds.left
               &&playerBounds.left + playerBounds.width<boxBounds.left + boxBounds.width
               &&playerBounds.top < boxBounds.top + boxBounds.height
               &&playerBounds.top + playerBounds.height>boxBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

                    box->setPosition(this->player->getBounds().left + this->player->getBounds().width,
                                     box->getGlobalBounds().top);
            }
            //left collision
            else if(playerBounds.left > boxBounds.left
               &&playerBounds.left + playerBounds.width>boxBounds.left + boxBounds.width
               &&playerBounds.top < boxBounds.top + boxBounds.height
               &&playerBounds.top + playerBounds.height>boxBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

                    box->setPosition(this->player->getBounds().left - box->getGlobalBounds().width,
                                     box->getGlobalBounds().top );
            }
        }
    }
}

void Game::updateBoxWallCollsion(){
    /*
        - Wykrywa kolzije pudelka ze sciana i informuje w ktora strone pudelko NIE moze byc przesuniete
    */
    for(auto &box : boxes){
        for(auto &wall : walls){
            box->setCanMove(wall->getGlobalBounds());
        }
    }
}

void Game::updateBoxRemovableWallCollision(){
    /*
        - Wykrywa kolzije pudelka z brama i informuje w ktora strone pudelko NIE moze byc przesuniete
    */
    for(auto &box : boxes){
        for(auto &wall : this->removableWalls){
            box->setCanMove(wall->getGlobalBounds());
        }
    }
}

void Game::resetBoxes(){
    /*
        - Ta funkcja umozliwia nam przesuwanie pudelka w kierunku, w ktorym przedtem nie moglo sie przesuwac ze wzgledu
        na poprzednia funkcje
    */
    for(auto &box:this->boxes){
        box->reset();
    }
}

void Game::updateBoxPlayerCollision(){
    /*
        - Wykrywa kolizje gracza z pudelkiem kiedy pudelko jest przyblokowane przez sciane
        - Uniemozliwia graczowi wejscie w pudelko, gdy pudelko nie moze juz byc dalej przesuniete
    */
    for(auto &box : this->boxes){
        sf::FloatRect playerBounds = this->player->getBounds();
        sf::FloatRect boxBounds = box->getGlobalBounds();
        this->nextPos_ = playerBounds;
        this->nextPos_.left += this->velocity_.x;
        this->nextPos_.top += this->velocity_.y;

        if(boxBounds.intersects(nextPos_)){
            //bottom collision
            if(playerBounds.top < boxBounds.top
               &&playerBounds.top + playerBounds.height<boxBounds.top + boxBounds.height
               &&playerBounds.left < boxBounds.left + boxBounds.width
               &&playerBounds.left + playerBounds.width>boxBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::S)
               &&!box->getCanMoveBot()){
                    this->velocity_.y = 0;
                    this->player->setPosition(playerBounds.left,
                                              boxBounds.top - playerBounds.height);
            }
            //top collision
            else if(playerBounds.top > boxBounds.top
               &&playerBounds.top + playerBounds.height>boxBounds.top+ boxBounds.height
               &&playerBounds.left < boxBounds.left + boxBounds.width
               &&playerBounds.left + playerBounds.width>boxBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::W)
               &&!box->getCanMoveTop()){
                    this->velocity_.y = 0;
                    this->player->setPosition(playerBounds.left,
                                          boxBounds.top + boxBounds.height);
            }
            //right collision
            if(playerBounds.left < boxBounds.left
               &&playerBounds.left + playerBounds.width<boxBounds.left + boxBounds.width
               &&playerBounds.top < boxBounds.top + boxBounds.height
               &&playerBounds.top + playerBounds.height>boxBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)
               &&!box->getCanMoveRight()){
                    this->velocity_.x = 0;
                    this->player->setPosition(boxBounds.left - playerBounds.width,
                                              playerBounds.top);
            }
            //left collision
            else if(playerBounds.left > boxBounds.left
               &&playerBounds.left + playerBounds.width>boxBounds.left + boxBounds.width
               &&playerBounds.top < boxBounds.top + boxBounds.height
               &&playerBounds.top + playerBounds.height>boxBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)
               &&!box->getCanMoveLeft()){
                    this->velocity_.x = 0;
                    this->player->setPosition(boxBounds.left + boxBounds.height,
                                              playerBounds.top);
            }
        }
    }
}

void Game::updateButtonBox(){
    /*
        - Wykrywa kolizje pudelka z przyciskiem
        - Gdy pudelko wejdzie na przycisk, wtedy przycisk jest uznany za wcisniety
    */
    for(auto &button : this->buttons){
        for(auto &box : this->boxes){
            button->pressButton(box->getGlobalBounds());
        }
    }
}



void Game::removeWalls(){
    /*
        - Gdy odpowiedni przycisk jest wcisniety, wtedy odpowiednia brama zaczyna sie otwierac/przesuwac
        - Bardziej czytelnym rozwiazaniem byloby wykorzystanie mapy, ale przy tak malym projekcie takie rozwiazanie
        tez jest skuteczne
        !Opcjonalnie poprawic
    */
    for(size_t i = 0; i<this->buttons.size(); i++){
        if(this->buttons[i]->isButtonPressed()
                &&this->counterRemoveWall[i] < this->distance[i]){
            this->removableWalls[i]->reMove(this->dirX[i],
                                            this->dirY[i]);
            this->counterRemoveWall[i]++;
        }
    }
}




