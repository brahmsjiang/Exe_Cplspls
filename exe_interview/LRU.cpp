#include <iostream>
#include <map>
#include <memory>

using namespace std;

class LRU {
public:
    struct Node {
        Node(int key = 0, int value = 0) : m_key(key), m_value(value) {}
        int m_key;
        int m_value;
        Node* prev;
        Node* next;
    };
public:
    LRU(int capacity) : m_capacity(capacity) {
        head = new Node;
        tail = new Node;
        tail->prev = head;//tail point to head
        head->next = tail;//head point to tail
    }
    int get(int key) {
        if (m_map.find(key) == m_map.end())
            return -1;
        Node* node = m_map[key];
        removeNode(node);
        addToHead(node);
        return node->m_value;
    }
    void put(int key, int value) {
        if (m_map.find(key) != m_map.end()) {
            Node* node = m_map[key];
            node->m_value = value;
            removeNode(node);
            addToHead(node);
        } else {
            if (m_map.size() >= m_capacity) {
                Node* tailPrev = tail->prev;
                removeNode(tailPrev);
                m_map.erase(tailPrev->m_key);
            }
            Node* newNode = new Node(key, value);
            //m_map.insert(std::make_pair(key, newNode));
            m_map[key] = newNode;
            addToHead(newNode);
        }
    }
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void addToHead(Node* node) {
        node->next = head->next;//before
        head->next->prev = node;
        node->prev = head;
        head->next = node;//after
    }
private:
    int m_capacity;
    std::map<int, Node*> m_map;
    Node* head;
    Node* tail;
};

int main(int argc, char* argv[])
{
	LRU cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "cache.get(2)" << cache.get(2) << endl;
    cache.put(3, 3);
    cout << "cache.get(1)" << cache.get(1) << endl;
    cache.put(4, 4);
    cout << "cache.get(2)" << cache.get(2) << endl;
    cout << "cache.get(3)" << cache.get(3) << endl;
    cout << "cache.get(4)" << cache.get(4) << endl;

}

