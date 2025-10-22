#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class gem
{
protected:
    int gemType;             
    sf::Texture texture;    
    sf::Sprite sprite;     

public:

public:
    gem();
    virtual ~gem();

    void setType(int t, const std::string& textureFile);

    virtual int getType() const = 0;        
    virtual sf::Sprite& getSprite() = 0;    
    virtual sf::Texture& getTexture() = 0;  
};
