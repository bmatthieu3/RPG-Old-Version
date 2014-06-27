#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "parser.h"

Parser::Parser()
{
    fichier.open("Data/Environnement/Tileset/Tilesets.txt", std::ios::in);

    if(fichier)
    {
        std::string parser_actu = "";

        fichier >> parser_actu;

        while(parser_actu != "$")
        {
            _tilesets_directory.push_back(parser_actu);
            fichier >> parser_actu;
        }

        fichier.close();
    }
    else
    {
        std::cerr << "Impossible d'ouvrir le fichier tileset.txt" << std::endl;
    }
}

std::vector< std::string > Parser::getFilesDirectory() const
{
    return _tilesets_directory;
}

Parser::~Parser()
{

}
