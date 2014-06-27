#ifndef MATRIX_H
#define MATRIX_H

#include <SFML/Graphics.hpp>
#include "constantes.h"

float dot(sf::Vector2f& a, sf::Vector2f& b);

float det(sf::Vector2f& a, sf::Vector2f& b);

float norme(sf::Vector2f& a);

float angle(sf::Vector2f& a, sf::Vector2f& b);

sf::Vector2i& CartesienAIsometrique(sf::Vector2i origine, sf::Vector2i coordCartesien);


#endif
