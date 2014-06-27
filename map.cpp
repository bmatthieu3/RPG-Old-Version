#include <iostream>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "constantes.h"

Tiles::Tiles(const sf::VertexArray& vertexArray)
{
    _collision = true;
    _vertexArray = vertexArray;

    _tile_id = 0;
    _tileset_id = 0;
}

Tiles::Tiles()
{
    _collision = true;

    _tile_id = 0;
    _tileset_id = 0;

    _vertexArray.setPrimitiveType(sf::Quads);
    _vertexArray.resize(4);

    _vertexArray[0].position = sf::Vector2f(0, 0);
    _vertexArray[1].position = sf::Vector2f(WIDTH_TILE, 0);
    _vertexArray[2].position = sf::Vector2f(WIDTH_TILE, HEIGHT_TILE);
    _vertexArray[3].position = sf::Vector2f(0, HEIGHT_TILE);

    _vertexArray[0].texCoords = sf::Vector2f(0, 0);
    _vertexArray[1].texCoords = sf::Vector2f(WIDTH_TILE, 0);
    _vertexArray[2].texCoords = sf::Vector2f(WIDTH_TILE, HEIGHT_TILE);
    _vertexArray[3].texCoords = sf::Vector2f(0, HEIGHT_TILE);
}

Tiles::~Tiles()
{

}

void Tiles::setPosition(const sf::Vector2i& pos)
{
    _vertexArray[0].position = sf::Vector2f(pos.x, pos.y);
    _vertexArray[1].position = sf::Vector2f(pos.x + WIDTH_TILE, pos.y);
    _vertexArray[2].position = sf::Vector2f(pos.x + WIDTH_TILE, pos.y + HEIGHT_TILE);
    _vertexArray[3].position = sf::Vector2f(pos.x, pos.y + HEIGHT_TILE);
}

sf::VertexArray& Tiles::getVertexArray()
{
    return _vertexArray;
}

sf::Vector2i Tiles::getPosition()
{
    sf::Vector2i pos;

    pos.x = _vertexArray[0].position.x;
    pos.y = _vertexArray[0].position.y;

    return pos;
}

void Tiles::setTexture(const unsigned int tile_id, const unsigned int tileset_id, const std::vector< sf::Texture >& tilesets)
{
    _tileset_id = tileset_id%tilesets.size();

    unsigned int tilesParLigne = tilesets[_tileset_id].getSize().x/WIDTH_TILE;
    unsigned int tilesParColonne = tilesets[_tileset_id].getSize().y/HEIGHT_TILE;

    _tile_id = tile_id%(tilesParLigne*tilesParColonne);

    unsigned int colonne_tileset_i = _tile_id%tilesParLigne;
    unsigned int ligne_tileset_i = ((_tile_id - colonne_tileset_i)/tilesParLigne)%tilesParColonne;

    _vertexArray[0].texCoords = sf::Vector2f(colonne_tileset_i*WIDTH_TILE, ligne_tileset_i*HEIGHT_TILE);
    _vertexArray[1].texCoords = sf::Vector2f((colonne_tileset_i + 1)*WIDTH_TILE, ligne_tileset_i*HEIGHT_TILE);
    _vertexArray[2].texCoords = sf::Vector2f((colonne_tileset_i + 1)*WIDTH_TILE, (ligne_tileset_i + 1)*HEIGHT_TILE);
    _vertexArray[3].texCoords = sf::Vector2f(colonne_tileset_i*WIDTH_TILE, (ligne_tileset_i + 1)*HEIGHT_TILE);
}

void Tiles::afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets)
{
    fenetre->draw(_vertexArray, &tilesets[_tileset_id]);
}

unsigned int Tiles::getTilesetId() const
{
    return _tileset_id;
}

unsigned int Tiles::getTileId() const
{
    return _tile_id;
}

void Tiles::setTileId(const unsigned int tile_id)
{
    _tile_id = tile_id;


}

void Tiles::setTilesetId(const unsigned int tileset_id)
{
    _tileset_id = tileset_id;
}

Carte::Carte()
{
    sf::Texture tileset_actu;

    for(unsigned int i = 0; i < _parser_tileset.getFilesDirectory().size(); i++)
    {
        if(!tileset_actu.loadFromFile((_parser_tileset.getFilesDirectory()[i]).c_str()))
        {
            std::cout << "Erreur chargement du tileset" << std::endl;
        }

        _tilesets.push_back(tileset_actu);
    }

    charger(TAILLE_CARTE_X, TAILLE_CARTE_Y);
}

Carte::~Carte()
{

}

void Carte::detruire()
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        _tiles[i].clear();
    }

    _tiles.clear();
}

bool Carte::charger(const int w, const int h)
{
    this->detruire();

    for(int i = 0; i < w; i++)
    {
        _tiles.push_back(std::vector< Tiles > ());

        for(int j = 0; j < h; j++)
        {
            sf::VertexArray current_vertexArray(sf::Quads, 4);

            current_vertexArray[0].position = sf::Vector2f(ORIGINE_X + (WIDTH_TILE/2)*(i - j), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[1].position = sf::Vector2f(ORIGINE_X + (WIDTH_TILE/2)*(i - j + 2), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[2].position = sf::Vector2f(ORIGINE_X + (WIDTH_TILE/2)*(i - j + 2), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j + 2));
            current_vertexArray[3].position = sf::Vector2f(ORIGINE_X + (WIDTH_TILE/2)*(i - j), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j + 2));

            Tiles current_tile(current_vertexArray);

            current_tile.setTexture(current_tile.getTileId(), current_tile.getTilesetId(), _tilesets);

            _tiles[i].push_back(current_tile);
        }
    }

    return true;
}

void Carte::bouger(const sf::Vector2f& m)
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        for(unsigned int j = 0; j < _tiles[i].size(); j++)
        {
            for(unsigned int k = 0; k < 4; k++)
            {
                (_tiles[i][j].getVertexArray())[k].position += m;
            }
        }
    }
}

void Carte::afficher(sf::RenderWindow* fenetre)
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        for(unsigned int j = 0; j < _tiles[i].size(); j++)
        {
            _tiles[i][j].afficher(fenetre, _tilesets);
        }
    }
}

Tiles& Carte::getTile(unsigned int i, unsigned int j)
{
    if(i < 0)
    {
        i = 0;
    }
    else if(i >= TAILLE_CARTE_Y)
    {
        i = TAILLE_CARTE_Y - 1;
    }

    if(j < 0)
    {
        j = 0;
    }
    else if(j >= TAILLE_CARTE_X)
    {
        j = TAILLE_CARTE_X - 1;
    }

    return _tiles[i][j];
}

Tiles& Carte::getTile(sf::Vector2i coordIsometric)
{
    limiteCarte(coordIsometric);

    return _tiles[coordIsometric.y][coordIsometric.x];
}

void limiteCarte(sf::Vector2i& coordIsometric)
{
    if(coordIsometric.y < 0)
    {
        coordIsometric.y = 0;
    }
    else if(coordIsometric.y >= TAILLE_CARTE_Y)
    {
        coordIsometric.y = TAILLE_CARTE_Y - 1;
    }

    if(coordIsometric.x < 0)
    {
        coordIsometric.x = 0;
    }
    else if(coordIsometric.x >= TAILLE_CARTE_X)
    {
        coordIsometric.x = TAILLE_CARTE_X - 1;
    }
}
