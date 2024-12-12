/**
 * MIT License

Copyright (c) 2024 오픈소스응용프로그래밍 3분반 5팀

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "avl_tree.h"
#include <iostream>
#include <string>

using namespace std;

void UserTest();

int main() {
  int T;
  std::cin >> T;
  for (int test_case = 1; test_case <= T; test_case++) {
    UserTest();
  }
}

void UserTest() {
  AvlTree<int> avltree;
  int Q;
  std::cin >> Q;

  for (int i = 0; i < Q; i++) {
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
      std::pair<Node<int> *, int> result = avltree.Find(x);
      std::cout << result.second << "\n";
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