#ifndef EDITEUR_H
#define EDITEUR_H

#include <SFML/Graphics.hpp>

#include "map.h"
#include "fenetre.h"
#include "parser.h"

class editeur
{
    public:

        editeur();
        ~editeur();

        bool main(sf::RenderWindow& window);

    private:

        Carte _carte;

        Fenetre _fenetre_selection_tiles;

        Parser _parser_tileset;

        sf::Texture _curseur;
        sf::Sprite _sprite_curseur;

        std::vector< sf::Texture > _tilesets;

        Tiles _tile_selection;
};

#endif
