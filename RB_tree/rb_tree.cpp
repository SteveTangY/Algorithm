/*
    红黑树实例
    5 6 1 2 4 7 8 9
*/
#include <unistd.h>
#include <cstdio>
//#include <vector>

class RB_Tree
{
private:
    struct data_node {
        int data = 0;
        char color = 'r';   //创建新节点时将节点颜色默认设为红色
        data_node *parent = nullptr;
        data_node *left_child = nullptr;
        data_node *right_child = nullptr;
    } *nil;
    unsigned int tree_size;

    void right_rotate(struct data_node *node);
    void left_rotate(struct data_node *node);
    void rb_insert_fixup(struct data_node *node);
    void rb_transplant(struct data_node *u, struct data_node *v);
    auto rb_search(const int& data, struct data_node *node)->struct data_node*;
    auto find_tree_minimux_node(struct data_node *node)->struct data_node*;
    void rb_delete_fixup(struct data_node *x_node);
    void rb_insert(const int& new_data);
    void rb_delete(struct data_node *z_node);
    void rb_display(struct data_node *node);

public:
    struct data_node *root;

    RB_Tree() : root(nullptr), nil(new data_node), tree_size(0) {
        nil->color = 'b';
    }
    ~RB_Tree() {}

    void display() {rb_display(root);}
    void insert_(const int& new_data) {rb_insert(new_data);}
    void delete_(const int& data) {rb_delete(rb_search(data, root));}
    unsigned int  size() {return tree_size;}
};

void RB_Tree::rb_insert(const int& new_data) 
{
    // printf("begin rb_insert");
    if (root == nullptr) {
        root = new data_node;
        root->color = 'b';
        root->data = new_data;
        root->parent = nil;
        root->left_child = nil;
        root->right_child = nil;
    } else {
        struct data_node *current_ptr = root;
        while (current_ptr != nil) {
            if (new_data < current_ptr->data) {
                if (current_ptr->left_child == nil) {
                    current_ptr->left_child = new data_node;  // 注意要将新节点和current_node完全链接起来(所有指针)，否则会出现segmennt fault的错误
                    current_ptr->left_child->data = new_data;
                    current_ptr->left_child->left_child = nil;
                    current_ptr->left_child->right_child = nil;
                    current_ptr->left_child->parent = current_ptr;
                    current_ptr = current_ptr->left_child;
                    break;
                } else
                    current_ptr = current_ptr->left_child;
            } else {
                if (current_ptr->right_child == nil) {
                    current_ptr->right_child = new data_node;
                    current_ptr->right_child->data = new_data;
                    current_ptr->right_child->left_child = nil;
                    current_ptr->right_child->right_child = nil;
                    current_ptr->right_child->parent = current_ptr;
                    current_ptr = current_ptr->right_child;
                    break;
                } else
                    current_ptr = current_ptr->right_child; 
            }
        }
        rb_insert_fixup(current_ptr);
    }
    tree_size++;
    // printf("end of rb_insert\n");
}

void RB_Tree::right_rotate(struct data_node *node)
{
    // printf("begin right_rotate ");
    struct data_node *x_node = node->left_child;  // 右旋时，将node的左孩子作为x_node

    node->left_child = x_node->right_child;  // 将x_node的右孩子设为node的左孩子
    if (node->left_child != nil)
        node->left_child->parent = node;
    
    x_node->parent = node->parent;  // 将x_node与node的父节点链接
    if (node->parent == nil)
        root = x_node;
    else if (node->parent->left_child == node)
        node->parent->left_child = x_node;
    else if (node->parent->right_child == node)
        node->parent->right_child = x_node;

    x_node->right_child = node;  // 将x_node的右孩子设为node
    node->parent = x_node;
    // printf("end right_rotate");
}

void RB_Tree::left_rotate(struct data_node *node)
{
    // printf("\n\nbegin left_rotate,root=%d, node = %d, node->parent=%d\n\n", root->data, node->data, node->parent->data);
    struct data_node *x_node = node->right_child;  // 左旋时，将node的右孩子作为x_node

    node->right_child = x_node->left_child;  // 将x_node的左孩子设为node的右孩子
    if (node->right_child != nil)
        node->right_child->parent = node;
    
    x_node->parent = node->parent;  // 将x_node与node的父节点链接
    if (node->parent == nil)
        root = x_node;
    else if (node->parent->left_child == node)
        node->parent->left_child = x_node;
    else if (node->parent->right_child == node)
        node->parent->right_child = x_node;

    x_node->left_child = node;  // 将x_node的左孩子设为node
    node->parent = x_node;
    // printf("\n\nend of left_rotate, x_node=%d,x_node->parent=%d\n\n", x_node->data, x_node->parent->data);
}

