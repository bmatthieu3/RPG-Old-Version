#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "map.h"
#include "anim.h"
#include "hero.h"
#include "editeur.h"
#include "constantes.h"
#include "matrix.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cursed Crown");
    Carte carte;

    carte.charger(TAILLE_CARTE_X, TAILLE_CARTE_Y);

    Personnage personnage(carte);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2i origine = carte.getTile(0,0).getPosition();
                origine.x += WIDTH_TILE/2;

                personnage.attaquer(CartesienAIsometrique(origine, sf::Mouse::getPosition(window)));
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i origine = carte.getTile(0,0).getPosition();
                origine.x += WIDTH_TILE/2;

                personnage.deplacer(CartesienAIsometrique(origine, sf::Mouse::getPosition(window)));
            }

            if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    personnage.stop_attaquer();
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                     editeur editeur;
                     editeur.main(window);
                }
                else if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        personnage.actualiser(carte);

        carte.afficher(&window);
        personnage.afficher(&window);

        window.display();
    }

    return 0;
}
