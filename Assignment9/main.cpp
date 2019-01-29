#include <iostream>
#define maxsize 201 //the index is set to 1 initially
using namespace std;

int heap[maxsize]; //max size of heap is 200 (stated in question)
int heap_index = 1; //index of heap, initalize it to 1 to avoid out of bound
bool max_heap = true; //determine whether it is max heap or min heap

//build up heap
void insert(int num)
{
    //empty heap array
    if(heap_index == 1)
    {
        heap[heap_index] = num;
    }
    //construct max heap
    else if(max_heap==true)
    {
        heap[heap_index] = num;
        int child = heap_index;
        int parent = heap_index/2; // child/2 = parent
        //max heap will change when the value of parent is smaller than the value of child
        while(heap[parent]<heap[child] && parent >0)
        {
            int temp = heap[child]; //swap the value of child and parent
            heap[child] = heap[parent];
            heap[parent] = temp;
            child = parent; //parent become child after swap
            parent = child/2; //parent = child/2
        }
    }
    //construct min heap
    else if(max_heap==false)
    {
        heap[heap_index] = num;
        int child = heap_index;
        int parent = heap_index/2;
        //min heap will change when the value of parent is greater than the value of child
        while(heap[parent]>heap[child] && parent >0)
        {
            int temp = heap[child];
            heap[child] = heap[parent];
            heap[parent] = temp;
            child = parent;
            parent = child/2;
        }
    }
    heap_index++;
    //cout << "#" << " "; test bug no problem.
}

//similar to PPT 5.2 delete from the max heap
void extract()
{
    cout << heap[1] <<endl; //the request of the question (output the key first)
    int temp = heap[--heap_index];
    //max heap
    if(max_heap==true)
    {
        int parent = 1; //5.2 PPT
        int child = 2;
        //keep running until touches the end
        while(child<heap_index)
        {
            //modified from PPT
            if(child<heap_index && heap[child]<heap[child+1])
            {
                child++;
            }
            //matches the rule
            if(temp > heap[child])
            {
                break;
            }
            heap[parent] = heap[child];
            parent = child;
            child *=2;
        }
        heap[parent]=temp;
        // cout << "@" <<" "; test bug, no problem
    }
    //min heap
    else if(max_heap==false)
    {
        int parent = 1; //5.2 PPT
        int child = 2;
        while(child<heap_index)
        {
            if(child<heap_index && heap[child]>heap[child+1])
            {
                child++;
            }
            //matches the rule
            if(temp < heap[child])
            {
                break;
            }
            heap[parent] = heap[child];
            parent = child;
            child *=2;
        }
        heap[parent]=temp;
        // cout << "@1" <<" "; test bug , no problem
    }
}

void decreaseKey(int num, int sub)
{
    int child = 1;
    for(; child < heap_index; child++)
    {
        if(heap[child] == num)
        {
            heap[child] -= sub;
            break;
        }
    }
    int parent = child/2;
    while(heap[parent] > heap[child])
    {
        int temp = heap[child];
        heap[child] = heap[parent];
        heap[parent] = temp;
        child = parent;
        parent = child/2;
    }
}

int main()
{
    string command; //command
    while(cin >> command)
    {
        if(command=="MaxHeap:")
        {
            int num = 0;
            max_heap = true;
            while(cin >> num)
            {
                if(num==-1)
                {
                    break;
                }
                else
                {
                    insert(num);
                }
            }
            continue;
        }
        else if(command=="MinHeap:")
        {
            int num=0;
            max_heap = false;
            while(cin >> num)
            {
                if(num==-1)
                {
                    break;
                }
                else
                {
                    insert(num); // need to be corrected in future.
                }
            }
        }
        else if(command=="ExtractMax")
        {
            extract();
            continue;
        }
        else if(command=="ExtractMin")
        {
            extract();
            continue;
        }
        else if(command=="Insert:")
        {
            int num = 0;
            cin >> num;
            insert(num);
            continue;
        }
        else if(command=="DecreaseKey:")
        {
            int num = 0;
            int sub = 0; //number that going to be delete
            cin >> num >> sub;
            decreaseKey(num,sub);
            continue;
        }
        else if(command=="Print")
        {
            for(int i=1; i<heap_index; i++)
            {
                cout << heap[i] << " ";
            }
            break;
        }
    }
    return 0;
}
