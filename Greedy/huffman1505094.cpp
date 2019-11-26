#include<iostream>
#include<stdio.h>

using namespace std;

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
    //char c;
    char data; //actual data that is stored
    int key; //key value of the data, heap is constructed based on key
    HeapItem *right,*left;
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    //HeapItem *left,*right;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        //map = new int[MAX_HEAP_SIZE];
        heapLength=0;

    }

    ~MinHeap() //destructor
    {
        //if(map) delete [] map;
        if(A) delete [] A;
        //map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(char v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            //map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(HeapItem a)
    {
        //Write your codes here
        heapLength++;
        A[heapLength] = a;
        //A[heapLength].key = key;
        buHeapify(heapLength);
    }

    HeapItem *removeMin()
    {
        //write your codes here
        if(Empty())
        {
            printf("Heap is empty\n");
            //return 0;
        }
        else
        {
            HeapItem *temp = new HeapItem() ;//= new HeapItem;
            temp->data = A[1].data;
            temp->key = A[1].key;
            temp->right = A[1].right;
            temp->left = A[1].left;
            A[1] = A[heapLength];
            heapLength--;
            heapify(1);
            //map[A[1].data] = 1;
            return temp;
        }
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
                //map[A[i].data]=i;
                A[smallest]=t;
                //map[A[smallest].data]=smallest;
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
        if(i > 0 && parentNode > 0 && A[parentNode].key > A[i].key )
        {
            temp = A[i];
            A[i] = A[parentNode];
            //map[A[i].data] = i;
            A[parentNode] = temp;
            //map[A[parentNode].data] = parentNode;
            buHeapify(parentNode);
        }
    }

    int getSize()
    {
        return heapLength;
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%c,%d) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }

    HeapItem *makehuffmantree()
    {
        //Minheap heap;
        HeapItem c;
        while(heapLength != 1)
        {
            c.left = new HeapItem();
            c.right = new HeapItem();
            c.left = removeMin();
            c.right = removeMin();
            c.data = '$';
            c.key = c.left->key+c.right->key;
            insertItem(c);
        }
        return removeMin();
    }



    int leaf(HeapItem *a)
    {
        if((a->left == NULL) && (a->right == NULL))
            return 1;
        else return 0;
    }

    void printArray(int a[],int n)
    {
        for(int i =0; i<n; i++)
        {
            cout<<a[i];
        }
        cout<<endl;
    }

    void printarr(HeapItem *h,int top,int a[])
    {
        if(h->left)
        {
            a[top]=0;
            printarr(h->left,top+1,a);
        }
        if(h->right)
        {
            a[top]=1;
            printarr(h->right,top+1,a);
        }
        if(leaf(h) == 1)
        {
            cout<<h->data<<":";
            printArray(a,top);
        }
    }


};

int main()
{
    MinHeap heap;
    int n;
    int key;
    char c;
    cin>>n;
    for(int i = 0; i < n; i++)
    {
        cin>>c>>key;
        HeapItem q;
        //q = new HeapItem();
        q.data = c;
        q.key = key;
        q.left = NULL;
        q.right = NULL;
        heap.insertItem(q);

    }

    //heap.printHeap();
    HeapItem *a;
    a = new HeapItem();
    a = heap.makehuffmantree();
    //heap.printHeap();
    //cout<<a->data<<" "<<a->key<<endl;
    cout<<"Huffman coding is"<<endl;
    int Array[n];
    //cout<<a->left->data<<" ";
    heap.printarr(a,0,Array);
    return main();
}


