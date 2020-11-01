//
// Created by danil on 17.10.2020.
//

#include "../Exception.h"
#include <stack>

#define OUT

#ifndef TESTING_TEST_DICTIONARY_H
#define TESTING_TEST_DICTIONARY_H



template < typename K, typename V>
class Dictionary final
{
private:
    class Iterator;
    class Node
    {
        K key;
        V value;
        unsigned int height;
        Node* parent;
        Node* left;
        Node* right;
        Node(K k, V v) : key(k), value(v), height(1), parent(nullptr), left(nullptr), right(nullptr){}
        Node() : height(1), parent(nullptr), left(nullptr), right(nullptr){}

        friend Iterator;
        friend Dictionary;
    };

    void delete_node_recursively(Node* n);
    Node* insert_node_recursively(Node* node, const K& key, const V& value);
    Node* balance(Node* node);
    void fix_height(Node* node);
    unsigned int height(Node* node);
    int balance_factor(Node* node);
    Node* rotate_right(Node* node);
    Node* rotate_left(Node* node);
    Node* find_and_remove(Node* node, K k);
    Node* find_min_and_remove(Node* node, OUT Node* node_without_min);
    Node* find_key(Node* node, const K& key);


    int length;
    Node* root_node;

    class Iterator{ //NLR
    private:
        Dictionary<K,V>* iterated;
        Node* current;
    public:
        Iterator(Dictionary<K,V>* iterated);

        const K& key() const ;
        const V& get() const ;
        void set( const V& value);
        void next();
        void prev();
        bool hasNext() const ;
        bool hasPrev() const ;

    };


public:
    Dictionary();
    Dictionary(const Dictionary<K,V>& copiedDictionary);
    ~Dictionary();
    void put( const K& key, const V& value);
    void remove( const K& key);
    bool contains( const K& key);
    const V& operator []( const K& key) const ;
    V& operator []( const K& key);
    int size() const ;

    Iterator iterator();
    const Iterator iterator() const ;
};

template < typename K, typename V>
void Dictionary<K, V>::delete_node_recursively(Node* node)
{
    if(node == nullptr)
        return;
    delete_node_recursively(node->left);
    delete_node_recursively(node->right);

    delete node;
}

template<typename K, typename V>
unsigned int Dictionary<K, V>::height(Dictionary::Node* node) {
    return node != nullptr ? node->height : 0;
}

template<typename K, typename V>
int Dictionary<K, V>::balance_factor(Dictionary::Node* node) {
    return height(node->right) - height(node->left);
}

template<typename K, typename V>
void Dictionary<K, V>::fix_height(Node* node) {
    unsigned int left_height = height(node->left);
    unsigned int right_height = height(node->right);
    node->height = (left_height > right_height ? left_height : right_height) + 1;
}
template<typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotate_right(Dictionary::Node* node) {
    Node* old_left = node->left;
    node->left = old_left->right;
    old_left->right = node;

    old_left->parent = node->parent;
    node->parent = old_left;
    if(node->left)
        node->left->parent = node;

    fix_height(node);
    fix_height(old_left);
    return old_left;
}

template<typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotate_left(Dictionary::Node* node) {
    Node* old_right = node->right;
    node->right = old_right->left;
    old_right->left = node;

    old_right->parent = node->parent;
    node->parent = old_right;
    if(node->right)
        node->right->parent = node;

    fix_height(node);
    fix_height(old_right);
    return old_right;
}

template < typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::balance(Node* node)
{
    fix_height(node);
    if(balance_factor(node) == 2)
    {
        if(balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if(balance_factor(node) == -2)
    {
        if(balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node; ////no need to balance
}

template < typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::insert_node_recursively(Node* node, const K& key, const V& value) ////node is root node for tree
{
    if(node == nullptr)
    {
        ++length;
        return new Node(key, value);
    }

    if(key == node->key)
        node->value = value;
    else if(key < node->key)
    {
        node->left = insert_node_recursively(node->left, key, value);
        node->left->parent = node;
    }
    else
    {
        node->right = insert_node_recursively(node->left, key, value);
        node->right->parent = node;
    }

    return balance(node);
}

template<typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::find_min_and_remove(Dictionary::Node *node, OUT Dictionary::Node *node_without_min) {
    if(node->left == nullptr){
        node_without_min = node->right;
        return node;
    }

    node->left = find_min_and_remove(node->left, node_without_min);
    node->left->parent = node;
    return balance(node);
}

template<typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::find_and_remove(Dictionary::Node *node, K key) {
    if(node == nullptr)
        return nullptr;

    if(key < node->key)
    {
        node->left = find_and_remove(node->left, key);
        if(node->left)
            node->left->parent = node;
    }
    else if(key > node->key)
    {
        node->right = find_and_remove(node->right, key);
        if(node->right)
            node->right->parent = node;
    }
    else
    {
        Node* l = node->left;
        Node* r = node->right;
        delete node;
        if(r == nullptr)
            return l;

        Node* r_without_min;
        Node* min = find_min_and_remove(r, r_without_min);
        min->right = r_without_min;
        if(min->right)
            min->right->parent = min;
        min->left = l;
        if(min->left)
            min->left->parent = min;

        --length;
        return balance(min);
    }

    return balance(node); ////balance tree going upon recursion
}

template<typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::find_key(Node *node, const K& key) {

    if(node == nullptr)
        return nullptr;

    if(key < node->key)
    {
        return find_key(node->left, key);
    }
    else if(key > node->key)
    {
        return find_key(node->right, key);
    }
    else
        return node;
}




template < typename K, typename V>
Dictionary<K, V>::Dictionary() : length(0), root_node(new Node()){}

template < typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary<K,V>& copiedDictionary)
{
    if(copiedDictionary.root_node == nullptr) {
        Dictionary<K,V>();
        return;
    }

    length = copiedDictionary.length;
    Node* current = root_node;

    std::stack<Node> nodes;
    nodes.push(copiedDictionary.root_node);
    while (!nodes.empty()){
        Node* copiedNode = nodes.pop();
        current = new Node(copiedNode->key, copiedNode->value);

        if(copiedNode->left != nullptr){
            current = current->left;
            nodes.push(copiedNode->left);
        }

        if(copiedNode->right != nullptr){
            current = current->rigth;
            nodes.push(copiedNode->right);
        }
    }

}

template < typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
    delete_node_recursively(root_node);
}

template < typename K, typename V>
void Dictionary<K, V>::put( const K& key, const V& value)
{
    if(length == 0){
        root_node->key = key;
        root_node->value = value;
        ++length;
    }
    else
    {
        root_node = insert_node_recursively(root_node, key, value);
    }
}

template<typename K, typename V>
void Dictionary<K, V>::remove(const K& key) {
    root_node = find_and_remove(root_node, key);
}

template<typename K, typename V>
bool Dictionary<K, V>::contains(const K& key) {
    if(find_key(root_node, key) == nullptr)
        return false;
    return true;
}

template<typename K, typename V>
const V &Dictionary<K, V>::operator[](const K& key) const {
    Node* found_node = find_key(root_node, key);
    if(found_node == nullptr)
        return nullptr;
    return found_node->value;
}

template<typename K, typename V>
V &Dictionary<K, V>::operator[](const K &key) {
    Node* found_node = find_key(root_node, key);

    if(found_node == nullptr){
        found_node = insert_node_recursively(root_node, key, V());
    }

    return found_node->value;
}

template<typename K, typename V>
int Dictionary<K, V>::size() const {
    return length;
}




template < typename K, typename V>
Dictionary<K, V>::Iterator::Iterator(Dictionary<K,V>* iterated) : iterated(iterated), current(iterated->root_node){}

template<typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() {
    return Dictionary::Iterator(this);
}

template<typename K, typename V>
const typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const {
    return Dictionary::Iterator(this);
}

template<typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const {
    return current->key;
}

template<typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const {
    return current->value;
}

template<typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& value) {
    current->value = value;
}

template<typename K, typename V>
void Dictionary<K, V>::Iterator::next() {
    if(hasNext())
    {

    }
    else
    {
        throw Exception("iterator points on last element");
    }
}

template<typename K, typename V>
void Dictionary<K, V>::Iterator::prev() {
    if(hasPrev())
    {

    }
    else
    {
        throw Exception("iterator points on first element");
    }
}

template<typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const {
    return true;
}

template<typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const {
    return true;
}


#endif //TESTING_TEST_DICTIONARY_H
