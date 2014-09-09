#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "parser.h"

Parser::Parser()
{

}

std::string ParserCompetence::getAnimDirectory() const
{
    return _anim_directory;
}

Parser::~Parser()
{

}

ParserFichier::ParserFichier()
{

}

ParserFichier::ParserFichier(const std::string& file)
{
    setFichierOuvrir(file);
}

void ParserFichier::setFichierOuvrir(const std::string& file)
{
    fichier.open(file.c_str(), std::ios::in);

    if(fichier.good())
    {
        std::string parser_actu = "";

        fichier >> parser_actu;

        while(parser_actu != "$")
        {
            _fichiers_directory.push_back(parser_actu);
            fichier >> parser_actu;
        }

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }
}

std::vector< std::string > ParserFichier::getFilesDirectory() const
{
    return _fichiers_directory;
}

ParserFichier::~ParserFichier()
{

}

ParserSprite::ParserSprite()
{

}

ParserSprite::ParserSprite(const std::string& file)
{
    setFichierOuvrir(file);
}

ParserSprite::~ParserSprite()
{

}

std::string ParserSprite::getSpriteDirectory() const
{
    return _sprite_directory;
}

unsigned int ParserSprite::getSpritesheetId() const
{
    return _sprite_id;
}

std::vector< sf::Vector2< int > > ParserSprite::getPosition() const
{
    return _pos;
}

std::vector< unsigned int > ParserSprite::getWidth() const
{
    return _width;
}

std::vector< unsigned int > ParserSprite::getHeight() const
{
    return _height;
}

std::vector< unsigned int > ParserSprite::getProfondeur() const
{
    return _profondeur;
}

unsigned int* ParserSprite::getColor()
{
    return _color;
}

void ParserSprite::setFichierOuvrir(const std::string& file)
{
    std::string chaine = "";

    fichier.open(file.c_str(), std::ios::in);

    if(fichier.good())
    {
        std::string parser_actu = "";

        while(parser_actu != "$")
        {
            fichier >> parser_actu;
            chaine += parser_actu + " ";
        }

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }

    std::stringstream buffer(chaine);

    buffer >> _sprite_directory;
    buffer >> _sprite_id;

    buffer >> _color[0];
    buffer >> _color[1];
    buffer >> _color[2];

    unsigned int num = 0;

    buffer >> num;

    for(unsigned int i = 0; i < num; i++)
    {
        unsigned int w, h, p;
        sf::Vector2< int > pos;

        buffer >> pos.x;
        buffer >> pos.y;
        buffer >> w;
        buffer >> h;
        buffer >> p;

        _pos.push_back(pos);
        _width.push_back(w);
        _height.push_back(h);
        _profondeur.push_back(p);
    }
}

ParserCarte::ParserCarte()
{

}

ParserCarte::ParserCarte(const std::string& file)
{
    setFichierOuvrir(file);
}

ParserCarte::~ParserCarte()
{

}

void ParserCarte::setFichierOuvrir(const std::string& file)
{
    std::string chaine = "";

    fichier.open(file.c_str(), std::ios::in);

    if(fichier.good())
    {
        std::string parser_actu = "";

        while(parser_actu != "$")
        {
            fichier >> parser_actu;
            chaine += parser_actu + " ";
        }

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }

    std::stringstream buffer(chaine);

    buffer >> _width;
    buffer >> _height;

    std::vector< unsigned int > tilesets_i, tiles_i;
    std::vector< bool > collisions_i;

    for(unsigned int i = 0; i < _width; i++)
    {
        tilesets_i.clear();
        tiles_i.clear();
        collisions_i.clear();

        for(unsigned int j = 0; j < _height; j++)
        {
            unsigned int tileset_actu, tile_actu;
            bool collision_actu;

            buffer >> tileset_actu;
            buffer >> tile_actu;
            buffer >> collision_actu;

            tilesets_i.push_back(tileset_actu);
            tiles_i.push_back(tile_actu);
            collisions_i.push_back(collision_actu);
        }

        _tilesets_id.push_back(tilesets_i);
        _tiles_id.push_back(tiles_i);
        _collision.push_back(collisions_i);
    }

    unsigned int decors_size;

    buffer >> decors_size;

    for(unsigned int i = 0; i < decors_size; i++)
    {
        unsigned int spritesheet_actu;
        int sprite_actu;
        sf::Vector2< int > pos_actu;

        buffer >> spritesheet_actu;
        buffer >> sprite_actu;
        buffer >> pos_actu.x;
        buffer >> pos_actu.y;

        _spritesheets_id.push_back(spritesheet_actu);
        _sprites_id.push_back(sprite_actu);
        _position_sprites.push_back(pos_actu);
    }

    unsigned int switch_size;

    buffer >> switch_size;

    for(unsigned int i = 0; i < switch_size; i++)
    {
        int carte_id;
        sf::Vector2< int > pos_tile_switch;
        sf::Vector2< int > pos_tile;

        buffer >> carte_id;
        buffer >> pos_tile.x;
        buffer >> pos_tile.y;
        buffer >> pos_tile_switch.x;
        buffer >> pos_tile_switch.y;

        _carte_id.push_back(carte_id);
        _pos_tile.push_back(pos_tile);
        _pos_tile_switch.push_back(pos_tile_switch);
    }
}

