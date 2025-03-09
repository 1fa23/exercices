#include <iostream>
#include <vector> 
#include<memory>
#include <algorithm>

// la liste sera de cette facon : pour un node d'indice p ,
// son fils gauche est d'indice 2p+1 et son fils droite estd 'indice 2p+2
struct BST{
   std::vector<int> bst;

   

};

// neoad d'indice p
void infixe(BST& Bst, int p){
    if(p>=Bst.bst.size()){
        return ;
    };

    infixe(Bst,2*p+1);

    std::cout<<Bst.bst.at(p)<<" ";

    infixe(Bst,2*p+2);

}

void inserer(BST& Bst, int val ,int p){
    if (p >= Bst.bst.size()) {
        // Remplissage avec -1 (indique une case vide)
    }
    
    if (val<=Bst.bst.at(p)){
        if(Bst.bst.at(2*p+1)>=Bst.bst.size()){
            Bst.bst.at(2*p+1)=val;
             return;
        }

        else {
            inserer(Bst, val ,2*p+1);
        }
    }

    else{
        if(Bst.bst.at(2*p+2)>=Bst.bst.size()){
            Bst.bst.at(2*p+2)=val;
            return ;
       }

       else {
           inserer(Bst, val ,2*p+2);
       }

    }
}


void trouver_successeur_parcours(BST& Bst,std::vector<int> visited , int p){
    if(p>=Bst.bst.size()){
        return ;
    }

    else{
    
        trouver_successeur_parcours(Bst,visited ,2*p+1);
        visited.push_back(Bst.bst.at(p));
        trouver_successeur_parcours(Bst,visited ,2*p+2);
    }

};

int trouver_sucesseur(BST& Bst, int val){

    std::vector<int> visited;
    trouver_successeur_parcours(Bst,visited,0);

    for(size_t i=0;i <visited.size()-1;i++){
        if (visited[i]==val){
            return visited[i+1];
        }
    }

    return -1;


};
    




#include <iostream>
#include <vector>
#include <algorithm>

struct BST {
    std::vector<int> bst;
};

// Trouver le successeur (le plus petit élément du sous-arbre droit)
int trouver_successeur(BST& Bst, int p) {
    int index = 2 * p + 2;  // Aller dans le sous-arbre droit
    while (2 * index + 1 < Bst.bst.size() && Bst.bst[index] != -1) {
        index = 2 * index + 1;  // Aller vers le plus petit élément
    }
    return Bst.bst[index];  
}

// Supprimer un élément du BST sans utiliser `-1`
void supprimer(BST& Bst, int val) {
    auto it = std::find(Bst.bst.begin(), Bst.bst.end(), val);
    if (it == Bst.bst.end()) {
        std::cout << "La valeur " << val << " n'existe pas dans l'arbre." << std::endl;
        return;
    }

    int p = std::distance(Bst.bst.begin(), it); // Trouver l'index de `val`

    // Cas 1 : Nœud sans enfant (Feuille)
    if ((2 * p + 1 >= Bst.bst.size() || Bst.bst[2 * p + 1] == -1) &&
        (2 * p + 2 >= Bst.bst.size() || Bst.bst[2 * p + 2] == -1)) {
        Bst.bst.erase(it);  // Supprimer l'élément du vecteur
        return;
    }

    // Cas 2 : Nœud avec un seul enfant
    if ((2 * p + 1 < Bst.bst.size() && Bst.bst[2 * p + 1] != -1) &&
        (2 * p + 2 >= Bst.bst.size() || Bst.bst[2 * p + 2] == -1)) {
        *it = Bst.bst[2 * p + 1];  // Remplacer par le fils gauche
        Bst.bst.erase(Bst.bst.begin() + 2 * p + 1);  // Supprimer le fils gauche
        return;
    }

    if ((2 * p + 2 < Bst.bst.size() && Bst.bst[2 * p + 2] != -1) &&
        (2 * p + 1 >= Bst.bst.size() || Bst.bst[2 * p + 1] == -1)) {
        *it = Bst.bst[2 * p + 2];  // Remplacer par le fils droit
        Bst.bst.erase(Bst.bst.begin() + 2 * p + 2);  // Supprimer le fils droit
        return;
    }

    // Cas 3 : Nœud avec deux enfants (Remplacement par le successeur)
    int successeur = trouver_successeur(Bst, p);
    *it = successeur;
    
    // Trouver l'index du successeur et le supprimer
    auto it_succ = std::find(Bst.bst.begin(), Bst.bst.end(), successeur);
    if (it_succ != Bst.bst.end()) {
        Bst.bst.erase(it_succ);  // Supprimer le successeur du vecteur
    }
}

// Affichage infixe (gauche - racine - droite)
void afficher_infixe(BST& Bst, int p) {
    if (p >= Bst.bst.size() || Bst.bst[p] == -1) return;

    afficher_infixe(Bst, 2 * p + 1);
    std::cout << Bst.bst[p] << " ";
    afficher_infixe(Bst, 2 * p + 2);
}

int main() {
    BST arbre;
    arbre.bst = {20, 10, 30, 5, 15, 25, 35, 3, 7, 12, 18};

    std::cout << "Avant suppression : ";
    afficher_infixe(arbre, 0);
    std::cout << std::endl;

    supprimer(arbre, 10);

    std::cout << "Après suppression de 10 : ";
    afficher_infixe(arbre, 0);
    std::cout << std::endl;

    return 0;
}
