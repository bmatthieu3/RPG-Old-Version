#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "matrix.h"
#include "constantes.h"

Noeud::Noeud() : _f(0.0f), _g(0.0f), _h(0.0f)
{
    _parent = NULL;
}

Noeud::~Noeud()
{
    delete _parent;
}

void Noeud::setProprietes(const float g, const float h)
{
    _g = g;
    _h = h;

    _f = _g + _h;
}

void Noeud::setParent(Noeud* parent)
{
    _parent = parent;
}

float Noeud::get_h() const
{
    return _h;
}

float distance(const sf::Vector2< float > vec_1, const sf::Vector2< float > vec_2)
{
    return std::sqrt(std::pow(vec_1.x - vec_2.x, 2) + std::pow(vec_1.y - vec_2.y, 2));
}

float cos(sf::Vector2< float > vec1, sf::Vector2< float > vec2)
{
    return float((vec1.x*vec2.x + vec1.y*vec2.y)/(norme(vec1)*norme(vec2)));
}

float sin(sf::Vector2< float > vec1, sf::Vector2< float > vec2)
{
    return float((vec1.x*vec2.y - vec1.y*vec2.x)/(norme(vec1)*norme(vec2)));
}

float norme(sf::Vector2< float > vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}