std::vector< sf::Vector2< int > > ParserCarte::getPositionTile() const
{
    return _pos_tile;
}

std::vector< std::vector < unsigned int > > ParserCarte::getTilesetId() const
{
    return _tilesets_id;
}

std::vector< std::vector < unsigned int > > ParserCarte::getTileId() const
{
    return _tiles_id;
}

std::vector< sf::Vector2< int > > ParserCarte::getPositionTileSwitch() const
{
    return _pos_tile_switch;
}

std::vector< int > ParserCarte::getCarteId() const
{
    return _carte_id;
}

std::vector< std::vector < bool > > ParserCarte::getCollision() const
{
    return _collision;
}

std::vector< int > ParserCarte::getSpriteId() const
{
    return _sprites_id;
}

std::vector< int > ParserCarte::getSpritesheetId() const
{
    return _spritesheets_id;
}

std::vector< sf::Vector2< int > > ParserCarte::getPositionSprites() const
{
    return _position_sprites;
}

unsigned int ParserCarte::getWidth() const
{
    return _width;
}

unsigned int ParserCarte::getHeight() const
{
    return _height;
}

ParserCompetence::ParserCompetence()
{

}

ParserCompetence::ParserCompetence(const std::string& file)
{
    setFichierOuvrir(file);
}

ParserCompetence::~ParserCompetence()
{

}

void ParserCompetence::setFichierOuvrir(const std::string& file)
{
    std::string chaine = "";

    fichier.open(file.c_str(), std::ios::in);

    if(fichier.good())
    {
        std::string parser_actu = "";

        while(parser_actu != "$")
        {
            fichier >> parser_actu;
            chaine += parser_actu + " ";
        }

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }

    std::stringstream buffer(chaine);

    buffer >> _anim_directory;
    buffer >> _icone_directory;

    buffer >> _color[0];
    buffer >> _color[1];
    buffer >> _color[2];

    buffer >> _width;
    buffer >> _height;
    buffer >> _n_frame;
    buffer >> _t_anim;

    buffer >> _temps_recharge;
    buffer >> _temps_incantation;
    buffer >> _caracteristiques[0];
    buffer >> _caracteristiques[1];
    buffer >> _distance_max;
    buffer >> _distance_degats;
    buffer >> _duree;
    buffer >> _cout_mana;

    std::string tmp = "";

    do
    {
        _nom += " " + tmp;

        buffer >> tmp;

    }while(tmp != "#");

    tmp = "";

    do
    {
        _description += " " + tmp;

        buffer >> tmp;

    }while(tmp != "#");

    std::cout << _description << std::endl;
}

unsigned int* ParserCompetence::getColor()
{
    return _color;
}

unsigned int ParserCompetence::getWidth() const
{
    return _width;
}

unsigned int ParserCompetence::getHeight() const
{
    return _height;
}

unsigned int ParserCompetence::getNFrame() const
{
    return _n_frame;
}

unsigned int ParserCompetence::getTAnim() const
{
    return _t_anim;
}

float ParserCompetence::getTempsRecharge() const
{
    return _temps_recharge;
}

float ParserCompetence::getTempsIncantation() const
{
    return _temps_incantation;
}

unsigned int* ParserCompetence::getCaracteristiques()
{
    return _caracteristiques;
}

float ParserCompetence::getDistanceMax() const
{
    return _distance_max;
}

float ParserCompetence::getDistanceDegats() const
{
    return _distance_degats;
}

std::string ParserCompetence::getNom() const
{
    return _nom;
}

std::string ParserCompetence::getDescription() const
{
    return _description;
}

unsigned int ParserCompetence::getCoutMana() const
{
    return _cout_mana;
}

float ParserCompetence::getDuree() const
{
    return _duree;
}

std::string ParserCompetence::getIconeDirectory() const
{
    return _icone_directory;
}
