#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "cluster.hpp"

using namespace std;

void write_file_cluster(ofstream &outfile,vector<cluster::centroid> centroids,pair<vector<float>,float> silhouettes,vector<string> ids,double time_cluster,string algorithm,bool complete)
{
	outfile << "Algorithm: " << algorithm << endl;
	for (int i = 0; i < centroids.size(); i++)
	{
		outfile<<"CLUSTER-"<<i+1;
		outfile<<" {size: "<<centroids[i].vectors.size();
		outfile<<", centroid: ";
		
		outfile<<"[";
		for(auto it = centroids[i].coordinates.begin(); it != centroids[i].coordinates.end(); ++it)
		{
			outfile<<*it;
			if(next(it,1)!=centroids[i].coordinates.end()) outfile<<",";
		}
		outfile<<"]}"<<endl;
	}

	outfile << "clustering_time: " << time_cluster << endl;
	outfile << "Silhouette: [";
	for(auto it = silhouettes.first.begin(); it < silhouettes.first.end(); ++it)
	{
		outfile<<*it<<",";
	}
	outfile<<silhouettes.second<<"]"<<endl;

	if(complete)
	{
		for (int i = 0; i < centroids.size(); i++)
		{
			outfile<<"CLUSTER-"<<i+1;
			outfile<<" { ";
			outfile<<"[";
			for(auto it = centroids[i].coordinates.begin(); it != centroids[i].coordinates.end(); ++it)
			{
				outfile<<*it;
				if(next(it,1)!=centroids[i].coordinates.end()) outfile<<",";
			}
			outfile<<"]";

			for(auto it = centroids[i].vectors.begin(); it != centroids[i].vectors.end(); ++it)
			{
				outfile<<", "<<ids[it->index];
			}
			outfile<<"}"<<endl;
		}
	}
}

int main(int argc, char *argv[]){
	srand((time(0)));

	string input_file; //-i
	string output_file; //-o
    int complete = false;//-complete
    string method = "Hypercube";//-m

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

	struct stat info;
	if (stat("./output",&info) == -1) {
		mkdir("./output", 0700);
	}
	ofstream outfile ("./output/" + output_file, ios::out | ios::trunc);
	
	if(method=="Classic")
	{
		cout << "Using k-means clustering with Lloyd's assignment" << endl;
		auto start_cluster = chrono::high_resolution_clock::now();
		cluster_lloyds cluster(K_cluster,vectors,ids);
		auto stop_cluster = chrono::high_resolution_clock::now();
		auto elapsed_cluster = stop_cluster - start_cluster ;
		double time_cluster = chrono::duration<double>(elapsed_cluster).count();
		write_file_cluster(outfile,cluster.get_clusters(),cluster.get_silhouettes_average(),ids,time_cluster,"Lloyds",complete);
	}
	else if(method=="Hypercube")
	{
		cout << "Using k-means clustering with Approximate Reverse Approach using " << method << " method" << endl;
		auto start_cluster = chrono::high_resolution_clock::now();
		cluster_cube cluster(vectors,ids,K_cluster,k_cube,probes_cube,M_cube);
		auto stop_cluster = chrono::high_resolution_clock::now();
		auto elapsed_cluster = stop_cluster - start_cluster ;
		double time_cluster = chrono::duration<double>(elapsed_cluster).count();
		write_file_cluster(outfile,cluster.get_clusters(),cluster.get_silhouettes_average(),ids,time_cluster,"Hypercube",complete);
	}
	else if(method=="LSH")
	{
		cout << "Using k-means clustering with Approximate Reverse Approach using " << method << endl;
		auto start_cluster = chrono::high_resolution_clock::now();
		cluster_lsh cluster(vectors,ids,K_cluster,k_lsh,L_lsh);
		auto stop_cluster = chrono::high_resolution_clock::now();
		auto elapsed_cluster = stop_cluster - start_cluster ;
		double time_cluster = chrono::duration<double>(elapsed_cluster).count();
		write_file_cluster(outfile,cluster.get_clusters(),cluster.get_silhouettes_average(),ids,time_cluster,"LSH",complete);
	}

	outfile.close();
	exit(0);
}