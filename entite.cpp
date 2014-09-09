#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constantes.h"
#include "matrix.h"
#include "hero.h"
#include "pathfinder.h"

#include "entite.h"

Entite::Entite()
{

}

Entite::Entite(const std::string nom, unsigned int vie, unsigned int mana, unsigned int degats, float vitesse, float distanceLimiteAttaque, float champVision, sf::Vector2< int > posInitiale, Carte* carte)
: _vie(vie), _mana(mana), _degats(degats), _vitesse(vitesse), _distanceLimiteAttaque(distanceLimiteAttaque), _champVision(champVision), _pos(posInitiale), _carte(carte)
{
    _profondeur = 72;

    sf::Vector2< int > pos_ecran = isometriqueVersCartesien(_carte, _pos);

    pos_ecran.x -= WIDTH_PERSONNAGE/2;
    pos_ecran.y -= _profondeur;

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim = new Anim("Data/Personnage/squelette_run.png", 96, 96, pos_ecran, 9, i*9, sf::milliseconds(9*80));

        _anims.push_back(_anim);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim_stopped = new Anim("Data/Personnage/squelette_stop.png", 96, 96, pos_ecran, 1, i, sf::milliseconds(100));

        _anims.push_back(_anim_stopped);

    }

    for(unsigned int i = 0; i < 8; i++)
    {
        Anim* _anim_attack = new Anim("Data/Personnage/squelette_attaque.png", 96, 96, pos_ecran, 10, i*10, sf::milliseconds(10*50));

        _anims.push_back(_anim_attack);

    }

    _actu = _anims[0];

    _statut = 1;

    _direction = B;

    _chemin.push_back(_pos);
}

Entite::~Entite()
{

}

void Entite::afficher(sf::RenderWindow* window, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites)
{
    _actu->afficher(window);
}

sf::Vector2< int > Entite::getSize() const
{
    return sf::Vector2< int >(_actu->getWidth(), _actu->getHeight());
}

void Entite::soigner(unsigned int pointsVie)
{
    _vie += pointsVie;
}

void Entite::parler(const char* texte)
{
    std::cout << _nom << " : " << texte << std::endl;
}

unsigned int Entite::getVie() const
{
    return _vie;
}

sf::Vector2< int > Entite::getPositionIso()
{
    return _pos;
}

void Entite::actualiser_direction(sf::Vector2< int > cible)
{
    if(_pos.x > cible.x)
        _direction = HD;
    else if(_pos.x < cible.x)
        _direction = BG;

    if(_pos.y > cible.y)
        _direction = HG;
    else if(_pos.y < cible.y)
        _direction = BD;

    if(_pos.x > cible.x && _pos.y > cible.y)
        _direction = H;
    else if(_pos.x < cible.x && _pos.y < cible.y)
        _direction = B;
    else if(_pos.x > cible.x && _pos.y < cible.y)
        _direction = D;
    else if(_pos.x < cible.x && _pos.y > cible.y)
        _direction = G;

}

sf::Vector2< int > Entite::getPosition()
{
    return _actu->getPosition();
}

void Entite::setPosition(const sf::Vector2< int >& pos)
{
    _actu->setPosition(pos);
}

void Entite::actualiser(std::vector< Entite* > entites)
{
    if(_pos == _chemin[0] && _statut == DEPLACE)
    {
        if(_chemin.size() > 1)
            _chemin.erase(_chemin.begin(), _chemin.begin() + 1);
        else
            _statut = DEBOUT;
    }

    if(_pos != _chemin[0] && _statut == DEPLACE)
    {
        sf::Vector2< int > u;

        u.x = 0;
        u.y = 0;

        actualiser_direction(_chemin[0]);

        // deplacement de la map
        switch(_direction)
        {
            case B:
                u.y += _vitesse*5;
            break;
            case H:
                u.y -= _vitesse*5;
            break;
            case D:
                u.x += _vitesse*5;
            break;
            case G:
                u.x -= _vitesse*5;
            break;
            case BG:
                u.y += _vitesse*3;
                u.x -= _vitesse*4;
            break;
            case HG:
                u.y -= _vitesse*3;
                u.x -= _vitesse*4;
            break;
            case BD:
                u.y += _vitesse*3;
                u.x += _vitesse*4;
            break;
            case HD:
                u.y -= _vitesse*3;
                u.x += _vitesse*4;
            break;
            default:
            break;
        }

        sf::Vector2< int > t = cartesienVersIsometrique< int >(_carte, _actu->getPosition() + sf::Vector2< int >(WIDTH_PERSONNAGE/2, _profondeur) + sf::Vector2< int >(3*u.x, 3*u.y));

        if(_carte->getTile(t.x, t.y).getCollision())
        {
            _actu->setPosition(_actu->getPosition() + u);
        }
        else
        {
            _statut = DEBOUT;
        }
    }

    if(_statut == ATTAQUE)
    {
        actualiser_direction(_cible);
    }

    _pos = cartesienVersIsometrique< int >(_carte, _actu->getPosition() + sf::Vector2< int >(WIDTH_PERSONNAGE/2, _profondeur));

    sf::Vector2< int > pos_ecran = _actu->getPosition();

    _actu = _anims[N_DEPLACEMENT*_statut + _direction];

    _actu->setPosition(pos_ecran);
}

float Entite::distance(sf::Vector2< int > pos_cible)
{
    sf::Vector2< int > pos_ecran = _actu->getPosition();
    pos_ecran.x += WIDTH_PERSONNAGE/2;
    pos_ecran.y += _profondeur;

    sf::Vector2< int > pos_iso = cartesienVersIsometrique< int >(_carte, pos_ecran);

    return std::sqrt(std::pow(pos_cible.x - pos_iso.x, 2) + std::pow(pos_cible.y - pos_iso.y, 2));
}

bool Entite::estAttaquable(Entite* entite)
{
    float distance = this->distance(entite->getPositionIso());

    if(distance < entite->getDistanceLimiteAttaque())
        return true;

    return false;
}

float Entite::getDistanceLimiteAttaque()
{
    return _distanceLimiteAttaque;
}

float Entite::getChampVision()
{
    return _champVision;
}

Entite* Entite::getNearestEntite(std::vector< Entite* > entites)
{
    unsigned int entite_id = 0;

    for(unsigned int i = 1; i < entites.size(); i++)
    {
        if(entites[i] == this)
            continue;

        if(this->distance(entites[i]->getPositionIso()) < this->distance(entites[entite_id]->getPositionIso()))
            entite_id = i;
    }

    return entites[entite_id];
}

// Deplacement des ennemis et npc

void Entite::suivre(Entite* entite)
{
    _chemin.clear();

    sf::Vector2< int > arrive = entite->getPositionIso();

    Pathfinder pathfinder(_carte);
    _chemin = pathfinder.A_Star(_pos.x, _pos.y, arrive.x, arrive.y);

    // on supprime la case arrive pour éviter la superposition des pnj et du joueur
    _chemin.pop_back();

    _statut = DEPLACE;
}

void Entite::deplacer(const sf::Vector2< int > arrive)
{
    _chemin.clear();

    Pathfinder pathfinder(_carte);
    _chemin = pathfinder.A_Star(_pos.x, _pos.y, arrive.x, arrive.y);

    _statut = DEPLACE;
}

void Entite::attaquer(Entite* entite)
{
    _cible = entite->getPositionIso();

    //entite->_vie -= 10;

    _statut = ATTAQUE;
}



