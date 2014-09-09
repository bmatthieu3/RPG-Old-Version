#ifndef ENTITE_H
#define ENTITE_H

#include "anim.h"
#include "map.h"
#include "competence.h"

enum {FORCE, DEXTERITE, INTELLIGENCE, SAGESSE, CONSTITUTION};

class Entite : public Drawable
{
    public:

        Entite();

        Entite(const std::string nom, unsigned int vie, unsigned int mana, unsigned int degats, float vitesse, float distanceLimiteAttaque, float champVision, sf::Vector2< int > posInitiale, Carte* carte);

        virtual ~Entite();

        // Fonctions graphiques

        sf::Vector2< int > getPositionIso();

        virtual sf::Vector2< int > getPosition();

        virtual void setPosition(const sf::Vector2< int >& pos);

        virtual void afficher(sf::RenderWindow* window, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites);

        virtual sf::Vector2< int > getSize() const;

        // Fonctions gameplay

        void actualiser_direction(sf::Vector2< int > cible);

        virtual void actualiser(std::vector< Entite* > entites);


        virtual void deplacer(const sf::Vector2< int > arrive);

        void suivre(Entite* entite);

        void attaquer(Entite* entite);


        void soigner(unsigned int pointsVie);

        void parler(const char* texte);

        unsigned int getVie() const;

        Entite* getNearestEntite(std::vector< Entite* > entites);

        float distance(sf::Vector2< int > pos_cible);

        bool estAttaquable(Entite* entite);

        float getDistanceLimiteAttaque();

        float getChampVision();

        float _champVision;

    protected:

        // Attributs graphiques

        enum{D, H, HD, HG, B, BD, BG, G, N_DEPLACEMENT};

        std::vector< Anim* > _anims;

        Anim* _actu;

        Carte* _carte;


        sf::Vector2< int > _pos;

        // Attributs gameplay

        enum{DEPLACE, DEBOUT, ATTAQUE};

        int _statut;

        std::vector< sf::Vector2< int > > _chemin;

        sf::Vector2< int > _cible;

        int _direction;


        unsigned int _vie, _mana, _degats;

        std::string _nom;

        float _vitesse;

        float _distanceLimiteAttaque;
};

#endif
