#pragma once

//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System.hpp>
#include "player.h"
#include "walls.h"
#include "boxes.h"
#include "button.h"
#include "finish.h"
#include "teleport.h"
#include "sagittarius.h"
#include "bullets.h"
#include "rifle.h"
#include "gun.h"
#include "randomdog.h"
#include "narrator.h"
#include <memory>
#include <map>

class Game
{
private:
    //Okno
    sf::RenderWindow* window_;
    sf::VideoMode videoMode_;
    //Variables
    sf::Event ev_;
    int level;
    int nextLevel;
    //Finish
    std::unique_ptr<Finish> finish;
    //Tekstury
    std::map<std::string,sf::Texture*> textures_;
    //Gui
    sf::Font font;
    sf::Text endgameText;
    //Narrator
    std::unique_ptr<Narrator> narrator;
    sf::RectangleShape backgroundForNarrator;
    //Gracz
    std::unique_ptr<Player> player;
    sf::FloatRect nextPos_;
    sf::Vector2f velocity_;
    float relodeTime;
    //Sciany
    std::vector<std::unique_ptr<Walls>> walls;
    std::vector<std::unique_ptr<Walls>> removableWalls;
    //kierunek w którym będą się poruszać removableWalls
    std::vector<float> dirX;
    std::vector<float> dirY;
    std::vector<float> distance;
    std::vector<int> counterRemoveWall;
    //Pudla
    std::vector<std::unique_ptr<Boxes>> boxes;
    //Przyciski
    std::vector<std::unique_ptr<Button>> buttons;
    //Teleporty
    std::vector<std::unique_ptr<Teleport>> teleports;
    //Strzelcy
    std::vector<std::unique_ptr<Sagittarius>> sagittariuses;
    //Random dogs
    std::vector<std::unique_ptr<RandomDog>> randDogs;
    std::vector<sf::RectangleShape> changeDirection;
    std::vector<bool> firstTime;
    //Pociski
    std::vector<Bullets*> enemyBullets;
    std::vector<Bullets*> playerBullets;
    //Bronie
    std::vector<std::unique_ptr<Weapons>> weapons;
    //Czas
    sf::Time elapsed;
    sf::Clock* clock;
    //Koniec gry
    bool endgame;
    //Inicjacje
    void initWindow();
    void initTime();
    void initVariables();
    void initGui();
    void initTextures();

public:
    Game();
    ~Game();

    //Metody klasy
    void run();
    void updateTime();
    void updatePollEvents();
    void updateInput();
    void updateCollision();
    void updateWallCollision();
    void updateRemovableWallCollision();
    void updateBoxCollision();
    void updateBoxWallCollsion();
    void updateBoxRemovableWallCollision();
    void updateBoxPlayerCollision();
    void updateButtonBox();
    void teleportPlayer();
    void removeWalls();
    void updatePlayer();
    void weaponPicked();
    void playerIsShooting();
    void updateWeaponsReload();
    void updateSagittarius();
    void updateRandDogs();
    void dogChangeDir();
    void doesEnemySeePlayer();
    void updateBullets();
    void updatePlayerBullets();
    void updateCombatPlayer();
    void updateCombat();
    void resetBoxes();
    void endLevel();
    void update();
    void render();
    void createLevel(int level);
};

