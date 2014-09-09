#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constantes.h"
#include "boite.h"

void Boite::chargerSprites()
{
    if(!_textures[CENTRE].loadFromFile("Data/Interface/centre2.jpg"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[H].loadFromFile("Data/Interface/boite_h.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[B].loadFromFile("Data/Interface/boite_b.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[D].loadFromFile("Data/Interface/boite_d.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[G].loadFromFile("Data/Interface/boite_g.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[HD].loadFromFile("Data/Interface/boite_hd.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[HG].loadFromFile("Data/Interface/boite_hg.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[BG].loadFromFile("Data/Interface/boite_bg.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[BD].loadFromFile("Data/Interface/boite_bd.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    for(unsigned int i = 0; i < N_SPRITES_BOITE; i++)
    {
        _sprites[i].setTexture(_textures[i]);
    }

    if (!_beneg.loadFromFile("Data/Interface/LinLibertine_R.ttf"))
    {
        std::cerr << "Erreur chargement de la police" << std::endl;
    }
}

Boite::Boite()
{
    _textures = new sf::Texture[N_SPRITES_BOITE];
    _sprites = new sf::Sprite[N_SPRITES_BOITE];

    this->chargerSprites();

    _pos = sf::Vector2< int >(0,0);
    _width = 0;
    _height = 0;
}

Boite::Boite(const unsigned int width, const unsigned int height, const sf::Vector2< int >& pos)
{
    _textures = new sf::Texture[N_SPRITES_BOITE];
    _sprites = new sf::Sprite[N_SPRITES_BOITE];

    this->chargerSprites();

    setPosition(pos);
    setDimensions(width, height);
}

void Boite::ajouterTexte(const std::string& texte)
{
    sf::Text texte_actu;

    texte_actu.setFont(_beneg);
    texte_actu.setCharacterSize(14);
    texte_actu.setColor(sf::Color::White);
    texte_actu.setString(texte);

    if(_textes.size() == 0)
        texte_actu.setPosition(_pos.x + 10, _pos.y + 5);
    else
        texte_actu.setPosition(_pos.x + 10, _textes.back().getLocalBounds().height + _textes.back().getPosition().y + 3);

    _textes.push_back(texte_actu);

    // Calcul des nouvelles dimensions de la fenetre

    unsigned int h = 0;
    unsigned int w = 0;

    for(unsigned int i = 0; i < _textes.size(); i++)
    {
        if(_textes[i].getLocalBounds().width > w)
        {
            w = _textes[i].getLocalBounds().width;
        }

        h += _textes[i].getLocalBounds().height + 3;
    }

    setDimensions(w + 20, h + 20);
}

Boite::~Boite()
{
    delete[] _sprites;
    delete[] _textures;
}

void Boite::setDimensions(const unsigned int width, const unsigned int height)
{
    _width = width;
    _height = height;

    _sprites[HG].setPosition(sf::Vector2< float >(_pos));
    _sprites[HD].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_width - _textures[HD].getSize().x, 0));
    _sprites[BD].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_width - _textures[BD].getSize().x, _height - _textures[BD].getSize().y));
    _sprites[BG].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(0, _height - _textures[BG].getSize().y));

    _sprites[H].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HD].getSize().x, 0));
    _sprites[B].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HD].getSize().x, _height - _textures[BG].getSize().y));
    _sprites[D].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_width - _textures[HD].getSize().x, _textures[HD].getSize().y));
    _sprites[G].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(0, _textures[HG].getSize().y));

    _sprites[CENTRE].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HG].getSize().x, _textures[HG].getSize().y));
}

void Boite::setPosition(const sf::Vector2< int >& pos)
{
    _sprites[HG].setPosition(_sprites[HG].getPosition() + sf::Vector2< float >(pos) - sf::Vector2< float >(_pos));
    _sprites[HD].setPosition(_sprites[HD].getPosition() + sf::Vector2< float >(pos) - sf::Vector2< float >(_pos));
    _sprites[BG].setPosition(_sprites[BG].getPosition() + sf::Vector2< float >(pos) - sf::Vector2< float >(_pos));
    _sprites[BD].setPosition(_sprites[BD].getPosition() + sf::Vector2< float >(pos) - sf::Vector2< float >(_pos));

    for(std::vector< sf::Text >::iterator it = _textes.begin(); it != _textes.end(); it++)
    {
        it->setPosition(it->getPosition() + sf::Vector2< float >(pos) - sf::Vector2< float >(_pos));
    }

    _pos = pos;
}

sf::Vector2< int > Boite::getSize() const
{
    return sf::Vector2< int >(_width, _height);
}

