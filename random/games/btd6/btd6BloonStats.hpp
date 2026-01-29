#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Bloon
{
    std::string nom;
    int         vie;
    int         mancheDApparition;
    std::string projectilesEfficaces;
};

class BloonCatalogue
{
private:
    std::unordered_map<std::string, Bloon> bloons;

    void ajouter(const Bloon& b)
    {
        bloons[b.nom] = b;
    }

public:
    BloonCatalogue() 
    {
        // Bloons normaux
        ajouter({"Rouge", 1, 1, "Tous"});
        ajouter({"Bleu", 2, 3, "Tous"});
        ajouter({"Vert", 3, 6, "Tous"});
        ajouter({"Jaune", 4, 11, "Tous"});
        ajouter({"Rose", 5, 15, "Tous"});
        ajouter({"Noir", 11, 20, "Tous sauf explosions"});
        ajouter({"Blanc", 11, 22, "Tous sauf gel"});
        ajouter({"Violet", 11, 25, "Tous sauf énergie, feu et plasma"});
        ajouter({"Plomb", 23, 28, "Tous sauf projectiles tranchants"});
        ajouter({"Zèbre", 23, 26, "Tous sauf explosions et gel"});
        ajouter({"Arc-en-ciel", 47, 35, "Tous"});
        ajouter({"Céramique", 104, 38, "Tous"});

        // Bloons MOAB-class
        ajouter({"M.O.A.B.", 616, 40, "Tous"});
        ajouter({"B.F.B.", 3164, 60, "Tous"});
        ajouter({"Z.O.M.G.", 16656, 80, "Tous"});
        ajouter({"D.D.T.", 816, 90, "Tous sauf explosions et projectiles tranchants"});
        ajouter({"B.A.D.", 55760, 100, "Tous"});
    }

    const Bloon& get(const std::string& nom) const 
    {
        return bloons.at(nom);
    }

    bool existe(const std::string& nom) const 
    {
        return bloons.find(nom) != bloons.end();
    }

	void afficherParVie() const
    {
        std::vector<Bloon> tmp;
        for (const auto& pair : bloons) {
            tmp.push_back(pair.second);
        }
        std::sort(tmp.begin(), tmp.end(), [](const Bloon& a, const Bloon& b) {
            return a.vie < b.vie;
        });
        std::cout << "=== Bloons triés par points de vie ===\n";
        for (const auto& b : tmp) {
            std::cout << b.nom << " : " << b.vie << " PV\n";
        }
        std::cout << "====================================\n";
    }

    void afficherParManche() const
    {
        std::vector<Bloon> tmp;
        for (const auto& pair : bloons)
            tmp.push_back(pair.second);
        std::sort(tmp.begin(), tmp.end(), [](const Bloon& a, const Bloon& b) {
            return a.mancheDApparition < b.mancheDApparition;
        });
        std::cout << "=== Bloons triés par manche d'apparition ===\n";
        for (const auto& b : tmp) {
            std::cout << b.nom << " : Manche " << b.mancheDApparition << "\n";
        }
        std::cout << "==========================================\n";
    }
};
