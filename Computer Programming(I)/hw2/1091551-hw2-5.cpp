#include <iostream>
using namespace std;
int main() {
    int number;
    
    while (cin >> number) {
        if (number == 0) {
            break;
        }
        cout << (number * (number + 1) * (number * 2 + 1)) / 6 << endl;
        

    }
    return 0;
}