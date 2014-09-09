#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "constantes.h"

Drawable::Drawable()
{

}

Drawable::Drawable(const sf::VertexArray& vertexArray)
{
    _vertexArray = vertexArray;
}

Drawable::~Drawable()
{

}

int Drawable::getProfondeur() const
{
    return _profondeur;
}

void Tiles::setPosition(const sf::Vector2< int >& pos)
{
    _vertexArray[0].position = static_cast< sf::Vector2< float > >(pos);
    _vertexArray[1].position = sf::Vector2< float >(pos.x + WIDTH_TILE, pos.y);
    _vertexArray[2].position = sf::Vector2< float >(pos.x + WIDTH_TILE, pos.y + HEIGHT_TILE);
    _vertexArray[3].position = sf::Vector2< float >(pos.x, pos.y + HEIGHT_TILE);
}

sf::VertexArray& Drawable::getVertexArray()
{
    return _vertexArray;
}

sf::Vector2< int > Drawable::getPosition()
{
    sf::Vector2< int > pos;

    pos.x = _vertexArray[0].position.x;
    pos.y = _vertexArray[0].position.y;

    return pos;
}

sf::Vector2< int > Decor::getSize() const
{
    return sf::Vector2< int >(_vertexArray[1].position.x - _vertexArray[0].position.x, _vertexArray[2].position.y - _vertexArray[1].position.y);
}

sf::Vector2< int > Tiles::getSize() const
{
    return sf::Vector2< int >(WIDTH_TILE, HEIGHT_TILE);
}

Tiles::Tiles(const sf::VertexArray& vertexArray) : Drawable(vertexArray), _f(0.0f), _g(0.0f), _h(0.0f), _collision(true)
{
    _parent = NULL;

    _tile_id = 0;
    _tileset_id = 0;

    _carte_id = -1;
    _pos_switch_tile = sf::Vector2< int >(0, 0);
}

Tiles::Tiles() : _f(0.0f), _g(0.0f), _h(0.0f), _collision(true)
{
    _parent = NULL;

    _tile_id = 0;
    _tileset_id = 0;

    _vertexArray.setPrimitiveType(sf::Quads);
    _vertexArray.resize(4);

    _vertexArray[0].position = sf::Vector2< float >(0, 0);
    _vertexArray[1].position = sf::Vector2< float >(WIDTH_TILE, 0);
    _vertexArray[2].position = sf::Vector2< float >(WIDTH_TILE, HEIGHT_TILE);
    _vertexArray[3].position = sf::Vector2< float >(0, HEIGHT_TILE);

    _vertexArray[0].texCoords = sf::Vector2< float >(0, 0);
    _vertexArray[1].texCoords = sf::Vector2< float >(WIDTH_TILE, 0);
    _vertexArray[2].texCoords = sf::Vector2< float >(WIDTH_TILE, HEIGHT_TILE);
    _vertexArray[3].texCoords = sf::Vector2< float >(0, HEIGHT_TILE);

    _carte_id = -1;
    _pos_switch_tile = sf::Vector2< int >(0, 0);
}

Tiles::~Tiles()
{
    _parent = NULL;
}

void Tiles::setTexture(const int tile_id, const unsigned int tileset_id, const std::vector< sf::Texture >& tilesets)
{
    _tileset_id = tileset_id%tilesets.size();

    unsigned int tilesParLigne = tilesets[_tileset_id].getSize().x/WIDTH_TILE;
    unsigned int tilesParColonne = tilesets[_tileset_id].getSize().y/HEIGHT_TILE;

    if(tile_id < 0)
        _tile_id += tilesParLigne*tilesParColonne;
    else
        _tile_id = tile_id%(tilesParLigne*tilesParColonne);

    unsigned int colonne_tileset_i = _tile_id%tilesParLigne;
    unsigned int ligne_tileset_i = ((_tile_id - colonne_tileset_i)/tilesParLigne)%tilesParColonne;

    _vertexArray[0].texCoords = sf::Vector2< float >(colonne_tileset_i*WIDTH_TILE, ligne_tileset_i*HEIGHT_TILE);
    _vertexArray[1].texCoords = sf::Vector2< float >((colonne_tileset_i + 1)*WIDTH_TILE, ligne_tileset_i*HEIGHT_TILE);
    _vertexArray[2].texCoords = sf::Vector2< float >((colonne_tileset_i + 1)*WIDTH_TILE, (ligne_tileset_i + 1)*HEIGHT_TILE);
    _vertexArray[3].texCoords = sf::Vector2< float >(colonne_tileset_i*WIDTH_TILE, (ligne_tileset_i + 1)*HEIGHT_TILE);
}

void Tiles::afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites)
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

bool Tiles::getCollision() const
{
    return _collision;
}

Tiles* Tiles::getParent() const
{
    return _parent;
}

void Tiles::setCollision(bool collision)
{
    _collision = collision;
}

void Tiles::setProprietes(const float g, const float h)
{
    _g = g;
    _h = h;

    _f = _g + _h;
}

