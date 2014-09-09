#ifndef MATRIX_H
#define MATRIX_H

#include <SFML/Graphics.hpp>
#include "constantes.h"
#include "map.h"

class Noeud
{
    public:

        Noeud();

        ~Noeud();

        void setProprietes(const float g, const float h);

        void setParent(Noeud* parent);

        float get_h() const;

    private:

        float _f, _g, _h;

        Noeud* _parent;
};

template< typename T > sf::Vector2< int >& isometriqueVersCartesien(Carte* carte, const sf::Vector2< T > coordIsometrique)
{
    sf::Vector2< int > coordCartesien;

    sf::Vector2< int > origine = carte->getTile(0,0).getPosition();
    origine.x += WIDTH_TILE/2;

    coordCartesien.x = origine.x - coordIsometrique.x*WIDTH_TILE/2.0 + coordIsometrique.y*WIDTH_TILE/2.0;
    coordCartesien.y = origine.y + coordIsometrique.x*HEIGHT_TILE/2.0 + coordIsometrique.y*HEIGHT_TILE/2.0;

    return coordCartesien;
}

template< typename F > sf::Vector2< F >& cartesienVersIsometrique(Carte* carte, const sf::Vector2< int > coordCartesien)
{
    sf::Vector2< F > coordIsometrique;

    sf::Vector2< int > origine = carte->getTile(0,0).getPosition();
    origine.x += WIDTH_TILE/2;

    coordIsometrique.x = -coordCartesien.x/WIDTH_TILE + coordCartesien.y/HEIGHT_TILE + (HEIGHT_TILE*origine.x - WIDTH_TILE*origine.y)/(WIDTH_TILE*HEIGHT_TILE);
    coordIsometrique.y = coordCartesien.x/WIDTH_TILE + coordCartesien.y/HEIGHT_TILE - (HEIGHT_TILE*origine.x + WIDTH_TILE*origine.y)/(WIDTH_TILE*HEIGHT_TILE);

    return coordIsometrique;
}

float distance(const sf::Vector2< float > vec_1, const sf::Vector2< float > vec_2);

float cos(sf::Vector2< float > vec1, sf::Vector2< float > vec2);

float sin(sf::Vector2< float > vec1, sf::Vector2< float > vec2);

float norme(sf::Vector2< float > vec);

#endif
