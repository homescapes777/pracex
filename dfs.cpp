#include <iostream>
// #include <queue>
using namespace std;

#define MAXSIZE 20

class node
{
    int data;
    node *next;

public:
    node()
    {
        data = 0;
        next = NULL;
    }
    node(int val)
    {
        data = val;
        next = NULL;
    }
    friend class graph;
    friend class stack;
    friend class queue;
};

class stack
{
private:
    int data[MAXSIZE];
    int top;

public:
    stack()
    {
        top = -1;
    }
    bool isempty()
    {
        return top == -1;
    }
    void push(int element)
    {
        data[++top] = element;
    }
    void pop()
    {
        top--;
    }
    int gettop()
    {
        return data[top];
    }
};

class queue
{
    node *front;
    node *rear;
    int size;

public:
    queue()
    {
        front = NULL;
        rear = NULL;
        size = 0;
    }
    void push(int no)
    {
        node *newn = new node();
        newn->data = no;
        newn->next = NULL;
        if (front == NULL && rear == NULL)
        {
            front = newn;
            rear = newn;
        }
        else
        {
            rear->next = newn;
            rear = newn;
        }
        size++;
    }
    void pop()
    {
        node *temp = front;
        if (front == NULL && rear == NULL)
        {
            cout << "Queue is empty " << endl;
        }
        if (front == rear)
        {
            delete front;
            front = rear = NULL;
        }
        else
        {
            front = front->next;
            delete temp;
        }
        size--;
    }
    bool empty()
    {
        return size == 0;
    }
    int getfront()
    {
        return front->data;
    }
};

class graph
{
    int maxsize;
    node *arr[MAXSIZE];

public:
    graph()
    {
        maxsize = 0;
    }
    graph(int max)
    {
        maxsize = max;
        for (int i = 0; i < maxsize; i++)
        {
            arr[i] = NULL;
        }
    }
    void addedge(int src, int dest)
    {
        node *newn1 = new node(dest);
        node *newn2 = new node(src);
        node *temp;
        if (arr[src] == NULL)
        {
            arr[src] = newn1;
        }
        else
        {
            temp = arr[src];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newn1;
        }
        if (arr[dest] == NULL)
        {
            arr[dest] = newn2;
        }
        else
        {
            temp = arr[dest];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newn2;
        }
    }
    void display()
    {
        for (int i = 0; i < maxsize; i++)
        {
            cout << "Vertex  " << i << "->";
            node *temp = arr[i];
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void BFS(int src)
    {
        queue q;
        bool visited[maxsize] = {};
        q.push(src);
        visited[src] = true;
        while (!q.empty())
        {
            src = q.getfront();
            q.pop();
            cout << src << " , ";
            node *temp = arr[src];
            while (temp != NULL)
            {
                if (!visited[temp->data])
                {
                    visited[temp->data] = true;
                    q.push(temp->data);
                }
                temp = temp->next;
            }
        }
    }
    void DFS(int src)
    {
        stack st;
        bool visited[maxsize] = {};
        st.push(src);
        visited[src] = true;
        while (!st.isempty())
        {
            src = st.gettop();
            st.pop();
            cout << src << " ,";
            node *temp = arr[src];
            while (temp != NULL)
            {
                if (!visited[temp->data])
                {
                    visited[temp->data] = true;
                    st.push(temp->data);
                }
                temp = temp->next;
            }
        }
    }

    // Function to calculate degree of each node
    void calculateDegrees()
    {
        int degrees[MAXSIZE] = {0}; // Initialize degrees array with 0s
        for (int i = 0; i < maxsize; i++)
        {
            node *temp = arr[i];
            while (temp != NULL)
            {
                degrees[i]++; // Increment degree for each adjacent node
                temp = temp->next;
            }
        }

        // Display degrees
        cout << "Degrees of each node:" << endl;
        for (int i = 0; i < maxsize; i++)
        {
            cout << "Node " << i << ": " << degrees[i] << endl;
        }
    }
};

int main()
{
    int vertices, v1, v2;
    char choice;

    cout << "Enter number of vertices\n";
    cin >> vertices;
    graph g(vertices);
    do
    {
        cout << "----MENU----\n";
        cout << "1) Add Edge\n";
        cout << "2) Display\n";
        cout << "3) BFS\n";
        cout << "4) DFS\n";
        cout << "5) Calculate Degrees\n";
        cout << "6) Exit\n";
        cout << "Enter your choice\n";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "Enter vertex 1 : \n";
            cin >> v1;
            cout << "Enter vertex 2 : \n";
            cin >> v2;
            g.addedge(v1, v2);
            break;
        case '2':
            g.display();
            break;
        case '3':
            cout << "Enter starting vertex for BFS: ";
            cin >> v1;
            g.BFS(v1);
            cout << endl;
            break;
        case '4':
            cout << "Enter starting vertex for DFS: ";
            cin >> v1;
            g.DFS(v1);
            cout << endl;
            break;
        case '5':
            g.calculateDegrees();
            break;
        case '6':
            cout << "Thank you\n";
            break;
        default:
            cout << "Choose between (1-6)\n";
        }
    } while (choice != '6');

    return 0;
}