void Tiles::setParent(Tiles* parent)
{
    _parent = parent;
}

float Tiles::get_h() const
{
    return _h;
}

float Tiles::get_g() const
{
    return _g;
}

float Tiles::get_f() const
{
    return _f;
}

void Tiles::setSwitch(int carte_id, sf::Vector2< int > pos_switch_tile)
{
    _carte_id = carte_id;

    _pos_switch_tile = pos_switch_tile;
}

int Tiles::getCarteId() const
{
    return _carte_id;
}

sf::Vector2< int > Tiles::getPositionTileSwitch()
{
    return _pos_switch_tile;
}

Decor::Decor()
{
    _vertexArray.setPrimitiveType(sf::Quads);
    _vertexArray.resize(4);

    _spritesheet_id = 0;
    _sprite_id = 0;
}

Decor::~Decor()
{

}

int Decor::getSpriteId() const
{
    return _sprite_id;
}

int Decor::getSpritesheetId() const
{
    return _spritesheet_id;
}

void Decor::setTexture(const int spritesheet_id, const int sprite_id, const sf::Vector2< int > pos, const unsigned int width, const unsigned int height, const unsigned int profondeur)
{
    _spritesheet_id = spritesheet_id;
    _sprite_id = sprite_id;
    _profondeur = profondeur;

    _vertexArray[0].texCoords = static_cast< sf::Vector2< float > >(pos);
    _vertexArray[1].texCoords = sf::Vector2< float >(pos.x + width, pos.y);
    _vertexArray[2].texCoords = sf::Vector2< float >(pos.x + width, pos.y + height);
    _vertexArray[3].texCoords = sf::Vector2< float >(pos.x, pos.y + height);
}

void Decor::setPosition(const sf::Vector2< int >& pos)
{
    unsigned int width = _vertexArray[1].texCoords.x - _vertexArray[0].texCoords.x;
    unsigned int height = _vertexArray[2].texCoords.y - _vertexArray[0].texCoords.y;

    _vertexArray[0].position = static_cast< sf::Vector2< float > >(pos);
    _vertexArray[1].position = sf::Vector2< float >(pos.x + width, pos.y);
    _vertexArray[2].position = sf::Vector2< float >(pos.x + width, pos.y + height);
    _vertexArray[3].position = sf::Vector2< float >(pos.x, pos.y + height);
}

Decor Decor::operator=(const Decor decor)
{
    _vertexArray = decor._vertexArray;
    _spritesheet_id = decor._spritesheet_id;
    _sprite_id = decor._sprite_id;


    _profondeur = decor._profondeur;

    return *this;
}

void Decor::setSprite(const int sprite_id, const int spritesheet_id)
{
    _sprite_id = sprite_id;

    _spritesheet_id = spritesheet_id;
}

void Decor::afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites)
{
    fenetre->draw(_vertexArray, &sprites[_spritesheet_id]);
}

Carte::Carte()
{

}

Carte::~Carte()
{
    detruire();
}

Carte::Carte(const std::string fichier, std::vector< std::vector< Decor > >& decors, const std::vector< sf::Texture >& _tilesets)
{
    ParserCarte parser_carte;

    parser_carte.setFichierOuvrir(fichier);

    for(int j = 0; j < parser_carte.getWidth(); j++)
    {
        _tiles.push_back(std::vector< Tiles > ());

        for(int i = 0; i < parser_carte.getHeight(); i++)
        {
            sf::VertexArray current_vertexArray(sf::Quads, 4);

            current_vertexArray[0].position = sf::Vector2< float >(WINDOW_WIDTH/2 + (WIDTH_TILE/2)*(i - j - 1), WINDOW_HEIGHT/2 + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[1].position = sf::Vector2< float >(WINDOW_WIDTH/2 + (WIDTH_TILE/2)*(i - j + 1), WINDOW_HEIGHT/2 + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[2].position = sf::Vector2< float >(WINDOW_WIDTH/2 + (WIDTH_TILE/2)*(i - j + 1), WINDOW_HEIGHT/2 + (HEIGHT_TILE/2)*(i + j + 2));
            current_vertexArray[3].position = sf::Vector2< float >(WINDOW_WIDTH/2 + (WIDTH_TILE/2)*(i - j - 1), WINDOW_HEIGHT/2 + (HEIGHT_TILE/2)*(i + j + 2));

            Tiles current_tile(current_vertexArray);

            current_tile.setTexture(parser_carte.getTileId()[i][j], parser_carte.getTilesetId()[i][j], _tilesets);
            current_tile.setCollision(parser_carte.getCollision()[i][j]);


            for(unsigned int k = 0; k < parser_carte.getCarteId().size(); k++)
            {
                if(i == parser_carte.getPositionTile()[k].x && j == parser_carte.getPositionTile()[k].y)
                    current_tile.setSwitch(parser_carte.getCarteId()[k], parser_carte.getPositionTileSwitch()[k]);
            }

            _tiles[j].push_back(current_tile);
        }
    }

    for(unsigned int i = 0; i < parser_carte.getPositionSprites().size(); i++)
    {
        for(unsigned int j = 0; j < decors.size(); j++)
        {
            for(unsigned int k = 0; k < decors[j].size(); k++)
            {
                if(parser_carte.getSpritesheetId()[i] == decors[j][k].getSpritesheetId() && parser_carte.getSpriteId()[i] == decors[j][k].getSpriteId())
                {
                    _decors.push_back(decors[j][k]);

                    (_decors.back()).setPosition(parser_carte.getPositionSprites()[i]);
                }
            }
        }
    }
}

void Carte::detruire()
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        _tiles[i].clear();
    }

    _tiles.clear();

    _decors.clear();
}

