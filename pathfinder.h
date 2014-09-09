#ifndef PATHFINDER_H
#define PATHFINDER_H

class Pathfinder
{
    public :

        Pathfinder();

        Pathfinder(Carte* carte);

        ~Pathfinder();

        std::vector< sf::Vector2< int > > reconstruire_chemin(const std::vector< Tiles* >& liste_fermee, const Tiles* start, const Tiles* arrive);

        Tiles* min_f(std::vector< Tiles* >& tiles);

        bool isTile(const Tiles* tile, const std::vector< Tiles* > tiles);

        int distance_h(const unsigned int tile_x, const unsigned int tile_y, const unsigned int arrive_x, const unsigned int arrive_y);

        std::vector< sf::Vector2< int > > A_Star(const unsigned int start_x, const unsigned int start_y, const unsigned int arrive_x, const unsigned int arrive_y);

        int get_tile_g(int i, int j);

    private:

        Carte* _carte;

        std::vector < Tiles* > liste_ouverte;

        std::vector < Tiles* > liste_fermee;
};

#endif
