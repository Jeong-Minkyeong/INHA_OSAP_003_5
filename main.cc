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

    if (command == "Insert") {
      int x;
      cin >> x;
      cout << avltree.Insert(x) << "\n";
    }

    else if (command == "Erase") {
      int x;
      cin >> x;
      cout << avltree.Erase(x) << "\n";
    }

    else if (command == "Empty") {
      avltree.Empty();
    }

    else if (command == "Find") {
      int x;
      cin >> x;
      cout << avltree.Find(x) << "\n";
    }

    else if (command == "Size") {
      avltree.Size();
    }

   /*
    else if (command == "Rank") {
      int x;
      cin >> x;
      cout << avltree.Rank(x) << "\n";
    }
 */
    
    else if (command == "Average") {
            int x;
            cin >> x;
            cout << avltree.Average(x) << "\n";
    }
    
    
    else if (command == "Ancestor") {
            int x;
            cin >> x;
            cout << avltree.Ancestor(x).first << " " << avltree.Ancestor(x).second << "\n";
    }
    
  }
}
