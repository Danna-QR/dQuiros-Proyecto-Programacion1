#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class gem
{
private:
    int gemType;               // tipo de gema (0-4)
    sf::Texture texture;    // textura de la gema
    sf::Sprite sprite;      // sprite de la gema

public:

public:
    gem();

    void setType(int t, const std::string& filename);

    int getType() const;
    sf::Sprite& getSprite();
    sf::Texture& getTexture();
};