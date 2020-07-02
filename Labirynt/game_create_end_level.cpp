#include "game.h"
#include <iostream>
/*
    Funkcja konczaca poziom oraz funkcja budujaca kazdy poziom
*/
void Game::endLevel(){
    /*
        - Sprawdzanie, czy gracz doszedl do celu
        - Usuwanie wszystkich elemntow kazdego wektora
        - Informowanie, ze nalezy przejsc na nastepny poziom
    */
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
        this->randDogs.clear();
        for(auto *bul : this->enemyBullets){
            delete bul;
        }
        this->enemyBullets.clear();
        for(auto *bul : this->playerBullets){
            delete bul;
        }
        this->playerBullets.clear();
        this->weapons.clear();
        if(this->boss.size()>0){
            for(size_t i = 0; i<boss.size(); i++){
                this->boss[i]->reset();
            }
        }
        this->boss.clear();
    }
}

void Game::createLevel(int level){
    /*
        - Tworzenie kazdego poziomu na podstawie tego jaka liczba zostanie podana funkcji
        - Opcjonalnie mozna tworzyc kazdy poziom w osobnej funkcji
        !Opcjonalnie poprawic
    */
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
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech.txt");
        //this->narrator->setSpeaking(true);
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
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech2.txt");
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
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech3.txt");
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
        std::unique_ptr<Weapons> gun = std::make_unique<Gun>(this->textures_["GUN"]);
        this->weapons.push_back(std::move(rifle));
        this->weapons.push_back(std::move(gun));
        this->weapons[0]->setPosition(1050.f,400.f);
        this->weapons[0]->setScale(0.3f,0.3f);
        this->weapons[1]->setPosition(100.f,245.f);
        this->weapons[1]->setScale(0.5f,0.5f);
        //Strzelcy
        for(int i = 0; i<1;i++){
            std::unique_ptr<Sagittarius> sag = std::make_unique<Sagittarius>(this->textures_["STRZELEC"]);
            this->sagittariuses.push_back(std::move(sag));
        }
        this->sagittariuses[0]->setScale(0.7f,0.7f);
        this->sagittariuses[0]->setPosition(600.f,480.f);
        this->sagittariuses[0]->setStartingMove(-2.f,0.f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(410.f,290.f);
    }
    if(level == 4){
        //walls
        for(int i = 0; i<42; i++){
            std::unique_ptr<Walls> wall = std::make_unique<Walls>();
            this->walls.push_back(std::move(wall));
        }
        for(auto &wall : this->walls){
            wall->setTexture(*this->textures_["WALL"]);
            wall->setPosition(0.f,this->window_->getSize().y);
        }
        this->walls[0]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[0]->setPosition(0.f,200.f);
        this->walls[1]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[1]->setPosition(100.f,130.f);
        this->walls[2]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[2]->setPosition(100.f,100.f);
        this->walls[2]->setCanBeClosest(true);
        this->walls[2]->setDirectionForEnemy(0);
        this->walls[3]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[3]->setPosition(250.f,0.f);
        this->walls[4]->setTextureRect(sf::IntRect(0,0,200,30));
        this->walls[4]->setPosition(280.f,0.f);
        this->walls[4]->setCanBeClosest(true);
        this->walls[4]->setDirectionForEnemy(0);
        this->walls[5]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[5]->setPosition(480.f,0.f);
        this->walls[5]->setCanBeClosest(true);
        this->walls[5]->setDirectionForEnemy(1);
        this->walls[6]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[6]->setPosition(510.f,100.f);
        this->walls[7]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[7]->setPosition(630.f,130.f);
        this->walls[7]->setCanBeClosest(true);
        this->walls[7]->setDirectionForEnemy(1);
        this->walls[8]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[8]->setPosition(660.f,200.f);
        this->walls[9]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[9]->setPosition(730.f,230.f);
        this->walls[10]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[10]->setPosition(630.f,300.f);
        this->walls[11]->setTextureRect(sf::IntRect(0,0,30,120));
        this->walls[11]->setPosition(630.f,330.f);
        this->walls[12]->setTextureRect(sf::IntRect(0,0,120,30));
        this->walls[12]->setPosition(510.f,420.f);
        this->walls[12]->setCanBeClosest(true);
        this->walls[12]->setDirectionForEnemy(0);
        this->walls[13]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[13]->setPosition(480.f,420.f);
        this->walls[14]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[14]->setPosition(410.f,520.f);
        this->walls[14]->setCanBeClosest(true);
        this->walls[14]->setDirectionForEnemy(0);
        this->walls[15]->setTextureRect(sf::IntRect(0,0,30,80));
        this->walls[15]->setPosition(380.f,520.f);
        this->walls[16]->setTextureRect(sf::IntRect(0,0,30,80));
        this->walls[16]->setPosition(300.f,520.f);
        this->walls[17]->setTextureRect(sf::IntRect(0,0,50,30));
        this->walls[17]->setPosition(250.f,520.f);
        this->walls[18]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[18]->setPosition(250.f,420.f);
        this->walls[18]->setCanBeClosest(true);
        this->walls[18]->setDirectionForEnemy(1);
        this->walls[19]->setTextureRect(sf::IntRect(0,0,120,30));
        this->walls[19]->setPosition(130.f,420.f);
        this->walls[20]->setTextureRect(sf::IntRect(0,0,30,120));
        this->walls[20]->setPosition(100.f,330.f);
        this->walls[20]->setCanBeClosest(true);
        this->walls[20]->setDirectionForEnemy(1);
        this->walls[21]->setTextureRect(sf::IntRect(0,0,130,30));
        this->walls[21]->setPosition(0.f,300.f);
        this->walls[22]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[22]->setPosition(1110.f,500.f);
        this->walls[23]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[23]->setPosition(1040.f,470.f);
        this->walls[24]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[24]->setPosition(1010.f,470.f);
        this->walls[25]->setTextureRect(sf::IntRect(0,0,60,30));
        this->walls[25]->setPosition(950.f,570.f);
        this->walls[26]->setTextureRect(sf::IntRect(0,0,30,130));
        this->walls[26]->setPosition(920.f,470.f);
        this->walls[27]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[27]->setPosition(770.f,470.f);
        this->walls[28]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[28]->setPosition(770.f,370.f);
        this->walls[29]->setTextureRect(sf::IntRect(0,0,120,30));
        this->walls[29]->setPosition(800.f,370.f);
        this->walls[30]->setTextureRect(sf::IntRect(0,0,30,80));
        this->walls[30]->setPosition(920.f,320.f);
        this->walls[31]->setTextureRect(sf::IntRect(0,0,150,30));
        this->walls[31]->setPosition(800.f,290.f);
        this->walls[32]->setTextureRect(sf::IntRect(0,0,30,100));
        this->walls[32]->setPosition(770.f,220.f);
        this->walls[33]->setTextureRect(sf::IntRect(0,0,180,30));
        this->walls[33]->setPosition(770.f,190.f);
        this->walls[34]->setTextureRect(sf::IntRect(0,0,30,190));
        this->walls[34]->setPosition(920.f,0.f);
        this->walls[35]->setTextureRect(sf::IntRect(0,0,90,30));
        this->walls[35]->setPosition(950.f,0.f);
        this->walls[36]->setTextureRect(sf::IntRect(0,0,30,370));
        this->walls[36]->setPosition(1010.f,30.f);
        this->walls[37]->setTextureRect(sf::IntRect(0,0,100,30));
        this->walls[37]->setPosition(1040.f,370.f);
        this->walls[38]->setTextureRect(sf::IntRect(0,0,30,370));
        this->walls[38]->setPosition(1110.f,0.f);
        this->walls[39]->setTextureRect(sf::IntRect(0,0,60,30));
        this->walls[39]->setPosition(1140.f,0.f);
        this->walls[40]->setTextureRect(sf::IntRect(0,0,30,600));
        this->walls[40]->setPosition(1200.f,0.f);
        this->walls[41]->setTextureRect(sf::IntRect(0,0,60,30));
        this->walls[41]->setPosition(1140.f,600.f);
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech4.txt");
        //Teleports
        for(int i = 0; i<2; i++){
            std::unique_ptr<Teleport> tp = std::make_unique<Teleport>();
            this->teleports.push_back(std::move(tp));
        }
        for(auto &tp : this->teleports){
            tp->setTexture(*this->textures_["TELEPORT"]);
        }
        this->teleports[0]->setPosition(730.f-this->teleports[0]->getGlobalBounds().width,
                                        230.f);
        this->teleports[1]->setPosition(this->window_->getSize().x - this->teleports[1]->getGlobalBounds().width,
                                        this->window_->getSize().y - this->teleports[1]->getGlobalBounds().height);
        this->teleports[0]->setExitBounds(this->teleports[1]->getGlobalBounds());
        this->teleports[0]->setDirection(0.f,-1.f);
        this->teleports[1]->setExitBounds(this->teleports[0]->getGlobalBounds());
        this->teleports[1]->setDirection(-1.f,0.f);
        //boxes
        for(int i = 0; i<1; i++){
            std::unique_ptr<Boxes> box = std::make_unique<Boxes>();
            this->boxes.push_back(std::move(box));
        }
        for(auto &box : this->boxes){
            box->setTexture(*this->textures_["BOX"]);
            box->setScale(0.6,0.6);
        }
        this->boxes[0]->setPosition(950.f,160.f);
        //buttons
        for(int i = 0; i<1; i++){
            std::unique_ptr<Button> button = std::make_unique<Button>();
            this->buttons.push_back(std::move(button));
        }
        for(auto &button: this->buttons){
            button->setTexture(*this->textures_["BUTTON"]);
        }
        this->buttons[0]->setPosition(955.f,30.f);
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
        this->removableWalls[0]->setTextureRect(sf::IntRect(0,0,30,50));
        this->removableWalls[0]->setPosition(380.f,520.f);
        for(size_t i = 0; i<this->removableWalls.size(); i++){
            this->distance[i] = this->removableWalls[i]->getGlobalBounds().height;
        }
        this->removableWalls[0]->rotate(90.f);
        this->dirX.push_back(-1.f);
        this->dirY.push_back(0.f);
        //player
        this->player = std::make_unique<Player>();
        this->player->setTexture(this->textures_["GRACZ"]);
        this->player->setPosition(0.f,245.f);
        this->player->setScale(0.5f,0.5f);
        //Weapons
        std::unique_ptr<Weapons> rifle = std::make_unique<Rifle>(this->textures_["RIFLE"]);
        this->weapons.push_back(std::move(rifle));
        this->weapons[0]->setPosition(1146.f,36.f);
        this->weapons[0]->setScale(0.3f,0.3f);
        //Strzelcy
        for(int i = 0; i<2;i++){
            std::unique_ptr<Sagittarius> sag = std::make_unique<Sagittarius>(this->textures_["STRZELEC"]);
            this->sagittariuses.push_back(std::move(sag));
        }
        this->sagittariuses[0]->setScale(0.7f,0.7f);
        this->sagittariuses[0]->setPosition(520.f,300.f);
        this->sagittariuses[0]->setStartingMove(-2.f,0.f);
        this->sagittariuses[1]->setScale(0.7f,0.7f);
        this->sagittariuses[1]->setPosition(280.f,40.f);
        this->sagittariuses[1]->setStartingMove(2.f,0.f);
        //RandomDogs
        for(int i = 0; i<1; i++){
            std::unique_ptr<RandomDog> dog = std::make_unique<RandomDog>(this->textures_["RANDOMDOG"]);
            this->randDogs.push_back(std::move(dog));
        }
        this->randDogs[0]->setScale(0.7f,0.7f);
        this->randDogs[0]->setPosition(1146.f,36.f);
        this->randDogs[0]->setMovementSpeed(0.f,2.f);
        for(int i = 0; i<3; i++){
            this->changeDirection.push_back(sf::RectangleShape(sf::Vector2f(60.f,70.f)));
        }
        for(auto &rect : this->changeDirection){
            rect.setSize(sf::Vector2f(60.f - this->randDogs[0]->getGlobalBounds().width*2.f,
                                      70.f - this->randDogs[0]->getGlobalBounds().height*2.f));
        }
        this->changeDirection[0].setFillColor(sf::Color::Green);
        this->changeDirection[0].setPosition(1140.f + this->randDogs[0]->getGlobalBounds().width,
                                             400.f + this->randDogs[0]->getGlobalBounds().height);
        this->changeDirection[1].setFillColor(sf::Color::Green);
        this->changeDirection[1].setPosition(950.f + this->randDogs[0]->getGlobalBounds().width,
                                             400.f + this->randDogs[0]->getGlobalBounds().height);
        this->changeDirection[2].setFillColor(sf::Color::Green);
        this->changeDirection[2].setPosition(950.f + this->randDogs[0]->getGlobalBounds().width,
                                             220.f + this->randDogs[0]->getGlobalBounds().height);
        for(int i = 0; i<3; i++){
            this->firstTime.push_back(true);
        }
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setScale(0.8f,0.8f);
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(340.f,560.f);
    }
    if(level == 5){
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech5.txt");
        //weapons
        std::unique_ptr<Weapons> rifle = std::make_unique<Rifle>(this->textures_["RIFLE"]);
        this->weapons.push_back(std::move(rifle));
        this->weapons[0]->setPosition(300.f,300.f);
        this->weapons[0]->setScale(0.5f,0.5f);
        //Player
        this->player = std::make_unique<Player>();
        this->player->setTexture(this->textures_["GRACZ"]);
        this->player->setPosition(0.f,300.f);
        this->player->setScale(0.8f,0.8f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setScale(0.8f,0.8f);
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(1150.f,240.f);
        this->finish->follow();
        //boss
        std::unique_ptr<Boss> b = std::make_unique<Boss>();
        this->boss.push_back(std::move(b));
    }
    if(level >= 6){
        //narrator
        this->narrator = std::make_unique<Narrator>(this->textures_["NARRATOR"]);
        this->narrator->loadFile("Teksty\\Speech6.txt");
        //Player
        this->player = std::make_unique<Player>();
        this->player->setTexture(this->textures_["GRACZ"]);
        this->player->setPosition(0.f,300.f);
        this->player->setScale(0.8f,0.8f);
        //Finish
        this->finish = std::make_unique<Finish>();
        this->finish->setScale(0.8f,0.8f);
        this->finish->setTexture(*this->textures_["FINISH"]);
        this->finish->setPosition(1150.f,240.f);
    }
}
















