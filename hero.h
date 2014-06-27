#ifndef HERO_H
#define HERO_H

#include "anim.h"
#include "map.h"

enum{B, BD, D, HD, H, HG, G, BG, N_DEPLACEMENT};
enum{DEPLACE, DEBOUT, ATTAQUE};

class Personnage
{
    public:

        Personnage(Carte& carte);
        ~Personnage();

        void afficher(sf::RenderWindow* window);

        void actualiser(Carte& carte);

        void deplacer(const sf::Vector2i cible);
        void attaquer(const sf::Vector2i cible);

        void stop_attaquer();

    private:

        std::vector< anim > _anims;
        anim _actu;
        int _statut;

        int _vie, _mana;

        sf::Vector2i _pos;
        sf::Vector2i _cible;
};

#endif