void RB_Tree::rb_insert_fixup(struct data_node *z_node)
{
    // printf("begin rb_insert_fixup ");
    //struct data_node *z_node = node;
    struct data_node *z_uncle_node = nullptr;
    struct data_node *z_parent_node = z_node->parent;

    while (z_parent_node->color == 'r') {
        z_parent_node = z_node->parent;
        if (z_parent_node->parent->left_child == z_parent_node) {  // 当插入节点的父节点是在祖父节点的左边时
            z_uncle_node = z_parent_node->parent->right_child;
            if (z_uncle_node->color == 'r') {  //  情况1 插入节点的叔节点颜色为红色
                z_parent_node->color = 'b';
                z_uncle_node->color = 'b';
                z_parent_node->parent->color = 'r';
                z_node = z_parent_node->parent;
            } else if (z_uncle_node->color == 'b') {
                if (z_parent_node->right_child == z_node) {  // 情况2 插入节点的叔节点为黑色且插入节点在父节点的右边
                    z_node = z_parent_node;
                    left_rotate(z_node);  // 左旋转情况2转为情况3，且注意先将插入节点z的父节点视为z节点再旋转
                    z_parent_node = z_node->parent;
                }
                // 情况3 插入节点的叔节点为黑色且插入节点在父节点的左边，但注意z.p与z.p.p所指的node自情况2后就再也没变过
                z_parent_node->color = 'b';  // 右旋转并重新染色使其符合红黑树的性质
                z_parent_node->parent->color = 'r';
                right_rotate(z_parent_node->parent);  
            }
        } else if (z_parent_node->parent->right_child == z_parent_node) {  // 当插入节点的父节点是在祖父节点的右边时
            z_uncle_node = z_parent_node->parent->left_child;
            if (z_uncle_node->color == 'r') {  //  情况1 插入节点的叔节点颜色为红色
                z_parent_node->color = 'b';
                z_uncle_node->color = 'b';
                z_parent_node->parent->color = 'r';
                z_node = z_parent_node->parent;
            } else if (z_uncle_node->color == 'b') {
                if (z_parent_node->left_child == z_node) {  // 情况2 插入节点的叔节点为黑色且插入节点在父节点的左边
                    z_node = z_parent_node;
                    right_rotate(z_node);  // 右旋转情况2转为情况3，且注意先将插入节点z的父节点视为z节点再旋转
                    z_parent_node = z_node->parent;
                }
                // 情况3 插入节点的叔节点为黑色且插入节点在父节点的右边，但注意z.p与z.p.p所指的node自情况2后就再也没变过
                z_parent_node->color = 'b';  // 左旋转并重新染色使其符合红黑树的性质
                z_parent_node->parent->color = 'r';
                left_rotate(z_parent_node->parent);  
            }
        } else 
            break;
    }
    root->color = 'b';
    // printf("end of rb_insert_fixup\n");
}

void RB_Tree::rb_transplant(struct data_node *u, struct data_node *v)
{
    if (u->parent == nil)
        root = v;
    else if (u->parent->left_child == u)
        u->parent->left_child = v;
    else if (u->parent->right_child == u)
        u->parent->right_child = v;
    v->parent = u->parent;
    // printf("\nu data:%d,v data:%d\n", u->data, v->parent->data);
}

auto RB_Tree::rb_search(const int& data, struct data_node *node)->struct data_node*
{
    // printf("\nstart rb_search, current node:%d\n", node->data);
    if (node == nil || node == nullptr || node->data == data)
        return node;
    else if (data < node->data)
        return rb_search(data, node->left_child);
    else if (data > node->data)
        return rb_search(data, node->right_child);
}

auto RB_Tree::find_tree_minimux_node(struct data_node *node)->struct data_node*
{
    struct data_node *minimux_node = node;
    while (minimux_node->left_child != nil)
        minimux_node = minimux_node->left_child;
    return minimux_node;
}