void Carte::evenement_deplacer(const sf::Keyboard::Key key)
{
    sf::Vector2< int > u = sf::Vector2< int >(0, 0);

    if(key == sf::Keyboard::Up)
    {
        u.y += 20;
    }
    else if(key == sf::Keyboard::Down)
    {
        u.y -= 20;
    }
    else if(key == sf::Keyboard::Left)
    {
        u.x += 20;
    }
    else if(key == sf::Keyboard::Right)
    {
        u.x -= 20;
    }

    bouger(u);
}

bool Carte::charger(const std::vector< sf::Texture>& _sprites, const std::vector< sf::Texture >& _tilesets)
{
    for(int j = 0; j < TAILLE_CARTE_X; j++)
    {
        _tiles.push_back(std::vector< Tiles > ());

        for(int i = 0; i < TAILLE_CARTE_Y; i++)
        {
            sf::VertexArray current_vertexArray(sf::Quads, 4);

            current_vertexArray[0].position = sf::Vector2< float >(ORIGINE_X + (WIDTH_TILE/2)*(i - j), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[1].position = sf::Vector2< float >(ORIGINE_X + (WIDTH_TILE/2)*(i - j + 2), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j));
            current_vertexArray[2].position = sf::Vector2< float >(ORIGINE_X + (WIDTH_TILE/2)*(i - j + 2), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j + 2));
            current_vertexArray[3].position = sf::Vector2< float >(ORIGINE_X + (WIDTH_TILE/2)*(i - j), ORIGINE_Y + (HEIGHT_TILE/2)*(i + j + 2));

            Tiles current_tile(current_vertexArray);

            current_tile.setTexture(current_tile.getTileId(), current_tile.getTilesetId(), _tilesets);

            _tiles[j].push_back(current_tile);
        }
    }

    return true;
}

sf::Vector2< int > Carte::getTileId(const Tiles* tile) const
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        for(unsigned int j = 0; j < _tiles[i].size(); j++)
        {
            if(&_tiles[i][j] == tile)
                return sf::Vector2< int >(i, j);
        }
    }

    return sf::Vector2< int >(0, 0);
}

void Carte::ajouterSprite(Decor decor)
{
    _decors.push_back(decor);
}

bool Drawable::zOrder(Drawable* i, Drawable* j)
{
    return ((i->getPosition().y + i->getProfondeur()) < (j->getPosition().y + j->getProfondeur()));
}

void Carte::bouger(const sf::Vector2< int >& m)
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        for(unsigned int j = 0; j < _tiles[i].size(); j++)
        {
            for(unsigned int k = 0; k < _tiles[i][j].getVertexArray().getVertexCount(); k++)
            {
                (_tiles[i][j].getVertexArray())[k].position += static_cast< sf::Vector2< float > >(m);
            }
        }
    }

    for(unsigned int i = 0; i < _decors.size(); i++)
    {
        for(unsigned int k = 0; k < _decors[i].getVertexArray().getVertexCount(); k++)
        {
            (_decors[i].getVertexArray())[k].position += static_cast< sf::Vector2< float > >(m);
        }
    }
}

void Carte::afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites)
{
    for(unsigned int i = 0; i < _tiles.size(); i++)
    {
        for(unsigned int j = 0; j < _tiles[i].size(); j++)
        {
            _tiles[i][j].afficher(fenetre, tilesets, sprites);
        }
    }

    for(unsigned int i = 0; i < _decors.size(); i++)
    {
        _decors[i].afficher(fenetre, tilesets, sprites);
    }
}

Tiles& Carte::getTile(unsigned int i, unsigned int j)
{
    if(i < 0)
    {
        i = 0;
    }
    else if(i >= TAILLE_CARTE_X)
    {
        i = TAILLE_CARTE_X - 1;
    }

    if(j < 0)
    {
        j = 0;
    }
    else if(j >= TAILLE_CARTE_Y)
    {
        j = TAILLE_CARTE_Y - 1;
    }

    return _tiles[i][j];
}

std::vector< std::vector < Tiles > >& Carte::getTiles()
{
    return _tiles;
}

std::vector< Decor >& Carte::getDecors()
{
    return _decors;
}
