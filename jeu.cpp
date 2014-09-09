#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "constantes.h"
#include "matrix.h"
#include "parser.h"
#include "anim.h"
#include "map.h"
#include "hero.h"
#include "competence.h"
#include "fenetre.h"
#include "barre_etat.h"


#include "jeu.h"

#include <luabind/operator.hpp>



Jeu::Jeu()
{
    // Parser et chargement des données de jeu

    _parser_tileset.setFichierOuvrir("Data//Environnement//Tileset//Tilesets.txt");
    _parser_sprites.setFichierOuvrir("Data//Environnement//Decors//Sprites.txt");
    _parser_competences.setFichierOuvrir("Data//Competences//Competences.txt");
    _parser_cartes.setFichierOuvrir("Data//Cartes//Cartes.txt");

    sf::Texture tileset_actu;
    sf::Image sprite_actu;

    for(unsigned int i = 0; i < _parser_tileset.getFilesDirectory().size(); i++)
    {
        if(!tileset_actu.loadFromFile((_parser_tileset.getFilesDirectory()[i]).c_str()))
        {
            std::cout << "Erreur chargement du tileset" << std::endl;
        }

        _tilesets.push_back(tileset_actu);
    }

    _parser_sprite = new ParserSprite[_parser_sprites.getFilesDirectory().size()];

    for(unsigned int i = 0; i < _parser_sprites.getFilesDirectory().size(); i++)
    {
        _parser_sprite[i].setFichierOuvrir(_parser_sprites.getFilesDirectory()[i]);

        if(!sprite_actu.loadFromFile((_parser_sprite[i].getSpriteDirectory()).c_str()))
        {
            std::cout << "Erreur chargement du sprite" << std::endl;
        }

        sf::Color color_actu(_parser_sprite[i].getColor()[0], _parser_sprite[i].getColor()[1], _parser_sprite[i].getColor()[2]);
        sprite_actu.createMaskFromColor(color_actu);

        sf::Texture sprite_texture_actu;
        sprite_texture_actu.loadFromImage(sprite_actu);

        _sprites.push_back(sprite_texture_actu);
    }

    std::vector< Decor > decors_actu;

    for(unsigned int i = 0; i < _parser_sprites.getFilesDirectory().size(); i++)
    {
        decors_actu.clear();

        for(unsigned int j = 0; j < _parser_sprite[i].getPosition().size(); j++)
        {
            Decor decor_actu;

            decor_actu.setTexture(_parser_sprite[i].getSpritesheetId(), j, _parser_sprite[i].getPosition()[j], _parser_sprite[i].getWidth()[j], _parser_sprite[i].getHeight()[j], _parser_sprite[i].getProfondeur()[j]);

            decors_actu.push_back(decor_actu);
        }

        _decors.push_back(decors_actu);
    }

    // Chargement de toutes les competences

    for(unsigned int i = 0; i < _parser_competences.getFilesDirectory().size(); i++)
    {
        Competence* competence_actu = new Competence(_parser_competences.getFilesDirectory()[i]);

        _competences.push_back(competence_actu);
    }

    // Création des cartes

    for(unsigned int i = 0; i < _parser_cartes.getFilesDirectory().size(); i++)
    {
        Carte* _carte_actu = new Carte(_parser_cartes.getFilesDirectory()[i].c_str(), _decors, _tilesets);

        _cartes.push_back(_carte_actu);
    }

    _carte = _cartes[0];

    _personnage = new Personnage("Vous", _carte, sf::Vector2< int >(10, 10));
    _personnage->ajouterCompetence(_competences[0]);
    _personnage->ajouterCompetence(_competences[1]);
    _personnage->ajouterCompetence(_competences[2]);
    _personnage->ajouterCompetence(_competences[3]);

    _entites.clear();

    Entite* squelette = new Entite("squelette", 100, 100, 10, 2.0f, 1.5f, 5.0f, sf::Vector2< int >(7, 5), _carte);
    _entites.push_back(squelette);

    // Remplissage de drawables
    _drawables.clear();

    for(unsigned int i = 0; i < _carte->getDecors().size(); i++)
    {
        _drawables.push_back(&_carte->getDecors()[i]);
    }

    _drawables.push_back(_entites[0]);
    _drawables.push_back(_personnage);

    _inventaire = new Fenetre("Inventaire", 200, 200, sf::Vector2< int >(100, 100));

    _barre_etat = new Barre_etat(_personnage);

    //Script Lua

    _lua_state = luaL_newstate();
    luaL_openlibs(_lua_state);

    luabind::open(_lua_state);

    luabind::module(_lua_state)
    [
        luabind::class_< Entite >("Entite")
          .def(luabind::constructor< >())
          .def("getVie", &Entite::getVie)
          .def("attaquer", &Entite::attaquer)
          .def("soigner", &Entite::soigner)
          .def("parler", &Entite::parler)
          .def("deplacer", &Entite::deplacer)
          .def("distance", &Entite::distance)
          .def("suivre", &Entite::suivre)
          .def("getChampVision", &Entite::getChampVision)
          .def("getPosition", &Entite::getPositionIso)
          .def("estAttaquable", &Entite::estAttaquable),


        luabind::class_< Personnage, Entite >("Personnage")
          .def(luabind::constructor< const std::string, Carte*, sf::Vector2< int > >()),

        luabind::class_< sf::Vector2< int > >("vec")
          .def(luabind::constructor< int, int >())
          .def_readwrite("x", &sf::Vector2< int >::x)
          .def_readwrite("y", &sf::Vector2< int >::y)

    ];

    luabind::globals(_lua_state)["squelette"] = squelette;
    luabind::globals(_lua_state)["joueur"] = _personnage;
}

