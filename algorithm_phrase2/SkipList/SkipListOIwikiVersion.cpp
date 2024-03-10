#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
struct SkipListNode {
  int level;
  K key;
  V value;
  SkipListNode **forward;

  SkipListNode() {}

  SkipListNode(K k, V v, int l, SkipListNode *nxt = NULL) {
    key = k;
    value = v;
    level = l;
    forward = new SkipListNode *[l + 1];
    for (int i = 0; i <= l; ++i) forward[i] = nxt;
  }

  ~SkipListNode() {
    if (forward != NULL) delete[] forward;
  }
};

template <typename K, typename V>
struct SkipList {
  static const int MAXL = 32;
  static const int P = 4;
  static const int S = 0xFFFF;
  static const int PS = S / P;
  static const int INVALID = INT_MAX;

  SkipListNode<K, V> *head, *tail;
  int length;
  int level;

  SkipList() {
    srand(time(0));

    level = length = 0;
    tail = new SkipListNode<K, V>(INVALID, 0, 0);
    head = new SkipListNode<K, V>(INVALID, 0, MAXL, tail);
  }

  ~SkipList() {
    delete head;
    delete tail;
  }

  int randomLevel() {
    int lv = 1;
    while ((rand() & S) < PS) ++lv;
    return MAXL > lv ? lv : MAXL;
  }

  void insert(const K &key, const V &value) {
    SkipListNode<K, V> *update[MAXL + 1];

    SkipListNode<K, V> *p = head;
    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
      update[i] = p;
    }
    p = p->forward[0];

    if (p->key == key) {
      p->value = value;
      return;
    }

    int lv = randomLevel();
    if (lv > level) {
      lv = ++level;
      update[lv] = head;
    }

    SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
    for (int i = lv; i >= 0; --i) {
      p = update[i];
      newNode->forward[i] = p->forward[i];
      p->forward[i] = newNode;
    }

    ++length;
  }

  bool erase(const K &key) {
    SkipListNode<K, V> *update[MAXL + 1];
    SkipListNode<K, V> *p = head;

    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
      update[i] = p;
    }
    p = p->forward[0];

    if (p->key != key) return false;

    for (int i = 0; i <= level; ++i) {
      if (update[i]->forward[i] != p) {
        break;
      }
      update[i]->forward[i] = p->forward[i];
    }

    delete p;

    while (level > 0 && head->forward[level] == tail) --level;
    --length;
    return true;
  }

  V &operator[](const K &key) {
    V v = find(key);
    if (v == tail->value) insert(key, 0);
    return find(key);
  }

  V &find(const K &key) {
    SkipListNode<K, V> *p = head;
    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
    }
    p = p->forward[0];
    if (p->key == key) return p->value;
    return tail->value;
  }

  bool count(const K &key) { return find(key) != tail->value; }
};

int main() {
//   SkipList<int, int> L;
//   map<int, int> M;

//   clock_t s = clock();

//   for (int i = 0; i < 1e5; ++i) {
//     int key = rand(), value = rand();
//     L[key] = value;
//     M[key] = value;
//   }

//   for (int i = 0; i < 1e5; ++i) {
//     int key = rand();
//     if (i & 1) {
//       L.erase(key);
//       M.erase(key);
//     } else {
//       int r1 = L.count(key) ? L[key] : 0;
//       int r2 = M.count(key) ? M[key] : 0;
//       assert(r1 == r2);
//     }
//   }

//   clock_t e = clock();
//   cout << "Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << endl;
//   // about 0.2s
 SkipList<int,int> sl;
    std::map<int,int> m; 
    clock_t s=clock();
    for(int i=0;i<100000;i++){
        int key=rand(),val=rand();
        sl[key]=val;
    }
    for(int i=0;i<100000;i++){
        int key=rand();
        if(i&1)sl.erase(key);
    }
    clock_t e=clock();
    std::cout<<"Performance of SkipList:"<<(double)(e-s)<<std::endl;
    s=clock();
    for(int i=0;i<1e5;i++){
        int key=rand(),val=rand();
        m[key]=val;
    }
    for(int i=0;i<1e5;i++){
        int key=rand();
        if(i&1)m.erase(key);
    }
    e=clock();
    std::cout<<"Performance of built-in map:"<<(double)(e-s)<<std::endl;
  return 0;
}