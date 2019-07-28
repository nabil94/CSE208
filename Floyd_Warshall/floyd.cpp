#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

struct edge{
    int source,dest,cost;
}edges[100];

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************MinHeap class ends here**************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color;
	int *parent;
	int **weight;
	int **predecessor;
	int **distance;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	int getDegree(int u);
	bool isEdge(int u, int v);
    void printGraph();
    bool BellmanFord(int source);
    void kEdges(int s,int k);
    int minimum(int a,int b);
    void FloydWarshall();
    void predecessorGraph();
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void path(int s,int d);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	weight = 0;
	parent  = 0;
	distance = 0;
	predecessor = 0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	//time = 0;

}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices+1] ;
	weight = new int*[nVertices+1];

    for(int i=1; i<=nVertices; i++)
    {
        weight[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++)
            weight[i][j] = 0; //initialize the matrix cells to 0
    }
	distance = new int*[nVertices+1];
	for(int i=1; i<=nVertices; i++)
    {
        distance[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++){
            if(i == j){
                distance[i][j] = 0;
            }
            else distance[i][j] = INFINITY;
        } //initialize the matrix cells to 0
    }

    predecessor = new int*[nVertices+1];
	for(int i=1; i<=nVertices; i++)
    {
        predecessor[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++){
            if(i == j || distance[i][j] == INFINITY){
                predecessor[i][j] = NULL_VALUE;
            }
            else
                predecessor[i][j] = i;
        } //initialize the matrix cells to 0
    }

	parent = new int[nVertices+1];
	//visited = new bool[nVertices+1];
	//dist = new int[nVertices];
	//start = new int[nVertices];
	//finish = new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>nVertices || v>nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	weight[u][v] = w;
	distance[u][v] = w;
	predecessor[u][v] = u;
	if(!directed){
        adjList[v].insertItem(u) ;
        weight[v][u] = w;
        distance[v][u] = w;
        predecessor[v][u] = v;
	}
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>nVertices || v>nVertices) return;
    this->nEdges--;
    if(isEdge(u,v) == true){
        adjList[u].removeItem(v);
        weight[u][v] = 0;
    }
    else printf("Cannot be removed.\n");
    if(!directed) {
        adjList[v].removeItem(u) ;
        weight[v][u] = 0;
    }

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>nVertices || v>nVertices) return false;
    int i = adjList[u].searchItem(v);
    if(i != NULL_VALUE){
        return true;
    }
    else return false;


}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>nVertices)
        return NULL_VALUE;
    else return adjList[u].getLength();
}

int Graph::minimum(int a,int b){
    if(a < b) return a;
    else return b;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=1;i<=nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d (%d)", adjList[i].getItem(j),weight[i][adjList[i].getItem(j)]);
        }
        printf("\n");
    }
}

void Graph::printDistanceMatrix(){
    for(int i=1;i<=nVertices;i++)
    {
        for(int j=1; j<=nVertices;j++)
        {
            if(distance[i][j] != INFINITY){
                printf("%d ",distance[i][j]);
            }
            else printf("INF ");
        }
        printf("\n");
    }
    printf("\n");
}

void Graph::printPredecessorMatrix(){
    for(int i=1;i<=nVertices;i++)
    {
        for(int j=1; j<=nVertices;j++)
        {
            if(predecessor[i][j] != NULL_VALUE){
                printf("%d ",predecessor[i][j]);
            }
            else printf("NIL ");
        }
        printf("\n");
    }
    printf("\n");
}


void Graph::FloydWarshall(){
    for(int k = 1; k<=nVertices;k++){
        for(int i = 1; i <= nVertices;i++){
            for(int j = 1; j <= nVertices;j++){
                distance[i][j] = minimum(distance[i][j],distance[i][k]+distance[k][j]);
                //if(distance[i][j] > distance[i][k] + distance[k][j])
                    //predecessor[i][j] = predecessor[k][j];
            }
        }
    }
    printDistanceMatrix();
    //printPredecessorMatrix();
}

void Graph::predecessorGraph(){
    for(int k = 1; k<=nVertices;k++){
        for(int i = 1; i <= nVertices;i++){
            for(int j = 1; j <= nVertices;j++){
                if(distance[i][j] > distance[i][k] + distance[k][j]){
                    distance[i][j] = distance[i][k] + distance[k][j];
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }
    printDistanceMatrix();
    printPredecessorMatrix();
}


Graph::~Graph()
{
    //write your destructor here
    if(adjList!=0) delete[] adjList ;
    if(weight!=0) delete[] weight;
    delete[] parent;
    delete[] distance;


}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main()
{

    int n,e,u,v,w,s,k;
    //FILE *fp;
    //fp = fopen("/Users/User/Desktop/CSE208 Offlines/HW1 - Minimum Spanning Tree - st/in.txt","r");
    Graph g;
    //printf("Enter number of vertices: ");
    //fscanf(fp,"%d\n",&n) ;
    scanf("%d",&n);
    scanf("%d", &e);
    g.setnVertices(n);
    //fscanf(fp,"%d\n",&e) ;
    for(int i = 0; i < e; i++){
        //fscanf(fp,"%d %d %d",&u,&v,&w);
        scanf("%d %d %d",&u,&v,&w);
        edges[i].source = u;
        edges[i].dest = v;
        edges[i].cost = w;

        g.addEdge(edges[i].source,edges[i].dest,edges[i].cost);
    }


    //g.primsAlgorithm(1);
    g.printGraph();
    g.printDistanceMatrix();
    //g.FloydWarshall();
    //g.printPredecessorMatrix();
    g.predecessorGraph();
    //g.path(5,1);
    return main();

}


