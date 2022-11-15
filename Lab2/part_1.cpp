/*
Designed for part (a) of the Lab 2 Poject (Samiksha) 
*/
#include <bits/stdc++.h>  
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <limits>
#include <queue> 
#include <vector>
#include <chrono>
#include <random>

typedef std::pair<int, int> iPair;  
struct item {
        int value;
        int priority;
};

//make a class for the priority queue 
class priorityQ{
    private:
    // Store the element of a priority queue
    item pr[100000];
    int size = -1;
    public:
     void enqueue(int value, int priority)
        {
            size++;
            pr[size].value = value;
            pr[size].priority = priority;
        }
        int peek()
        {
           int lowestpriority = INT_MAX;
            int ind = -1;
            for (int i = 0; i <= size; i++) {
                if (lowestpriority== pr[i].priority && ind > -1 && pr[ind].value > pr[i].value) {
                    lowestpriority = pr[i].priority;
                    ind = i;
                }
                else if (lowestpriority > pr[i].priority) {
                    lowestpriority = pr[i].priority;
                    ind = i;
                }
            }
        
            return ind;
        }


        int peekA()
        {
            int lowestpriority = INT_MAX;
            int ind = -1;
             for (int i = 0; i <= size; i++) {
                if (lowestpriority== pr[i].priority && ind > -1 && pr[ind].value > pr[i].value) {
                    lowestpriority = pr[i].priority;
                    ind = i;
                }
                else if (lowestpriority > pr[i].priority) {
                    lowestpriority = pr[i].priority;
                    ind = i;
                }
            }
            if (ind!= -1){
                return pr[ind].value;
            }

            return ind;
        }
        void dequeue()
        {
            int ind = peek();
            for (int i = ind; i < size; i++) {
                pr[i] = pr[i + 1];
            }
            size--;
        }

        void removeV(int v, int newp){
             for (int j = 0; j < size; j++) {
                if (v == pr[j].value){
                    pr[j].priority = INT_MAX;
                } //time complexity depends on this 
            }
        }

        void updateV(int v, int newp){
            for (int i = 0; i < size; i++) {
                if (pr[i].value == v){
                    pr[i].priority = newp;
                }
            }
        }





};

class adjacency_matrix{
    private:
        int _V;
        int _E;
        int **_matrix; 
    public:
        adjacency_matrix(int V): _V(V){
            _E = 0;
            //initializing the matrix 
            _matrix = (int **) new int[_V];
            for(int i=0;i<_V;i++)
                _matrix[i] = (int *)new int[_V];

            for(int i=0;i<_V;i++)
                for(int j=0;j<_V;j++)
                    _matrix[i][j] = 0;
        }
        void printMatrix(){
            for(int i=0;i<_V;i++){
                for(int j=0;j<_V;j++)
                    std::cout<<_matrix[i][j]<< " ";
                std::cout<<" "<<std::endl;
            }

        }
        void fillMatrix(){
            
            int V1, V2, W;
            while(scanf("%d %d %d",&V1,&V2, &W)==3)
            {
                if(V1>=0 && V1<_V && V2>=0 && V2<_V)
                {
                    _matrix[V1][V2] = W;
                    //_matrix[V2][V1] = W;
                    _E++;
                }
                else
                    break;
               
            }
        }
        int **getMatrix(){
            return _matrix;
        }

        int randomfillMatrix(int E){
            int count = E;
            int randV = 0; 
            while (count > 0){
                int v1 = std::rand() % ( _V );
                int v2 = std::rand() % ( _V );
                randV = v1;
                if (v1 != v2){
                    _matrix[v1][v2] = std::rand() % ( 10 + 1 );
                    count--;
                }
            }
            return randV;
        }

    ~adjacency_matrix(){
        
    }
};

class Dijkstra_ShortestPath{

    private:
        int _V;
        int *d;
        int *pi;
        int *S; 
        int **_matrix; 

