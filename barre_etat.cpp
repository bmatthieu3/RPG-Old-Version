#include <iostream>

#include <SFML/Graphics.hpp>

#include "clickable.h"
#include "constantes.h"
#include "hero.h"

#include "barre_etat.h"

Barre_etat::Barre_etat()
{

}

Barre_etat::Barre_etat(Personnage* hero)
{
    if(!_action_tex.loadFromFile("Data//Interface//action.png"))
    {
        std::cout << "Erreur chargement barre d'etat : " << std::endl;
    }

    for(unsigned int i = 0; i < 6; i++)
    {
        _action[i].setTexture(_action_tex);
        _action[i].setPosition(sf::Vector2< float >(WINDOW_WIDTH/2 - _action_tex.getSize().x*3 + i*_action_tex.getSize().x + 5*i, WINDOW_HEIGHT - _action_tex.getSize().y - 30));
    }

    _clickables.clear();

    for(unsigned int i = 0; i < 6; i++)
    {
        if(i < hero->getCompetences().size())
        {
            _clickables.push_back(hero->getCompetences()[i]);

            _clickables.back()->getSpriteIcone().setPosition(sf::Vector2< float >(_action[i].getPosition().x + 5, _action[i].getPosition().y + 6));
        }
        else
        {
            _clickables.push_back(NULL);
        }
    }
}

Barre_etat::~Barre_etat()
{

}

Competence* Barre_etat::getSelectionCompetence(sf::Vector2< int > mouse_clic, Personnage* hero)
{
    for(unsigned int i = 0; i < _clickables.size(); i++)
    {
        if(_action[i].getPosition().x < mouse_clic.x
           && _action[i].getPosition().x + _action_tex.getSize().x > mouse_clic.x
           && _action[i].getPosition().y < mouse_clic.y
           && _action[i].getPosition().y + _action_tex.getSize().y > mouse_clic.y)
        {
            for(unsigned int j = 0; j < hero->getCompetences().size(); j++)
            {
                if(hero->getCompetences()[j] == _clickables[i])
                    return hero->getCompetences()[j];
            }

            return NULL;
        }
    }

    return NULL;
}

void Barre_etat::afficher(sf::RenderWindow* fenetre)
{
    for(unsigned int i = 0; i < 6; i++)
    {
        fenetre->draw(_action[i]);

        if(_clickables[i] != NULL)
            fenetre->draw(_clickables[i]->getSpriteIcone());
    }
}
