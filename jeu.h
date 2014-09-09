#ifndef JEU_H
#define JEU_H

extern "C"
{
    #include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"

}

#include <luabind/luabind.hpp>

#include "fenetre.h"
#include "map.h"
#include "hero.h"

#include "parser.h"
#include "competence.h"
#include "barre_etat.h"

class Jeu
{
    public:

        Jeu();

        ~Jeu();

        void jouer(sf::RenderWindow& fenetre);

        void afficher(sf::RenderWindow& fenetre);

    private:

        std::vector< sf::Texture > _tilesets;

        std::vector< sf::Texture > _sprites;

        std::vector< std::vector< Decor > > _decors;

        std::vector< Drawable* > _drawables;

        ParserFichier _parser_tileset, _parser_sprites, _parser_competences, _parser_cartes;

        ParserSprite* _parser_sprite;


        std::vector< Carte* > _cartes;

        Carte* _carte;

        std::vector< Competence* > _competences;

        Personnage* _personnage;

        Fenetre* _inventaire;

        Barre_etat* _barre_etat;

        std::vector< Entite* > _entites;


        // Script lua

        lua_State* _lua_state;
};

#endif
