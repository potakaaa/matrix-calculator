#include <iostream>
using namespace std;

string print_backward(string txt, int size, string& rev) {
    if (size == 0) {
        return rev;
    } 
    cout << "text: " << txt[size-1] << endl;
    rev += txt[size-1];
    return print_backward(txt, size-1, rev);
}

int main() {
    string r = "";
    string txt = "2 x 1";
    cout << print_backward("2 x 1", txt.length(), r);
}