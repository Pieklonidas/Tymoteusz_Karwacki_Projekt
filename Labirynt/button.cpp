#include "button.h"

//cons/des
Button::Button(){
    this->isPressed=false;
}

Button::~Button(){

}

//Metody
void Button::pressButton(sf::FloatRect bounds){
    if(bounds.intersects(getGlobalBounds())){
        this->isPressed = true;
    }
    //else this->isPressed = false;
}
//Accessors
const bool Button::isButtonPressed() const{
    return this->isPressed;
}
