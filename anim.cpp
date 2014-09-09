#include <iostream>

#include <SFML/Graphics.hpp>

#include "constantes.h"
#include "anim.h"

Anim::Anim()
{

}

Anim::Anim(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2< int > position, int n_frames, int first_frame, sf::Time t_anim) : _t_anim(t_anim), _n_frames(n_frames), _first_frame(first_frame), _width_sprite(width_sprite), _height_sprite(height_sprite)
{
    if(!_charset.loadFromFile(fichier.c_str()))
    {
        std::cout << "Erreur chargement du tileset" << std::endl;
    }
    else
    {
        int w = _charset.getSize().x/width_sprite;
        int h = _charset.getSize().y/height_sprite;

        for(unsigned int i = 0; i < w*h; i++)
        {
            int colonne_charset_i = i%w;
            int ligne_charset_i = (i - colonne_charset_i)/w;

            sf::VertexArray current(sf::Quads, 4);

            current[0].position = sf::Vector2< float >(position.x, position.y);
            current[1].position = sf::Vector2< float >(position.x + width_sprite, position.y);
            current[2].position = sf::Vector2< float >(position.x + width_sprite, position.y + height_sprite);
            current[3].position = sf::Vector2< float >(position.x, position.y + height_sprite);

            current[0].texCoords = sf::Vector2< float >(colonne_charset_i*width_sprite, ligne_charset_i*height_sprite);
            current[1].texCoords = sf::Vector2< float >((colonne_charset_i + 1)*width_sprite, ligne_charset_i*height_sprite);
            current[2].texCoords = sf::Vector2< float >((colonne_charset_i + 1)*width_sprite, (ligne_charset_i + 1)*height_sprite);
            current[3].texCoords = sf::Vector2< float >(colonne_charset_i*width_sprite, (ligne_charset_i + 1)*height_sprite);

            _sprites.push_back(current);

            _width_sprite = width_sprite;
            _height_sprite = height_sprite;
            _t_anim = t_anim;
            _n_frames = n_frames;
            _first_frame = first_frame;
        }

        _charset_tex.loadFromImage(_charset);
    }
}

Anim::~Anim()
{

}

void Anim::setPosition(sf::Vector2< int > pos)
{
    for(unsigned int i = 0; i < _sprites.size(); i++)
    {
        _sprites[i][0].position = static_cast< sf::Vector2< float > >(pos);
        _sprites[i][1].position = sf::Vector2< float >(pos.x + _width_sprite, pos.y);
        _sprites[i][2].position = sf::Vector2< float >(pos.x + _width_sprite, pos.y + _height_sprite);
        _sprites[i][3].position = sf::Vector2< float >(pos.x, pos.y + _height_sprite);
    }
}

sf::Time Anim::getTempsEcoule()
{
    return _c.getElapsedTime();
}

std::vector< sf::VertexArray >& Anim::getVertexArrays()
{
    return _sprites;
}

sf::Vector2< int > Anim::getPosition()
{
    sf::Vector2< int > pos;

    pos.x = _sprites[0][0].position.x;
    pos.y = _sprites[0][0].position.y;

    return pos;
}

void Anim::afficher(sf::RenderWindow* window)
{
    sf::Time _t_actu = _c.getElapsedTime();

    float _t_frame = _t_anim.asMicroseconds()/_n_frames;
    int i = _first_frame + int((_t_actu.asMicroseconds()%_t_anim.asMicroseconds())/_t_frame);

    window->draw(_sprites[i], &_charset_tex);
}

void Anim::setColorToAlpha(sf::Color& color)
{
    _charset.createMaskFromColor(color);

    _charset_tex.loadFromImage(_charset);
}

int Anim::getWidth() const
{
    return _width_sprite;
}

int Anim::getHeight() const
{
    return _height_sprite;
}