Jeu::~Jeu()
{
    delete _barre_etat;

    delete _inventaire;

    delete _personnage;

    delete _carte;
}

void Jeu::jouer(sf::RenderWindow& fenetre)
{
    while (fenetre.isOpen())
    {
        luaL_dofile(_lua_state, "squelette.lua");

        sf::sleep(sf::milliseconds(10));

        sf::Event event;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(_barre_etat->getSelectionCompetence(sf::Mouse::getPosition(fenetre), _personnage) != NULL)
            {
                _personnage->setCompetenceActu(_barre_etat->getSelectionCompetence(sf::Mouse::getPosition(fenetre), _personnage));
            }
            else
            {
                _personnage->deplacer(cartesienVersIsometrique< int >(_carte, sf::Mouse::getPosition(fenetre)));
            }
        }

        while (fenetre.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                fenetre.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if(_personnage->getCompetenceActu() != NULL)
                {
                    if(_personnage->getCompetenceActu()->distanceCible(_carte, sf::Mouse::getPosition(fenetre), _personnage->getPosition()))
                    {
                        _personnage->lancerCompetence(sf::Vector2< int >(sf::Mouse::getPosition(fenetre).x - _personnage->getCompetenceActu()->getAnim()->getWidth()/2, sf::Mouse::getPosition(fenetre).y - _personnage->getCompetenceActu()->getAnim()->getHeight()/2));
                    }

                    _personnage->setCompetenceActu(NULL);
                }
                else
                {
                    _personnage->attaquer(cartesienVersIsometrique< int >(_carte, sf::Mouse::getPosition(fenetre)));
                }
            }

            if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    _personnage->stop_attaquer();
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    fenetre.close();
                }
            }
        }

        fenetre.clear();

        _personnage->actualiser(_entites);

        _entites[0]->actualiser(_entites);


        for(unsigned int i = 0; i < _personnage->getCompetences().size(); i++)
        {
            _personnage->getCompetences()[i]->actualiser();
        }

        if(_carte->getTile(_personnage->getPositionIso().x, _personnage->getPositionIso().y).getCarteId() != -1)
        {
            Tiles* tile_tmp = &_carte->getTile(_personnage->getPositionIso().x, _personnage->getPositionIso().y);

            _carte = _cartes[_carte->getTile(_personnage->getPositionIso().x, _personnage->getPositionIso().y).getCarteId()];

            _personnage->setCarte(_carte, tile_tmp->getPositionTileSwitch());

            // Remplissage de drawables
            _drawables.clear();

            std::cout << _carte->getDecors().size() << std::endl;

            for(unsigned int i = 0; i < _carte->getDecors().size(); i++)
            {
                _drawables.push_back(&_carte->getDecors()[i]);
            }

            _drawables.push_back(_entites[0]);
            _drawables.push_back(_personnage);

            for(unsigned int i = 0; i < _personnage->getCompetences().size(); i++)
            {
                if(_personnage->getCompetences()[i]->getActive())
                {
                    _personnage->getCompetences()[i]->setActive(false);
                }
            }
        }

        afficher(fenetre);

        fenetre.display();
    }

    lua_close(_lua_state);
}

void Jeu::afficher(sf::RenderWindow& fenetre)
{
    for(unsigned int i = 0; i < _carte->getTiles().size(); i++)
    {
        for(unsigned int j = 0; j < _carte->getTiles()[i].size(); j++)
        {
            _carte->getTiles()[i][j].afficher(&fenetre, _tilesets, _sprites);
        }
    }

    std::sort(_drawables.begin(), _drawables.end(), Drawable::zOrder);

    for(std::vector< Drawable* >::iterator it = _drawables.begin(); it != _drawables.end(); it++)
    {
        (*it)->afficher(&fenetre, _tilesets, _sprites);
    }

    for(unsigned int i = 0; i < _personnage->getCompetences().size(); i++)
    {
        if(_personnage->getCompetences()[i]->getActive())
        {
            _personnage->getCompetences()[i]->afficher(&fenetre);
        }
    }

    _barre_etat->afficher(&fenetre);

    for(unsigned int i = 0; i < _personnage->getCompetences().size(); i++)
    {
        if(_personnage->getCompetences()[i]->onClickable(sf::Mouse::getPosition(fenetre)))
        {
            _personnage->getCompetences()[i]->afficherBoite(&fenetre);
        }
    }

    //_inventaire->afficher(&fenetre);
}
