#ifndef BOITE_H
#define BOITE_H

class Boite
{
    public:

        Boite();

        Boite(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos);

        ~Boite();

        void setDimensions(const unsigned int width, const unsigned int height);

        void setPosition(const sf::Vector2< int >& pos);

        void ajouterTexte(const std::string& texte);

        void afficher(sf::RenderWindow* fenetre);

        sf::Vector2< int > getSize() const;

    private:

        void chargerSprites();

        unsigned int _width, _height;

        sf::Vector2< int > _pos;

        enum{CENTRE, H, B, D, G, HG, HD, BG, BD, N_SPRITES_BOITE};

        sf::Texture* _textures;

        sf::Sprite* _sprites;


        sf::Font _beneg;

        std::vector< sf::Text > _textes;
};

#endif // BOITE_H
