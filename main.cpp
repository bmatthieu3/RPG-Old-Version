#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

extern "C"
{
    #include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"

}

#include <luabind/luabind.hpp>


#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cursed Crown");

    sf::Sprite menu;
    sf::Texture menu_texture;

    sf::Sprite selection;
    sf::Texture selection_texture;

    sf::Font beneg;

    sf::Text titre;

    enum{JEU, EDITEUR, QUITTER, N_TEXTE};

    sf::Text text[N_TEXTE];

    if(!menu_texture.loadFromFile("Data//wall-of-skulls.png"))
    {
        std::cout << "Erreur chargement du sprite" << std::endl;
    }

    menu.setTexture(menu_texture);

    if(!selection_texture.loadFromFile("Data//selection.png"))
    {
        std::cout << "Erreur chargement du sprite" << std::endl;
    }

    selection.setTexture(selection_texture);

    if (!beneg.loadFromFile("Data/Interface/beneg.ttf"))
    {
        std::cerr << "Erreur chargement de la police" << std::endl;
    }

    titre.setFont(beneg);
    titre.setCharacterSize(150);
    titre.setColor(sf::Color::White);

    for(unsigned int i = 0; i < N_TEXTE; i++)
    {
        text[i].setFont(beneg);
        text[i].setCharacterSize(100);
        text[i].setColor(sf::Color::White);
    }

    titre.setString("Cursed Crown");
    titre.setPosition(WINDOW_WIDTH/2 - titre.getGlobalBounds().width/2, 0);

    text[JEU].setString("Jouer");
    text[JEU].setPosition(WINDOW_WIDTH/2 - text[JEU].getGlobalBounds().width/2, 200);

    text[EDITEUR].setString("Editeur");
    text[EDITEUR].setPosition(WINDOW_WIDTH/2 - text[EDITEUR].getGlobalBounds().width/2, 300);

    text[QUITTER].setString("Quitter");
    text[QUITTER].setPosition(WINDOW_WIDTH/2 - text[QUITTER].getGlobalBounds().width/2, 400);

    selection.setPosition(text[JEU].getPosition().x - 150, text[JEU].getPosition().y + 40);

    unsigned int choix = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Return)
                {
                    if(choix%(N_TEXTE) == QUITTER)
                    {
                        window.close();
                    }
                    else if(choix%(N_TEXTE) == JEU)
                    {
                        Jeu cursed_crown;

                        cursed_crown.jouer(window);
                    }
                    else if(choix%(N_TEXTE) == EDITEUR)
                    {
                        Editeur editeur;
                        editeur.main(window);
                    }
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    choix--;
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    choix++;
                }
                else if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }

                selection.setPosition(text[JEU].getPosition().x - 150, text[JEU].getPosition().y + 40 + choix%(N_TEXTE)*100);
            }
        }

        window.clear();

        window.draw(menu);

        window.draw(titre);

        for(unsigned int i = 0; i < N_TEXTE; i++)
        {
            window.draw(text[i]);
        }

        window.draw(selection);

        window.display();
    }

    return 0;
}
