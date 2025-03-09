#include <iostream>
#include <unordered_map>
#include <memory>

class Objet {
public:
    std::string name;
    int quantite;

    Objet(std::string n, int q) : name(n), quantite(q) {}
};

class Inventaire {
public:
    std::unordered_map<std::string, std::unique_ptr<Objet>> inventaire;

    void ajouter(const Objet& obj) { // 👈 Prend un objet par référence constante
        std::unique_ptr<Objet> newObjet = std::make_unique<Objet>(obj.name, obj.quantite);
        inventaire[obj.name] = std::move(newObjet);
        std::cout << "Ajout de " << obj.name << " (x" << obj.quantite << ")\n";
    }

    void display() {
        std::cout << "Inventaire :\n";
        for (const auto& pair : inventaire) {
            std::cout << "- " << pair.first << " (x" << pair.second->quantite << ")\n";
        }
    }

    ~Inventaire() {
        std::cout << "Mémoire de l'inventaire libérée." << std::endl;
    }
};

int main() {
    Inventaire inventaire1;

    Objet pomme("Pomme", 3);
    Objet epee("Épée", 1);

    inventaire1.ajouter(pomme);  // 👈 On passe l'objet directement
    inventaire1.ajouter(epee);

    inventaire1.display();

    return 0;
}
