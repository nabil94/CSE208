#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 100
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

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

//******************MinHeap class starts here*************************

class HeapItem
{
public:
	int data; //actual data that is stored
	int key; //key value of the data, heap is constructed based on key
	//int parent;
  /*  HeapItem(){
        this->data = data;
        this->key = key;
    }
*/

};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(HeapItem a)
    {
        //Write your codes here
            heapLength++;
            A[heapLength].data = a.data;
            A[heapLength].key = a.key;
            map[a.data] = heapLength;
            buHeapify(heapLength);
    }


	HeapItem removeMin()
	{
	    //write your codes here
	    if(Empty()){
            printf("Heap is empty\n");
            //return 0;
	    }
        else{
            HeapItem temp = A[1];
            A[1] = A[heapLength];
            heapLength--;
            heapify(1);
            //map[A[1].data] = 1;
            return temp;
        }
	}



    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, int key)
	{
		//Write your codes here.
		float temp;
		int d = map[data];
		if(d > 0){
            temp = A[d].key;
            A[d].key = key;
            if(temp > A[d].key){   //decrease key
            buHeapify(d);
            }
            else if(temp < A[d].key){ //increase key
                heapify(d);
            }
		}
		else printf("Not found\n");
	}


    //This function returns the key value of a data stored in heap
	int getKey(int data)
	{
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i)
	{
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i)
	{
	    int parentNode = i/2;
	    HeapItem temp;
        if(i > 0 && parentNode > 0 && A[parentNode].key >= A[i].key ){
            temp = A[i];
            A[i] = A[parentNode];
            map[A[i].data] = i;
            A[parentNode] = temp;
            map[A[parentNode].data] = parentNode;
            buHeapify(parentNode);
        }
    }



    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%d) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}

	bool isMinHeapNode(int data){
	    int flag = 0;
	    for(int i = 1; i <= heapLength;i++){
            if(A[i].data == data){
                flag = 1;
                break;
            }

	    }
	    if(flag == 1) return true;
	    else return false;
	}
};

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
	int *vert;
	HeapItem *nodes;
	bool *visited;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	int getDegree(int u);
	bool isEdge(int u, int v);
    void printGraph();
    void primsAlgorithm(int r);

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	weight = 0;
	parent  = 0;
	vert = 0;
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
	nodes = new HeapItem[nVertices+1];
	for(int i=1; i<=nVertices; i++)
    {
        nodes[i].data = i;
    }
    for(int i=1; i<=nVertices; i++)
    {
        weight[i] = new int[nVertices+1];
        for(int j=1; j<=nVertices; j++)
            weight[i][j] = 0; //initialize the matrix cells to 0
    }
	//color = new int[nVertices];
	parent = new int[nVertices+1];
	visited = new bool[nVertices+1];
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
	if(!directed){
        adjList[v].insertItem(u) ;
        weight[v][u] = w;
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

void Graph::primsAlgorithm(int r){

    for(int i = 1 ; i <= nVertices;i++){
        nodes[i].key = INFINITY;
        parent[i] = NULL_VALUE;
        visited[i] = false;
    }
    nodes[r].key = 0;
    MinHeap heap;
    for(int i = 1; i <= nVertices; i++ ){
        heap.insertItem(nodes[i]);
    }
    while(heap.Empty() != true){
        HeapItem u = heap.removeMin();
        //heap.printHeap();
        if(visited[u.data] == true){
            continue;
        }
        visited[u.data] = true;
        for(int i = 0; i < getDegree(u.data);i++){
            int v = adjList[u.data].getItem(i);
            //printf("%d %d\n",u.data,v);
           if(visited[v]!= true && weight[u.data][v] < heap.getKey(v)){
                heap.updateKey(v,weight[u.data][v]);
                parent[v] = u.data;
                //heap.decreaseKey(v,weight[u.data][v]);
            }
        //printf("%d ",u.data);
        }
    }

    for(int i = 2; i <= nVertices; i++){
        printf("%d - %d   %d  \n",parent[i],i,weight[parent[i]][i]);
    }
    //heap.printHeap();
   int cost = 0;
    for(int i = 2; i <= nVertices; i++){
        cost = cost + weight[parent[i]][i];
    }
    printf("%d\n",cost);



}


Graph::~Graph()
{
    //write your destructor here
    if(adjList!=0) delete[] adjList ;
    if(weight!=0) delete[] weight;
    delete[] parent;
    delete[] nodes;
    delete[] visited;


}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main()
{
    int n,e,u,v,w;
    FILE *fp;
    fp = fopen("/Users/User/Desktop/1505094/in.txt","r");
    Graph g;
    //printf("Enter number of vertices: ");
    fscanf(fp,"%d\n",&n) ;
    //scanf("%d", &e);
    g.setnVertices(n);
    fscanf(fp,"%d\n",&e) ;
    for(int i = 0; i < e; i++){
        fscanf(fp,"%d %d %d",&u,&v,&w);
        g.addEdge(u,v,w);
    }


    g.primsAlgorithm(1);
    printf("\n");
    //g.printGraph();
    return 0;

}
