//File for cube implementation
#include "cube.hpp"
#include <chrono>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>

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

	//handle given parameters 
	int c;

	struct option long_opt[] =
	{
		{"probes",required_argument,NULL,'p'},
		{NULL,0,NULL,0}
	};
	while ((c = getopt_long_only(argc, argv, "i:q:k:M:p:o:N:R:",long_opt,NULL)) != -1)
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
			k=std::stoi(optarg);
			break;
		case 'M':
			M=std::stoi(optarg);
			break;
        case 'p':
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

		//handle input file 
		vector<vector<float>> vectors;
		vector<string> ids;

		read_file(input_file,vectors,ids);
		Cube cube(vectors,ids,k,M,probes,L2);

		//handle output file
		struct stat info;
		if (stat("./output",&info) == -1) {
			mkdir("./output", 0700);
		}
		ofstream outfile ("./output/" + output_file, ios::out | ios::trunc);

		//handle queries
		vector<vector<float>> vectors_query;
		vector<string> ids_query;

		read_file(query_file,vectors_query,ids_query);
		unsigned int n_query=ids_query.size();

		for (unsigned int i=0 ; i<n_query ; i++)
		{
			auto start_cube = chrono::high_resolution_clock::now();
			vector<pair<float,unsigned int>> N_Nearest = cube.find_N_nearest(vectors_query[i],N);
			auto stop_cube = chrono::high_resolution_clock::now();
			auto elapsed_cube = stop_cube - start_cube ;
			double time_cube = chrono::duration<double>(elapsed_cube).count();

			vector<pair<float,unsigned int>> R_Nearest = cube.find_R_nearest(vectors_query[i],R);

			auto start_true = chrono::high_resolution_clock::now();
			vector<pair<float,unsigned int>> True_N_Nearest = exhaustive_search(vectors_query[i],vectors,N,&eucledian_distance);
			auto stop_true = chrono::high_resolution_clock::now();
			auto elapsed_true = stop_true - start_true;
			double time_true = chrono::duration<double>(elapsed_true).count();
			write_file(outfile,ids_query[i],vectors,ids,N_Nearest,R_Nearest,True_N_Nearest,time_cube,time_true,"Cube");
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