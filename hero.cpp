#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "matrix.h"
#include "hero.h"
#include "constantes.h"
#include "pathfinder.h"
#include "entite.h"

Personnage::Personnage()
{

}

Personnage::Personnage(const std::string nom, Carte* carte, const sf::Vector2< int > pos)
{
    _profondeur = 72;

    _carte = carte;

    _nom = nom;

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim = new Anim("Data/Personnage/heros_run.png", 96, 96, sf::Vector2< int >(WINDOW_WIDTH/2 - WIDTH_PERSONNAGE/2, WINDOW_HEIGHT/2 - HEIGHT_PERSONNAGE/2), 8, i*8, sf::milliseconds(8*80));

        _anims.push_back(_anim);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim_stopped = new Anim("Data/Personnage/heros_stop.png", 96, 96, sf::Vector2< int >(WINDOW_WIDTH/2 - WIDTH_PERSONNAGE/2, WINDOW_HEIGHT/2 - HEIGHT_PERSONNAGE/2), 1, i, sf::milliseconds(100));

        _anims.push_back(_anim_stopped);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim_attack = new Anim("Data/Personnage/heros_attaque.png", 96, 96, sf::Vector2< int >(WINDOW_WIDTH/2 - WIDTH_PERSONNAGE/2, WINDOW_HEIGHT/2 - HEIGHT_PERSONNAGE/2), 13, i*13, sf::milliseconds(13*30));

        _anims.push_back(_anim_attack);

    }

    _actu = _anims[0];

    _pos = pos;

    _statut = DEBOUT;

    _direction = B;

    sf::Vector2< int > pos_ecran = isometriqueVersCartesien(_carte, _pos);
    pos_ecran.x -= _carte->getTile(0, 0).getPosition().x;
    pos_ecran.y -= _carte->getTile(0, 0).getPosition().y;

    _carte->bouger(-pos_ecran);

    _distanceLimiteAttaque = 1.0f; // 1 métre

    _vitesse = 2.0f;

    _champVision = 10;

    _chemin.push_back(_pos);

    _competence_actu = NULL;
}

Personnage::~Personnage()
{
    _carte = NULL;
}

void Personnage::deplacer(const sf::Vector2< int > arrive)
{
    _chemin.clear();

    _chemin.push_back(arrive);

    _statut = DEPLACE;
}

void Personnage::lancerCompetence(const sf::Vector2< int > mouse_clic)
{
    if(!_competence_actu->getActive())
    {
        _competence_actu->setActive(true);
        _competence_actu->setPosition(mouse_clic);

        _mana -= _competence_actu->getCoutMana(); // on enleve le pourcentage de mana voulu
    }
}

void Personnage::attaquer(const sf::Vector2< int > cible)
{
    _cible = cible;

    _statut = ATTAQUE;
}

void Personnage::stop_attaquer()
{
    _statut = DEBOUT;

    _cible = _pos;
}

void Personnage::actualiser(std::vector< Entite* > entites)
{
    if(_pos != _chemin[0] && _statut == DEPLACE)
    {
        sf::Vector2< int > u;

        actualiser_direction(_chemin[0]);

        // deplacement de la map
        switch(_direction)
        {
            case B:
                u.y -= _vitesse*5;
            break;
            case H:
                u.y += _vitesse*5;
            break;
            case D:
                u.x -= _vitesse*5;
            break;
            case G:
                u.x += _vitesse*5;
            break;
            case BG:
                u.y -= _vitesse*3;
                u.x += _vitesse*4;
            break;
            case HG:
                u.y += _vitesse*3;
                u.x += _vitesse*4;
            break;
            case BD:
                u.y -= _vitesse*3;
                u.x -= _vitesse*4;
            break;
            case HD:
                u.y += _vitesse*3;
                u.x -= _vitesse*4;
            break;
            default:
            break;
        }

        sf::Vector2< int > t = cartesienVersIsometrique< int >(_carte, _actu->getPosition() + sf::Vector2< int >(WIDTH_PERSONNAGE/2, _profondeur) + sf::Vector2< int >(3*u.x, 3*u.y));

        if(_carte->getTile(t.x, t.y).getCollision())
        {
            _carte->bouger(u);

            for(unsigned int i = 0; i < _competences.size(); i++)
            {
                _competences[i]->setPosition(_competences[i]->getPosition() + u);
            }

            for(unsigned int i = 0; i < entites.size(); i++)
                entites[i]->setPosition(entites[i]->getPosition() + u);
        }
        else
        {
            _statut = DEBOUT;
        }
    }
    else if(_pos == _chemin[0] && _statut == DEPLACE)
    {
        if(_chemin.size() > 1)
            _chemin.erase(_chemin.begin(), _chemin.begin() + 1);
        else
            _statut = DEBOUT;
    }
    else if(_statut == ATTAQUE)
    {
        actualiser_direction(_cible);
    }

    _pos = cartesienVersIsometrique< int >(_carte, _actu->getPosition() + sf::Vector2< int >(WIDTH_PERSONNAGE/2, _profondeur));

    _actu = _anims[N_DEPLACEMENT*_statut + _direction];
}

void Personnage::setCarte(Carte* carte, sf::Vector2< int > pos)
{
    _carte = carte;

    _pos = pos;

    sf::Vector2< int > u;

    u.x = WINDOW_WIDTH/2 - _carte->getTile(_pos.x ,_pos.y).getPosition().x + WIDTH_TILE/2;
    u.y = WINDOW_HEIGHT/2 - _carte->getTile(_pos.x ,_pos.y).getPosition().y + HEIGHT_TILE/2;

    _carte->bouger(u);

    for(unsigned int i = 0; i < _competences.size(); i++)
        _competences[i]->setPosition(u);
}

Carte* Personnage::getCarte()
{
    return _carte;
}

std::vector< Competence* > Personnage::getCompetences()
{
    return _competences;
}

void Personnage::ajouterCompetence(Competence* competence)
{
    _competences.push_back(competence);
}

void Personnage::setCompetenceActu(Competence* competence_actu)
{
    _competence_actu = competence_actu;
}

Competence* Personnage::getCompetenceActu()
{
    return _competence_actu;
}


