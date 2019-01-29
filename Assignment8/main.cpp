#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node *tree_pointer;
typedef struct node
{
    int value;
    tree_pointer left_child, right_child;
};

int num_of_node = 0; //global variable for record the number of node, same as the node in int main()
int tree_level = 1; //record the level of tree

//insert into a binary tree(ppt5.2 , p.30)
//value is the cin value
//modified_search in the slide and book are missing = =
void insert_node(tree_pointer *root_pointer, int value){
    int level = 1;
    tree_pointer temp = (tree_pointer)malloc(sizeof(node));
    tree_pointer current_pointer = NULL;
    temp->value = value;
    temp->left_child = NULL;
    temp->right_child = NULL;

    if(*root_pointer == NULL) //empty tree in original
        *root_pointer = temp;
    else{
        for(current_pointer = *root_pointer ; ; ){ //start the search
            level++;
            if(value > current_pointer->value){
                if(current_pointer->right_child==NULL)
                    break;
                current_pointer = current_pointer->right_child;
            }
            else{
                if(current_pointer->left_child==NULL)
                    break;
                current_pointer = current_pointer->left_child;
            }
        }
        if(value > current_pointer->value)
            current_pointer->right_child = temp;
        else
            current_pointer->left_child = temp;
    }
    if(level>tree_level){
        tree_level = level;
    }
}

//inorder (left-->mid-->right)
//come form ppt5.1
void inorder(tree_pointer ptr)
{
    if(ptr)
    {
        inorder(ptr->left_child);
        cout << ptr->value;
        num_of_node--;
        if(num_of_node>0)
        {
            cout << " ";
        }
        inorder(ptr->right_child);
    }
}

//preorder (mid-->left-->right)
//come form ppt5.1
void preorder(tree_pointer ptr)
{
    if(ptr)
    {
        cout <<ptr->value;
        num_of_node--;
        if(num_of_node>0)
        {
            cout << " ";
        }
        preorder(ptr->left_child);
        preorder(ptr->right_child);
    }
}

//postorder (left-->right-->mid)
//come form ppt5.1
void postorder(tree_pointer ptr)
{
    if(ptr)
    {
        postorder(ptr->left_child);
        postorder(ptr->right_child);
        cout << ptr->value;
        num_of_node--;
        if(num_of_node>0)
        {
            cout << " ";
        }
    }
}

tree_pointer queue[100];
void levelorder(tree_pointer ptr, int *num_of_leaf){
    int queue_front = 0;
    int queue_rear = 0;
    queue[queue_rear++] = ptr;
    for(;;){
        ptr = queue[queue_front++];
        if(ptr){
            cout<<ptr->value;
            num_of_node--;
            if(num_of_node>0)
                cout<<" ";
            if(ptr->left_child)
                queue[queue_rear++] = ptr->left_child;
            if(ptr->right_child)
                queue[queue_rear++] = ptr->right_child;
            if(!ptr->left_child && !ptr->right_child)
                (*num_of_leaf)++;
        }
        else
            break;
    }
}

int main()

{
    bool empty_tree = true; //empty tree?? (assignment 7)
    int root = 0; //first number input into the program
    int value = 0; //value of node/leaves
    int node = 0; //record number of node
    int leaf = 0; //record number of leaf
    int level = 1; //record tree level;
    tree_pointer root_pointer = NULL ;

    while(cin >> value)
    {
        if(empty_tree==true)
        {
            root = value;
        }
        empty_tree = false; //not a empty input
        insert_node(&root_pointer,value);
        node++; //node increase when input has inputed
    }
    num_of_node = node; //assign the number of node from local variable node to global variable

    //situation: empty tree
    if(empty_tree==true)
    {
        cout <<"Tree is empty";
    }

    if(empty_tree==false){
    preorder(root_pointer); //1st row: output the result in preorder
    cout << endl;
    num_of_node = node; //assign the number of node from local variable node to global variable
    inorder(root_pointer); //2nd row: output the result in inorder
    cout << endl;
    num_of_node = node; //assign the number of node from local variable node to global variable
    postorder(root_pointer); //3rd row: output the result in postorder
    cout << endl;
    num_of_node = node; //assign the number of node from local variable node to global variable
    levelorder(root_pointer,&leaf); //4th row: output the result in level order
    cout << endl;
    cout << root << endl; //5th row: output the root value
    cout << tree_level << endl; //6th row: output the tree level
    cout << leaf; //7th row: output the number of leaves
    }

    return 0;
}
