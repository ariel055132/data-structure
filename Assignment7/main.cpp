#include <iostream>
#include <malloc.h>
// #define max_size 100000

using namespace std;

//node
typedef struct
{
    int value; //value in input
    int level; //level
} node;

//queue struct (PPT 4.2)
typedef struct queue *queue_pointer;
typedef struct queue
{
    node tree_node;  // used to represent the tree
    queue_pointer link; //link behind the value
};

//define node,left child, right child in global.can be used in int main
//original in string_to_int function
int node_value = 0;
int left_tree_value = 0; //similar as left child, need to declare new one as using the original one will pop out ambiguous error after compile
int right_tree_value = 0; //similar as right child

//function read the input seperately
void string_to_int(string input)
{
    int sub_no = 0; //result of input (Assignment 6)
    int ctrl = 0; // controller for the switch
    //reused from Assignment 6
    for(int i=0; i<input.length(); i++)
    {
        sub_no*=10;
        sub_no+=input[i]-'0';
        if(input[i+1]==' ' || input[i+1]=='\0')
        {
            switch(ctrl)
            {
            case 0: //root
                node_value = sub_no;
                break;
            case 1: //left children
                left_tree_value = sub_no;
                break;
            case 2: //right children
                right_tree_value = sub_no;
                break;
            }
            sub_no = 0;
            ctrl++;
            i++;
        }
    }
}

//add elements to queue (PPT 4.2)
void addq(queue_pointer *front,queue_pointer *rear, node tree_node)
{
    //add the element to the rear of the queue
    queue_pointer temp = (queue_pointer)malloc(sizeof(queue)); //request memory
    temp->tree_node = tree_node; //pointer temp points to node (location position)
    temp->link = NULL; //link initalized to NULL at the beginning
    if(*front) //not empty queue
        (*rear)->link = temp;
    else *front = temp; //empty queue
    *rear = temp; //rear = temp
}

//pop from the linked queue(reference in PPT 4.2)
node pop(queue_pointer *front)
{
    queue_pointer temp = *front;
    node tree_node;
    if(*front) //not empty list
    {
        tree_node = temp->tree_node;
        *front = temp->link;
        free(temp);
        return tree_node;
    }/*
    else{ //empty list
        break;
    }*/
}

int main()
{
    //input root --> left child --> right child
    //left child in above --> left child --> right child
    //right child in above --> left child --> right child
    string input; //tree that input by user
    int level = 1; //output tree height stated in question
    int leaves = 0; //output number of leaves stated in question
    bool valid = false; //whether the tree is valid or not
    bool first_node_input = true; //the input root is inputted?
    bool empty_input = true; //whether there is input or not
    queue_pointer front=NULL, rear=NULL; //front used for delete the data, rear used for add the data
    node tree_node, left_child,right_child; //left/right child of the tree

    while(getline(cin,input))
    {
        empty_input = false;
        valid = false;
        string_to_int(input);

        //check whether it is valid
        if(first_node_input==false)
        {
            for(; front;)
            {
                tree_node = pop(&front);
                //valid input
                if(tree_node.value == node_value)
                {
                    valid = true;
                    break;
                }
                else
                {
                    leaves++;
                    continue;
                }

            }
            //cout << "@"; test bug and no problem can found
            //invalid input
            if(valid== false)
            {
                break;
            }
            /*
            //cout << "@"; test bug and no problem can found
            //invalid input
            if(valid== false)
            {
                break;
            }*/
        }

        //insert first row value
        else
        {
            tree_node.value = node_value;
            tree_node.level = 1;
        }
        //insert value into left child when it has value
        if(left_tree_value!=0)
        {
            left_child.value = left_tree_value;
            left_child.level = tree_node.level + 1; //left child starts at height 2
            addq(&front,&rear,left_child);
        }
        //insert value into right child when it has value
        if(right_tree_value!=0)
        {
            right_child.value = right_tree_value;
            right_child.level = tree_node.level +1; //same as the left child
            addq(&front,&rear,right_child);
        }

        //left child and right child can be 0
        if(left_tree_value == 0 && right_tree_value==0 && first_node_input==true)
        {
            continue;
        }
        //initalize the first input again
        first_node_input = false;
       // cout << left_child.value << " " << right_child.value << endl; //test bug
    }

    //output result of empty tree
    if(empty_input == true)
    {
        cout << "Tree is empty";
    }
    //output result of invalid trees
    else if(valid == false)
    {
        cout <<"Invalid tree";
    }
    //output result of valid tree
    else if(valid == true)
    {
        for(; front;)
        {
            tree_node = pop(&front);
            leaves++;
        }
        level = tree_node.level;
        cout<<level<<endl;
        cout<<leaves;
    }
    return 0;
}

