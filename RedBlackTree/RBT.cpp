#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

#define RED 0
#define BLACK 1

struct treeNode
{
    int item;
    int color;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
    struct treeNode * parent;//points to the parent
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}

struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    node->parent = 0;
    node->color = RED;
    return node;
};

struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};

struct treeNode *insertItem(struct treeNode *node,struct treeNode *newNode){
    if(node == 0) //insert as the root as the tree is empty
    {
        //struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==newNode->item) return NULL; //already an item exists, so return NULL

    if(newNode->item<node->item && node->left==0) //insert as the left child
    {
        //struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        newNode->parent = node;
        return newNode;
    }

    if(newNode->item>node->item && node->right==0) //insert as the right child
    {
        //struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        newNode->parent = node;
        return newNode;
    }

    if(newNode->item<node->item)
        return insertItem(node->left, newNode); //insert at left sub-tree
    else
        return insertItem(node->right, newNode); //insert at right sub-tree
}



void leftRotate(struct treeNode *node,struct treeNode *pt)
{
    /*struct treeNode *y = x->right;//set y
    ->right = y->left; //turn y's left subtree into x's right subtree
    if(y->left != NULL)
    {x
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent = NULL)
    {
        node = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else x->parent->right = y;
    y->left = x;  //put x on y's left
    x->parent = y;*/
    struct treeNode *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;

}


void rightRotate(struct treeNode *node,struct treeNode *pt)
{
    /*struct treeNode *y = x->left;
    x->left = y->right;
    if(y->right != 0)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == 0)
    {
        node = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else x->parent->right = y;

    y->right = x;
    x->parent = y;*/
    struct treeNode *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}


void RBInsertFixup(struct treeNode *node,struct treeNode *son)
{
    //struct treeNode *son = makeTreeNode(item);
    struct treeNode *father = 0;
    struct treeNode *grandfather = 0;
    while(son != root && son->color == RED && son->parent->color == RED)
    {
        father = son->parent;
        grandfather = son->parent->parent;
        if(father == grandfather->left)
        {
            struct treeNode *uncle = grandfather->right;
            if(uncle != 0 && uncle->color == RED)
            {
                father->color = BLACK;
                uncle->color = BLACK;
                grandfather->color = RED;
                son = grandfather;
            }
            else
            {
                if(son == father->right)
                {
                    leftRotate(node,father);
                    son = father;
                    father = son->parent;
                }
                rightRotate(node,grandfather);
                int s = father->color;
                father->color = grandfather->color; ;
                grandfather->color = s;
                son=father;
            }
        }
        else
        {
            struct treeNode *uncle = grandfather->left;
            if(uncle != 0 && uncle->color == RED)
            {
                grandfather->color = RED;
                father->color = BLACK;
                uncle->color = BLACK;
                son = grandfather;
            }
            else
            {
                if(son == father->left)
                {
                    rightRotate(node,father);
                    son = father;
                    father = son->parent;
                }
                leftRotate(node,grandfather);
                int s = father->color;
                father->color = grandfather->color; ;
                grandfather->color = s;
                son=father;
            }
        }
    }
    //node->color = BLACK;
    root->color = BLACK;
}

void RBInsert(int item){
    struct treeNode *node = makeTreeNode(item);
    insertItem(root,node);
    RBInsertFixup(root,node);
}


struct treeNode *getMinItem(struct treeNode *node) //returns the minimum item in the tree
{
    //write your codes here
    if(node == NULL)
    {
        printf("Tree is empty\n");
        return NULL;
    }
    else
    {
        struct treeNode *temp;
        temp = node;
        while(temp->left != NULL)
            temp = temp->left;
        //int m = temp->item;
        return temp;
    }
}

struct treeNode *successor(struct treeNode *node,struct treeNode *x){
    if(x->right != NULL){
        return getMinItem(x->right);
    }
    else return NULL;
    struct treeNode *y = x->parent;
    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}



void  RBDeleteFixup(struct treeNode *node, struct treeNode *son){
    struct treeNode *father = 0;
    //struct treeNode *grandfather = 0;
    while(son != root && son->color == BLACK){
        father = son->parent;
        if(son == father->left){
            struct treeNode *sibling = father->right;
            if(sibling->color == RED){
                sibling->color = BLACK;
                father->color = RED;
                leftRotate(node,father);
                sibling = father->right;
            }

            if(sibling->left->color == BLACK && sibling->right->color == BLACK){
                sibling->color = RED;
                son = father;
            }
            else{
                if(sibling->right->color == BLACK){
                sibling->left->color = BLACK;
                sibling->color = RED;
                rightRotate(node,sibling);
                sibling = father->right;
                }
            sibling->color = father->color;
            father->color = BLACK;
            sibling->right->color = BLACK;
            leftRotate(node,father);
            son = node;
        }
        }
        else{
            struct treeNode *sibling = father->left;
            if(sibling->color == RED){
                sibling->color = BLACK;
                father->color = RED;
                rightRotate(node,father);
                sibling = father->left;
            }

            if(sibling->right->color == BLACK && sibling->left->color == BLACK){
                sibling->color = RED;
                son = father;
            }
            else{
                if(sibling->left->color == BLACK){
                sibling->right->color = BLACK;
                sibling->color = RED;
                leftRotate(node,sibling);
                sibling = father->left;
            }
            sibling->color = father->color;
            father->color = BLACK;
            sibling->left->color = BLACK;
            rightRotate(node,father);
            son = node;
            }
        }

    }
    son->color = BLACK;

}


void transplant(struct treeNode *u,struct treeNode *v){
    if(u->parent == NULL){
        root = v;
    }
    else if(u = u->parent->left){
        u->parent->left = v;
    }
    else u->parent->right = v;

    if(v!=0 && v->parent!=0){
        v->parent = u->parent;
    }

}
void RBDelete(struct treeNode *node, struct treeNode *z){
    struct treeNode *y = z;
    struct treeNode *x;
    int y_color = y->color;

    if(z->left == NULL){
        x = z->right;
        transplant(z,z->left);
    }
    else if(z->right == NULL){
        x = z->left;
        transplant(z,z->right);
    }
    else{
        y = getMinItem(z->right);
        y_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }
        else{
            transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }



    if(y_color == BLACK){
        RBDeleteFixup(root,x);
    }


}


int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0) return 0;
    int ls = getSize(node->left);
    int rs = getSize(node->right);
    int Size = ls + rs + 1;
    return Size;

}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    if(root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }
    else
    {
        struct treeNode *temp;
        temp = root;
        while(temp->right != NULL)
            temp = temp->right;
        int m = temp->item;
        return m;
    }
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d(%d)\n",node->item,node->color);
    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main()
{
    initializeTree();
    //RBInsert(11);
    //RBInsert(2);
    ////RBInsert(14);
    //RBInsert(15);
    //RBInsert(1);
    //RBInsert(7);
    //RBInsert(5);
    //RBInsert(8);
    //RBInsert(4);
    //RBInsert(19);
    //RBInsert(3);
    //RBInsert(6);

    //int h = calcNodeHeight(root);
    //printf("\n--------------------------------\n");
    //printInOrder(root, h);
    //printf("--------------------------------\n");
    while(1)
    {
        printf("1. Insert item. 2. Successor. 3. Search item. \n");
        printf("4. Delete Item. 5. Print InOrder. 6. Minimum value. \n");
        printf("7. Maximum value \n");
        //printf("10. Maximum value. 11. Size of a tree 12.Range search 13. Subtree Sum\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            RBInsert(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0){
                struct treeNode *a = successor(root,res);
                if(a!=NULL){
                    printf("%d\n",a->item);
                }
                else printf("No successor\n");
            }
            else printf("Not found.\n");
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) {
                RBDelete(root,res);
            }
            else printf("Not found.\n");

        }
        else if(ch==5)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==6){
            struct treeNode *s = getMinItem(root);
            printf("Minimum item is %d\n",s->item);

        }
        else if(ch==7){
            int s = getMaxItem();
            printf("Maximum item is %d\n",s);

        }

    }


    return 0;
}

