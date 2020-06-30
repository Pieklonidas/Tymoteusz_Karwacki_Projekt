#ifndef BOSS_H
#define BOSS_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "bossbullet.h"

class Boss
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::CircleShape> objects;
    std::vector<BossBullet> bullets;
    sf::RectangleShape bossHpBar;
    sf::RectangleShape bossHpBarBack;
    float movementDir;
    int HP;
    int maxHP;
    int bulletCooldown;
    int maxBulletCooldown;
    int randomNumber;
    int cooldown;
    int maxCooldown;
    bool dead;
    bool beatPl;
    void initSprite();
    void initVariables();
    void initGui();
    void playerIsBeaten();
    void creatObject();
    void reload(Player& pl);
public:
    Boss();
    void setPosition(float x, float y);
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    void reset();
    bool isDead();
    void move();
    void die();
    void getHit();
    void updateGui();
    void closeHit(Player& pl);
    void airAttack(Player& pl);
    void shoot(Player& pl);
    bool endGame();
    void render(sf::RenderTarget& target);
};

#endif // BOSS_H
