#include <iostream>

using namespace std;

typedef struct element{
    int starting_pos;
    int ending_pos;
    int cost;
};

int vertex = 0;
int edge= 0;

int main()
{
    cin>>vertex>>edge;
    int adj_matrix[vertex][vertex];      ///create an adjacency matrix
    element result[vertex-1];      ///the element array for output result
    bool visited[vertex] = {false};      ///check if the vertex has visited
    int starting_pos = 0, ending_pos = 0, cost = 0;   ///declare two vertex and the cost of edge

    ///initialize for adj_matrix
    for(int i=0; i<vertex; i++){
        for(int j=0; j<vertex; j++){
            adj_matrix[i][j] = 0;
        }
    }

    for(int i=0; i<edge; i++){
        cin>>starting_pos>>ending_pos>>cost;
        adj_matrix[starting_pos][ending_pos] = cost;
        adj_matrix[ending_pos][starting_pos] = cost;
    }
    ///Prim's algorithm
    int result_index = 0;
    bool valid;
    element temp;
    temp.cost = 0;
    visited[0] = true;

    for(;;){
        valid = false;
        temp.cost = 0;
        for(int i=0; i<vertex; i++){
            if(visited[i]==true){
                for(int j=0; j<vertex; j++){
                    if(visited[j]==true)
                        continue;
                    else if(adj_matrix[i][j]==0)
                        continue;
                    valid = true;
                    if(adj_matrix[i][j] < temp.cost || temp.cost ==0){
                        temp.starting_pos = i;
                        temp.ending_pos = j;
                        temp.cost = adj_matrix[i][j];
                    }
                }
            }
        }
        result[result_index++] = temp;
        visited[temp.ending_pos] = true;
        if(result_index == vertex-1 || !valid)
            break;
    }

    if(!valid){
        cout<<"No Spanning Tree."<<endl;
        cout<<"No Spanning Tree.";
        return 0;
    }
    else{
        int total_cost = 0;
        for(int i=0; i<vertex-1; i++){
            cout<<result[i].starting_pos<<" "<<result[i].ending_pos<<" "<<result[i].cost<<endl;
            total_cost+=result[i].cost;
        }
        cout<<total_cost<<endl<<endl;
    }
    temp.cost = 0;

    ///Kruskal's algorithm
    int min_cost = 0;
    int edge_index = 0;
    element edge_store[edge];

    for(;;){
        for(int i=0; i<vertex; i++){
            for(int j=0; j<vertex; j++){
                if(adj_matrix[i][j]<=min_cost)
                    continue;
                if(adj_matrix[i][j] < temp.cost || temp.cost ==0){
                    temp.starting_pos = i;
                    temp.ending_pos = j;
                    temp.cost = adj_matrix[i][j];
                }
            }
        }
        min_cost = temp.cost;
        edge_store[edge_index++] = temp;
        temp.cost = 0;
        if(edge_index == edge)
            break;
    }

    int tree_num[vertex];
    int result2_index = 0;
    element result2[vertex-1];

    for(int i=0; i<vertex; i++){
        tree_num[i] = i;
    }
    for(int i=0; i<edge_index; i++){
        temp = edge_store[i];
        if(tree_num[temp.starting_pos] == tree_num[temp.ending_pos]){
            continue;
        }
        else if(tree_num[temp.starting_pos] != tree_num[temp.ending_pos]){
            result2[result2_index++] = temp;
            int temp_num = tree_num[temp.ending_pos];
            for(int j=0; j<vertex; j++){
                if(tree_num[j] == temp_num){
                    tree_num[j] = tree_num[temp.starting_pos];
                }
            }
        }
    }
    int total_cost = 0;
    for(int i=0; i<vertex-1; i++){
        if(result2[i].starting_pos < result2[i].ending_pos)
            cout<<result2[i].starting_pos<<" "<<result2[i].ending_pos<<" "<<result2[i].cost<<endl;
        else
            cout<<result2[i].ending_pos<<" "<<result2[i].starting_pos<<" "<<result2[i].cost<<endl;
        total_cost+=result2[i].cost;
    }
    cout<<total_cost;
}
