// Resources and collaboration:
// I used the textbook to understand hash tables and linked lists,
// worked with a friend to discuss the lab concepts, and used LLMs
// to help me understand the code and how the implementation works.
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int main() {
    int m;
    cin >> m;

    if (!cin || m <= 0) {
        return 0;
    }

    vector<list<int>> table(m);

    string command;

    while (cin >> command) {
        if (command == "e") {
            break;
        }

        if (command == "o") {
            for (int i = 0; i < m; ++i) {
                cout << i << ":";

                for (int key : table[i]) {
                    cout << key << "->";
                }

                cout << ";" << '\n';
            }

            continue;
        }

        char operation = command[0];
        int key = stoi(command.substr(1));
        int slot = key % m;

        list<int>& chain = table[slot];

        if (operation == 'i') {
            chain.push_front(key);
        }
        else if (operation == 's') {
            int position = 0;
            bool found = false;

            for (int value : chain) {
                if (value == key) {
                    cout << key << ":FOUND_AT"
                         << slot << "," << position << ";" << '\n';
                    found = true;
                    break;
                }

                position++;
            }

            if (!found) {
                cout << key << ":NOT_FOUND;" << '\n';
            }
        }
        else if (operation == 'd') {
            auto it = chain.begin();

            while (it != chain.end() && *it != key) {
                ++it;
            }

            if (it != chain.end()) {
                chain.erase(it);
                cout << key << ":DELETED;" << '\n';
            }
            else {
                cout << key << ":DELETE_FAILED;" << '\n';
            }
        }
    }

    return 0;
}
