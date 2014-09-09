#include <SFML/Graphics.hpp>
#include <cmath>

#include "editeur.h"
#include "map.h"
#include "constantes.h"
#include "matrix.h"


FenetreTileSelection::FenetreTileSelection()
{

}

FenetreTileSelection::FenetreTileSelection(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos) : Fenetre("Selection de Tiles", width, height, pos)
{
    if(!_curseur.loadFromFile("Data/Environnement/curseur.png"))
    {
        std::cout << "Erreur chargement du curseur" << std::endl;
    }

    _sprite_curseur.setTexture(_curseur);

    _offset = sf::Vector2< int >(15, _textures[HG].getSize().y);

}

FenetreTileSelection::~FenetreTileSelection()
{

}

void FenetreTileSelection::setTileset(const sf::Texture& tileset)
{
    _tileset.setTexture(tileset, true);

    _tileset.setPosition(static_cast< sf::Vector2< float > >(_pos + _offset));
}

void FenetreTileSelection::afficher(sf::RenderWindow* fenetre)
{
    Fenetre::afficher(fenetre);

    fenetre->draw(_tileset);
    fenetre->draw(_sprite_curseur);
}

void FenetreTileSelection::evenement_changer_tile(const unsigned int tile_id)
{
    unsigned int tilesParLigne = _tileset.getTexture()->getSize().x/WIDTH_TILE;
    unsigned int tilesParColonne = _tileset.getTexture()->getSize().y/HEIGHT_TILE;

    unsigned int colonne_tileset_i = tile_id%tilesParLigne;
    unsigned int ligne_tileset_i = ((tile_id - colonne_tileset_i)/tilesParLigne)%tilesParColonne;

    _sprite_curseur.setPosition(_tileset.getPosition() + sf::Vector2< float >(WIDTH_TILE*colonne_tileset_i, HEIGHT_TILE*ligne_tileset_i));
}

FenetreSpriteSelection::FenetreSpriteSelection(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos) : Fenetre("Selection de Sprites", width, height, pos)
{
    _offset = sf::Vector2< int >(15, _textures[HG].getSize().y);
}

FenetreSpriteSelection::FenetreSpriteSelection()
{
    _offset = sf::Vector2< int >(15, _textures[HG].getSize().y);
}

FenetreSpriteSelection::~FenetreSpriteSelection()
{

}

void FenetreSpriteSelection::setSprite(const std::vector< Decor >& sprites)
{
    Fenetre::setPosition(sf::Vector2< int >(0, 0));

    _decors.clear();

    for(unsigned int i = 0; i < sprites.size(); i++)
    {
        _decors.push_back(sprites[i]);
    }
}

void FenetreSpriteSelection::afficher(sf::RenderWindow* fenetre, const std::vector< sf::Texture >& tilesets, const std::vector< sf::Texture >& sprites)
{
    Fenetre::afficher(fenetre);

    for(unsigned int i = _sprite_id; i < _sprite_id_end; i++)
    {
        i = i%_decors.size();

        _decors[i].afficher(fenetre, tilesets, sprites);
    }
}

Decor FenetreSpriteSelection::getSprite(const unsigned int i) const
{
    return _decors[i];
}

std::vector < Decor > FenetreSpriteSelection::getSprites() const
{
    return _decors;
}

void FenetreSpriteSelection::evenement_changer_sprite(const int sprite_id)
{
    _decors[sprite_id%_decors.size()].setPosition(sf::Vector2< int >(_pos + _offset));

    int i = sprite_id;

    do
    {
        i = (i + 1)%_decors.size();

        _decors[i].setPosition(sf::Vector2< int >(_decors[(i - 1)%_decors.size()].getPosition().x, _decors[(i - 1)%_decors.size()].getPosition().y + _decors[(i - 1)%_decors.size()].getSize().y));

    }while(_decors[i].getPosition().y + _decors[i].getSize().y < _pos.y + _height - _offset.y);

    _sprite_id_end = i;

    _sprite_id = sprite_id%_decors.size();
}

Editeur::Editeur()
{
    // Parser et chargement des données de jeu
    ParserFichier _parser_tileset, _parser_sprites;
    ParserSprite* _parser_sprite;

    _parser_tileset.setFichierOuvrir("Data//Environnement//Tileset//Tilesets.txt");
    _parser_sprites.setFichierOuvrir("Data//Environnement//Decors//Sprites.txt");

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

    if(!_curseur.loadFromFile("Data/Environnement/curseur.png"))
    {
        std::cout << "Erreur chargement du curseur" << std::endl;
    }

    _sprite_curseur.setTexture(_curseur);

    if(!_switch.loadFromFile("Data/Environnement/changement.png"))
    {
        std::cout << "Erreur chargement du curseur" << std::endl;
    }

    _sprite_switch.setTexture(_switch);

    _carte = new Carte;

    _carte->charger(_sprites, _tilesets);

    _fenetre_selection_tiles = new FenetreTileSelection(WINDOW_WIDTH, 190, sf::Vector2< int >(0, WINDOW_HEIGHT - 185));
    _fenetre_selection_sprites = new FenetreSpriteSelection(200, WINDOW_HEIGHT - 180, sf::Vector2< int >(0, 0));

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

    _fenetre_selection_sprites->setSprite(_decors[0]);

    _fenetre_selection_sprites->evenement_changer_sprite(0);

    _drawable_selection = &_carte->getTile(0,0);

    _parser_sprite = NULL;
    delete _parser_sprite;

    _drawables.clear();
}