    public: 
        Dijkstra_ShortestPath(int V): _V(V){
              
        }
        void algorithm(int source){
            d = new int[_V];
            pi = new int [_V];
            S = new int[_V]; 
            //priority_Q *Q = new priority_Q();
            for(int i=0; i<_V;i++){
                d[i] = std::numeric_limits<int>::max();
                pi[i] = std::numeric_limits<int>::max();
                S[i] = 0;
            }
            //we are using ANOTHER queue this is not the same as the d array 
            //this queue is priority queue Q
            //Every item of PQ is a pair. The first value is weight and the second value is the vertex
            priorityQ *Q = new priorityQ();
            for(int i=0; i<_V;i++){
                Q->enqueue(i, 99999);
            }
            d[source] = 0;
            Q->updateV(source, 0); //source put into the queue             
            while (Q->peek() != -1){
                int u = Q->peekA(); //ExtractCheapest(Q) based on the notes 
                Q->dequeue(); //need a dequeue option
                S[u] = 1;
                pi[source] = source;
                //for each vertex, v, adjacent to u
                for(int v=0; v<_V;v++){
                    if (_matrix[u][v]>0 && S[v] != 1 && d[v] > d[u] + _matrix[u][v]){
                        Q->removeV(v, d[v]);
                        d[v] = d[u] + _matrix[u][v];
                        pi[v] =  u; 
                        Q->enqueue(v, d[v]); //need an update function
                    }
                }
                
            }

        }
        void printValues(){
            std::cout<<"Vertices: ";
            for(int j=0; j<_V; j++){
                std::cout<<j << " ";
            }
            std::cout<<std::endl;
            std::cout<<"Source: ";
            for(int j=0; j<_V; j++){
                std::cout<<S[j] << " ";
            }
            std::cout<<std::endl;
            std::cout<<"d Array: ";
            for(int j=0; j<_V; j++){
                std::cout<<d[j] << " ";
            }
            std::cout<<std::endl;
            std::cout<<"pi Array: ";
            for(int j=0; j<_V; j++){
                std::cout<<pi[j] << " ";
            }
            std::cout<<std::endl;
        }
    
    void setMatrix(int **matrix){
        _matrix = matrix;
    }

    ~Dijkstra_ShortestPath(){

    }

};

int main(){
    
    /* input 1 to 4
    int V, S;
    scanf("%d", &V);
    adjacency_matrix adjMatrix(V);
    adjMatrix.fillMatrix();
    std::cout<<"Adjacency Matrix"<<std::endl;
    adjMatrix.printMatrix();
    std::cout<<"-----------------"<<std::endl;
    Dijkstra_ShortestPath myAlgo(V);
    scanf("%d", &S);

    double timet =0;
    
    for (int i=0;i<50;i++){
        myAlgo.setMatrix(adjMatrix.getMatrix());
        auto start = std::chrono::high_resolution_clock::now();
        myAlgo.algorithm(S);
        auto end = std::chrono::high_resolution_clock::now();
        timet += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    } 
    
    std::cout << "elapsed time in seconds: " << timet << "microseconds\n";
    myAlgo.printValues();

    */
    int V, S, E;
    scanf("%d %d", &V, &E);
    adjacency_matrix adjMatrix(V);
    S = adjMatrix.randomfillMatrix(E);
    printf("%d ", S);
    //std::cout<<"Adjacency Matrix"<<std::endl;
    //adjMatrix.printMatrix();
    //std::cout<<"-----------------"<<std::endl;
    Dijkstra_ShortestPath myAlgo(V);
    double timet =0;
    for (int i=0;i<50;i++){
        myAlgo.setMatrix(adjMatrix.getMatrix());

        auto start = std::chrono::high_resolution_clock::now();
        myAlgo.algorithm(S);
        auto end = std::chrono::high_resolution_clock::now();
        timet += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    } 
    std::cout << "elapsed time in seconds: " << timet << "microseconds\n";
    //myAlgo.printValues();


    return 0;
}