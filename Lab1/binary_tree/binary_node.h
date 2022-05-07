#pragma once
#include <memory>
#include <iostream>

namespace tree{
    template<typename T>
    class TreeNode{
    public:
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        T value;

        explicit TreeNode(const T& value, std::shared_ptr<TreeNode> left = nullptr,
                          std::shared_ptr<TreeNode> right = nullptr);
    };
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const std::shared_ptr<TreeNode<T>>& node);
}
namespace tree{
    template<typename T>
    TreeNode<T>::TreeNode(const T& value, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right):
            left(left), right(right), value(value) {

    }
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const std::shared_ptr<TreeNode<T>>& node){
        if(node != nullptr){
            out << node->value;
            if(node->left) out << "\n->left: " << node->left;
            if(node->right) out <<"\n->right: " << node->right;
        }
        return out;
    }
}