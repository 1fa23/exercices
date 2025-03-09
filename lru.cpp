#include <iostream>
#include <list>
#include <unordered_map>
#include <memory>

using namespace std;

class Node {
public:
    int key, value;
    Node(int k, int v) : key(k), value(v) {}
};

class LRUCache {
private:
    int capacity;
    list<shared_ptr<Node>> lru; // Liste pour l'ordre d'utilisation
    unordered_map<int, weak_ptr<Node>> cache; // Table de hachage clé -> weak_ptr vers Node

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end() || it->second.expired()) {
            return -1; // Clé non trouvée
        }
        
        shared_ptr<Node> node = it->second.lock();
        lru.remove(node);
        lru.push_front(node);
        cache[key] = node;
        return node->value;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end() && !it->second.expired()) {
            shared_ptr<Node> node = it->second.lock();
            node->value = value;
            lru.remove(node);
            lru.push_front(node);
            return;
        }
        
        if (lru.size() >= capacity) {
            shared_ptr<Node> lastNode = lru.back();
            cache.erase(lastNode->key);
            lru.pop_back();
        }
        
        shared_ptr<Node> newNode = make_shared<Node>(key, value);
        lru.push_front(newNode);
        cache[key] = newNode;
    }

    void display() {
        for (const auto& node : lru) {
            cout << "(" << node->key << ", " << node->value << ") ";
        }
        cout << endl;
    }
};

int main() {
    LRUCache cache(4); // Capacité de 4
    
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(1, 10);
    cache.put(4, 40);
    cache.display(); // Affiche : (4, 40) (1, 10) (3, 30) (2, 20)
    
    cout << "Accès à la clé 5 -> Eviction de la clé 2" << endl;
    cache.put(5, 50); // Insère (5, 50) et supprime (2, 20)
    cache.display(); // Affiche : (5, 50) (4, 40) (1, 10) (3, 30)
    
    return 0;
}
