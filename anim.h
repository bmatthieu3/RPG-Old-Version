#ifndef ANIM_H
#define ANIM_H

class Anim
{
    public:

        Anim();

        Anim(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2< int > position, int n_frames, int first_frame, sf::Time t_anim);

        ~Anim();

        void afficher(sf::RenderWindow* window);

        void setPosition(sf::Vector2< int > pos);

        sf::Vector2< int > getPosition();

        sf::Time getTempsEcoule();

        int getWidth() const;

        int getHeight() const;

        void setColorToAlpha(sf::Color& color);

        std::vector< sf::VertexArray >& getVertexArrays();

    private:

        sf::Image _charset;
        sf::Texture _charset_tex;

        std::vector< sf::VertexArray > _sprites;
        sf::Time _t_anim;

        sf::Clock _c;

        int _n_frames, _first_frame;
        int _width_sprite, _height_sprite;
};

#endif // ANIM_H
