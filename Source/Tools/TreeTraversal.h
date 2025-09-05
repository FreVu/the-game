#pragma once
#include "TreeNode.h"
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>

template<typename T>
class TreeTraversal
{
public:
    // Types de parcours
    enum class TraversalType
    {
        PREORDER,    // Préfixe (racine, gauche, droite)
        INORDER,     // Infixe (gauche, racine, droite)
        POSTORDER,   // Suffixe (gauche, droite, racine)
        LEVEL_ORDER  // Par niveau (largeur d'abord)
    };
    
    // Constructeur
    TreeTraversal(TreeNode<T>* root) : _root(root) {}
    
    // Parcours avec callback
    void traverse(TraversalType type, std::function<void(const T&)> callback) const;
    void traverse(TreeNode<T>* node, TraversalType type, std::function<void(const T&)> callback) const;
    
    // Parcours qui retourne un vecteur
    std::vector<T> getTraversal(TraversalType type) const;
    std::vector<T> getTraversal(TreeNode<T>* node, TraversalType type) const;
    
    // Parcours avec prédicat (filtre)
    std::vector<T> findNodes(std::function<bool(const T&)> predicate) const;
    std::vector<T> findNodes(TreeNode<T>* node, std::function<bool(const T&)> predicate) const;
    
    // Recherche d'un nœud spécifique
    TreeNode<T>* findNode(const T& data) const;
    TreeNode<T>* findNode(TreeNode<T>* node, const T& data) const;
    
    // Parcours des nœuds (pas seulement les données)
    void traverseNodes(TraversalType type, std::function<void(TreeNode<T>*)> callback) const;
    void traverseNodes(TreeNode<T>* node, TraversalType type, std::function<void(TreeNode<T>*)> callback) const;
    
    // Statistiques de l'arbre
    size_t getNodeCount() const;
    size_t getNodeCount(TreeNode<T>* node) const;
    size_t getLeafCount() const;
    size_t getLeafCount(TreeNode<T>* node) const;
    size_t getMaxDepth() const;
    size_t getMaxDepth(TreeNode<T>* node) const;
    
    // Parcours par niveau avec informations de profondeur
    void traverseByLevel(std::function<void(const T&, size_t level)> callback) const;
    void traverseByLevel(TreeNode<T>* node, std::function<void(const T&, size_t level)> callback) const;
    
private:
    TreeNode<T>* _root;
    
    // Implémentations des différents types de parcours
    void preorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const;
    void inorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const;
    void postorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const;
    void levelOrderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const;
    
    // Parcours des nœuds
    void preorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const;
    void inorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const;
    void postorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const;
    void levelOrderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const;
};

// Implémentation des méthodes publiques
template<typename T>
void TreeTraversal<T>::traverse(TraversalType type, std::function<void(const T&)> callback) const
{
    if (_root)
    {
        traverse(_root, type, callback);
    }
}

template<typename T>
void TreeTraversal<T>::traverse(TreeNode<T>* node, TraversalType type, std::function<void(const T&)> callback) const
{
    if (!node) return;
    
    switch (type)
    {
        case TraversalType::PREORDER:
            preorderTraversal(node, callback);
            break;
        case TraversalType::INORDER:
            inorderTraversal(node, callback);
            break;
        case TraversalType::POSTORDER:
            postorderTraversal(node, callback);
            break;
        case TraversalType::LEVEL_ORDER:
            levelOrderTraversal(node, callback);
            break;
    }
}

template<typename T>
std::vector<T> TreeTraversal<T>::getTraversal(TraversalType type) const
{
    std::vector<T> result;
    traverse(type, [&result](const T& data) {
        result.push_back(data);
    });
    return result;
}

template<typename T>
std::vector<T> TreeTraversal<T>::getTraversal(TreeNode<T>* node, TraversalType type) const
{
    std::vector<T> result;
    traverse(node, type, [&result](const T& data) {
        result.push_back(data);
    });
    return result;
}

template<typename T>
std::vector<T> TreeTraversal<T>::findNodes(std::function<bool(const T&)> predicate) const
{
    std::vector<T> result;
    traverse(TraversalType::PREORDER, [&result, predicate](const T& data) {
        if (predicate(data))
        {
            result.push_back(data);
        }
    });
    return result;
}

template<typename T>
std::vector<T> TreeTraversal<T>::findNodes(TreeNode<T>* node, std::function<bool(const T&)> predicate) const
{
    std::vector<T> result;
    traverse(node, TraversalType::PREORDER, [&result, predicate](const T& data) {
        if (predicate(data))
        {
            result.push_back(data);
        }
    });
    return result;
}

template<typename T>
TreeNode<T>* TreeTraversal<T>::findNode(const T& data) const
{
    if (_root)
    {
        return findNode(_root, data);
    }
    return nullptr;
}

template<typename T>
TreeNode<T>* TreeTraversal<T>::findNode(TreeNode<T>* node, const T& data) const
{
    if (!node) return nullptr;
    
    if (node->getData() == data)
    {
        return node;
    }
    
    for (const auto& child : node->getChildren())
    {
        TreeNode<T>* result = findNode(child.get(), data);
        if (result) return result;
    }
    
    return nullptr;
}

template<typename T>
void TreeTraversal<T>::traverseNodes(TraversalType type, std::function<void(TreeNode<T>*)> callback) const
{
    if (_root)
    {
        traverseNodes(_root, type, callback);
    }
}

