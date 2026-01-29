#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <limits> // pour std::numeric_limits

std::string to_lowercase(const std::string &s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool contient_lettres(const std::string &mot, const std::string &lettres)
{
    for (char c : lettres)
    {
        if (mot.find(c) == std::string::npos)
            return false;
    }
    return true;
}

// Vérifie si 'mot' commence par 'prefixe'
bool commence_par(const std::string &mot, const std::string &prefixe)
{
    if (prefixe.empty() || prefixe == ".")
        return true; // aucun préfixe demandé
    if (prefixe.size() > mot.size())
        return false;
    return mot.substr(0, prefixe.size()) == prefixe;
}

// Vérifie si 'mot' ne contient aucune lettre bannie
bool ne_contient_pas(const std::string &mot, const std::string &lettres_bannies)
{
    for (char c : lettres_bannies)
    {
        if (mot.find(c) != std::string::npos)
            return false; // contient une lettre bannie
    }
    return true;
}

int main()
{
    std::set<std::string> dictionnaire;
    std::ifstream fichier("mots_francais.txt");

    if (!fichier.is_open())
    {
        std::cerr << "Erreur : impossible d'ouvrir le fichier mots_francais.txt" << std::endl;
        return 1;
    }

    std::string mot;
    while (std::getline(fichier, mot))
    {
        if (!mot.empty())
        {
            dictionnaire.insert(to_lowercase(mot));
        }
    }
    fichier.close();

    std::cout << "=== Dictionnaire Français 2025 ===" << std::endl;

    while (true)
    {
        int longueur;
        std::string prefixe;
        std::string lettres_inclues;
        std::string lettres_bannies;

        std::cout << "\nEntrez la longueur du mot (0 pour quitter) : ";
        std::cin >> longueur;
        if (longueur == 0)
            break;

        std::cout << "Entrez le préfixe du mot (ou '.' pour aucun) : ";
        std::cin >> prefixe;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vider le buffer
        prefixe = to_lowercase(prefixe);

        std::cout << "Entrez les lettres devant être dans le mot (appuyez sur Entrée si aucune) : ";
        std::getline(std::cin, lettres_inclues);
        lettres_inclues = to_lowercase(lettres_inclues);

        std::cout << "Entrez les lettres à bannir (appuyez sur Entrée si aucune) : ";
        std::getline(std::cin, lettres_bannies);
        lettres_bannies = to_lowercase(lettres_bannies);

        bool trouve = false;
        for (const auto &m : dictionnaire)
        {
            if ((longueur == -1 || m.size() == longueur) &&
                commence_par(m, prefixe) &&
                (lettres_inclues.empty() || contient_lettres(m, lettres_inclues)) &&
                (lettres_bannies.empty() || ne_contient_pas(m, lettres_bannies)))
            {
                std::cout << m << std::endl;
                trouve = true;
            }
        }

        if (!trouve)
        {
            std::cout << "Aucun mot trouvé avec ces critères." << std::endl;
        }
    }

    return 0;
}
