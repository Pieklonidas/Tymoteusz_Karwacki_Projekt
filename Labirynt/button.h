#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button : public sf::Sprite
{
private:
    bool isPressed;
public:
    Button();
    ~Button();
    void pressButton(sf::FloatRect bounds);
    //Accessors
    const bool isButtonPressed() const;

};

#endif // BUTTON_H
