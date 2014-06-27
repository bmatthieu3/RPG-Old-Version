#ifndef BOITE_H
#define BOITE_H


class Boite
{
    public:

        Boite();
        Boite(const unsigned int width, const unsigned int height, const sf::Vector2f& pos);
        ~Boite();

        void setDimensions(const unsigned int width, const unsigned int height);
        void setPosition(const sf::Vector2f& pos);

        void afficher(sf::RenderWindow* fenetre);

    private:

        void chargerSprites();

        unsigned int _width, _height;
        sf::Vector2f _pos;

        enum{CENTRE, H, B, D, G, HG, HD, BG, BD, N_SPRITES_BOITE};

        sf::Texture* _textures;
        sf::Sprite* _sprites;
};

#endif // BOITE_H
