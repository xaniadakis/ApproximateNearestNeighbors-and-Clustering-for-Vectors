//File for cube implementation
#include "cube.hpp"

// να τρεχει με παραμετρους απο την γραμμή εντολών ή να τους δίνει διαδραστικά κατα την εκτέλεση
// στο τέλος θα διερωτάται ο χρήστης αν θέλει να τερματίσει ή να επαναλάβει με διαφορετικές παραμέτρους όπου ξαναχτίζω
 
int main(int argc, char *argv[]){
	
	srand((time(0)));


    //./cube –i<input  file> –q  <query  file> –k  <int> -M  <int> -probes  <int> -ο<output file> -Ν<number of nearest> -R <radius>
	
    string input_file; //-i
	string query_file; //-q
	string output_file; //-o
	int k = 14; //-k
	int M = 10; //-M
	int probes = 2; //-probes
    int N = 1;//-N
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
		case 'M':
			M_flag=1;
			M=std::stoi(optarg);
			break;
        case 'probes':
			probes_flag=1;
			probes=std::stoi(optarg);
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

	cube c(input_file,k,M,&eucledian_distance);

	string option;
	cout << "Enter /exit to exit program.\n";
	cout << "Enter /rerun to rerun program with new options.\n";

	while (option.compare("/exit")!=0)
	{   
		cin >> option;
	}
	return 0;
}