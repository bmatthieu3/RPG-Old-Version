#ifndef MAP_H
#define MAP_H

#include <iostream>

#include "parser.h"

class Carte;

class Drawable
{
    public:

       Drawable();

       Drawable(const sf::VertexArray& vertexArray);

       virtual ~Drawable();

       virtual void setPosition(const sf::Vector2< int >& pos) = 0;

       int getProfondeur() const;

       sf::VertexArray& getVertexArray();

       virtual sf::Vector2< int > getPosition();

       virtual void afficher(sf::RenderWindow* window, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites) = 0;

       virtual sf::Vector2< int > getSize() const = 0;

       static bool zOrder(Drawable* i, Drawable* j);

    protected:

       sf::VertexArray _vertexArray;

       int _profondeur;
};

class Tiles : public Drawable
{
    public:

        Tiles();

        Tiles(const sf::VertexArray& vertexArray);

        virtual ~Tiles();

        unsigned int getTilesetId() const;

        unsigned int getTileId() const;

        virtual sf::Vector2< int > getSize() const;

        void setTileId(const unsigned int tile_id);

        void setTilesetId(const unsigned int tileset_id);

        void setTexture(const int tile_id, const unsigned int tileset_id, const std::vector< sf::Texture >& tilesets);

        virtual void setPosition(const sf::Vector2< int >& pos);

        virtual void afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites);

        // Changement de carte

        void setSwitch(int carte_id, sf::Vector2< int > pos_switch_tile);

        int getCarteId() const;

        sf::Vector2< int > getPositionTileSwitch();

        // Pathfinding

        void setProprietes(const float g, const float h);

        void setParent(Tiles* parent);

        Tiles* getParent() const;

        float get_h() const;

        float get_f() const;

        float get_g() const;

        bool getCollision() const;

        void setCollision(bool collision);

    private:

        unsigned int _tile_id, _tileset_id;

        bool _collision;

        // changement de carte

        sf::Vector2< int > _pos_switch_tile;

        unsigned int _carte_id;

        // pathfinding

        float _f, _g, _h;

        Tiles* _parent;
};

class Decor : public Drawable
{
    public:

        Decor();

        Decor(const sf::VertexArray& vertexArray);

        virtual ~Decor();

        virtual sf::Vector2< int > getSize() const;

        int getSpriteId() const;

        int getSpritesheetId() const;

        virtual void setPosition(const sf::Vector2< int >& pos);

        void setTexture(const int spritesheet_id, const int sprite_id, const sf::Vector2< int > pos, const unsigned int width, const unsigned int height, const unsigned int profondeur);

        void setSprite(const int sprite_id, const int spritesheet_id);

        virtual void afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites);

        Decor operator=(const Decor decor);

    private:

        unsigned int _spritesheet_id;

        int _sprite_id;
};

class Carte
{
    public:

        Carte();

        Carte(const std::string fichier, std::vector< std::vector< Decor > >& decors, const std::vector< sf::Texture >& _tilesets);

        ~Carte();

        bool charger(const std::vector< sf::Texture>& _sprites, const std::vector< sf::Texture >& _tilesets);

        void afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites);

        void bouger(const sf::Vector2< int >& m);

        void ajouterSprite(Decor decor);

        Tiles& getTile(unsigned int i, unsigned int j);

        sf::Vector2< int > getTileId(const Tiles* tile) const;

        void detruire();

        void evenement_deplacer(const sf::Keyboard::Key key);

        std::vector< std::vector < Tiles > >& getTiles();

        std::vector< Decor >& getDecors();

    private:

        std::vector< std::vector< Tiles > > _tiles;

        std::vector< Decor > _decors;

        unsigned int _width;

        unsigned int _height;
};

#endif // MAP_H
