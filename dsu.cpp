#include <iostream>
#include <random>
#include <vector>
#include <cassert>

using namespace std;

struct Node {
  int rank = 0;
  int size = 1;
  int id = -1;
  Node* parent = 0;
  Node (int id): id(id), parent(this) {}
};

class DSU {
private:
  
  int n;
  vector <Node*> dsu;
  mt19937 rng;
  
  Node* find (Node*& u) {
    return u -> parent = (u -> parent -> id == u -> id) ? u : find(u -> parent);
  }

public:
  
  DSU (int n): n(n) {
    for (int i = 0; i <= n; i++) {
      rng.seed(random_device()());
      dsu.push_back(new Node(i));
    }
  }
  
  int find (int u) {
    assert(1 <= u and u <= n);
    return find(dsu[u]) -> id;
  }
  
  void joinRandom (int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return;
    if (rng() % 2) swap(x, y);
    dsu[x] -> parent = dsu[y];
  }
  
  void joinRank (int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return;
    if (dsu[x] -> rank < dsu[y] -> rank) swap(x, y);
    dsu[y] -> parent = dsu[x];
    if (dsu[x] -> rank == dsu[y] -> rank) dsu[x] -> rank++;
  }
  
  void joinSize (int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return;
    if (dsu[x] -> size < dsu[y] -> size) swap(x, y);
    dsu[y] -> parent = dsu[x];
    dsu[x] -> size += dsu[y] -> size;
  }
  
  void print () {
    cout << "Nodo -> parent" << endl;
    for (int i = 1; i <= n; i++) {
      cout << i << ' ' << find(i) << endl; 
    }
  }
};

int main () {
  vector <pair <int, int>> test = {
    {1, 2}, {3, 4}, {3, 5}, {1, 7}, {3, 6}, {8, 9},
    {1, 8}, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {14, 15},
    {16, 1}, {14, 16}, {1, 3}, {1, 4}
  };
  cout << "Union arbitraria" << endl;
  DSU dsuA(16);
  for (auto pp: test) {
    dsuA.joinRandom(pp.first, pp.second);
  }
  dsuA.print();
  
  cout << "Union por rank" << endl;
  DSU dsuB(16);
  for (auto pp: test) {
    dsuB.joinRank(pp.first, pp.second);
  }
  dsuB.print();

  cout << "Union por tamaño" << endl;
  DSU dsuC(16);
  for (auto pp: test) {
    dsuC.joinSize(pp.first, pp.second);
  }
  dsuC.print();
  return (0);
}