template<typename T>
void TreeTraversal<T>::traverseNodes(TreeNode<T>* node, TraversalType type, std::function<void(TreeNode<T>*)> callback) const
{
    if (!node) return;
    
    switch (type)
    {
        case TraversalType::PREORDER:
            preorderNodeTraversal(node, callback);
            break;
        case TraversalType::INORDER:
            inorderNodeTraversal(node, callback);
            break;
        case TraversalType::POSTORDER:
            postorderNodeTraversal(node, callback);
            break;
        case TraversalType::LEVEL_ORDER:
            levelOrderNodeTraversal(node, callback);
            break;
    }
}

template<typename T>
size_t TreeTraversal<T>::getNodeCount() const
{
    return getNodeCount(_root);
}

template<typename T>
size_t TreeTraversal<T>::getNodeCount(TreeNode<T>* node) const
{
    if (!node) return 0;
    
    size_t count = 1; // Compter le nœud actuel
    for (const auto& child : node->getChildren())
    {
        count += getNodeCount(child.get());
    }
    return count;
}

template<typename T>
size_t TreeTraversal<T>::getLeafCount() const
{
    return getLeafCount(_root);
}

template<typename T>
size_t TreeTraversal<T>::getLeafCount(TreeNode<T>* node) const
{
    if (!node) return 0;
    
    if (node->isLeaf())
    {
        return 1;
    }
    
    size_t count = 0;
    for (const auto& child : node->getChildren())
    {
        count += getLeafCount(child.get());
    }
    return count;
}

template<typename T>
size_t TreeTraversal<T>::getMaxDepth() const
{
    return getMaxDepth(_root);
}

template<typename T>
size_t TreeTraversal<T>::getMaxDepth(TreeNode<T>* node) const
{
    if (!node) return 0;
    
    size_t maxChildDepth = 0;
    for (const auto& child : node->getChildren())
    {
        maxChildDepth = std::max(maxChildDepth, getMaxDepth(child.get()));
    }
    return maxChildDepth + 1;
}

template<typename T>
void TreeTraversal<T>::traverseByLevel(std::function<void(const T&, size_t level)> callback) const
{
    if (_root)
    {
        traverseByLevel(_root, callback);
    }
}

template<typename T>
void TreeTraversal<T>::traverseByLevel(TreeNode<T>* node, std::function<void(const T&, size_t level)> callback) const
{
    if (!node) return;
    
    std::queue<std::pair<TreeNode<T>*, size_t>> queue;
    queue.push({node, 0});
    
    while (!queue.empty())
    {
        auto [currentNode, level] = queue.front();
        queue.pop();
        
        callback(currentNode->getData(), level);
        
        for (const auto& child : currentNode->getChildren())
        {
            queue.push({child.get(), level + 1});
        }
    }
}

// Implémentation des méthodes privées
template<typename T>
void TreeTraversal<T>::preorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const
{
    if (!node) return;
    
    callback(node->getData());
    for (const auto& child : node->getChildren())
    {
        preorderTraversal(child.get(), callback);
    }
}

template<typename T>
void TreeTraversal<T>::inorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const
{
    if (!node) return;
    
    const auto& children = node->getChildren();
    size_t childCount = children.size();
    
    // Pour un arbre n-aire, on traite la moitié des enfants avant la racine
    for (size_t i = 0; i < childCount / 2; ++i)
    {
        inorderTraversal(children[i].get(), callback);
    }
    
    callback(node->getData());
    
    // Et la moitié après la racine
    for (size_t i = childCount / 2; i < childCount; ++i)
    {
        inorderTraversal(children[i].get(), callback);
    }
}

template<typename T>
void TreeTraversal<T>::postorderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const
{
    if (!node) return;
    
    for (const auto& child : node->getChildren())
    {
        postorderTraversal(child.get(), callback);
    }
    callback(node->getData());
}

template<typename T>
void TreeTraversal<T>::levelOrderTraversal(TreeNode<T>* node, std::function<void(const T&)> callback) const
{
    if (!node) return;
    
    std::queue<TreeNode<T>*> queue;
    queue.push(node);
    
    while (!queue.empty())
    {
        TreeNode<T>* currentNode = queue.front();
        queue.pop();
        
        callback(currentNode->getData());
        
        for (const auto& child : currentNode->getChildren())
        {
            queue.push(child.get());
        }
    }
}

template<typename T>
void TreeTraversal<T>::preorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const
{
    if (!node) return;
    
    callback(node);
    for (const auto& child : node->getChildren())
    {
        preorderNodeTraversal(child.get(), callback);
    }
}

template<typename T>
void TreeTraversal<T>::inorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const
{
    if (!node) return;
    
    const auto& children = node->getChildren();
    size_t childCount = children.size();
    
    for (size_t i = 0; i < childCount / 2; ++i)
    {
        inorderNodeTraversal(children[i].get(), callback);
    }
    
    callback(node);
    
    for (size_t i = childCount / 2; i < childCount; ++i)
    {
        inorderNodeTraversal(children[i].get(), callback);
    }
}

template<typename T>
void TreeTraversal<T>::postorderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const
{
    if (!node) return;
    
    for (const auto& child : node->getChildren())
    {
        postorderNodeTraversal(child.get(), callback);
    }
    callback(node);
}

template<typename T>
void TreeTraversal<T>::levelOrderNodeTraversal(TreeNode<T>* node, std::function<void(TreeNode<T>*)> callback) const
{
    if (!node) return;
    
    std::queue<TreeNode<T>*> queue;
    queue.push(node);
    
    while (!queue.empty())
    {
        TreeNode<T>* currentNode = queue.front();
        queue.pop();
        
        callback(currentNode);
        
        for (const auto& child : currentNode->getChildren())
        {
            queue.push(child.get());
        }
    }
}