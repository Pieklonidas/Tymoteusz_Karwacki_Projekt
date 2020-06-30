#include "boss.h"
#include <iostream>
#include <math.h>

Boss::Boss()
{
    this->initSprite();
    this->initVariables();
    this->initGui();


}

void Boss::setPosition(float x, float y)
{
    this->sprite.setPosition(x,y);
}

const sf::Vector2f &Boss::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Boss::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Boss::reset()
{
    this->bullets.clear();
    this->HP = this->maxHP;
    this->objects.clear();
}

bool Boss::isDead()
{
    return this->dead;
}

void Boss::move()
{
    if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height > 600.f){
        this->movementDir = -2.f;
    }
    else if(this->sprite.getGlobalBounds().top < 0.f){
        this->movementDir = 2.f;
    }
    this->sprite.move(0.f,this->movementDir);
}

void Boss::getHit()
{
    this->HP-=10;
}

void Boss::updateGui()
{
    float hpPercent = static_cast<float>(this->HP)/this->maxHP;
    this->bossHpBar.setSize(sf::Vector2f(610.f * hpPercent,
                                           this->bossHpBar.getSize().y));
}

void Boss::closeHit(Player &pl)
{
    if(this->sprite.getGlobalBounds().intersects(pl.getBounds())){
        this->playerIsBeaten();
    }
}

void Boss::initSprite()
{
    if(!this->texture.loadFromFile("Obrazki\\Boss.png")){
        std::cout << "BLAD" << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(1200 - this->sprite.getGlobalBounds().width, 120.f);
}

void Boss::initVariables()
{
    this->movementDir = 2.f;
    this->maxCooldown = 40;
    this->cooldown = this->maxCooldown;
    this->maxHP = 600;
    this->HP = this->maxHP;
    this->maxBulletCooldown = 40;
    this->bulletCooldown = this->maxBulletCooldown;
    this->dead = false;
    this->beatPl = false;
}

void Boss::initGui()
{
    this->bossHpBar.setSize(sf::Vector2f(610.f,25.f));
    this->bossHpBar.setFillColor(sf::Color::Red);
    this->bossHpBar.setPosition(sf::Vector2f(10.f,10.f));

    this->bossHpBarBack = this->bossHpBar;
    this->bossHpBarBack.setFillColor(sf::Color(25,25,25,200));
}

void Boss::die()
{
    if(this->HP <= 0){
        this->dead = true;
    }
}

void Boss::playerIsBeaten()
{
    this->beatPl = true;
}

void Boss::creatObject()
{
    if(this->cooldown < this->maxCooldown){
        this->cooldown++;
    }
    if(this->cooldown >= this->maxCooldown){
        this->randomNumber = rand()%10 + 10;
        sf::CircleShape obj;
        obj.setRadius(this->randomNumber);
        obj.setPointCount(this->randomNumber);
        obj.setFillColor(sf::Color(rand()%255+1,rand()%255+1,rand()%255+1,255));
        obj.setPosition(static_cast<float>(rand()%1200),-obj.getGlobalBounds().height);
        this->objects.push_back(obj);
        this->cooldown = 0;
    }
}

void Boss::reload(Player &pl)
{
    sf::Vector2f bossCenter = sf::Vector2f(sprite.getGlobalBounds().left,
                                           sprite.getGlobalBounds().top + sprite.getGlobalBounds().height/2.f);
    sf::Vector2f target = sf::Vector2f(pl.getBounds().left + pl.getBounds().width/2.f,
                                      pl.getBounds().top + pl.getBounds().height/2.f);
    sf::Vector2f aimDir = target - bossCenter;
    sf::Vector2f aimDirNorm = sf::Vector2f(aimDir.x / sqrt(pow(aimDir.x,2) + pow(aimDir.y,2)),
                                           aimDir.y / sqrt(pow(aimDir.x,2) + pow(aimDir.y,2)));;
    BossBullet b1;
    b1.shape.setPosition(bossCenter);
    b1.currVelocity = aimDirNorm * b1.maxSpeed;
    bullets.push_back(BossBullet(b1));
}

void Boss::airAttack(Player &pl)
{
    this->creatObject();
    for(size_t i = 0; i<this->objects.size(); i++){
        this->objects[i].move(0.f,3.f);
        if(this->objects[i].getGlobalBounds().intersects(pl.getBounds())){
            this->playerIsBeaten();
        }

        if(this->objects[i].getGlobalBounds().top > 600){
            this->objects.erase(this->objects.begin() + i);
        }
    }
}

void Boss::shoot(Player &pl)
{
    if(this->bulletCooldown < this->maxBulletCooldown){
        this->bulletCooldown++;
    }
    if(this->bulletCooldown >= this->maxBulletCooldown){
        this->reload(pl);
        this->bulletCooldown = 0;
    }
    for(size_t i = 0; i<bullets.size(); i++){
        bullets[i].shape.move(bullets[i].currVelocity);
        if(bullets[i].shape.getGlobalBounds().intersects(pl.getBounds())){
            this->playerIsBeaten();
        }
        if(bullets[i].shape.getPosition().x<0 || bullets[i].shape.getPosition().x>1200 ||
           bullets[i].shape.getPosition().y<0 || bullets[i].shape.getPosition().y>600){
            bullets.erase(bullets.begin() + i);
        }
    }
}

bool Boss::endGame()
{
    return this->beatPl;
}

void Boss::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
    target.draw(this->bossHpBarBack);
    target.draw(this->bossHpBar);
    for(size_t i = 0; i<bullets.size(); i++){
        target.draw(this->bullets[i].shape);
    }
    if(this->objects.size()>0){
        for(auto &obj : this->objects){
            target.draw(obj);
        }
    }

}



