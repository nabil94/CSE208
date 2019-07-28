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

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

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
	bool *visited;
	int **residualGraph;
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
    int minimum(int a,int b);
    void path(int s,int d);
    bool bfs(int **graph,int source,int dest);
    int FordFulkerson(int s,int t);
    void printResGraph();
    void dfs();
    void dfs_visit(int u);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	weight = 0;
	parent  = 0;
	//distance = 0;
	//predecessor = 0;
	visited = 0;
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

  /*  residualGraph = new int*[nVertices+1];

    for(int i=1; i<=nVertices; i++)
    {
        residualGraph[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++)
            residualGraph[i][j] = 0; //initialize the matrix cells to 0
    }
*/
	parent = new int[nVertices+1];
	visited = new bool[nVertices+1];
	color = new int[nVertices+1];
	//start = new int[nVertices];
	//finish = new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<=0 || v<=0 || u>nVertices || v>nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	weight[u][v] = w;
	//residualGraph[u][v] = w;
	if(!directed){
        adjList[v].insertItem(u) ;
        weight[v][u] = w;
        //residualGraph[v][u] = w;
	}
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<=0 || v<=0 || u>nVertices || v>nVertices) return;
    this->nEdges--;
    if(isEdge(u,v) == true){
        adjList[u].removeItem(v);
        weight[u][v] = 0;
       // residualGraph[u][v] = 0;
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
    if(u<=0 || v<=0 || u>nVertices || v>nVertices) return false;
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

void Graph::printResGraph(){
    for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
           printf("%d\t",residualGraph[i][j]);
        }
        printf("\n");
    }
}

bool Graph::bfs(int **graph,int source,int dest)
{
    //complete this function
    //initialize BFS variables
    if(source<1 || source>nVertices) return false;

  /*  graph = new int*[nVertices+1];

    for(int i=1; i<=nVertices; i++)
    {
        graph[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++)
            graph[i][j] = weight[i][j]; //initialize the matrix cells to 0
    }
*/
    for(int i=1; i<=nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        //dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    //dist[source] = 0 ;
    parent[source] = -1;
    q.enqueue(source);
    //printf("%d   %d   %d\n",source,dist[source],parent[source]);
    while( !q.empty() )
    {
        //complete this part
        int u = q.dequeue();
        //printf("%d ",u);

        for(int i = 1; i <= nVertices; i++){
            if(graph[u][i] > 0 && color[i] == WHITE){

                    color[i] = GREY;
                    //dist[i] = dist[u] + 1;
                    parent[i] = u;
                    q.enqueue(i);
                    }
                }
    }
    //return (color[dest] == GREY);
    if(color[dest] == GREY)
        return true;
    else return false;
}


void Graph::dfs()
{
    //write this function
    for(int i=1; i<=nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        //start[i] = INFINITY;
        //finish[i] = INFINITY;
    }
    //time = 0;

    for(int i = 1;i<=nVertices;i++){
        if(color[i] == WHITE){
            dfs_visit(i);
        }
    }
}

void Graph::dfs_visit(int u){
    //time = time + 1;
    //start[u] = time;
    color[u] = GREY;
    printf("%d ",u);
    for(int i = 1; i<=nVertices; i++){
        if(isEdge(u,i) == true && color[i] == WHITE){
            parent[i] = u;
            color[i] = GREY;
            dfs_visit(i);
        }
    }
    //printf("%d %d %d\n" , u,start[u],finish[u]);
    color[u] = BLACK;
    //time = time + 1;
    //finish[u] = time;
    //printf(" %d\n",finish[u]);
    //printf("%d %d %d\n" , u,start[u],finish[u]);

}


int Graph::FordFulkerson(int s,int t){
    int u,v;
    int max_flow = 0;
    int **residualGraph;

    residualGraph = new int*[nVertices+1];

    for(int i=1; i<=nVertices; i++)
    {
        residualGraph[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++)
            residualGraph[i][j] = 0; //initialize the matrix cells to 0
    }

    for (u = 1; u <= nVertices; u++)
        for (v = 1; v <= nVertices; v++)
             residualGraph[u][v] = weight[u][v];
    //printResGraph();
    while(bfs(residualGraph,s,t))
    {
        int path_flow = INFINITY;
        /*for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = minimum(path_flow, residualGraph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            residualGraph[u][v] = residualGraph[u][v] - path_flow;
            residualGraph[v][u] = residualGraph[v][u] + path_flow;
        }*/
        int r = t;
        while(r != s){
            path_flow = minimum(path_flow, residualGraph[parent[r]][r]);
            r = parent[r];
        }
        max_flow = max_flow + path_flow;
        v = t;
        while(v != s){
            u = parent[v];
            residualGraph[u][v] = residualGraph[u][v] - path_flow;
            residualGraph[v][u] = residualGraph[v][u] + path_flow;
            v=parent[v];

        }

    }
    for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
           printf("%d\t",residualGraph[i][j]);
        }
        printf("\n");
    }
    int flow_table[nVertices+1][nVertices+1];
    for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
            flow_table[i][j] = weight[i][j] - residualGraph[i][j];
        }
        //printf("\n");
    }

    for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
           if(flow_table[i][j] > 0){
            printf("%d - %d   %d/%d\n",i,j,flow_table[i][j],weight[i][j]);
           }
           //printf("\n");
        }
    }

    printf("Min cuts are:- \n");
    /*for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
           if(weight[i][j] == flow_table[i][j] && flow_table[i][j] > 0){
            printf("%d - %d  \n",i,j);
           }
           //printf("\n");
        }
    }*/

    /*dfs();
    for(int i = 1;i<=nVertices;i++){
        for(int j = 1;j<=nVertices;j++){
            if(isEdge(i,j) == true && color[i] == GREY && color[j] == WHITE){
                printf("%d - %d \n",i,j);
            }
        }
    }*/
    bool a = bfs(residualGraph,s,t);
    if(a == false){
        for(int i = 1;i<=nVertices;i++){
            for(int j = 1;j<=nVertices;j++){
            if(isEdge(i,j) == true && color[i] == GREY && color[j] == WHITE){
                printf("%d - %d \n",i,j);
                }
            }
        }
    }


    return max_flow;

}



Graph::~Graph()
{
    //write your destructor here
    if(adjList!=0) delete[] adjList ;
    if(weight!=0) delete[] weight;
    delete[] parent;
    //delete[] distance;


}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main()
{

    int n,e,u,v,w,k;
    int s,t;
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
    //scanf("%d %d",&s,&t);

    //g.primsAlgorithm(1);
    //g.printGraph();
    //bool a1 = g.bfs(1,6);
    scanf("%d %d",&s,&t);
    int a = g.FordFulkerson(s,t);
    printf("Maximum flow %d",a);
    //g.printResGraph();

    return main();

}
