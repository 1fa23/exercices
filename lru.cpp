#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>

using namespace std;

class Node {
public:
    int key, value;
    Node(int k, int v) : key(k), value(v) {}
};

class LRUCache {
public:
    int capacity;
    list<shared_ptr<Node>> lru;
    unordered_map<int, weak_ptr<Node>> cache;

    LRUCache(int cap) : capacity(cap) {}

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            shared_ptr<Node> node = it->second.lock();
            if (node) {
                node->value = value;
                lru.remove(node);
                lru.push_front(node);
                return;
            }
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

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end() || it->second.expired()) {
            return -1;
        }

        shared_ptr<Node> node = it->second.lock();
        if (!node) {
            return -1;
        }

        lru.remove(node);
        lru.push_front(node);
        return node->value;
    }

    void display() {
        for (const auto& pair : lru) {
            cout << "(" << pair->key << ", " << pair->value << ") ";
        }
        cout << endl;
    }
};

int main() {
    LRUCache cache(4);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(1, 10);
    cache.put(4, 40);
    cache.display();  // Affiche : (4, 40) (1, 10) (3, 30) (2, 20)

    cout << "Accès à la clé 5 -> Eviction de la clé 2" << std::endl;
    cache.put(5, 50);
    cache.display();  // Affiche : (5, 50) (4, 40) (1, 10) (3, 30)

    return 0;
}
