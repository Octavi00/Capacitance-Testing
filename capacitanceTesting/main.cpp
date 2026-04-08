#include <iostream>
#include "cpp/unitTest.h"
 using namespace std;

//im using lldb to debug, must install extension CodeLLDB in vscode, and set the launch.json to use lldb, and set the program path to the compiled executable file

void print(string s) {  cout << s << endl;   }

int main() {
    print("This is going to be interesting");

    //call unitTests mainTesting function
    mainTest();
}

