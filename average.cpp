#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){

    double a;
    
    if(argc < 2){
        cout << "Please input numbers to find average.";
    }else{
    for(int i = 0; i < argc; i++){
        a += atoi(argv[i]);
    }
        cout << "---------------------------------\n";
        cout << "Average of " << argc-1 << " numbers = " << a/(argc-1) << endl;
        cout << "---------------------------------";
    }

    return 0;
}