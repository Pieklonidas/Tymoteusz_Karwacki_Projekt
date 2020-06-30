#ifndef FINISH_H
#define FINISH_H

#include <SFML/Graphics.hpp>
#include "boss.h"

class Finish : public sf::Sprite
{
private:
    bool followBoss_;
public:
    Finish();
    ~Finish();
    void follow(bool f = true);
    void followBoss(Boss& boss);
};

#endif // FINISH_H
