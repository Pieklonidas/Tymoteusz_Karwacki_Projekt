#include "narrator.h"
#include <iostream>
#include <sstream>
#include <fstream>


Narrator::Narrator(sf::Texture* texture_)
{
    this->narrator.setTexture(*texture_);
    this->ss << "";
    this->counter = 1;
}

void Narrator::render(sf::RenderTarget &target){
    target.draw(this->narrator);
    //Load font
    if(!this->font.loadFromFile("Fonts\\PixellettersFull.ttf")){
        std::cout<<"Nie wczytano czcionki"<<std::endl;
    }
    this->updateText();
    target.draw(this->speech);
    std::string s = "";
    for(size_t i = 0; i<this->lettersFromFile.size()&&i<this->counter; i++){
        s.push_back(this->lettersFromFile[i]);
    }
    ss << s;
    this->counter++;
}

void Narrator::loadFile(){
    std::fstream text("Teksty\\Speech.txt");
    if(text.is_open()){
        while (!text.eof()) {
            char letter;
            text >> letter;
            this->lettersFromFile.emplace_back(letter);
        }

    }

}

void Narrator::updateText(){
    this->speech.setFont(this->font);
    this->speech.setCharacterSize(30);
    this->speech.setFillColor(sf::Color::White);
    this->speech.setOutlineColor(sf::Color::Black);
    this->speech.setOutlineThickness(5);
    this->speech.setPosition(this->narrator.getGlobalBounds().width,50.f);
    this->speech.setString(ss.str());
}
