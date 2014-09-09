#ifndef OBJET_H
#define OBJET_H

class Objet : public Clickable
{
    public:

        Objet();

        Objet(const std::string nom, const unsigned int poids, const unsigned int prix);

        ~Objet();

    protected:

        std::string _nom;

        unsigned int _poids;

        unsigned int _prix; // monnaie unique
};

#endif // OBJET_H
