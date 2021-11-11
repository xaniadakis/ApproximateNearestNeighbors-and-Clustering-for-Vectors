//File for LSH implementation
#include "lsh.hpp"
#include <chrono>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
	float R = 10000; //-R


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

	while (true)
	{
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

		vector<vector<float>> vectors;
		vector<string> ids;
		read_file(input_file,vectors,ids);
		LSH lsh(vectors,k,L,L2);

		struct stat info;
		if (stat("./output",&info) == -1) {
			mkdir("./output", 0700);
		}
		ofstream outfile ("./output/" + output_file, ios::out | ios::trunc);

		vector<vector<float>> vectors_query;
		vector<string> ids_query;
		read_file(query_file,vectors_query,ids_query);
		unsigned int n_query=ids_query.size();
		for (unsigned int i=0 ; i<n_query ; i++)
		{
			auto start_lsh = chrono::high_resolution_clock::now();
			vector<pair<float,unsigned int>> N_Nearest = lsh.find_N_nearest(vectors_query[i],N);
			auto stop_lsh = chrono::high_resolution_clock::now();
			auto elapsed_lsh = stop_lsh - start_lsh ;
			double time_lsh = chrono::duration<double>(elapsed_lsh).count();


			vector<pair<float,unsigned int>> R_Nearest = lsh.find_R_nearest(vectors_query[i],R);

			auto start_true = chrono::high_resolution_clock::now();
			vector<pair<float,unsigned int>> True_N_Nearest = exhaustive_search(vectors_query[i],vectors,N,&eucledian_distance);
			auto stop_true = chrono::high_resolution_clock::now();
			auto elapsed_true = stop_true - start_true ;
			double time_true = chrono::duration<double>(elapsed_true).count();

			write_file(outfile,ids_query[i],vectors,ids,N_Nearest,R_Nearest,True_N_Nearest,time_lsh,time_true,"LSH");
		}

		outfile.close();
		

		string option;
		cout << "Enter /exit to exit program.\n";
		cout << "Enter /rerun to rerun program with new options.\n";
		while (true)
		{   
			cin >> option;
			if (option.compare("/rerun")==0)
			{
				input_file.clear();
				query_file.clear();
				output_file.clear();
				break;
			}
			if(option.compare("/exit")==0)
			{
				exit(0);
			}
		}
	}
}