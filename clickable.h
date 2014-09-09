#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <SFML/Graphics.hpp>

#include "boite.h"
#include "constantes.h"

class Clickable
{
    public:

        Clickable();

        virtual ~Clickable();

        bool onClickable(const sf::Vector2< int > mouse_position);

        sf::Sprite& getSpriteIcone();

        void afficherBoite(sf::RenderWindow* fenetre);

    protected:

        sf::Texture _icone_tex;

        sf::Sprite _icone;

        Boite* _boite;
};

#endif
