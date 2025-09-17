#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class gem
{
private:
    int gemType;             
    sf::Texture texture;    
    sf::Sprite sprite;     

public:

public:
    gem();

    void setType(int t, const std::string& textureFile);

    int getType() const;
    sf::Sprite& getSprite();
    sf::Texture& getTexture();
};
