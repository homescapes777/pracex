#include <iostream>
using namespace std;

class node
{
  node *lc, *rc;
  string x;
public:
  node(string a)
  {
    x = a;
    lc = rc = NULL;
  }
  friend class OBST;
};

class OBST
{

  node *root;

public:
  OBST() { root = NULL; }

  void calculate_wt(double *p, double *q, int n, string st[])
  {
    //	  p=array of successful probability
    //	  q=array of unsuccessful probability
    //	  n=number of elements or nodes

    // Allocate memory for weight
    double **w = new double *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
      w[i] = new double[n + 1];
    }
    // Allocate memory for Cost
    double **c = new double *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
      c[i] = new double[n + 1];
    }
    // Allocate memory for root
    double **r = new double *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
      r[i] = new double[n + 1];
    }
    // For first two iterations
    for (int i = 0; i < n; i++)
    {

      w[i][i] = q[i];
      r[i][i] = c[i][i] = 0;

      // calculate wts, costs of null tree and tree with one node
      w[i][i + 1] = q[i] + q[i + 1] + p[i];
      r[i][i + 1] = i + 1;
      c[i][i + 1] = w[i][i + 1];
    }

    // Initializing the last element
    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;

    for (int m = 2; m <= n; m++)
    {
      // calculate wt and cost of tree having more than two node
      for (int i = 0; i <= n - m; i++)
      {

        double min = 999;

        int j = i + m;
        int k = 0;
        w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

        for (int x = i + 1; x <= j; x++)
        {
          double sum = c[i][x - 1] + c[x][j];

          if (sum < min)
          {
            min = sum;
            k = x;
          }
        }

        c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
        r[i][j] = k;
      }
    }

    this->root = this->createTree(0, n, r, st); // IMP
    show(w, r, c, n + 1);
  }

  void show(double **w, double **c, double **r, int n)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = i; j < n; j++)
      {
        cout << w[i][j] << "  " << c[i][j] << "  " << r[i][j] << " | ";
      }

      cout << endl;
    }
  }

  node *createTree(int i, int j, double **r, string *st)
  {
    if (i != j)
    {
      int k = r[i][j];
      node *t = new node(st[k]);
      t->lc = createTree(i, k - 1, r, st);
      t->rc = createTree(k, j, r, st);
      return (t);
    }
    else
    {
      return (NULL);
    }
  }

  node *getroot() { return root; }

  void preorder(node *root)
  {
    if (root)
    {
      cout << root->x << " ";
      preorder(root->lc);
      preorder(root->rc);
    }
  }

  void postorder(node *root)
  {
    if (root)
    {
      postorder(root->lc);
      postorder(root->rc);
      cout << root->x << " ";
    }
  }
};

int main()
{
  OBST s;
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;
  double *p = new double[n];
  double *q = new double[n + 1];
  string *st = new string[n + 1];
  cout << "Enter the keys:" << endl;
  for (int i = 1; i <= n; i++)
  {
    cin >> st[i];
  }
  cout << "Enter the probabilities of successful search:" << endl;
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
  }
  cout << "Enter the probabilities of unsuccessful search (including imaginary keys at beginning and end):" << endl;
  for (int i = 0; i <= n; i++)
  {
    cin >> q[i];
  }
  s.calculate_wt(p, q, n, st);
  s.preorder(s.getroot());
  s.postorder(s.getroot());
  delete[] p;
  delete[] q;
  delete[] st;
  return 0;
}