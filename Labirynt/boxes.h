#ifndef BOXES_H
#define BOXES_H
#include <SFML/Graphics.hpp>

class Boxes : public sf::Sprite
{
private:
    //variables
    bool can_move_left;
    bool can_move_top;
    bool can_move_bot;
    bool can_move_right;

    void initVariables();
    void BoundsCollision();

public:
    Boxes();
    ~Boxes();
    //accessors
    const bool getCanMoveBot() const;
    const bool getCanMoveTop() const;
    const bool getCanMoveRight() const;
    const bool getCanMoveLeft() const;
    //metody klasy
    void setCanMove(sf::FloatRect wall);
    void reset();

};

#endif // BOXES_H
