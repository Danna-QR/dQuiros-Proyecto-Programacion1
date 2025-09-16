#include "gem.h"
using namespace std;

gem::gem()
{
    gemType = 0;
}


void gem::setType(int gemIndex, const string& textureFile)
{
    gemType = gemIndex;

    if (!texture.loadFromFile(textureFile)) {
        cout << "Error cargando textura: " << textureFile << "\n";
    }
    sprite.setTexture(texture);
}

int gem::getType() const
{
    return gemType;
}

sf::Sprite& gem::getSprite()
{
    return sprite;
}

sf::Texture& gem::getTexture()
{
    return texture;
}