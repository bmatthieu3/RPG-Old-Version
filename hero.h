#ifndef HERO_H
#define HERO_H

#include "anim.h"
#include "map.h"
#include "competence.h"
#include "entite.h"


class Personnage : public Entite
{
    public:

        Personnage();

        Personnage(const std::string nom, Carte* carte, const sf::Vector2< int > pos);

        virtual ~Personnage();

        // Méthodes graphiques

        void setCarte(Carte* carte, sf::Vector2< int > pos);

        Carte* getCarte();

        // Méthodes gameplay

        virtual void actualiser(std::vector< Entite* > entites);

        virtual void deplacer(const sf::Vector2< int > arrive);

        void attaquer(const sf::Vector2< int > cible);

        void stop_attaquer();

        void lancerCompetence(const sf::Vector2< int > mouse_clic);


        void ajouterCompetence(Competence* competence);

        void setCompetenceActu(Competence* competence_actu);

        std::vector< Competence* > getCompetences();

        Competence* getCompetenceActu();

    private:

        std::vector< Competence* > _competences;

        Competence* _competence_actu;
};

#endif
