#ifndef NARRATOR_H
#define NARRATOR_H

#include <SFML/Graphics.hpp>
#include <sstream>

class Narrator
{
private:
    sf::Sprite narrator;
    sf::Font font;
    sf::Text speech;
    std::stringstream ss;
    std::vector<char> lettersFromFile;
    unsigned counter;
public:
    Narrator(sf::Texture* texture_);
    void updateText();
    void loadFile();
    void render(sf::RenderTarget& target);
};

#endif // NARRATOR_H
