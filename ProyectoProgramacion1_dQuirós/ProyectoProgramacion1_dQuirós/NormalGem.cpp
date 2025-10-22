#include "NormalGem.h"


NormalGem::NormalGem() = default;
NormalGem::~NormalGem() = default;

int NormalGem::getType() const
{
    return gemType;
}

sf::Sprite& NormalGem::getSprite()
{
    return sprite;
}

sf::Texture& NormalGem::getTexture()
{
    return texture;
}