Editeur::~Editeur()
{

}

void Editeur::evenement_drawable(sf::RenderWindow& window)
{
    _sprite_curseur.setPosition(sf::Vector2< float >(_carte->getTile(_tile_focused.x, _tile_focused.y).getPosition()));

    _drawable_selection->setPosition(sf::Vector2< int >(sf::Mouse::getPosition(window).x - _drawable_selection->getSize().x/2, sf::Mouse::getPosition(window).y - _drawable_selection->getSize().y/2));
}

bool Editeur::main(sf::RenderWindow& window)
{
    Tiles tile_selection = _carte->getTile(0,0);
    Decor sprite_selection;

    _fenetre_selection_tiles->setTileset(_tilesets[tile_selection.getTilesetId()]);

    _drawable_selection = &tile_selection;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            _tile_focused = cartesienVersIsometrique< int >(_carte, sf::Mouse::getPosition(window));

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                _carte->evenement_deplacer(event.key.code);

                if(event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
                    _drawable_selection = &tile_selection;
                else if(event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::M)
                    _drawable_selection = &sprite_selection;

                switch(event.key.code)
                {
                    case sf::Keyboard::D:
                        tile_selection.setTexture(tile_selection.getTileId() + 1, tile_selection.getTilesetId(), _tilesets);
                    break;
                    case sf::Keyboard::Q:
                        tile_selection.setTexture(tile_selection.getTileId() - 1, tile_selection.getTilesetId(), _tilesets);
                    break;
                    case sf::Keyboard::Z:
                        tile_selection.setTexture(tile_selection.getTileId() - _tilesets[tile_selection.getTilesetId()].getSize().x/WIDTH_TILE, tile_selection.getTilesetId(), _tilesets);
                    break;
                    case sf::Keyboard::S:
                        tile_selection.setTexture(tile_selection.getTileId() + _tilesets[tile_selection.getTilesetId()].getSize().x/WIDTH_TILE, tile_selection.getTilesetId(), _tilesets);
                    break;
                    case sf::Keyboard::P:
                        sprite_selection = _decors[sprite_selection.getSpritesheetId()][(sprite_selection.getSpriteId() - 1)%_decors[sprite_selection.getSpritesheetId()].size()];
                    break;
                    case sf::Keyboard::M:
                        sprite_selection = _decors[sprite_selection.getSpritesheetId()][(sprite_selection.getSpriteId() + 1)%_decors[sprite_selection.getSpritesheetId()].size()];
                    break;
                    default:
                    break;
                }

                _fenetre_selection_tiles->evenement_changer_tile(tile_selection.getTileId());

                _fenetre_selection_sprites->evenement_changer_sprite(sprite_selection.getSpriteId());

                if(event.key.code == sf::Keyboard::A)
                {
                    tile_selection.setTexture(tile_selection.getTileId(), tile_selection.getTilesetId() + 1, _tilesets);

                    _fenetre_selection_tiles->setTileset(_tilesets[tile_selection.getTilesetId()]);
                }
                else if(event.key.code == sf::Keyboard::O)
                {
                    sprite_selection = _decors[(sprite_selection.getSpritesheetId() + 1)%_decors.size()][sprite_selection.getSpriteId()];

                    _fenetre_selection_sprites->setSprite(_decors[sprite_selection.getSpritesheetId()]);
                    _fenetre_selection_sprites->evenement_changer_sprite(0);
                }
                else if(event.key.code == sf::Keyboard::E)
                {
                    if(!_carte->getTile(_tile_focused.x, _tile_focused.y).getCollision())
                        _carte->getTile(_tile_focused.x, _tile_focused.y).setCollision(true);
                    else
                        _carte->getTile(_tile_focused.x, _tile_focused.y).setCollision(false);
                }
                else if(event.key.code == sf::Keyboard::N)
                {
                    unsigned int carte_id, tile_i, tile_j;

                    std::cout << "Numero de la carte visee : ";
                    std::cin >> carte_id;

                    std::cout << std::endl << "Tile i : ";
                    std::cin >> tile_i;

                    std::cout << std::endl << "Tile j : ";
                    std::cin >> tile_j;

                    _carte->getTile(_tile_focused.x, _tile_focused.y).setSwitch(carte_id, sf::Vector2< int >(tile_i, tile_j));
                }
                else if(event.key.code == sf::Keyboard::W)
                {
                    std::string nom_nouvelle_carte;

                    std::cout << std::endl;
                    std::cin >> nom_nouvelle_carte;

                    sauvegarderCarte("Data//Cartes//" + nom_nouvelle_carte + ".txt");
                }
                else if(event.key.code == sf::Keyboard::C)
                {
                    std::string fichier_carte = "";
                    std::cout << std::endl;
                    std::cin >> fichier_carte;

                    delete _carte;

                    _carte = new Carte("Data//Cartes//" + fichier_carte, _decors, _tilesets);
                }

                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(_drawable_selection == &tile_selection)
                    (_carte->getTile(_tile_focused.x, _tile_focused.y)).setTexture(tile_selection.getTileId(), tile_selection.getTilesetId(), _tilesets);
                else
                {
                    // Ajout du sprite à selectionne à la carte
                    _carte->ajouterSprite(sprite_selection);
                }
            }

            evenement_drawable(window);
        }

        window.clear();

        afficher(window);

        window.display();
    }

    return true;
}

