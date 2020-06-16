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
    bool isSpeaking;
public:
    Narrator(sf::Texture* texture_);
    void updateText();
    void loadFile();
    void setSpeaking(bool speak);
    void render(sf::RenderTarget& target);
    bool getSpeaking();
};

#endif // NARRATOR_H
