#include "game.h"
#include <iostream>
//Funkcje prywatne
void Game::initWindow(){
    /*
        Inicjacja okna
    */
    this->videoMode_ = sf::VideoMode(1200,600);
    this->window_ = new sf::RenderWindow(this->videoMode_,"Labirynt", sf::Style::Close | sf::Style::Titlebar);
    this->window_->setFramerateLimit(60);
}

void Game::initTime(){
    this->clock = new sf::Clock();
}

void Game::initVariables(){
    this->level = 1;
    this->nextLevel = this->level;
}

void Game::initTextures(){
    this->textures_["GRACZ"] = new sf::Texture();
    this->textures_["GRACZ"]->loadFromFile("Obrazki\\Maciek_2.png");
    this->textures_["WALL"] = new sf::Texture();
    this->textures_["WALL"]->loadFromFile("Obrazki\\wall.png");
    this->textures_["WALL"]->setRepeated(true);
    this->textures_["BOX"] = new sf::Texture();
    this->textures_["BOX"]->loadFromFile("Obrazki\\Box.png");
    this->textures_["BUTTON"] = new sf::Texture();
    this->textures_["BUTTON"]->loadFromFile("Obrazki\\Button.png");
    this->textures_["GATE"] = new sf::Texture();
    this->textures_["GATE"]->loadFromFile("Obrazki\\Gate.png");
    this->textures_["GATE"]->setRepeated(true);
    this->textures_["FINISH"] = new sf::Texture();
    this->textures_["FINISH"]->loadFromFile("Obrazki\\Finish.png");
    this->textures_["TELEPORT"] = new sf::Texture();
    this->textures_["TELEPORT"]->loadFromFile("Obrazki\\Teleport.png");
    this->textures_["STRZELEC"] = new sf::Texture();
    this->textures_["STRZELEC"]->loadFromFile("Obrazki\\Sagittarius.png");
    this->textures_["BULLET"] = new sf::Texture();
    this->textures_["BULLET"]->loadFromFile("Obrazki\\Bullets.png");
    this->textures_["RIFLE"] = new sf::Texture();
    this->textures_["RIFLE"]->loadFromFile("Obrazki\\Rifle.png");
}
//Cons/des
Game::Game()
{
    /*
        Inicjacja wszystkich elementów
    */
    this->initWindow();
    this->initTime();
    this->initVariables();
    this->initTextures();
}

Game::~Game()
{
    /*
        Usuwanie wszystkich wskaźników
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
        Run the game
    */
    while (this->window_->isOpen()) {
        if(this->level == this->nextLevel){
            this->createLevel(this->level);
            this->nextLevel++;
        }
        updatePollEvents();
        update();
        render();
        this->endLevel();
    }
}

void Game::updateTime(){
    this->elapsed = this->clock->restart();
}

void Game::updatePollEvents(){
    /*
        Zdarzenia
    */
    while (this->window_->pollEvent(this->ev_)) {
        if(this->ev_.type == sf::Event::Closed){
            this->window_->close();
        }
        if(this->ev_.key.code == sf::Keyboard::Escape){
            this->window_->close();
        }
        if(this->ev_.key.code == sf::Keyboard::R){
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
        if(this->ev_.key.code == sf::Keyboard::Z){
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
}

void Game::updateInput(){
    this->velocity_.y = 0.f;
    this->velocity_.x = 0.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->velocity_.x += -this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->velocity_.x += this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->velocity_.y += -this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->velocity_.y += this->player->getMovementSpeed()*this->elapsed.asSeconds();
    }
}

void Game::updateCollision(){
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
                //std::cout<<"TOP"<<std::endl;
            }
            //right collision
            if(playerBounds.left < wallBounds.left
               &&playerBounds.left + playerBounds.width<wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left - playerBounds.width,playerBounds.top);
                //std::cout<<"RIGHT"<<std::endl;
            }
            //left collision
            else if(playerBounds.left > wallBounds.left
               &&playerBounds.left + playerBounds.width>wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left + wallBounds.width,playerBounds.top);
                //std::cout<<"LEFT"<<std::endl;
            }
        }
    }
}

