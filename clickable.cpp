#include <iostream>

#include <SFML/Graphics.hpp>

#include "clickable.h"

Clickable::Clickable()
{

}

Clickable::~Clickable()
{

}

bool Clickable::onClickable(const sf::Vector2< int > mouse_position)
{
    if(mouse_position.x > _icone.getPosition().x && mouse_position.x < _icone.getPosition().x + _icone_tex.getSize().x)
    {
        if(mouse_position.y > _icone.getPosition().y && mouse_position.y < _icone.getPosition().y + _icone_tex.getSize().y)
        {
            _boite->setPosition(mouse_position - sf::Vector2< int >(0, _boite->getSize().y));

            return true;
        }
    }

    return false;
}

void Clickable::afficherBoite(sf::RenderWindow* fenetre)
{
    _boite->afficher(fenetre);
}

sf::Sprite& Clickable::getSpriteIcone()
{
    return _icone;
}
