#ifndef FENETRE_H
#define FENETRE_H

class Fenetre
{
    public:

       Fenetre();
       Fenetre(const std::string& titre, const unsigned int width, const unsigned int height, const sf::Vector2f& pos);
       ~Fenetre();

       void setDimensions(const unsigned int width, const unsigned int height);
       void setPosition(const sf::Vector2f& pos);
       void setTitre(const std::string& titre);

       bool getActif() const;

       void evenement_quitter(const sf::Vector2i& mouse_clic);

       void afficher(sf::RenderWindow* fenetre);

    private:

        void chargerSprites();

        bool _actif;

        unsigned int _width, _height;
        sf::Vector2f _pos;

        enum{CENTRE, H, B, D, G, HG, HD, BG, BD, ENTETE, QUITTER, N_SPRITES_FENETRE};

        sf::Texture* _textures;
        sf::Sprite* _sprites;

        sf::Font _beneg;
        sf::Text _titre;
};

#endif // FENETRE_H

