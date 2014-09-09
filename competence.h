#ifndef COMPETENCE_H
#define COMPETENCE_H

#include "anim.h"
#include "clickable.h"
#include "map.h"

class Competence : public Clickable
{
    public:

        Competence();

        Competence(const std::string& fichier);

        virtual ~Competence();

        void actualiser();

        void afficher(sf::RenderWindow* fenetre);

        Anim* getAnim() const;

        void setPosition(const sf::Vector2< int >& pos);

        bool distanceCible(Carte* carte, const sf::Vector2< int >& pos_cible, sf::Vector2< int > pos_perso);

        sf::Vector2< int > getPosition() const;

        bool getActive() const;

        void setActive(bool active);

        unsigned int getCoutMana() const;

    protected:

    private:

        // Graphisme

        Anim* _anim;

        bool _active;

        // Gameplay

        float _temps_recharge;

        float _temps_incantation;

        float _duree;

        unsigned int _caracteristiques[2];

        float _distance_max;

        float _distance_degats;

        std::string _nom;

        std::string _description;

        unsigned int _cout_mana;

        sf::Clock _clock_duree, _clock_recharge, _clock_incantation;
};

#endif // COMPETENCE_H
