#ifndef EDITEUR_H
#define EDITEUR_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "fenetre.h"
#include "parser.h"

class FenetreTileSelection : public Fenetre
{
    public:

        FenetreTileSelection(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos);

        FenetreTileSelection();

        ~FenetreTileSelection();

        void setTileset(const sf::Texture& tileset);

        void afficher(sf::RenderWindow* fenetre);

        void evenement_changer_tile(const unsigned int tile_id);

    private:

        sf::Sprite _tileset;

        sf::Vector2< int > _offset;

        sf::Texture _curseur;

        sf::Sprite _sprite_curseur;
};

class FenetreSpriteSelection : public Fenetre
{
    public:

        FenetreSpriteSelection(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos);

        FenetreSpriteSelection();

        ~FenetreSpriteSelection();

        void setSprite(const std::vector< Decor >& sprites);

        void afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites);

        Decor getSprite(const unsigned int i) const;

        std::vector < Decor > getSprites() const;

        void evenement_changer_sprite(const int sprite_id);

    private:

        std::vector< Decor > _decors;

        sf::Vector2< int > _offset;

        unsigned int _sprite_id;

        unsigned int _sprite_id_end;
};

class Editeur
{
    public:

        Editeur();

        ~Editeur();

        bool main(sf::RenderWindow& window);

        void evenement_drawable(sf::RenderWindow& window);

        void sauvegarderCarte(const std::string& file);

        void afficher(sf::RenderWindow& fenetre);

    private:

        Carte* _carte;

        std::vector< sf::Texture > _tilesets;

        std::vector< sf::Texture > _sprites;

        std::vector< std::vector < Decor > > _decors;

        std::vector< Drawable* > _drawables;

        FenetreTileSelection* _fenetre_selection_tiles;
        FenetreSpriteSelection* _fenetre_selection_sprites;

        sf::Texture _curseur;
        sf::Sprite _sprite_curseur;

        sf::Texture _collision;
        sf::Sprite _sprite_collision;

        sf::Texture _switch;
        sf::Sprite _sprite_switch;

        Drawable* _drawable_selection;

        sf::Vector2< int > _tile_focused;
};

#endif