void Game::updateRemovableWallCollision(){
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
                //std::cout<<"BOT"<<std::endl;

            }
            //top collision
            else if(playerBounds.top > wallBounds.top
               &&playerBounds.top + playerBounds.height>wallBounds.top+ wallBounds.height
               &&playerBounds.left < wallBounds.left + wallBounds.width
               &&playerBounds.left + playerBounds.width>wallBounds.left
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                this->velocity_.y=0.f;
                this->player->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                //std::cout<<"TOP"<<std::endl;
            }
            //right collision
            if(playerBounds.left < wallBounds.left
               &&playerBounds.left + playerBounds.width<wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left - playerBounds.width,playerBounds.top);
                //std::cout<<"RIGHT"<<std::endl;
            }
            //left collision
            else if(playerBounds.left > wallBounds.left
               &&playerBounds.left + playerBounds.width>wallBounds.left + wallBounds.width
               &&playerBounds.top < wallBounds.top + wallBounds.height
               &&playerBounds.top + playerBounds.height>wallBounds.top
               &&sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                this->velocity_.x = 0.f;
                this->player->setPosition(wallBounds.left + wallBounds.width,playerBounds.top);
                //std::cout<<"LEFT"<<std::endl;
            }
        }
    }
}

void Game::updateBoxCollision(){
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
    for(auto &box : boxes){
        for(auto &wall : walls){
            box->setCanMove(wall->getGlobalBounds());
        }
    }
}

void Game::updateBoxRemovableWallCollision(){
    for(auto &box : boxes){
        for(auto &wall : this->removableWalls){
            box->setCanMove(wall->getGlobalBounds());
        }
    }
}

void Game::updateBoxPlayerCollision(){
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
    for(auto &button : this->buttons){
        for(auto &box : this->boxes){
            button->pressButton(box->getGlobalBounds());
        }
    }
}

void Game::teleportPlayer(){
    for(auto &teleport : this->teleports){
        if(this->player->getBounds().intersects(teleport->getGlobalBounds())){
            teleport->teleportPlayer(*this->player);
        }
    }
}

void Game::removeWalls(){
    for(size_t i = 0; i<this->buttons.size(); i++){
        if(this->buttons[i]->isButtonPressed()
                &&this->counterRemoveWall[i] < this->distance[i]){
            this->removableWalls[i]->reMove(this->dirX[i],
                                            this->dirY[i]);
            this->counterRemoveWall[i]++;
        }
    }
}

void Game::updatePlayer(){
    /*
        Moving player
    */
    this->player->move(this->velocity_.x,this->velocity_.y);
}

void Game::weaponPicked(){
    for(auto &w : this->weapons){
        if(w->isPicked()){
            w->setPosition(this->player->getBounds().left,
                           this->player->getBounds().top + this->player->getBounds().height/2);
        }
    }
}

void Game::updateWeaponsReload(){
    for(auto &w : this->weapons){
        w->updateReload();
        w->updateDirection();
    }
}

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


void Game::updateBullets(){
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
}

void Game::updatePlayerBullets(){
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
}

void Game::updateCombat(){
    unsigned counter = 0;
    for(auto *bul : this->enemyBullets){
        if(bul->getGlobalBounds().intersects(this->player->getBounds())){
            this->enemyBullets.at(counter);
            this->enemyBullets.erase(this->enemyBullets.begin() + counter);
            counter--;
        }
        counter++;
    }
}

void Game::resetBoxes(){
    for(auto &box:this->boxes){
        box->reset();
    }
}

