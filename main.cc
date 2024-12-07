#include <iostream>
#include <string>
#include "avl_tree.h"

using namespace std;

void UserTest();

int main() {
   int T;
   std::cin >> T;
   for (int test_case = 1; test_case <= T; test_case++)
   {
      UserTest();
   }
}

void UserTest() {
   AvlTree<int> avltree;
   int Q;
   std::cin >> Q;
   
   for (int i = 0; i < Q; i++)
   {
      string command;
      std::cin >> command;

      if (command == "Insert") {
         int x;
         std::cin >> x;
         int result = avltree.Insert(x);
         std::cout << result << "\n";
      }

      else if (command == "Empty") {
         std::cout << avltree.Empty() << "\n";
      }

      else if (command == "Find") {
         int x;
         std::cin >> x;
         std::pair<Node<int>*, int> result = avltree.Find(x);
         std::cout << result.second  << "\n";
      }

      else if (command == "Size") {
         std::cout << avltree.Size() << "\n";
      }

      else if (command == "Rank") {
         int x;
         std::cin >> x;
         auto result = avltree.Rank(x);
         if (result.first == 0) {
             std::cout << "0\n";
         } else {
             std::cout << result.first << " " << result.second << "\n";
         }
      }

      else if (command == "Erase") {
         int x;
         std::cin >> x;
         int result = avltree.Erase(x);
         std::cout << result << "\n";
      }

      else if (command == "Height") {
         std::cout << avltree.Height() << "\n";
      }

      else if (command == "Ancestor") {
         int x;
         cin >> x;
         std::pair<int, int> result = avltree.Ancestor(x);
         std::cout << result.first << ' ' << result.second << "\n";
      }

      else if (command == "Average") {
         int x;
         cin >> x;
         cout << avltree.Average(x) << "\n";
      }

      else {
         cout << "Unknown command: " << command << "\n";
      }
   }
}