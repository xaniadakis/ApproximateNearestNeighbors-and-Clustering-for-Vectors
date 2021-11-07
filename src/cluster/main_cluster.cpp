#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <getopt.h>

#include "cluster.hpp"

using namespace std;

void write_file_cluster(ofstream &outfile,vector<cluster::centroid> centroids,vector<pair<vector<float>,float>> silhouettes,double time_cluster,string algorithm)
{

}

int main(int argc, char *argv[]){
	srand((time(0)));

	string input_file; //-i
	string output_file; //-o
    int complete = false;//-complete
    string method = "Classic";//-m

    string configuration_file; //-c
    int K_cluster;
    int L_lsh=3;
    int k_lsh=4;
    int M_cube=10;
    int k_cube=3;
    int probes_cube=2;

    bool K_flag=false;

	//Read given arguments 
	int c;

	struct option long_opt[] =
	{
		{"complete",no_argument,NULL,'l'},
		{NULL,0,NULL,0}
	};
	while ((c = getopt_long_only(argc, argv, "i:c:o:m:l",long_opt,NULL)) != -1)
	{
		switch (c)
		{
		case 'i':
			input_file = optarg;
			break;
		case 'c':
			configuration_file = optarg;
			break;
		case 'o':
			output_file = optarg;
			break;
		case 'm':
			method= optarg;
			break;
		case 'l':
			complete = true;
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
	while (configuration_file.empty())
	{
		cout<<"Enter configuration file location: ";
		cin >> configuration_file;
	}
	while (output_file.empty())
	{
		cout<<"Enter output file location: ";
		cin >> output_file;
	}

    //Read configuration file
    ifstream  file(configuration_file);
	string  line;
	while(getline(file, line))
	{
        string key;
        istringstream is_line(line);
        if(getline(is_line, key, ':'))
        {
            int value;
            is_line >> value;
            
            if(key=="number_of_clusters")
            {
                K_cluster=value;
                K_flag=true;
            }
            else if (key=="number_of_vector_hash_tables")
                L_lsh=value;
            else if (key=="number_of_vector_hash_functions")
                k_lsh=value;
            else if (key=="max_number_M_hypercube")
                M_cube=value;
            else if (key=="number_of_hypercube_dimensions")
                k_cube=value;
            else if (key=="number_of_probes")
                probes_cube=value;
        }
	}

	if(K_flag==false)
        exit(1);
	
	vector<vector<float>> vectors;
	vector<string> ids;
	read_file(input_file,vectors,ids);

	if(method=="Classic")
	{
		cout << "Using k-means clustering with Lloyd's assignment" << endl;
		auto start_cluster = chrono::high_resolution_clock::now();
		cluster_lloyds(K_cluster,vectors,ids);
		auto stop_cluster = chrono::high_resolution_clock::now();
		auto elapsed_cluster = stop_cluster - start_cluster ;
		double time_cluster = chrono::duration<double>(elapsed_cluster).count();
	}
	else if(method=="LSH" || method=="Hypercube")
	{
		cout << "Using k-means clustering with Approximate Reverse Approach using " << method << endl;
		auto start_cluster = chrono::high_resolution_clock::now();
		cluster_ANN(K_cluster,vectors,ids,method,K,k,M,L);
		auto stop_cluster = chrono::high_resolution_clock::now();
		auto elapsed_cluster = stop_cluster - start_cluster ;
		double time_cluster = chrono::duration<double>(elapsed_cluster).count();
	}

	string option;
	cout << "Enter /exit to exit program.\n";
	cout << "Enter /rerun to rerun program with new options.\n";
	while (option.compare("/exit")!=0)
	{   
		cin >> option;
	}
	return 0;
}