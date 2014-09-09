#ifndef BARRE_ETAT_H
#define BARRE_ETAT_H

class Barre_etat
{
    public :

        Barre_etat();

        Barre_etat(Personnage* hero);

        virtual ~Barre_etat();

        void afficher(sf::RenderWindow* fenetre);

        void actualiser();

        Competence* getSelectionCompetence(sf::Vector2< int > mouse_clic, Personnage* hero);

    private :

        sf::Texture _action_tex;

        sf::Sprite _action[6];

        std::vector< Clickable* > _clickables;
};

#endif
