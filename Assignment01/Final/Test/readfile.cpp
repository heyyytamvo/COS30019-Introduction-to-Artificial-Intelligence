#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main() {
    ifstream inputFile("input.txt"); // open the file
    if (!inputFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    string line;
    // read the first line
    if (getline(inputFile, line)) {
        cout << "First line: " << line << endl;
    }

    // read the second line
    if (getline(inputFile, line)) {
        cout << "Second line: " << line << endl;
    }

    // read the third line
    if (getline(inputFile, line)) {
        cout << "Third line: " << line << std::endl;
    }

    inputFile.close(); // close the file

    return 0;
}