#include "player.h"
//Prywatne funkcje
//Inicjacje
void Player::InitVariables(){
    this->movementSpeed_ = 20.f;
}

//cons/des
Player::Player()
{
    this->InitVariables();
}

Player::~Player(){

}
//Modifiers
void Player::setTexture(sf::Texture *texture){
    this->player_.setTexture(*texture);
}

void Player::setPosition(const float X, const float Y){
    this->player_.setPosition(X,Y);
}

void Player::setScale(const float x, const float y){
    this->player_.setScale(x,y);
}
//Accessors
const sf::Vector2f& Player::getPos() const{
    return this->player_.getPosition();
}

const sf::FloatRect Player::getBounds() const{
    return this->player_.getGlobalBounds();
}

const float Player::getMovementSpeed() const{
    return this->movementSpeed_;
}
//Metody klasy
void Player::move(const float dirX, const float dirY){
    this->player_.move(this->movementSpeed_*dirX,this->movementSpeed_*dirY);
}

void Player::update(){

}

void Player::render(sf::RenderTarget& target){
    target.draw(this->player_);
}
