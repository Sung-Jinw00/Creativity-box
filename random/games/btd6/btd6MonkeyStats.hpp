#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Bonus {
    int degats;
    int pierce;
    float vitesse;
    float range;
};

struct Chemin {
    int niveau;
    std::vector<Bonus> bonusParNiveau;
};

struct Singe {
    std::string nom;
    int degats;
    int pierce;
    float vitesseAttaque;
    float range;

    Chemin chemin1;
    Chemin chemin2;
    Chemin chemin3;
};

class SingeCatalogue
{
private:
    std::unordered_map<std::string, Singe> singes;

public:
    void ajouter(const Singe& s) {
        singes[s.nom] = s;
    }

    const Singe& get(const std::string& nom) const {
        return singes.at(nom);
    }

    bool existe(const std::string& nom) const {
        return singes.find(nom) != singes.end();
    }

    // Appliquer un bonus à un chemin spécifique
    void ameliorerChemin(Singe& s, int cheminNum) {
        Chemin* chemin = nullptr;
        if (cheminNum == 1) chemin = &s.chemin1;
        else if (cheminNum == 2) chemin = &s.chemin2;
        else if (cheminNum == 3) chemin = &s.chemin3;
        else return;

        // Vérification des règles de niveau max
        if (chemin->niveau >= 5) return; // max niveau atteint

        // Vérifier si un autre chemin a >=3
        int autresMax = 0;
        if (cheminNum != 1) autresMax = std::max(autresMax, s.chemin1.niveau);
        if (cheminNum != 2) autresMax = std::max(autresMax, s.chemin2.niveau);
        if (cheminNum != 3) autresMax = std::max(autresMax, s.chemin3.niveau);

        if (autresMax >= 3) {
            // Limite à 2 pour ce chemin
            if (chemin->niveau >= 2) return;
        }

        chemin->niveau++;
    }

    // Calcul des stats finales avec toutes les améliorations appliquées
    Singe calculerStats(const Singe& s) {
        Singe result = s;

        auto appliquerChemin = [&](const Chemin& c){
            for (int i = 0; i < c.niveau && i < c.bonusParNiveau.size(); ++i) {
                result.degats += c.bonusParNiveau[i].degats;
                result.pierce += c.bonusParNiveau[i].pierce;
                result.vitesseAttaque += c.bonusParNiveau[i].vitesse;
                result.range += c.bonusParNiveau[i].range;
            }
        };

        appliquerChemin(s.chemin1);
        appliquerChemin(s.chemin2);
        appliquerChemin(s.chemin3);

        return result;
    }
};
