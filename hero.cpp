#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "matrix.h"
#include "hero.h"
#include "constantes.h"

Personnage::Personnage(Carte& carte) : _vie(100), _mana(100)
{
    for(unsigned int i = 0; i < 8; i++)
    {
        anim _anim("Data/Personnage/heros_running.png", 96, 96, sf::Vector2i(ORIGINE_X - WIDTH_PERSONNAGE/2, ORIGINE_Y - HEIGHT_PERSONNAGE/2), 8, i*8, sf::milliseconds(8*80));

        _anims.push_back(_anim);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        anim _anim_stopped("Data/Personnage/heros_stopped.png", 96, 96, sf::Vector2i(ORIGINE_X - WIDTH_PERSONNAGE/2, ORIGINE_Y - HEIGHT_PERSONNAGE/2), 1, i, sf::milliseconds(100));

        _anims.push_back(_anim_stopped);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        anim _anim_attack("Data/Personnage/heros_attack.png", 96, 96, sf::Vector2i(ORIGINE_X - WIDTH_PERSONNAGE/2, ORIGINE_Y - HEIGHT_PERSONNAGE/2), 13, i*13, sf::milliseconds(13*30));

        _anims.push_back(_anim_attack);

    }

    _actu = _anims[0];
    _statut = 0;

    sf::Vector2i origine = carte.getTile(0,0).getPosition();
    origine.x += WIDTH_TILE/2;

    _pos = CartesienAIsometrique(origine, _actu.getPosition());

    _cible.x = 0;
    _cible.y = 0;
}

Personnage::~Personnage()
{

}

void Personnage::afficher(sf::RenderWindow* window)
{
    _actu.afficher(window);
}

void Personnage::deplacer(const sf::Vector2i cible)
{
    _cible = cible;
    limiteCarte(_cible);

    _statut = DEPLACE;
}

void Personnage::actualiser(Carte& carte)
{
    sf::Vector2f u;

    int direction = B;

    if(_pos.x > _cible.x)
        direction = HD;
    else if(_pos.x < _cible.x)
        direction = BG;

    if(_pos.y > _cible.y)
        direction = HG;
    else if(_pos.y < _cible.y)
        direction = BD;

    if(_pos.x > _cible.x && _pos.y > _cible.y)
        direction = H;
    else if(_pos.x < _cible.x && _pos.y < _cible.y)
        direction = B;
    else if(_pos.x > _cible.x && _pos.y < _cible.y)
        direction = D;
    else if(_pos.x < _cible.x && _pos.y > _cible.y)
        direction = G;

    if(_pos != _cible && _statut == DEPLACE)
    {
        // deplacement de la map
        switch(direction)
        {
            case B:
                u.y -= 2*5;
            break;
            case H:
                u.y += 2*5;
            break;
            case D:
                u.x -= 2*5;
            break;
            case G:
                u.x += 2*5;
            break;
            case BG:
                u.y -= 2*sqrt(5);
                u.x += 4*sqrt(5);
            break;
            case HG:
                u.y += 2*sqrt(5);
                u.x += 4*sqrt(5);
            break;
            case BD:
                u.y -= 2*sqrt(5);
                u.x -= 4*sqrt(5);
            break;
            case HD:
                u.y += 2*sqrt(5);
                u.x -= 4*sqrt(5);
            break;
            default:
            break;
        }

        carte.bouger(u);

    }
    else if(_pos == _cible && _statut == DEPLACE)
    {
        _statut = DEBOUT;
    }

    sf::Vector2i origine = carte.getTile(0,0).getPosition();
    origine.x += WIDTH_TILE/2;

    _pos = CartesienAIsometrique(origine, _actu.getPosition() + sf::Vector2i(WIDTH_PERSONNAGE/2, 72));

    _actu = _anims[N_DEPLACEMENT*_statut + direction];
}

void Personnage::attaquer(const sf::Vector2i cible)
{
    _cible = cible;

    _statut = ATTAQUE;
}

void Personnage::stop_attaquer()
{
    _statut = DEBOUT;

    _cible = _pos;
}

