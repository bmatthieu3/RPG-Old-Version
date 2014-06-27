#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "matrix.h"
#include "constantes.h"

float dot(sf::Vector2f& a, sf::Vector2f& b)
{
    return a.x*b.x + a.y*b.y;
}

float det(sf::Vector2f& a, sf::Vector2f& b)
{
    return a.x*b.y - a.y*b.x;
}

float norme(sf::Vector2f& a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

float angle(sf::Vector2f& a, sf::Vector2f& b)
{
    float theta = acosf(dot(a, b)/(norme(a)*norme(b)));

    if((det(a, b)/(norme(a)*norme(b))) < 0)
    {
        theta = 2*PI - theta;
    }

    return theta;
}

sf::Vector2i& CartesienAIsometrique(sf::Vector2i origine, sf::Vector2i coordCartesien)
{
    sf::Vector2i coordIsometrique;

    coordIsometrique.x = (int)(floor(-coordCartesien.x/64.0 + coordCartesien.y/32.0 + (origine.x - 2*origine.y)/64.0));
    coordIsometrique.y = (int)(floor(coordCartesien.x/64.0 + coordCartesien.y/32.0 - (origine.x + 2*origine.y)/64.0));

    return coordIsometrique;
}
