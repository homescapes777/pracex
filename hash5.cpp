#include <iostream>
#include <string>
using namespace std;

class node
{
    string key;
    string value;
    node* next;
    public:
    node()
    {
        key="";
        value="";
        next=NULL;
    }
    friend class hash1;
};

class hash1
{
    node* arr[10];
    public:
    hash1()
    {
        for(int i=0;i<10;i++)
        {
            arr[i]=NULL;
        }
    }
    int hashcode(string k);
    void insert(string k,string v);
    string search(string k);
    void remove(string k);
    void display();

};

int hash1::hashcode(string k)
{
    int key=int(k[0]);
    int x=(3*key+5)%10;
    // = (3x+5) %10
    // //int hash1::hashcode(string k)
    // {
    //     int x=k[0]%10;
    //     return x;
    // }
    return x;
}

void hash1::insert(string k,string v)
{
    node *item=new node;
    item->key=k;
    item->value=v;
    int hashindex=hashcode(k);
    if(arr[hashindex]==NULL)
    {
        arr[hashindex]=item;
    }
    else
    {
        node *c=arr[hashindex];
        while(c->next!=NULL)
        {
            c-c->next;
        }
        c->next=item;
        item->next=NULL;
    }
}

string hash1::search(string k)
{
    int hashindex=hashcode(k);
    node *c=arr[hashindex];
    while(c->key!=k)
    {
        c=c->next;
    }
    return c->value;
}

void hash1::remove(string k)
{
    int hashindex=hashcode(k);
    node *c=arr[hashindex];
    node *p=c;
    if(c->key==k)
    {
        p=c->next;
        c->next=NULL;
        delete(c);
        arr[hashindex]=p;
    }
    else
    {
        while(c->key!=k)
        {
            p=c;
            c=c->next;
        }
        p->next=c->next;
        c->next=NULL;
        delete(c);
    }
}

void hash1::display()
{
    for(int i=0;i<10;i++)
    {
        node *c=arr[i];
        while(c!=NULL)
        {
            cout<<"Key:"<<c->key<<"                            "<<"Value:"<<c->value<<endl;
            c=c->next;
        }
        cout<<"\n__________________"<<endl;
    }
}

int main()
{
    hash1 h;
    int c=1;
    string k;
    string v;
    while(c>0)
    {
        cout<<"Menu"<<endl;
        cout<<"1.Insert"<<endl;
        cout<<"2.Display"<<endl;
        cout<<"3.Search"<<endl;
        cout<<"4.Remove"<<endl;
        cout<<"Enter your choice:";
        cin>>c;
        if(c==1)
        {
                cout<<"Enter the key:";
                cin>>k;
                cout<<"Enter the value:";
                cin>>v;
                h.insert(k,v);
        }
        else if(c==2)
        {
            h.display();
        }
        else if(c==3)
        {
            string search;
            cout<<"Enter the key:";
            cin>>search;
            string find=h.search(search);
            cout<<"Value of key is:"<<find<<endl;
        }
        else if(c==4)
        {
            string del;
            cout<<"Enter key to delete:";
            cin>>del;
            h.remove(del);
        }
    }
    return 0;
}
