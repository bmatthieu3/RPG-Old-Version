#ifndef PARSER_H
#define PARSER_H

#include <fstream>

class Parser
{
    public:

        Parser();

        virtual ~Parser();

        virtual void setFichierOuvrir(const std::string& file) = 0;

    protected:

        std::ifstream fichier;

};

class ParserFichier : public Parser
{
    public :
        ParserFichier();

        ParserFichier(const std::string& file);

        ~ParserFichier();

        std::vector< std::string > getFilesDirectory() const;

        void setFichierOuvrir(const std::string& file);

    private :

        std::vector < std::string > _fichiers_directory;
};

class ParserSprite : public Parser
{
    public:

        ParserSprite();

        ParserSprite(const std::string& file);

        ~ParserSprite();

        void setFichierOuvrir(const std::string& file);

        std::string getSpriteDirectory() const;

        unsigned int getSpritesheetId() const;

        std::vector< sf::Vector2< int > > getPosition() const;

        std::vector< unsigned int > getWidth() const;

        std::vector< unsigned int > getHeight() const;

        std::vector< unsigned int > getProfondeur() const;

        unsigned int* getColor();

    private:

        unsigned int _sprite_id;

        std::vector< sf::Vector2< int > > _pos;
        std::vector< unsigned int > _width;
        std::vector< unsigned int > _height;

        std::vector< unsigned int > _profondeur;

        unsigned int _color[3];

        std::string _sprite_directory;
};

class ParserCarte : public Parser
{
    public:

        ParserCarte();

        ParserCarte(const std::string& file);

        ~ParserCarte();

        void setFichierOuvrir(const std::string& file);

        std::vector< std::vector < unsigned int > > getTilesetId() const;

        std::vector< std::vector < unsigned int > > getTileId() const;

        std::vector< std::vector < bool > > getCollision() const;

        std::vector< int > getSpriteId() const;

        std::vector< int > getSpritesheetId() const;

        std::vector< sf::Vector2< int > > getPositionSprites() const;

        std::vector< sf::Vector2< int > > getPositionTileSwitch() const;

        std::vector< sf::Vector2< int > > getPositionTile() const;

        std::vector< int > getCarteId() const;

        unsigned int getWidth() const;

        unsigned int getHeight() const;

    private:

        std::vector< std::vector < unsigned int > > _tilesets_id;

        std::vector< std::vector < unsigned int > > _tiles_id;

        std::vector< std::vector < bool > > _collision;

        std::vector< int > _sprites_id;

        std::vector< int > _spritesheets_id;

        std::vector< sf::Vector2< int > > _position_sprites;

        std::vector< sf::Vector2< int > > _pos_tile_switch;

        std::vector< sf::Vector2< int > > _pos_tile;

        std::vector< int > _carte_id;

        unsigned int _width;

        unsigned int _height;
};

class ParserCompetence : public Parser
{
    public:

        ParserCompetence();

        ParserCompetence(const std::string& file);

        ~ParserCompetence();

        void setFichierOuvrir(const std::string& file);

        unsigned int getWidth() const;

        unsigned int getHeight() const;

        unsigned int getNFrame() const;

        unsigned int getTAnim() const;

        unsigned int* getColor();

        std::string getAnimDirectory() const;

        float getTempsRecharge() const;

        float getTempsIncantation() const;

        unsigned int* getCaracteristiques();

        float getDistanceMax() const;

        float getDistanceDegats() const;

        std::string getNom() const;

        std::string getDescription() const;

        unsigned int getCoutMana() const;

        float getDuree() const;

        std::string getIconeDirectory() const;

    private:

        // Graphisme

        unsigned int _n_frame;

        unsigned int _t_anim;

        unsigned int _width;

        unsigned int _height;

        unsigned int _color[3];

        std::string _anim_directory;

        // Gameplay

        float _temps_recharge;

        float _temps_incantation;

        float _duree;

        unsigned int _caracteristiques[2];

        float _distance_max;

        float _distance_degats;

        std::string _nom;

        std::string _description;

        unsigned int _cout_mana;

        std::string _icone_directory;
};



#endif
