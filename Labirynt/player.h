#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
    //Gracz
    sf::Sprite player_;
    //Variables
    float movementSpeed_;
    //Inicjacja gracza
    void InitVariables();
public:
    Player();
    virtual ~Player();

    //Modifiers
    void setTexture(sf::Texture* texture);
    void setPosition(const float X, const float Y);
    void setScale(const float x, const float y);
    //Accessors
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const float getMovementSpeed() const;
    //Metody klasy
    void move(const float dirX, const float dirY);
    void update();
    void render(sf::RenderTarget& target);
};

#endif // PLAYER_H