void Editeur::sauvegarderCarte(const std::string& file)
{
    std::ofstream fichier(file.c_str(), std::ios::trunc);

    if(fichier.good())
    {
        fichier << _carte->getTiles().size() << " " << _carte->getTiles()[0].size() << std::endl;

        for(unsigned int j = 0; j < _carte->getTiles().size(); j++)
        {
            for(unsigned int i = 0; i < _carte->getTiles()[j].size(); i++)
            {
                fichier << _carte->getTile(i, j).getTilesetId() << " " << _carte->getTile(i, j).getTileId() << " " << _carte->getTile(i, j).getCollision() << "  ";
            }

            fichier << std::endl;
        }

        fichier << std::endl;

        fichier << _carte->getDecors().size() << std::endl;

        for(unsigned int i = 0; i < _carte->getDecors().size(); i++)
        {
            fichier << _carte->getDecors()[i].getSpritesheetId() << " " << _carte->getDecors()[i].getSpriteId() << " " << _carte->getDecors()[i].getPosition().x - _carte->getTile(0, 0).getPosition().x + ORIGINE_X << " " << _carte->getDecors()[i].getPosition().y - _carte->getTile(0, 0).getPosition().y + ORIGINE_Y << std::endl;
        }

        unsigned int n_switch = 0;

        for(unsigned int i = 0; i < _carte->getTiles().size(); i++)
        {
            for(unsigned int j = 0; j < _carte->getTiles()[i].size(); j++)
            {
                if(_carte->getTiles()[i][j].getCarteId() != -1)
                    n_switch++;
            }
        }

        fichier << n_switch << std::endl;

        for(unsigned int i = 0; i < _carte->getTiles().size(); i++)
        {
            for(unsigned int j = 0; j < _carte->getTiles()[i].size(); j++)
            {
                if(_carte->getTiles()[i][j].getCarteId() != -1)
                    fichier << _carte->getTiles()[i][j].getCarteId() << " " << i << " " << j << " " << _carte->getTiles()[i][j].getPositionTileSwitch().x << " " << _carte->getTiles()[i][j].getPositionTileSwitch().y << std::endl;
            }
        }

        fichier << "$";

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }
}

void Editeur::afficher(sf::RenderWindow& fenetre)
{
    for(unsigned int i = 0; i < _carte->getTiles().size(); i++)
    {
        for(unsigned int j = 0; j < _carte->getTiles()[i].size(); j++)
        {
            _carte->getTiles()[i][j].afficher(&fenetre, _tilesets, _sprites);
        }
    }

    _drawables.clear();

    for(unsigned int i = 0; i < _carte->getDecors().size(); i++)
    {
        _drawables.push_back(&_carte->getDecors()[i]);
    }

    std::sort(_drawables.begin(), _drawables.end(), Drawable::zOrder);

    for(std::vector< Drawable* >::iterator it = _drawables.begin(); it != _drawables.end(); it++)
    {
        (*it)->afficher(&fenetre, _tilesets, _sprites);
    }

    _drawable_selection->afficher(&fenetre, _tilesets, _sprites);

    for(unsigned int i = 0; i < _carte->getTiles().size(); i++)
    {
        for(unsigned int j = 0; j < _carte->getTiles()[i].size(); j++)
        {
            if(!_carte->getTile(i, j).getCollision())
            {
                _sprite_collision.setPosition(_carte->getTile(i, j).getPosition().x, _carte->getTile(i, j).getPosition().y);

                fenetre.draw(_sprite_collision);
            }
            else if(_carte->getTile(i, j).getCarteId() != -1)
            {
                _sprite_switch.setPosition(_carte->getTile(i, j).getPosition().x, _carte->getTile(i, j).getPosition().y);

                fenetre.draw(_sprite_switch);
            }
        }
    }

    fenetre.draw(_sprite_curseur);

    _fenetre_selection_tiles->afficher(&fenetre);
    _fenetre_selection_sprites->afficher(&fenetre, _tilesets, _sprites);
}
