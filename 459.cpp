#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <set>

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
    assert(0 <= u and u <= n);
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
  string line;
  getline(cin, line);
  int tc;
  sscanf(line.c_str(), "%d", &tc);
  getline(cin, line);
  while (tc--) {
    getline(cin, line);
    char ch;
    sscanf(line.c_str(), "%c", &ch);
    int n = ch - 'A' + 1;
    DSU dsu(n);
    while (getline(cin, line) and not line.empty()) {
      char a = line[0], b = line[1];
      dsu.joinSize(a - 'A', b - 'A');
    }
    set <int> st;
    for (int i = 0; i < n; i++) st.insert(dsu.find(i));
    cout << int(st.size()) << endl;
    if (tc) cout << endl;
  }
  return (0);
}
