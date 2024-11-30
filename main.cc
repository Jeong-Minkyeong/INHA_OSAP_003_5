#include "avl_tree.h"
#include <iostream>
#include <string>

using namespace std;

void UserTest();

int main() {
  int T;
  cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    UserTest();
  }
}

void UserTest() {
  AvlTree<int> avltree;
  int Q;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    string command;
    cin >> command;

    if (command == "insert") {
      int x;
      cin >> x;
      cout << avltree.Insert(x);
      << "\n";
    }

    else if (command == "erase") {
      int x;
      cin >> x;
      cout << avltree.Erase(x) << "\n";
    }

    else if (command == "empty") {
      avltree.Empty();
    }

    else if (command == "find") {
      int x;
      cin >> x;
      cout << avltree.Find(x) << "\n";
    }

    else if (command == "size") {
      avltree.Size();
    }

    else if (command == "rank") {
      int x;
      cin >> x;
      cout << avltree.Rank(x) << "\n";
    }

    /**
    else if (command == "average") {
            int x;
            cin >> x;
            avltree.Average(x);
    }
    */
  }
}
