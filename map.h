#ifndef MAP_H
#define MAP_H

#include <iostream>

#include "parser.h"

class Tiles
{
    public:

        Tiles();
        Tiles(const sf::VertexArray& vertexArray);

        ~Tiles();

        void setPosition(const sf::Vector2i& pos);
        sf::VertexArray& getVertexArray();

        sf::Vector2i getPosition();

        unsigned int getTilesetId() const;

        unsigned int getTileId() const;

        void setTileId(const unsigned int tile_id);

        void setTilesetId(const unsigned int tileset_id);

        void setTexture(const unsigned int tile_id, const unsigned int tileset_id, const std::vector< sf::Texture >& tilesets);

        void afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets);

    private:

        sf::VertexArray _vertexArray;

        unsigned int _tile_id, _tileset_id;

        bool _collision;
};

class Carte
{
    public:

        Carte();
        ~Carte();

        bool charger(const int w, const int h);

        void afficher(sf::RenderWindow* fenetre);

        void bouger(const sf::Vector2f& m);

        Tiles& getTile(unsigned int i, unsigned int j);
        Tiles& getTile(sf::Vector2i coordIsometric);

        void detruire();


    private:

        std::vector< std::vector< Tiles > > _tiles;
        std::vector< sf::Texture > _tilesets;

        Parser _parser_tileset;
};

void limiteCarte(sf::Vector2i& coordIsometric);

#endif // MAP_H
