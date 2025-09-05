#pragma once
#include <vector>
#include <memory>
#include <functional>

template<typename T>
class TreeNode
{
public:
    TreeNode(const T& data) : _data(data), _parent(nullptr) {}
    
    // Getters
    const T& getData() const { return _data; }
    T& getData() { return _data; }
    
    TreeNode<T>* getParent() const { return _parent; }
    const std::vector<std::unique_ptr<TreeNode<T>>>& getChildren() const { return _children; }
    
    // Tree operations
    TreeNode<T>* addChild(const T& data);
    TreeNode<T>* addChild(std::unique_ptr<TreeNode<T>> child);
    bool removeChild(TreeNode<T>* child);
    bool isLeaf() const { return _children.empty(); }
    bool isRoot() const { return _parent == nullptr; }
    size_t getChildCount() const { return _children.size(); }
    TreeNode<T>* getChild(size_t index) const;
    
    // Tree traversal helpers
    size_t getDepth() const;
    size_t getHeight() const;
    bool hasChild(const T& data) const;
    TreeNode<T>* findChild(const T& data) const;
    
private:
    T _data;
    TreeNode<T>* _parent;
    std::vector<std::unique_ptr<TreeNode<T>>> _children;
    
    void setParent(TreeNode<T>* parent) { _parent = parent; }
};

// Template implementation
template<typename T>
TreeNode<T>* TreeNode<T>::addChild(const T& data)
{
    auto child = std::make_unique<TreeNode<T>>(data);
    child->setParent(this);
    TreeNode<T>* childPtr = child.get();
    _children.push_back(std::move(child));
    return childPtr;
}

template<typename T>
TreeNode<T>* TreeNode<T>::addChild(std::unique_ptr<TreeNode<T>> child)
{
    if (child)
    {
        child->setParent(this);
        TreeNode<T>* childPtr = child.get();
        _children.push_back(std::move(child));
        return childPtr;
    }
    return nullptr;
}

template<typename T>
bool TreeNode<T>::removeChild(TreeNode<T>* child)
{
    auto it = std::find_if(_children.begin(), _children.end(),
        [child](const std::unique_ptr<TreeNode<T>>& node) {
            return node.get() == child;
        });
    
    if (it != _children.end())
    {
        _children.erase(it);
        return true;
    }
    return false;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getChild(size_t index) const
{
    if (index < _children.size())
    {
        return _children[index].get();
    }
    return nullptr;
}

template<typename T>
size_t TreeNode<T>::getDepth() const
{
    size_t depth = 0;
    TreeNode<T>* current = _parent;
    while (current != nullptr)
    {
        depth++;
        current = current->_parent;
    }
    return depth;
}

template<typename T>
size_t TreeNode<T>::getHeight() const
{
    if (isLeaf())
    {
        return 0;
    }
    
    size_t maxChildHeight = 0;
    for (const auto& child : _children)
    {
        maxChildHeight = std::max(maxChildHeight, child->getHeight());
    }
    return maxChildHeight + 1;
}

template<typename T>
bool TreeNode<T>::hasChild(const T& data) const
{
    return findChild(data) != nullptr;
}

template<typename T>
TreeNode<T>* TreeNode<T>::findChild(const T& data) const
{
    for (const auto& child : _children)
    {
        if (child->getData() == data)
        {
            return child.get();
        }
    }
    return nullptr;
}
