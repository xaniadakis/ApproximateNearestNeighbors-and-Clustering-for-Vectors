//File for LSH implementation
#include "lsh.hpp"

// να τρεχει με παραμετρους απο την γραμμή εντολών ή να τους δίνει διαδραστικά κατα την εκτέλεση
// στο τέλος θα διερωτάται ο χρήστης αν θέλει να τερματίσει ή να επαναλάβει με διαφορετικές παραμέτρους όπου ξαναχτίζω
 
int main(int argc, char *argv[]){
	srand((time(0)));

	string input_file; //-i
	string query_file; //-q
	string output_file; //-o
	int k = 4; //-k
	int L = 5; //-L
	unsigned int N = 1; //-N
	double R = 10000; //-R


	int k_flag=0,L_flag=0;

	//Read given arguments 
	int c;
	while ((c = getopt (argc, argv, "i:q:k:L:o:N:R:")) != -1)
	{
		switch (c)
		{
		case 'i':
			input_file = optarg;
			break;
		case 'q':
			query_file = optarg;
			break;
		case 'k':
			k_flag=1;
			k=std::stoi(optarg);
			break;
		case 'L':
			L_flag=1;
			L=std::stoi(optarg);
			break;
		case 'o':
			output_file = optarg;
			break;
		case 'N':
			N = std::stoi(optarg);
			break;
		case 'R':
			R = std::stof(optarg);
			break;
		default:
			exit (1);
		}
	}

	//k and L arguments not provided,use default values
	if (k_flag==0 || L_flag==0)
	{
		k = 4; //-k
		L = 5; //-L
		N = 1; //-N
		R = 10000; //-R
	}


	while(input_file.empty())
	{
		cout<<"Enter input file location: ";
		cin >> input_file;
	}
	while (query_file.empty())
	{
		cout<<"Enter query file location: ";
		cin >> query_file;
	}
	while (output_file.empty())
	{
		cout<<"Enter output file location: ";
		cin >> output_file;
	}

	LSH lsh(input_file,k,L,L2);
	lsh.query(query_file,output_file,N,R);

	string option;
	cout << "Enter /exit to exit program.\n";
	cout << "Enter /rerun to rerun program with new options.\n";
	while (option.compare("/exit")!=0)
	{   
		cin >> option;
	}
	return 0;
}