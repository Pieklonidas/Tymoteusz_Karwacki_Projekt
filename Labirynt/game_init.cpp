#include "game.h"
#include <iostream>
/*
    Funkcje inicjaliujace niektore wartosci oraz elementy gry, takie jak okno, czas, GUI, tekstury
*/
void Game::initWindow(){
    /*
        - Stworzenie okna, ustawienie rozmiaru, tytulu, stylu, limitu klatek na sekunde
    */
    this->videoMode_ = sf::VideoMode(1200,600);
    this->window_ = new sf::RenderWindow(this->videoMode_,"Labirynt", sf::Style::Close | sf::Style::Titlebar);
    this->window_->setFramerateLimit(60);
}

void Game::initTime(){
    /*
        - Utworzenie zegara
    */
    this->clock = new sf::Clock();
}

void Game::initVariables(){
    /*
        - Utworznie niektorych poczatkowych wartosci gry
    */
    this->endgame = false;
    this->level = 4;
    this->nextLevel = this->level;
}

void Game::initGui(){
    /*
        - Wczytanie czcionki
        - Ustawienie napisu konca gry
    */
    //Load font
    if(!this->font.loadFromFile("Fonts\\PixellettersFull.ttf")){
        std::cout<<"Nie wczytano czcionki"<<std::endl;
    }
    //Set endgame text
    this->endgameText.setFont(this->font);
    this->endgameText.setCharacterSize(70);
    this->endgameText.setFillColor(sf::Color::Black);
    this->endgameText.setOutlineColor(sf::Color::White);
    this->endgameText.setOutlineThickness(5);
    this->endgameText.setString("GAME OVER! PRES R TO RESTART");
    this->endgameText.setPosition(this->window_->getSize().x/2.f - this->endgameText.getGlobalBounds().width/2.f,
                                  this->window_->getSize().y/2.f - this->endgameText.getGlobalBounds().height/2.f);
}

void Game::initTextures(){
    /*
        - Tworzenie wszystkich potrzebnych do gry tekstur
        - Wczytanie tekstury z pliku
    */
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
    this->textures_["GUN"] = new sf::Texture();
    this->textures_["GUN"]->loadFromFile("Obrazki\\Gun.png");
}




