#include <iostream>
#include <ctime>
#include <cstring>
#include <utils.hpp>
#include <hash_functions.hpp>

using namespace std;

// να τρεχει με παραμετρους απο την γραμμή εντολών ή να τους δίνει διαδραστικά κατα την εκτέλεση
// στο τέλος θα διερωτάται ο χρήστης αν θέλει να τερματίσει ή να επαναλάβει με διαφορετικές παραμέτρους όπου ξαναχτίζω
 
int main(int argc, char *argv[]){
    
    srand((time(0)));

    string input_file; //-i
    string query_file; //-q
    string output_file; //-o 
    string number_of_nearest; //-N
    int k = 4; //-k
    int L = 5; //-L
    int N = 1; //-N
    int R = 10000; //-R

    read_parameters(argv);

    cout << "Hello World!";
    return 0;
}