void Boite::afficher(sf::RenderWindow* fenetre)
{
    fenetre->draw(_sprites[HG]);
    fenetre->draw(_sprites[HD]);
    fenetre->draw(_sprites[BG]);
    fenetre->draw(_sprites[BD]);

    while(_sprites[H].getPosition().x < _sprites[HD].getPosition().x)
    {
        if(_sprites[HD].getPosition().x - _sprites[H].getPosition().x < _textures[H].getSize().x)
        {
            sf::VertexArray vertexArray_h(sf::Quads, 4);

            vertexArray_h[0].position =  _sprites[H].getPosition();
            vertexArray_h[1].position =  sf::Vector2< float >(_sprites[HD].getPosition().x, _sprites[H].getPosition().y);
            vertexArray_h[2].position =  sf::Vector2< float >(_sprites[HD].getPosition().x, _sprites[H].getPosition().y + _textures[H].getSize().y);
            vertexArray_h[3].position =  sf::Vector2< float >(_sprites[H].getPosition().x, _sprites[H].getPosition().y + _textures[H].getSize().y);


            vertexArray_h[0].texCoords =  sf::Vector2< float >(0, 0);
            vertexArray_h[1].texCoords =  sf::Vector2< float >(_sprites[HD].getPosition().x - _sprites[H].getPosition().x, 0);
            vertexArray_h[2].texCoords =  sf::Vector2< float >(_sprites[HD].getPosition().x - _sprites[H].getPosition().x, _textures[H].getSize().y);
            vertexArray_h[3].texCoords =  sf::Vector2< float >(0, _textures[H].getSize().y);


            fenetre->draw(vertexArray_h, &_textures[H]);
        }
        else
        {
            fenetre->draw(_sprites[H]);
        }

        _sprites[H].setPosition(_sprites[H].getPosition() + sf::Vector2< float >(_textures[H].getSize().x, 0));
    }

    while(_sprites[B].getPosition().x < _sprites[BD].getPosition().x)
    {
        if(_sprites[BD].getPosition().x - _sprites[B].getPosition().x < _textures[B].getSize().x)
        {
            sf::VertexArray vertexArray_b(sf::Quads, 4);

            vertexArray_b[0].position =  _sprites[B].getPosition();
            vertexArray_b[1].position =  sf::Vector2< float >(_sprites[BD].getPosition().x, _sprites[B].getPosition().y);
            vertexArray_b[2].position =  sf::Vector2< float >(_sprites[BD].getPosition().x, _sprites[B].getPosition().y + _textures[B].getSize().y);
            vertexArray_b[3].position =  sf::Vector2< float >(_sprites[B].getPosition().x, _sprites[B].getPosition().y + _textures[B].getSize().y);


            vertexArray_b[0].texCoords =  sf::Vector2< float >(0, 0);
            vertexArray_b[1].texCoords =  sf::Vector2< float >(_sprites[BD].getPosition().x - _sprites[B].getPosition().x, 0);
            vertexArray_b[2].texCoords =  sf::Vector2< float >(_sprites[BD].getPosition().x - _sprites[B].getPosition().x, _textures[B].getSize().y);
            vertexArray_b[3].texCoords =  sf::Vector2< float >(0, _textures[B].getSize().y);


            fenetre->draw(vertexArray_b, &_textures[B]);
        }
        else
        {
            fenetre->draw(_sprites[B]);
        }

        _sprites[B].setPosition(_sprites[B].getPosition() + sf::Vector2< float >(_textures[B].getSize().x, 0));
    }

    while(_sprites[G].getPosition().y < _sprites[BG].getPosition().y)
    {
        if(_sprites[BG].getPosition().y - _sprites[G].getPosition().y < _textures[G].getSize().y)
        {
            sf::VertexArray vertexArray_g(sf::Quads, 4);

            vertexArray_g[0].position =  _sprites[G].getPosition();
            vertexArray_g[1].position =  sf::Vector2< float >(_sprites[G].getPosition().x + _textures[G].getSize().x, _sprites[G].getPosition().y);
            vertexArray_g[2].position =  sf::Vector2< float >(_sprites[G].getPosition().x + _textures[G].getSize().x, _sprites[BG].getPosition().y);
            vertexArray_g[3].position =  sf::Vector2< float >(_sprites[G].getPosition().x, _sprites[BG].getPosition().y);

            vertexArray_g[0].texCoords =  sf::Vector2< float >(0, 0);
            vertexArray_g[1].texCoords =  sf::Vector2< float >(_textures[G].getSize().x, 0);
            vertexArray_g[2].texCoords =  sf::Vector2< float >(_textures[G].getSize().x, _sprites[BG].getPosition().y - _sprites[G].getPosition().y);
            vertexArray_g[3].texCoords =  sf::Vector2< float >(0, _sprites[BG].getPosition().y - _sprites[G].getPosition().y);


            fenetre->draw(vertexArray_g, &_textures[G]);
        }
        else
        {
            fenetre->draw(_sprites[G]);
        }

        _sprites[G].setPosition(_sprites[G].getPosition() + sf::Vector2< float >(0, _textures[G].getSize().y));
    }

    while(_sprites[D].getPosition().y < _sprites[BD].getPosition().y)
    {
        if(_sprites[BD].getPosition().y - _sprites[D].getPosition().y < _textures[D].getSize().y)
        {
            sf::VertexArray vertexArray_d(sf::Quads, 4);

            vertexArray_d[0].position =  _sprites[D].getPosition();
            vertexArray_d[1].position =  sf::Vector2< float >(_sprites[D].getPosition().x + _textures[D].getSize().x, _sprites[D].getPosition().y);
            vertexArray_d[2].position =  sf::Vector2< float >(_sprites[D].getPosition().x + _textures[D].getSize().x, _sprites[BD].getPosition().y);
            vertexArray_d[3].position =  sf::Vector2< float >(_sprites[D].getPosition().x, _sprites[BD].getPosition().y);

            vertexArray_d[0].texCoords =  sf::Vector2< float >(0, 0);
            vertexArray_d[1].texCoords =  sf::Vector2< float >(_textures[D].getSize().x, 0);
            vertexArray_d[2].texCoords =  sf::Vector2< float >(_textures[D].getSize().x, _sprites[BD].getPosition().y - _sprites[D].getPosition().y);
            vertexArray_d[3].texCoords =  sf::Vector2< float >(0, _sprites[BD].getPosition().y - _sprites[D].getPosition().y);


            fenetre->draw(vertexArray_d, &_textures[D]);
        }
        else
        {
            fenetre->draw(_sprites[D]);
        }

        _sprites[D].setPosition(_sprites[D].getPosition() + sf::Vector2< float >(0, _textures[D].getSize().y));
    }

    while(_sprites[CENTRE].getPosition().y < _sprites[BD].getPosition().y)
    {
        while(_sprites[CENTRE].getPosition().x < _sprites[HD].getPosition().x)
        {
            if(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x < _textures[CENTRE].getSize().x || _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
            {
                sf::VertexArray vertexArray_centre(sf::Quads, 4);

                vertexArray_centre[0].position =  _sprites[CENTRE].getPosition();
                vertexArray_centre[1].position =  sf::Vector2< float >(_sprites[HD].getPosition().x, _sprites[CENTRE].getPosition().y);

                if(_sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
                {
                    vertexArray_centre[2].position =  sf::Vector2< float >(_sprites[HD].getPosition().x, _sprites[BD].getPosition().y);
                    vertexArray_centre[3].position =  sf::Vector2< float >(_sprites[CENTRE].getPosition().x, _sprites[BD].getPosition().y);
                }
                else
                {
                    vertexArray_centre[2].position =  sf::Vector2< float >(_sprites[HD].getPosition().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y);
                    vertexArray_centre[3].position =  sf::Vector2< float >(_sprites[CENTRE].getPosition().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y);
                }

                vertexArray_centre[0].texCoords =  sf::Vector2< float >(0, 0);
                vertexArray_centre[1].texCoords =  sf::Vector2< float >(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, 0);

                if(_sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
                {
                    vertexArray_centre[2].texCoords =  sf::Vector2< float >(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y);
                    vertexArray_centre[3].texCoords =  sf::Vector2< float >(0, _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y);
                }
                else
                {
                    vertexArray_centre[2].texCoords =  sf::Vector2< float >(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, _textures[CENTRE].getSize().y);
                    vertexArray_centre[3].texCoords =  sf::Vector2< float >(0, _textures[CENTRE].getSize().y);
                }

                fenetre->draw(vertexArray_centre, &_textures[CENTRE]);
            }
            else
            {
                fenetre->draw(_sprites[CENTRE]);
            }

            _sprites[CENTRE].setPosition(_sprites[CENTRE].getPosition() + sf::Vector2< float >(_textures[CENTRE].getSize().x, 0));
        }

        _sprites[CENTRE].setPosition(sf::Vector2< float >(_sprites[HG].getPosition().x + _textures[HG].getSize().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y));
    }

    for(unsigned int i = 0; i < _textes.size(); i++)
        fenetre->draw(_textes[i]);

    _sprites[H].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HD].getSize().x, 0));
    _sprites[B].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HD].getSize().x, _height - _textures[BG].getSize().y));
    _sprites[D].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_width - _textures[HD].getSize().x, _textures[HD].getSize().y));
    _sprites[G].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(0, _textures[HG].getSize().y));

    _sprites[CENTRE].setPosition(sf::Vector2< float >(_pos) + sf::Vector2< float >(_textures[HG].getSize().x, _textures[HG].getSize().y));
}
