#include <SFML/Graphics.hpp>

#include "editeur.h"
#include "map.h"
#include "constantes.h"
#include "matrix.h"


editeur::editeur()
{
    if(!_curseur.loadFromFile("Data/Environnement/curseur.png"))
    {
        std::cout << "Erreur chargement du curseur" << std::endl;
    }

    sf::Texture tileset_actu;

    for(unsigned int i = 0; i < _parser_tileset.getFilesDirectory().size(); i++)
    {
        if(!tileset_actu.loadFromFile((_parser_tileset.getFilesDirectory()[i]).c_str()))
        {
            std::cout << "Erreur chargement du tileset" << std::endl;
        }

        _tilesets.push_back(tileset_actu);
    }

    _sprite_curseur.setTexture(_curseur);

    _carte.charger(TAILLE_CARTE_X, TAILLE_CARTE_Y);

    _fenetre_selection_tiles.setPosition(sf::Vector2f(100, 100));
    _fenetre_selection_tiles.setDimensions(250, 500);

    _fenetre_selection_tiles.setTitre("Sélection de tiles");

}

editeur::~editeur()
{

}

bool editeur::main(sf::RenderWindow& window)
{
    sf::Vector2i origine, tile_focused;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            origine = _carte.getTile(0,0).getPosition();
            origine.x += WIDTH_TILE/2;

            tile_focused = CartesienAIsometrique(origine, sf::Mouse::getPosition(window));

            _sprite_curseur.setPosition(sf::Vector2f(_carte.getTile(tile_focused).getPosition()));

            _tile_selection.setPosition(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _fenetre_selection_tiles.evenement_quitter(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::KeyPressed)
            {
                sf::Vector2f u = sf::Vector2f(0.0f, 0.0f);

                if(event.key.code == sf::Keyboard::Space)
                {
                    return true;
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    u.y += 20.0f;
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    u.y -= 20.0f;
                }
                else if(event.key.code == sf::Keyboard::Left)
                {
                    u.x += 20.0f;
                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    u.x -= 20.0f;
                }
                else if(event.key.code == sf::Keyboard::Q)
                {
                    _tile_selection.setTexture(_tile_selection.getTileId() + 1, _tile_selection.getTilesetId(), _tilesets);
                }
                else if(event.key.code == sf::Keyboard::A)
                {
                    _tile_selection.setTexture(_tile_selection.getTileId(), _tile_selection.getTilesetId() + 1, _tilesets);
                }
                else if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }

                _carte.bouger(u);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                (_carte.getTile(tile_focused)).setTexture(_tile_selection.getTileId(), _tile_selection.getTilesetId(), _tilesets);
            }
        }

        window.clear();

        _carte.afficher(&window);

        _tile_selection.afficher(&window, _tilesets);
        window.draw(_sprite_curseur);

        _fenetre_selection_tiles.afficher(&window);

        window.display();
    }

    return true;
}
