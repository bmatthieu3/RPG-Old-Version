#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constantes.h"
#include "boite.h"

void Boite::chargerSprites()
{

}

Boite::Boite()
{
    _textures = new sf::Texture[N_SPRITES_BOITE];
    _sprites = new sf::Sprite[N_SPRITES_BOITE];

    this->chargerSprites();

    _pos = sf::Vector2f(0,0);
    _width = 0;
    _height = 0;
}

Boite::Boite(const unsigned int width, const unsigned int height, const sf::Vector2f& pos)
{
    _textures = new sf::Texture[N_SPRITES_BOITE];
    _sprites = new sf::Sprite[N_SPRITES_BOITE];

    this->chargerSprites();

    setPosition(pos);
    setDimensions(width, height);
}

Boite::~Boite()
{
    delete[] _sprites;
    delete[] _textures;
}

void Boite::setDimensions(const unsigned int width, const unsigned int height)
{

}

void Boite::setPosition(const sf::Vector2f& pos)
{

}

void Boite::afficher(sf::RenderWindow* fenetre)
{

}
