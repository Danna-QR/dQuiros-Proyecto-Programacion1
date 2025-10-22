#pragma once
#include "gem.h"

class NormalGem : public gem
{
public:
    NormalGem();
    ~NormalGem() override;

    int getType() const override;
    sf::Sprite& getSprite() override;
    sf::Texture& getTexture() override;
};


