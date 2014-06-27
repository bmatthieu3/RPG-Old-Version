#ifndef PARSER_H
#define PARSER_H

#include <fstream>

class Parser
{
    public:

        Parser();
        ~Parser();

        std::vector< std::string > getFilesDirectory() const;


    private:

        std::ifstream fichier;
        std::vector < std::string > _tilesets_directory;

};

#endif