void Game::endLevel(){
    if(this->player->getBounds().intersects(this->finish->getGlobalBounds())){
        this->level++;
        this->walls.clear();
        this->boxes.clear();
        this->buttons.clear();
        this->removableWalls.clear();
        this->teleports.clear();
        this->sagittariuses.clear();
        this->dirX.clear();
        this->dirY.clear();
        this->distance.clear();
        this->counterRemoveWall.clear();
        for(auto *bul : this->enemyBullets){
            delete bul;
        }
        this->enemyBullets.clear();
        for(auto *bul : this->playerBullets){
            delete bul;
        }
        this->playerBullets.clear();
        this->weapons.clear();
    }
}

void Game::update(){
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
    this->updateBullets();
    this->updatePlayerBullets();
    this->updateCombat();
    this->doesEnemySeePlayer();
    this->teleportPlayer();
    this->updateCollision();
    this->updateButtonBox();
    this->removeWalls();
    this->resetBoxes();
}

void Game::render(){
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


    this->window_->display();
}

void Game::createLevel(int level){
    if(level == 1){
        //walls
        for(int i = 0; i<37; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->walls.push_back(std::move(wall));
        }
        for(auto &wall : this->walls){
            wall->setTexture(*this->textures_["WALL"]);
        }
        walls[0]->setTextureRect(sf::IntRect(0,0,150,20));//
        walls[0]->setPosition(0.f,250.f);
        walls[1]->setTextureRect(sf::IntRect(0,0,150,20));//
        walls[1]->setPosition(0.f,350.f);
        walls[2]->setTextureRect(sf::IntRect(0,0,20,200));//
        walls[2]->setPosition(130.f,50.f);
        walls[3]->setTextureRect(sf::IntRect(0,0,300,20));//
        walls[3]->setPosition(150.f,50.f);
        walls[4]->setTextureRect(sf::IntRect(0,0,20,50));//
        walls[4]->setPosition(430.f,0.f);
        walls[5]->setTextureRect(sf::IntRect(0,0,80,20));//
        walls[5]->setPosition(450.f,0.f);
        walls[6]->setTextureRect(sf::IntRect(0,0,20,70));//
        walls[6]->setPosition(530.f,0.f);
        walls[7]->setTextureRect(sf::IntRect(0,0,550,20));//
        walls[7]->setPosition(550.f,50.f);
        walls[8]->setTextureRect(sf::IntRect(0,0,20,150));//
        walls[8]->setPosition(1100.f,50.f);
        walls[9]->setTextureRect(sf::IntRect(0,0,120,20));//
        walls[9]->setPosition(1000.f,200.f);
        walls[10]->setTextureRect(sf::IntRect(0,0,20,150));//
        walls[10]->setPosition(980.f,200.f);
        walls[11]->setTextureRect(sf::IntRect(0,0,170,20));//
        walls[11]->setPosition(830.f,350.f);
        walls[12]->setTextureRect(sf::IntRect(0,0,20,90));//
        walls[12]->setPosition(810.f,280.f);
        walls[13]->setTextureRect(sf::IntRect(0,0,400,20));//
        walls[13]->setPosition(410.f,280.f);
        walls[14]->setTextureRect(sf::IntRect(0,0,20,120));//
        walls[14]->setPosition(390.f,180.f);
        walls[15]->setTextureRect(sf::IntRect(0,0,420,20));//
        walls[15]->setPosition(410.f,180.f);
        walls[16]->setTextureRect(sf::IntRect(0,0,20,30));//
        walls[16]->setPosition(810.f,150.f);
        walls[17]->setTextureRect(sf::IntRect(0,0,550,20));//
        walls[17]->setPosition(260.f,150.f);
        walls[18]->setTextureRect(sf::IntRect(0,0,20,120));//
        walls[18]->setPosition(240.f,150.f);
        walls[19]->setTextureRect(sf::IntRect(0,0,120,20));//
        walls[19]->setPosition(260.f,250.f);
        walls[20]->setTextureRect(sf::IntRect(0,0,20,100));//
        walls[20]->setPosition(360.f,270.f);
        walls[21]->setTextureRect(sf::IntRect(0,0,120,20));//
        walls[21]->setPosition(240.f,350.f);
        walls[22]->setTextureRect(sf::IntRect(0,0,20,50));//
        walls[22]->setPosition(240.f,370.f);
        walls[23]->setTextureRect(sf::IntRect(0,0,200,20));//
        walls[23]->setPosition(260.f,400.f);
        walls[24]->setTextureRect(sf::IntRect(0,0,20,100));//
        walls[24]->setPosition(460.f,320.f);
        walls[25]->setTextureRect(sf::IntRect(0,0,150,20));//
        walls[25]->setPosition(480.f,320.f);
        walls[26]->setTextureRect(sf::IntRect(0,0,20,70));//
        walls[26]->setPosition(630.f,320.f);
        walls[27]->setTextureRect(sf::IntRect(0,0,200,20));//
        walls[27]->setPosition(650.f,370.f);
        walls[28]->setTextureRect(sf::IntRect(0,0,20,100));//
        walls[28]->setPosition(850.f,370.f);
        walls[29]->setTextureRect(sf::IntRect(0,0,120,20));//
        walls[29]->setPosition(750.f,470.f);
        walls[30]->setTextureRect(sf::IntRect(0,0,20,110));//
        walls[30]->setPosition(750.f,490.f);
        walls[31]->setTextureRect(sf::IntRect(0,0,270,20));//
        walls[31]->setPosition(480.f,580.f);
        walls[32]->setTextureRect(sf::IntRect(0,0,20,110));//
        walls[32]->setPosition(460.f,490.f);
        walls[33]->setTextureRect(sf::IntRect(0,0,440,20));//
        walls[33]->setPosition(20.f,490.f);
        walls[34]->setTextureRect(sf::IntRect(0,0,20,80));//
        walls[34]->setPosition(0.f,430.f);
        walls[35]->setTextureRect(sf::IntRect(0,0,150,20));//
        walls[35]->setPosition(0.f,420.f);
        walls[36]->setTextureRect(sf::IntRect(0,0,20,50));
        walls[36]->setPosition(130.f,370.f);
        //player
        this->player = std::make_unique<Player>();
        this->player->setScale(0.35,0.35);
        this->player->setPosition(0.f,290.f);
        this->player->setTexture(this->textures_["GRACZ"]);
        //boxes
        for(int i = 0; i<2; i++){
            std::unique_ptr<Boxes> box = std::make_unique<Boxes>();
            this->boxes.push_back(std::move(box));
        }
        for(auto &box : this->boxes){
            box->setTexture(*this->textures_["BOX"]);
            box->setScale(0.3,0.3);
        }
        this->boxes[0]->setPosition(466.f,250.f);//13
        this->boxes[1]->setPosition(720.f,500);
        //buttons
        for(int i = 0; i<2; i++){
            std::unique_ptr<Button> button = std::make_unique<Button>();
            this->buttons.push_back(std::move(button));
        }
        for(auto &button: this->buttons){
            button->setTexture(*this->textures_["BUTTON"]);
        }
        this->buttons[0]->setPosition(465.f,20.f);
        this->buttons[1]->setPosition(20.f,440.f);
        //removable walls
        for(int i = 0; i<2; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->removableWalls.push_back(std::move(wall));
            this->counterRemoveWall.push_back(0);
            this->distance.push_back(0);
        }
        for(auto &wall: this->removableWalls){
            wall->setTexture(*this->textures_["GATE"]);
        }
        this->removableWalls[0]->setTextureRect(sf::IntRect(0,0,20,50));
        this->removableWalls[0]->setPosition(130.f,440.f);
        this->removableWalls[1]->setTextureRect(sf::IntRect(0,0,20,80));
        this->removableWalls[1]->setPosition(240.f,270.f);
        for(size_t i = 0; i<this->removableWalls.size(); i++){
            this->distance[i] = this->removableWalls[i]->getGlobalBounds().height;
        }
        this->dirX.push_back(0.f);
        this->dirX.push_back(0.f);
        this->dirY.push_back(-1.f);
        this->dirY.push_back(-1.f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(310.f,300.f);

    }
    if(level == 2){
        //walls
        for(int i = 0; i<11; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->walls.push_back(std::move(wall));
        }
        for(auto &wall : this->walls){
            wall->setTexture(*this->textures_["WALL"]);
        }
        this->walls[0]->setTextureRect(sf::IntRect(0,0,40,250));
        this->walls[0]->setPosition(100.f,350.f);
        this->walls[1]->setTextureRect(sf::IntRect(0,0,150,40));
        this->walls[1]->setPosition(140.f,350.f);
        this->walls[2]->setTextureRect(sf::IntRect(0,0,40,190));
        this->walls[2]->setPosition(290.f,200.f);
        this->walls[3]->setTextureRect(sf::IntRect(0,0,150,40));
        this->walls[3]->setPosition(140.f,200.f);
        this->walls[4]->setTextureRect(sf::IntRect(0,0,40,240));
        this->walls[4]->setPosition(100.f,0.f);
        this->walls[5]->setTextureRect(sf::IntRect(0,0,40,350));
        this->walls[5]->setPosition(1000.f,250.f);
        this->walls[6]->setTextureRect(sf::IntRect(0,0,500,40));
        this->walls[6]->setPosition(500.f,250.f);
        this->walls[7]->setTextureRect(sf::IntRect(0,0,40,250));
        this->walls[7]->setPosition(500.f,0.f);
        this->walls[8]->setTextureRect(sf::IntRect(0,0,40,150));
        this->walls[8]->setPosition(650.f,0.f);
        this->walls[9]->setTextureRect(sf::IntRect(0,0,350,40));
        this->walls[9]->setPosition(690.f,110.f);
        this->walls[10]->setTextureRect(sf::IntRect(0,0,40,110));
        this->walls[10]->setPosition(1000.f,0.f);
        //player
        this->player = std::make_unique<Player>();
        this->player->setTexture(this->textures_["GRACZ"]);
        this->player->setPosition(0.f,500.f);
        this->player->setScale(0.8f,0.8f);
        //boxes
        for(int i = 0; i<2; i++){
            std::unique_ptr<Boxes> box = std::make_unique<Boxes>();
            this->boxes.push_back(std::move(box));
        }
        for(auto &box : this->boxes){
            box->setTexture(*this->textures_["BOX"]);
            box->setScale(0.6,0.6);
        }
        this->boxes[0]->setPosition(570.f,100.f);
        this->boxes[1]->setPosition(1120.f,170.f);
        //buttons
        for(int i = 0; i<2; i++){
            std::unique_ptr<Button> button = std::make_unique<Button>();
            this->buttons.push_back(std::move(button));
        }
        for(auto &button: this->buttons){
            button->setTexture(*this->textures_["BUTTON"]);
        }
        this->buttons[0]->setPosition(570.f,0.f);
        this->buttons[1]->setPosition(1100.f,0.f);
        //removable walls
        for(int i = 0; i<2; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->removableWalls.push_back(std::move(wall));
            this->counterRemoveWall.push_back(0);
            this->distance.push_back(0);
        }
        for(auto &wall: this->removableWalls){
            wall->setTexture(*this->textures_["GATE"]);
        }
        this->removableWalls[0]->setTextureRect(sf::IntRect(0,0,40,160));
        this->removableWalls[0]->setPosition(1200.f,110.f);
        this->removableWalls[1]->setTextureRect(sf::IntRect(0,0,40,110));
        this->removableWalls[1]->setPosition(100.f,240.f);
        for(size_t i = 0; i<this->removableWalls.size(); i++){
            this->distance[i] = this->removableWalls[i]->getGlobalBounds().height;
        }
        this->removableWalls[0]->rotate(90.f);
        this->dirX.push_back(-1.f);
        this->dirX.push_back(0.f);
        this->dirY.push_back(0.f);
        this->dirY.push_back(1.f);
        //Teleports
        for(int i = 0; i<2; i++){
            std::unique_ptr<Teleport> tp = std::make_unique<Teleport>();
            this->teleports.push_back(std::move(tp));
        }
        for(auto &tp : this->teleports){
            tp->setTexture(*this->textures_["TELEPORT"]);
        }
        this->teleports[0]->setPosition(0.f,0.f);
        this->teleports[1]->setPosition(1100.f,540.f);
        this->teleports[0]->setExitBounds(this->teleports[1]->getGlobalBounds());
        this->teleports[0]->setDirection(0.f,-1.f);
        this->teleports[1]->setExitBounds(this->teleports[0]->getGlobalBounds());
        this->teleports[1]->setDirection(0.f,1.f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(200.f,300.f);
    }
    if(level == 3){
        //walls
        for(int i = 0; i<25; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->walls.push_back(std::move(wall));
        }
        for(auto &wall : this->walls){
            wall->setTexture(*this->textures_["WALL"]);
        }
        this->walls[0]->setTextureRect(sf::IntRect(0,0,240,30));
        this->walls[0]->setPosition(0.f,210.f);
        this->walls[1]->setTextureRect(sf::IntRect(0,0,30,240));
        this->walls[1]->setPosition(240.f,0.f);
        this->walls[2]->setTextureRect(sf::IntRect(0,0,400,30));//
        this->walls[2]->setPosition(270.f,0.f);
        this->walls[2]->setCanBeClosest(true);
        this->walls[2]->setDirectionForEnemy(0);
        this->walls[3]->setTextureRect(sf::IntRect(0,0,30,150));//
        this->walls[3]->setPosition(670.f,0.f);
        this->walls[3]->setCanBeClosest(true);
        this->walls[3]->setDirectionForEnemy(1);
        this->walls[4]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[4]->setPosition(700.f,120.f);
        this->walls[5]->setTextureRect(sf::IntRect(0,0,30,150));//
        this->walls[5]->setPosition(850.f,120.f);
        this->walls[5]->setCanBeClosest(true);
        this->walls[5]->setDirectionForEnemy(1);
        this->walls[6]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[6]->setPosition(880.f,240.f);
        this->walls[7]->setTextureRect(sf::IntRect(0,0,30,240));
        this->walls[7]->setPosition(1000.f,0.f);
        this->walls[8]->setTextureRect(sf::IntRect(0,0,30,600));
        this->walls[8]->setPosition(1170.f,0.f);
        this->walls[9]->setTextureRect(sf::IntRect(0,0,170,30));
        this->walls[9]->setPosition(1000.f,570.f);
        this->walls[10]->setTextureRect(sf::IntRect(0,0,30,260));
        this->walls[10]->setPosition(1000.f,380.f);
        this->walls[11]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[11]->setPosition(880.f,380.f);
        this->walls[12]->setTextureRect(sf::IntRect(0,0,30,120));
        this->walls[12]->setPosition(850.f,380.f);
        this->walls[13]->setTextureRect(sf::IntRect(0,0,150,30));//
        this->walls[13]->setPosition(700.f,470.f);
        this->walls[13]->setCanBeClosest(true);
        this->walls[13]->setDirectionForEnemy(0);
        this->walls[14]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[14]->setPosition(670.f,470.f);
        this->walls[15]->setTextureRect(sf::IntRect(0,0,400,30));//
        this->walls[15]->setPosition(270.f,570.f);
        this->walls[15]->setCanBeClosest(true);
        this->walls[15]->setDirectionForEnemy(0);
        this->walls[16]->setTextureRect(sf::IntRect(0,0,30,220));//
        this->walls[16]->setPosition(240.f,380.f);
        this->walls[16]->setCanBeClosest(true);
        this->walls[16]->setDirectionForEnemy(1);
        this->walls[17]->setTextureRect(sf::IntRect(0,0,240,30));
        this->walls[17]->setPosition(0.f,380.f);
        this->walls[18]->setTextureRect(sf::IntRect(0,0,150,30));//
        this->walls[18]->setPosition(560.f,240.f);
        this->walls[18]->setCanBeClosest(true);
        this->walls[18]->setDirectionForEnemy(1);
        this->walls[19]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[19]->setPosition(530.f,140.f);
        this->walls[20]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[20]->setPosition(380.f,140.f);
        this->walls[21]->setTextureRect(sf::IntRect(0,0,30,270));
        this->walls[21]->setPosition(380.f,170.f);
        this->walls[22]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[22]->setPosition(380.f,410.f);
        this->walls[23]->setTextureRect(sf::IntRect(0,0,30,100));//
        this->walls[23]->setPosition(530.f,340.f);
        this->walls[23]->setCanBeClosest(true);
        this->walls[23]->setDirectionForEnemy(0);
        this->walls[24]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[24]->setPosition(560.f,340.f);
        //boxes
        for(int i = 0; i<1; i++){
            std::unique_ptr<Boxes> box = std::make_unique<Boxes>();
            this->boxes.push_back(std::move(box));
        }
        for(auto &box : this->boxes){
            box->setTexture(*this->textures_["BOX"]);
            box->setScale(0.6,0.6);
        }
        this->boxes[0]->setPosition(1100.f,400.f);
        //buttons
        for(int i = 0; i<1; i++){
            std::unique_ptr<Button> button = std::make_unique<Button>();
            this->buttons.push_back(std::move(button));
        }
        for(auto &button: this->buttons){
            button->setTexture(*this->textures_["BUTTON"]);
        }
        this->buttons[0]->setPosition(1075.f,0.f);
        //removable walls
        for(int i = 0; i<1; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->removableWalls.push_back(std::move(wall));
            this->counterRemoveWall.push_back(0);
            this->distance.push_back(0);
        }
        for(auto &wall: this->removableWalls){
            wall->setTexture(*this->textures_["GATE"]);
        }
        this->removableWalls[0]->setTextureRect(sf::IntRect(0,0,30,70));
        this->removableWalls[0]->setPosition(680.f,270.f);
        for(size_t i = 0; i<this->removableWalls.size(); i++){
            this->distance[i] = this->removableWalls[i]->getGlobalBounds().height;
        }
        this->dirX.push_back(0);
        this->dirY.push_back(-1);
        //player
        this->player = std::make_unique<Player>();
        this->player->setTexture(this->textures_["GRACZ"]);
        this->player->setPosition(0.f,245.f);
        this->player->setScale(0.5f,0.5f);
        //Weapons
        std::unique_ptr<Weapons> rifle = std::make_unique<Rifle>(this->textures_["RIFLE"]);
        this->weapons.push_back(std::move(rifle));
        this->weapons[0]->setPosition(1050.f,400.f);
        this->weapons[0]->setScale(0.3,0.3);
        //Strzelcy
        for(int i = 0; i<1;i++){
            std::unique_ptr<Sagittarius> sag = std::make_unique<Sagittarius>();
            this->sagittariuses.push_back(std::move(sag));
        }
        for(auto &sag : this->sagittariuses){
            sag->setTexture(*this->textures_["STRZELEC"]);
        }
        this->sagittariuses[0]->setScale(0.7f,0.7f);
        this->sagittariuses[0]->setPosition(600.f,480.f);
        this->sagittariuses[0]->setStartingMove(-2.f,0.f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(410.f,290.f);
    }
}




















