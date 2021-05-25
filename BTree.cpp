#include <stdio.h>
#include <stdexcept>
#include <stdint.h>
#include "Tree.h"

int main()
{    
    string str;
    bool exit = false;
    Tree tree = Tree();
    while (!exit && getline(cin, str)) {
        int num = 0;
        char command = str[0];
        if (command == 'I') {
            if (str != "") {
                tree.setT(stoi(str.substr(2)));
            }
        }
        else if (command == 'A') {
            if (str != "") {
                tree.insert(stoi(str.substr(2)));
            }
        }
        else if (command == '?') {
            if (str != "") {
                cout << stoi(str.substr(2)) << " ";
                if (tree.search(stoi(str.substr(2)))) {
                    cout << "+" << endl;
                }
                else {
                    cout << "-" << endl;
                }
            }
        }
        else if (command == 'P') {
            tree.print();
        }
        else if (command == 'L') {
            if (str != "") {
                tree.setT(stoi(str.substr(2)));
            }
            string line;
            getline(cin, line);
            tree.load(line);
        }
        else if (command == 'S') {
            tree.printS();
        }
        else if (command == 'R') {
            if (str != "") {
                tree.remove(stoi(str.substr(2)));
            }
        }
        else if (command == '\\#') {
        }
        else if (command == 'C') {
            if (str != "") {
                tree.getCache(str.substr(2));
            }
        }
        else if (command == 'X') {
            tree.~Tree();
            exit = true;
        }
    }
}