void RB_Tree::rb_delete(struct data_node *z_node)
{
    if (z_node == nil || z_node == nullptr) {
        printf("\ncan't delete such data, no found in tree.\n");
        return;
    } 
    // printf("\nstart rb_delete\n");
    struct data_node *y_node = z_node ;
    struct data_node *x_node = nullptr;
    char y_node_original_color = y_node->color;

    if (z_node->left_child == nil) {
        x_node = z_node->right_child;
        rb_transplant(z_node, z_node->right_child);
    } else if (z_node->right_child == nil) {
        x_node = z_node->left_child;
        rb_transplant(z_node, z_node->left_child);
    } else {
        y_node = find_tree_minimux_node(z_node->right_child);
        printf("\nminimux y_node data:%d", y_node->data);
        y_node_original_color = y_node->color;
        x_node = y_node->right_child;
        if (y_node->parent == z_node) {
            x_node->parent = y_node;  // 没搞懂有什么用
        } else {
            rb_transplant(y_node, y_node->right_child);
            y_node->right_child = z_node->right_child;
            y_node->right_child->parent = y_node;
        }
        rb_transplant(z_node, y_node);
        y_node->left_child = z_node->left_child;
        y_node->left_child->parent = y_node;
    }
    y_node->color = z_node->color;
    if (y_node_original_color == 'b')  // 之前没加这句导致bug
        rb_delete_fixup(x_node);
    delete z_node;
    tree_size--; 
}

void RB_Tree::rb_delete_fixup(struct data_node *x_node)
{
    // printf("\nstart rb_delete_fixup\n");
    struct data_node *w_node = nullptr;

    while (x_node != root && x_node->color == 'b') {
        if (x_node->parent->left_child == x_node) {  // 当x_node在父节点左边时
            w_node = x_node->parent->right_child;  // 令w_node为x_node的兄弟节点
            if (w_node->color == 'r') {  // case 1
                w_node->color = 'b';
                x_node->parent->color = 'r';
                left_rotate(x_node->parent);
                w_node = x_node->parent->right_child;
            }
            if (w_node->left_child->color == 'b' && w_node->right_child->color == 'b') {  // case 2
                w_node->color = 'r';
                x_node = x_node->parent;
            } else {
                if (w_node->left_child->color == 'r' && w_node->right_child->color == 'b') {  // case 3
                    w_node->color = 'r';
                    w_node->left_child->color = 'b';
                    right_rotate(w_node);
                    w_node = x_node->parent->right_child;
                }
                w_node->color = x_node->parent->color;  // case 4
                x_node->parent->color = 'b';
                w_node->right_child->color = 'b';
                left_rotate(x_node->parent);
                x_node = root;
            }
        } else if (x_node->parent->right_child == x_node) {  // 当x_node在父节点得右边时
            w_node = x_node->parent->left_child;  // w_node为x_node的兄弟节点
            if (w_node->color == 'r') {  // case 1
                x_node->parent->color = 'r';
                w_node->color = 'b';
                right_rotate(x_node->parent);
                w_node = x_node->parent->left_child;
            }
            if (w_node->left_child->color == 'b' && w_node->right_child->color == 'b') {  // case 2
                w_node->color = 'r';
                x_node = x_node->parent;
            } else {
                if (w_node->right_child->color == 'r' && w_node->left_child->color == 'b') {  // case 3
                    w_node->color = 'r';
                    w_node->right_child->color = 'b';
                    left_rotate(w_node);
                    w_node = x_node->parent->left_child;
                }
                w_node->color = x_node->parent->color;  // case 4
                x_node->parent->color = 'b';
                w_node->left_child->color = 'b';
                right_rotate(x_node->parent);
                x_node = root;
            }
        }
    }
    x_node->color = 'b';
}

void RB_Tree::rb_display(struct data_node *node)
{
    // 中序遍历输出树
    if (node == nullptr || node == nil) {
        printf("\ntree is empty\n");
        return;
    }
    if (node->left_child != nil) {
        printf("go left\n");
        rb_display(node->left_child);
    }
    printf("%d,%c  ", node->data, node->color);
    usleep(1000);
    if (node->right_child != nil) {
        printf("go rignt\n");
        rb_display(node->right_child);
    }
}

int main()
{
    int length = 0;
    int buffer = 0;
    RB_Tree my_rb_tree;

    scanf("%d", &length);
    for (int i=0; i < length; ++i) {
        scanf("%d", &buffer);
        my_rb_tree.insert_(buffer);
    }

   my_rb_tree.display();
//    printf("root:%d, root->left=%d, root->right=%d", my_rb_tree.root->data, my_rb_tree.root->left_child->data, my_rb_tree.root->right_child->data);

    while (1) {
        printf("\ninter a data to delete:");
        scanf("%d", &buffer);
        my_rb_tree.delete_(buffer);

        my_rb_tree.display();
        // printf("root:%d, root->left=%d, root->right=%d\n", my_rb_tree.root->data, my_rb_tree.root->left_child->data, my_rb_tree.root->right_child->data);
    }
    return 0;
}

