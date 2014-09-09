#ifndef FENETRE_H
#define FENETRE_H

class Fenetre
{
    public:

       Fenetre();
       Fenetre(const std::string& titre, const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos);
       ~Fenetre();

       void setDimensions(const unsigned int width, const unsigned int height);
       void setPosition(const sf::Vector2< int >& pos);
       void setTitre(const std::string& titre);

       bool getActif() const;

       sf::Vector2< int >& getSize() const;

       void evenement_quitter(const sf::Vector2< int >& mouse_clic);

       void afficher(sf::RenderWindow* fenetre);

    protected :

        enum{CENTRE, H, B, D, G, HG, HD, BG, BD, ENTETE, QUITTER, N_SPRITES_FENETRE};

        sf::Texture* _textures;

        sf::Vector2< int > _pos;

        void chargerSprites();

        bool _actif;

        unsigned int _width, _height;

        sf::Sprite* _sprites;

        sf::Font _beneg;
        sf::Text _titre;
};

#endif // FENETRE_H

