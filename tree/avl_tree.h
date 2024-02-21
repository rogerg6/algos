
#ifndef _AVL_TREE_H
#define _AVL_TREE_H

template<typename T>
struct AVLNode {
    T           val{};
    AVLNode<T> *left{};
    AVLNode<T> *right{};
    int         height = 0;
    AVLNode()          = default;
    AVLNode(T v)
        : val(v)
        , left(nullptr)
        , right(nullptr)
        , height(0) {}
};

/**
 * \brief: 平衡二叉搜索数. 链表实现
 *
 * 适用于高频查找、低频增删的场景。
 *
 * 应用:
 * 组织和存储大型数据，适用于高频查找、低频增删的场景。
 * 用于构建数据库中的索引系统。
 * 红黑树在许多应用中比 AVL
 * 树更受欢迎。这是因为红黑树的平衡条件相对宽松，在红黑树中插入与删除节点所需的旋转操作相对较少，其节点增删操作的平均效率更高
 */
template<typename T>
class AVLTree {
public:
    AVLTree()
        : _root(nullptr)
        , _size(0) {}

    ~AVLTree() {
        // while (_root) Remove(_root->val);
        destroy(_root);
        _root = nullptr;
        _size = 0;
    }

    void Insert(T val) { _root = doInsert(_root, val); }

    void Remove(T val) { _root = doRemove(_root, val); }

    AVLNode<T> *Find(T val) {
        AVLNode<T> *node = _root;
        while (node) {
            if (node->val == val)
                return node;
            else if (val < node->val)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    int Size() const { return _size; }

#ifdef UNIT_TEST
public:
#else
private:
#endif
    AVLNode<T> *doInsert(AVLNode<T> *node, T val) {
        if (!node) {
            // 找到插入点
            _size++;
            return new AVLNode<T>(val);
        }
        if (val < node->val)
            node->left = doInsert(node->left, val);
        else if (val > node->val)
            node->right = doInsert(node->right, val);
        else
            return node;   // val已经在tree中

        updateHeight(node);
        node = rotate(node);
        return node;
    }

    AVLNode<T> *doRemove(AVLNode<T> *node, T val) {
        // 未找到值为val的节点
        if (!node) return nullptr;

        if (val < node->val)
            node->left = doRemove(node->left, val);
        else if (val > node->val)
            node->right = doRemove(node->right, val);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                // 找到值为val的节点
                AVLNode<T> *child = (node->left != nullptr ? node->left : node->right);
                if (child == nullptr) {
                    // 度=0, 直接删除
                    delete node;
                    _size--;
                    return nullptr;
                } else {
                    // 度=1
                    delete node;
                    node = child;
                    _size--;
                }
            } else {
                //度=2,把中序遍历的下一个节点n的值父给node, 删除n
                AVLNode<T> *node_rtree = node->right;
                while (node_rtree->left) node_rtree = node_rtree->left;

                T tmp       = node_rtree->val;
                node->right = doRemove(node->right, tmp);   // node的右子树中删除val=tmp的节点
                node->val = tmp;
            }
        }

        updateHeight(node);
        node = rotate(node);
        return node;
    }

    AVLNode<T> *leftRotate(AVLNode<T> *node) {
        AVLNode<T> *child       = node->right;
        AVLNode<T> *grand_child = child->left;

        // 以child为原点,把node左转
        child->left = node;
        node->right = grand_child;
        updateHeight(node);
        updateHeight(child);
        return child;   //返回旋转后的根节点
    }

    AVLNode<T> *rightRotate(AVLNode<T> *node) {
        AVLNode<T> *child       = node->left;
        AVLNode<T> *grand_child = child->right;

        // 以child为原点,把node右转
        child->right = node;
        node->left   = grand_child;
        updateHeight(node);
        updateHeight(child);
        return child;
    }


    /**
     * rotate的关键在于: 平衡因子.
     * 平衡因子反映了当前node的left高还是right高,哪边高node就往哪边转
     *
     * node.bf  child.bf    rotate
     *   >1       >=0         right
     *   >1        <0         left, right
     *   <1       <=0         left
     *   <1        >0         right, left
     */
    AVLNode<T> *rotate(AVLNode<T> *node) {
        int bf = balanceFactor(node);

        if (bf > 1) {
            // 左偏树
            if (balanceFactor(node->left) >= 0)
                return rightRotate(node);
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (bf < -1) {
            // 右偏树
            if (balanceFactor(node->right) <= 0)
                return leftRotate(node);
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;   // 无需旋转
    }

    // 获取node的高度
    static int height(const AVLNode<T> *node) {
        return node == nullptr ? -1 : node->height;
    }
    // 更新 node的高度
    void updateHeight(AVLNode<T> *node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }
    // 获取node 的平衡因子
    static int balanceFactor(const AVLNode<T> *node) {
        return height(node->left) - height(node->right);
    }
    // 销毁树
    void destroy(AVLNode<T> *root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

    AVLNode<T> *_root;
    int         _size;
};


#endif