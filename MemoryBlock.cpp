#include <iostream>
#include <memory>  // Pour std::unique_ptr

// Définition de la structure MemoryBlock
struct MemoryBlock {
    int size;

    // Constructeur
    MemoryBlock(int s) : size(s) {
        std::cout << "Bloc de mémoire alloué de " << size << " unités.\n";
    }

    // Destructeur
    ~MemoryBlock() {
        std::cout << "Libération de la mémoire.\n";
    }
};

// Fonction pour fusionner deux blocs
std::unique_ptr<MemoryBlock> mergeBlocks(std::unique_ptr<MemoryBlock> b1, std::unique_ptr<MemoryBlock> b2) {
    int newSize = b1->size + b2->size;
    std::cout << "Fusion des deux blocs : " << newSize << " unités.\n";

    // Créer un nouveau bloc fusionné
    return std::make_unique<MemoryBlock>(newSize);
}

int main() {
    // Allocation des blocs de mémoire avec unique_ptr
    std::unique_ptr<MemoryBlock> block1 = std::make_unique<MemoryBlock>(100);
    std::unique_ptr<MemoryBlock> block2 = std::make_unique<MemoryBlock>(200);

    // Fusion des deux blocs
    std::unique_ptr<MemoryBlock> mergedBlock = mergeBlocks(std::move(block1), std::move(block2));

    // À la fin du programme, tous les `unique_ptr` sont automatiquement détruits et la mémoire est libérée.
    return 0;
}
