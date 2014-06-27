#include <iostream>

#include <SFML/Graphics.hpp>

#include "anim.h"
#include "constantes.h"

anim::anim()
{

}

anim::anim(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2i position, int n_frames, int first_frame, sf::Time t_anim) : _t_anim(t_anim), _n_frames(n_frames), _first_frame(first_frame), _width_sprite(width_sprite), _height_sprite(height_sprite)
{
    if(!this->charger(fichier, width_sprite, height_sprite, position, n_frames, first_frame, t_anim))
    {
        std::cout << "Erreur dans le chargement de anim : " << fichier << std::endl;
    }
}

anim::~anim()
{

}

bool anim::charger(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2i position, int n_frames, int first_frame, sf::Time t_anim)
{
    if(!_charset.loadFromFile(fichier.c_str()))
    {
        std::cout << "Erreur chargement du tileset" << std::endl;

        return false;
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

            current[0].position = sf::Vector2f(position.x, position.y);
            current[1].position = sf::Vector2f(position.x + width_sprite, position.y);
            current[2].position = sf::Vector2f(position.x + width_sprite, position.y + height_sprite);
            current[3].position = sf::Vector2f(position.x, position.y + height_sprite);

            current[0].texCoords = sf::Vector2f(colonne_charset_i*width_sprite, ligne_charset_i*height_sprite);
            current[1].texCoords = sf::Vector2f((colonne_charset_i + 1)*width_sprite, ligne_charset_i*height_sprite);
            current[2].texCoords = sf::Vector2f((colonne_charset_i + 1)*width_sprite, (ligne_charset_i + 1)*height_sprite);
            current[3].texCoords = sf::Vector2f(colonne_charset_i*width_sprite, (ligne_charset_i + 1)*height_sprite);

            _sprites.push_back(current);

            _width_sprite = width_sprite;
            _height_sprite = height_sprite;
            _t_anim = t_anim;
            _n_frames = n_frames;
            _first_frame = first_frame;
        }
    }

    return true;
}

void anim::setPosition(sf::Vector2f& pos)
{
    for(unsigned int i = 0; i < _sprites.size(); i++)
    {
        _sprites[i][0].position = pos;
        _sprites[i][1].position = sf::Vector2f(pos.x + _width_sprite, pos.y);
        _sprites[i][2].position = sf::Vector2f(pos.x + _width_sprite, pos.y + _height_sprite);
        _sprites[i][3].position = sf::Vector2f(pos.x, pos.y + _height_sprite);
    }
}

sf::Time anim::getTempsEcoule()
{
    return _c.getElapsedTime();
}

sf::Vector2i& anim::getPosition()
{
    sf::Vector2i pos;

    pos.x = _sprites[0][0].position.x;
    pos.y = _sprites[0][0].position.y;

    return pos;
}

void anim::afficher(sf::RenderWindow* window)
{
    sf::Time _t_actu = _c.getElapsedTime();

    float _t_frame = _t_anim.asMicroseconds()/_n_frames;
    int i = _first_frame + int((_t_actu.asMicroseconds()%_t_anim.asMicroseconds())/_t_frame);

    window->draw(_sprites[i], &_charset);
}

anim anim::operator=(const anim& copie)
{
    this->_c = copie._c;
    this->_charset = copie._charset;
    this->_first_frame = copie._first_frame;
    this->_height_sprite = copie._height_sprite;
    this->_n_frames = copie._n_frames;
    this->_sprites = copie._sprites;
    this->_t_anim = copie._t_anim;
    this->_width_sprite = copie._width_sprite;

    return *this;
}
