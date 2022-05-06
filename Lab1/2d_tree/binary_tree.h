#pragma once
#include <memory>
#include "binary_node.h"

namespace tree{
    template<typename ValueType>
    class BinaryTree{
    private:
        using Node = TreeNode<ValueType>;
        using NodePtr = std::shared_ptr<Node>;
        NodePtr root;
    public:
        BinaryTree();
        void add(ValueType value);
        template<typename T>
        friend std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree);
    };

    template<typename NodeType>
    BinaryTree<NodeType>::BinaryTree():root(nullptr) {}

    template<typename ValueType>
    void BinaryTree<ValueType>::add(ValueType value) {
        NodePtr node = std::make_shared<Node>(value);
        NodePtr current = root;
        while (current != nullptr){
            if(value >= current->value){
                if(current->right){
                    current = current->right;
                    continue;
                }
                current->right = node;
                break;
            }
            if(!current->left){
                current->left = node;
                break;
            }
            current = current->left;
        }
        if(!root){
            root = node;
        }
    }
    template<typename T>
    std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &tree) {
        out <<tree.root;
        return out;
    }

}
