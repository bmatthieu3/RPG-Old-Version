#ifndef ANIM_H
#define ANIM_H

class anim
{
    public:

        anim();
        anim(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2i position, int n_frames, int first_frame, sf::Time t_anim);
        ~anim();

        void afficher(sf::RenderWindow* window);

        bool charger(const std::string fichier, int width_sprite, int height_sprite, const sf::Vector2i position, int n_frames, int first_frame, sf::Time t_anim);

        void setPosition(sf::Vector2f& pos);

        sf::Vector2i& getPosition();

        sf::Time getTempsEcoule();

        anim operator=(const anim& copie);

    private:

        sf::Texture _charset;
        std::vector< sf::VertexArray > _sprites;
        sf::Time _t_anim;

        sf::Clock _c;

        int _n_frames, _first_frame;
        int _width_sprite, _height_sprite;
};

#endif // ANIM_H
