#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include <sstream>
#include <string>


#include "anim.h"
#include "constantes.h"
#include "competence.h"
#include "parser.h"
#include "matrix.h"

template <typename T> std::string tostr(const T& t)
{
    std::ostringstream os;
    os << t;

    return os.str();
}

Competence::Competence()
{

}

Competence::Competence(const std::string& fichier)
{
    ParserCompetence parser_competence;

    parser_competence.setFichierOuvrir(fichier);


    sf::Color colorToAlpha(parser_competence.getColor()[0], parser_competence.getColor()[1], parser_competence.getColor()[2]);


    _anim = new Anim(parser_competence.getAnimDirectory(), parser_competence.getWidth(), parser_competence.getHeight(), sf::Vector2< int >(WINDOW_WIDTH/2 - parser_competence.getWidth()/2, WINDOW_HEIGHT/2 - parser_competence.getHeight()/2), parser_competence.getNFrame(), 0, sf::milliseconds(parser_competence.getTAnim()));

    _anim->setColorToAlpha(colorToAlpha);

    _anim->setPosition(sf::Vector2< int >(WINDOW_WIDTH/2 - parser_competence.getWidth()/2, WINDOW_HEIGHT/2 - parser_competence.getHeight()/2));


    _active = false;

    _distance_degats = parser_competence.getDistanceDegats();

    _distance_max = parser_competence.getDistanceMax();

    _caracteristiques[0] = parser_competence.getCaracteristiques()[0];
    _caracteristiques[1] = parser_competence.getCaracteristiques()[1];

    _temps_incantation = parser_competence.getTempsIncantation();

    _temps_recharge = parser_competence.getTempsRecharge();

    _cout_mana = parser_competence.getCoutMana();

    _nom = parser_competence.getNom();

    _description = parser_competence.getDescription();

    _duree = parser_competence.getDuree();

    if(!_icone_tex.loadFromFile(parser_competence.getIconeDirectory().c_str()))
    {
        std::cout << "Erreur chargement de l'icone : " << parser_competence.getIconeDirectory().c_str() << std::endl;
    }

    _icone.setTexture(_icone_tex);

    _boite = new Boite;

    _boite->ajouterTexte("Nom : " + _nom);
    _boite->ajouterTexte("Description : " + _description);
    _boite->ajouterTexte("Temps de recharge : " + tostr(_temps_recharge) + " sec");
    _boite->ajouterTexte("Temps d'incantation : " + tostr(_temps_incantation) + " sec");
    _boite->ajouterTexte("Duree : " + tostr(_duree) + " sec");
    _boite->ajouterTexte("Distance max : " + tostr(_distance_max) + " m");
}

Competence::~Competence()
{

}

Anim* Competence::getAnim() const
{
    return _anim;
}

bool Competence::getActive() const
{
    return _active;
}

bool Competence::distanceCible(Carte* carte, const sf::Vector2< int >& pos_cible, sf::Vector2< int > pos_perso)
{
    pos_perso.x += WIDTH_PERSONNAGE/2;
    pos_perso.y += 72;

    sf::Vector2< float > pos_perso_iso = cartesienVersIsometrique< float >(carte ,pos_perso);
    sf::Vector2< float > cible_iso = cartesienVersIsometrique< float >(carte ,pos_cible);

    float distance = std::sqrt(pow(pos_perso_iso.x - cible_iso.x, 2) + pow(pos_perso_iso.y - cible_iso.y, 2));

    if(distance <= _distance_max)
        return true;

    return false;
}

void Competence::setActive(bool active)
{
    _active = active;

    if(_active)
    {
        _clock_duree.restart();
    }
}

void Competence::setPosition(const sf::Vector2< int >& pos)
{
    _anim->setPosition(pos);
}

sf::Vector2< int > Competence::getPosition() const
{
    return _anim->getPosition();
}

void Competence::afficher(sf::RenderWindow* fenetre)
{
    _anim->afficher(fenetre);
}

unsigned int Competence::getCoutMana() const
{
    return _cout_mana;
}

void Competence::actualiser()
{
    if(_clock_duree.getElapsedTime().asSeconds() >= _duree)
    {
        _active = false;

        _clock_duree.restart();
    }
}
