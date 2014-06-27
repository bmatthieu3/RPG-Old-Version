#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "fenetre.h"
#include "constantes.h"

void Fenetre::chargerSprites()
{
    if(!_textures[CENTRE].loadFromFile("Data/Interface/centre.jpg"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[H].loadFromFile("Data/Interface/h.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[B].loadFromFile("Data/Interface/b.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[D].loadFromFile("Data/Interface/d.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[G].loadFromFile("Data/Interface/g.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[HD].loadFromFile("Data/Interface/coin_hd.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[HG].loadFromFile("Data/Interface/coin_hg.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[BG].loadFromFile("Data/Interface/coin_bg.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[BD].loadFromFile("Data/Interface/coin_bd.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[ENTETE].loadFromFile("Data/Interface/entete.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    if(!_textures[QUITTER].loadFromFile("Data/Interface/quitter.png"))
    {
        std::cout << "Erreur chargement des textures" << std::endl;
    }

    for(unsigned int i = 0; i < N_SPRITES_FENETRE; i++)
    {
        _sprites[i].setTexture(_textures[i]);
    }

    if (!_beneg.loadFromFile("Data/Interface/beneg.ttf"))
    {
        std::cerr << "Erreur chargement de la police" << std::endl;
    }

    _titre.setFont(_beneg);
    _titre.setCharacterSize(30);
    _titre.setColor(sf::Color::Black);
}

Fenetre::Fenetre()
{
    _textures = new sf::Texture[N_SPRITES_FENETRE];
    _sprites = new sf::Sprite[N_SPRITES_FENETRE];

    this->chargerSprites();

    _pos = sf::Vector2f(0,0);
    _width = 0;
    _height = 0;
}

Fenetre::Fenetre(const std::string& titre, const unsigned int width, const unsigned int height, const sf::Vector2f& pos)
{
    _textures = new sf::Texture[N_SPRITES_FENETRE];
    _sprites = new sf::Sprite[N_SPRITES_FENETRE];

    this->chargerSprites();

    setPosition(pos);
    setDimensions(width, height);
    setTitre(titre);
}

Fenetre::~Fenetre()
{
    delete[] _sprites;
    delete[] _textures;
}

void Fenetre::setDimensions(const unsigned int width, const unsigned int height)
{
    _width = width;
    _height = height;

    _sprites[HG].setPosition(_pos);
    _sprites[HD].setPosition(_pos + sf::Vector2f(_width - _textures[HD].getSize().x, 0));
    _sprites[BD].setPosition(_pos + sf::Vector2f(_width - _textures[BD].getSize().x, _height - _textures[BD].getSize().y));
    _sprites[BG].setPosition(_pos + sf::Vector2f(0, _height - _textures[BG].getSize().y));

    _sprites[H].setPosition(_pos + sf::Vector2f(_textures[HD].getSize().x, 0));
    _sprites[B].setPosition(_pos + sf::Vector2f(_textures[HD].getSize().x, _height - _textures[BG].getSize().y));
    _sprites[D].setPosition(_pos + sf::Vector2f(_width - _textures[HD].getSize().x, _textures[HD].getSize().y));
    _sprites[G].setPosition(_pos + sf::Vector2f(0, _textures[HG].getSize().y));

    _sprites[CENTRE].setPosition(_pos + sf::Vector2f(_textures[HG].getSize().x, _textures[HG].getSize().y));

    _sprites[ENTETE].setPosition(_pos + sf::Vector2f(_textures[HG].getSize().x, OFFSET_ENTETE_Y));

    _sprites[QUITTER].setPosition(sf::Vector2f(_sprites[HD].getPosition().x, _pos.y + OFFSET_ENTETE_Y));

    _titre.setPosition(_pos + sf::Vector2f(_textures[HD].getSize().x, 0));
}

void Fenetre::setPosition(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Fenetre::setTitre(const std::string& titre)
{
    _titre.setString(titre);
}

bool Fenetre::getActif() const
{
   return _actif;
}

void Fenetre::evenement_quitter(const sf::Vector2i& mouse_clic)
{
    if(_actif)
    {
        if(mouse_clic.x >= _sprites[QUITTER].getPosition().x && mouse_clic.x <= _sprites[QUITTER].getPosition().x + _textures[QUITTER].getSize().x)
        {
            if(mouse_clic.y >= _sprites[QUITTER].getPosition().y && mouse_clic.y <= _sprites[QUITTER].getPosition().y + _textures[QUITTER].getSize().y)
            {
                _actif = false;
            }
        }
    }
}

void Fenetre::afficher(sf::RenderWindow* fenetre)
{
    if(_actif)
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
                vertexArray_h[1].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[H].getPosition().y);
                vertexArray_h[2].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[H].getPosition().y + _textures[H].getSize().y);
                vertexArray_h[3].position =  sf::Vector2f(_sprites[H].getPosition().x, _sprites[H].getPosition().y + _textures[H].getSize().y);


                vertexArray_h[0].texCoords =  sf::Vector2f(0, 0);
                vertexArray_h[1].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[H].getPosition().x, 0);
                vertexArray_h[2].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[H].getPosition().x, _textures[H].getSize().y);
                vertexArray_h[3].texCoords =  sf::Vector2f(0, _textures[H].getSize().y);


                fenetre->draw(vertexArray_h, &_textures[H]);
            }
            else
            {
                fenetre->draw(_sprites[H]);
            }

            _sprites[H].setPosition(_sprites[H].getPosition() + sf::Vector2f(_textures[H].getSize().x, 0));
        }

        while(_sprites[B].getPosition().x < _sprites[BD].getPosition().x)
        {
            if(_sprites[BD].getPosition().x - _sprites[B].getPosition().x < _textures[B].getSize().x)
            {
                sf::VertexArray vertexArray_b(sf::Quads, 4);

                vertexArray_b[0].position =  _sprites[B].getPosition();
                vertexArray_b[1].position =  sf::Vector2f(_sprites[BD].getPosition().x, _sprites[B].getPosition().y);
                vertexArray_b[2].position =  sf::Vector2f(_sprites[BD].getPosition().x, _sprites[B].getPosition().y + _textures[B].getSize().y);
                vertexArray_b[3].position =  sf::Vector2f(_sprites[B].getPosition().x, _sprites[B].getPosition().y + _textures[B].getSize().y);


                vertexArray_b[0].texCoords =  sf::Vector2f(0, 0);
                vertexArray_b[1].texCoords =  sf::Vector2f(_sprites[BD].getPosition().x - _sprites[B].getPosition().x, 0);
                vertexArray_b[2].texCoords =  sf::Vector2f(_sprites[BD].getPosition().x - _sprites[B].getPosition().x, _textures[B].getSize().y);
                vertexArray_b[3].texCoords =  sf::Vector2f(0, _textures[B].getSize().y);


                fenetre->draw(vertexArray_b, &_textures[B]);
            }
            else
            {
                fenetre->draw(_sprites[B]);
            }

            _sprites[B].setPosition(_sprites[B].getPosition() + sf::Vector2f(_textures[B].getSize().x, 0));
        }

        while(_sprites[G].getPosition().y < _sprites[BG].getPosition().y)
        {
            if(_sprites[BG].getPosition().y - _sprites[G].getPosition().y < _textures[G].getSize().y)
            {
                sf::VertexArray vertexArray_g(sf::Quads, 4);

                vertexArray_g[0].position =  _sprites[G].getPosition();
                vertexArray_g[1].position =  sf::Vector2f(_sprites[G].getPosition().x + _textures[G].getSize().x, _sprites[G].getPosition().y);
                vertexArray_g[2].position =  sf::Vector2f(_sprites[G].getPosition().x + _textures[G].getSize().x, _sprites[BG].getPosition().y);
                vertexArray_g[3].position =  sf::Vector2f(_sprites[G].getPosition().x, _sprites[BG].getPosition().y);

                vertexArray_g[0].texCoords =  sf::Vector2f(0, 0);
                vertexArray_g[1].texCoords =  sf::Vector2f(_textures[G].getSize().x, 0);
                vertexArray_g[2].texCoords =  sf::Vector2f(_textures[G].getSize().x, _sprites[BG].getPosition().y - _sprites[G].getPosition().y);
                vertexArray_g[3].texCoords =  sf::Vector2f(0, _sprites[BG].getPosition().y - _sprites[G].getPosition().y);


                fenetre->draw(vertexArray_g, &_textures[G]);
            }
            else
            {
                fenetre->draw(_sprites[G]);
            }

            _sprites[G].setPosition(_sprites[G].getPosition() + sf::Vector2f(0, _textures[G].getSize().y));
        }

        while(_sprites[D].getPosition().y < _sprites[BD].getPosition().y)
        {
            if(_sprites[BD].getPosition().y - _sprites[D].getPosition().y < _textures[D].getSize().y)
            {
                sf::VertexArray vertexArray_d(sf::Quads, 4);

                vertexArray_d[0].position =  _sprites[D].getPosition();
                vertexArray_d[1].position =  sf::Vector2f(_sprites[D].getPosition().x + _textures[D].getSize().x, _sprites[D].getPosition().y);
                vertexArray_d[2].position =  sf::Vector2f(_sprites[D].getPosition().x + _textures[D].getSize().x, _sprites[BD].getPosition().y);
                vertexArray_d[3].position =  sf::Vector2f(_sprites[D].getPosition().x, _sprites[BD].getPosition().y);

                vertexArray_d[0].texCoords =  sf::Vector2f(0, 0);
                vertexArray_d[1].texCoords =  sf::Vector2f(_textures[D].getSize().x, 0);
                vertexArray_d[2].texCoords =  sf::Vector2f(_textures[D].getSize().x, _sprites[BD].getPosition().y - _sprites[D].getPosition().y);
                vertexArray_d[3].texCoords =  sf::Vector2f(0, _sprites[BD].getPosition().y - _sprites[D].getPosition().y);


                fenetre->draw(vertexArray_d, &_textures[D]);
            }
            else
            {
                fenetre->draw(_sprites[D]);
            }

            _sprites[D].setPosition(_sprites[D].getPosition() + sf::Vector2f(0, _textures[D].getSize().y));
        }

        while(_sprites[CENTRE].getPosition().y < _sprites[BD].getPosition().y)
        {
            while(_sprites[CENTRE].getPosition().x < _sprites[HD].getPosition().x)
            {
                if(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x < _textures[CENTRE].getSize().x || _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
                {
                    sf::VertexArray vertexArray_centre(sf::Quads, 4);

                    vertexArray_centre[0].position =  _sprites[CENTRE].getPosition();
                    vertexArray_centre[1].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[CENTRE].getPosition().y);

                    if(_sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
                    {
                        vertexArray_centre[2].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[BD].getPosition().y);
                        vertexArray_centre[3].position =  sf::Vector2f(_sprites[CENTRE].getPosition().x, _sprites[BD].getPosition().y);
                    }
                    else
                    {
                        vertexArray_centre[2].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y);
                        vertexArray_centre[3].position =  sf::Vector2f(_sprites[CENTRE].getPosition().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y);
                    }

                    vertexArray_centre[0].texCoords =  sf::Vector2f(0, 0);
                    vertexArray_centre[1].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, 0);

                    if(_sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y < _textures[CENTRE].getSize().y)
                    {
                        vertexArray_centre[2].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y);
                        vertexArray_centre[3].texCoords =  sf::Vector2f(0, _sprites[BD].getPosition().y - _sprites[CENTRE].getPosition().y);
                    }
                    else
                    {
                        vertexArray_centre[2].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[CENTRE].getPosition().x, _textures[CENTRE].getSize().y);
                        vertexArray_centre[3].texCoords =  sf::Vector2f(0, _textures[CENTRE].getSize().y);
                    }

                    fenetre->draw(vertexArray_centre, &_textures[CENTRE]);
                }
                else
                {
                    fenetre->draw(_sprites[CENTRE]);
                }

                _sprites[CENTRE].setPosition(_sprites[CENTRE].getPosition() + sf::Vector2f(_textures[CENTRE].getSize().x, 0));
            }

            _sprites[CENTRE].setPosition(sf::Vector2f(_sprites[HG].getPosition().x + _textures[HG].getSize().x, _sprites[CENTRE].getPosition().y + _textures[CENTRE].getSize().y));
        }

        while(_sprites[ENTETE].getPosition().x < _sprites[HD].getPosition().x)
        {
            if(_sprites[HD].getPosition().x - _sprites[ENTETE].getPosition().x < _textures[ENTETE].getSize().x || _sprites[BD].getPosition().y - _sprites[ENTETE].getPosition().y < _textures[ENTETE].getSize().y)
            {
                sf::VertexArray vertexArray_entete(sf::Quads, 4);

                vertexArray_entete[0].position =  _sprites[ENTETE].getPosition();
                vertexArray_entete[1].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[ENTETE].getPosition().y);

                if(_sprites[BD].getPosition().y - _sprites[ENTETE].getPosition().y < _textures[ENTETE].getSize().y)
                {
                    vertexArray_entete[2].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[BD].getPosition().y);
                    vertexArray_entete[3].position =  sf::Vector2f(_sprites[ENTETE].getPosition().x, _sprites[BD].getPosition().y);
                }
                else
                {
                    vertexArray_entete[2].position =  sf::Vector2f(_sprites[HD].getPosition().x, _sprites[ENTETE].getPosition().y + _textures[ENTETE].getSize().y);
                    vertexArray_entete[3].position =  sf::Vector2f(_sprites[ENTETE].getPosition().x, _sprites[ENTETE].getPosition().y + _textures[ENTETE].getSize().y);
                }

                vertexArray_entete[0].texCoords =  sf::Vector2f(0, 0);
                vertexArray_entete[1].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[ENTETE].getPosition().x, 0);

                if(_sprites[BD].getPosition().y - _sprites[ENTETE].getPosition().y < _textures[ENTETE].getSize().y)
                {
                    vertexArray_entete[2].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[ENTETE].getPosition().x, _sprites[BD].getPosition().y - _sprites[ENTETE].getPosition().y);
                    vertexArray_entete[3].texCoords =  sf::Vector2f(0, _sprites[BD].getPosition().y - _sprites[ENTETE].getPosition().y);
                }
                else
                {
                    vertexArray_entete[2].texCoords =  sf::Vector2f(_sprites[HD].getPosition().x - _sprites[ENTETE].getPosition().x, _textures[ENTETE].getSize().y);
                    vertexArray_entete[3].texCoords =  sf::Vector2f(0, _textures[ENTETE].getSize().y);
                }

                fenetre->draw(vertexArray_entete, &_textures[ENTETE]);
            }
            else
            {
                fenetre->draw(_sprites[ENTETE]);
            }

            _sprites[ENTETE].setPosition(_sprites[ENTETE].getPosition() + sf::Vector2f(_textures[ENTETE].getSize().x, 0));
        }

        fenetre->draw(_sprites[QUITTER]);
        fenetre->draw(_titre);

        _sprites[H].setPosition(_pos + sf::Vector2f(_textures[HD].getSize().x, 0));
        _sprites[B].setPosition(_pos + sf::Vector2f(_textures[HD].getSize().x, _height - _textures[BG].getSize().y));
        _sprites[D].setPosition(_pos + sf::Vector2f(_width - _textures[HD].getSize().x, _textures[HD].getSize().y));
        _sprites[G].setPosition(_pos + sf::Vector2f(0, _textures[HG].getSize().y));

        _sprites[CENTRE].setPosition(_pos + sf::Vector2f(_textures[HG].getSize().x, _textures[HG].getSize().y));

        _sprites[ENTETE].setPosition(_pos + sf::Vector2f(_textures[HG].getSize().x, OFFSET_ENTETE_Y));
    }
}
