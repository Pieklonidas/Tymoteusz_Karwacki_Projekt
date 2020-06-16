#include "narrator.h"
#include <iostream>
#include <sstream>
#include <fstream>


Narrator::Narrator(sf::Texture* texture_)
{
    this->narrator.setTexture(*texture_);
    this->ss << "";
    this->counter = 0;
    this->loadFile();
    this->isSpeaking = true;
}

void Narrator::render(sf::RenderTarget &target){
    target.draw(this->narrator);
    //Load font
    if(!this->font.loadFromFile("Fonts\\PixellettersFull.ttf")){
        std::cout<<"Nie wczytano czcionki"<<std::endl;
    }
    this->updateText();
    target.draw(this->speech);
    std::string s;
    if(this->counter < this->lettersFromFile.size()/2){
        s.push_back(this->lettersFromFile[counter]);
        ss << s;
        this->counter++;
    }
    if(this->speech.getGlobalBounds().width + this->speech.getGlobalBounds().left > target.getSize().x - 20.f){
        ss << "\r\n";
    }
    s.clear();
}

void Narrator::loadFile(){
    std::fstream text("Teksty\\Speech.txt", std::ios::in);
    if(text.is_open()){
        while (!text.eof()) {
            std::string letter;//
            std::getline(text,letter);
            for(size_t i = 0; i<letter.size(); i++){
                this->lettersFromFile.emplace_back(letter[i]);
            }
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

void Narrator::setSpeaking(bool speak){
    this->isSpeaking = speak;
}

bool Narrator::getSpeaking(){
    return this->isSpeaking;
}
