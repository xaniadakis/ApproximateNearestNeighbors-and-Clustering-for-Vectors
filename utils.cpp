#include <iostream>
#include <cstring>

void read_parameters(char *argv[]) {

    string input_file; //-i
    string query_file; //-q
    int k = 4; //-k
    int L = 5; //-L
    int N = 1; //-N
    int R = 10000; //-R
    string output_file; //-o 
    string number_of_nearest; //-N

    if(!strcmp("-i", argv[1]))
        input_file=atoi(argv[2]);
    else if(!strcmp("-i", argv[3]))
        input_file=atoi(argv[4]);
    else if(!strcmp("-i", argv[5]))
        input_file=atoi(argv[6]);
    else if(!strcmp("-i", argv[7]))
        input_file=atoi(argv[8]);
    else if(!strcmp("-i", argv[9]))
        input_file=atoi(argv[10]);
    else if(!strcmp("-i", argv[11]))
        input_file=atoi(argv[12]);
    else if(!strcmp("-i", argv[13]))
        input_file=atoi(argv[14]);
    else if(!strcmp("-i", argv[15]))
        input_file=atoi(argv[16]);

    if(!strcmp("-q", argv[1]))
        query_file=atoi(argv[2]);
    else if(!strcmp("-q", argv[3]))
        query_file=atoi(argv[4]);
    else if(!strcmp("-q", argv[5]))
        query_file=atoi(argv[6]);
    else if(!strcmp("-q", argv[7]))
        query_file=atoi(argv[8]);
    else if(!strcmp("-q", argv[9]))
        query_file=atoi(argv[10]);
    else if(!strcmp("-q", argv[11]))
        query_file=atoi(argv[12]);
    else if(!strcmp("-q", argv[13]))
        query_file=atoi(argv[14]);
    else if(!strcmp("-q", argv[15]))
        query_file=atoi(argv[16]);

    if(!strcmp("-k", argv[1]))
        k=atoi(argv[2]);
    else if(!strcmp("-k", argv[3]))
        k=atoi(argv[4]);
    else if(!strcmp("-k", argv[5]))
        k=atoi(argv[6]);
    else if(!strcmp("-k", argv[7]))
        k=atoi(argv[8]);
    else if(!strcmp("-k", argv[9]))
        k=atoi(argv[10]);
    else if(!strcmp("-k", argv[11]))
        k=atoi(argv[12]);
    else if(!strcmp("-k", argv[13]))
        k=atoi(argv[14]);
    else if(!strcmp("-k", argv[15]))
        k=atoi(argv[16]);

    if(!strcmp("-L", argv[1]))
        L=atoi(argv[2]);
    else if(!strcmp("-L", argv[3]))
        L=atoi(argv[4]);
    else if(!strcmp("-L", argv[5]))
        L=atoi(argv[6]);
    else if(!strcmp("-L", argv[7]))
        L=atoi(argv[8]);
    else if(!strcmp("-L", argv[9]))
        L=atoi(argv[10]);
    else if(!strcmp("-L", argv[11]))
        L=atoi(argv[12]);
    else if(!strcmp("-L", argv[13]))
        L=atoi(argv[14]);
    else if(!strcmp("-L", argv[15]))
        L=atoi(argv[16]);

    if(!strcmp("-o", argv[1]))
        output_file=atoi(argv[2]);
    else if(!strcmp("-o", argv[3]))
        output_file=atoi(argv[4]);
    else if(!strcmp("-o", argv[5]))
        output_file=atoi(argv[6]);
    else if(!strcmp("-o", argv[7]))
        output_file=atoi(argv[8]);
    else if(!strcmp("-o", argv[9]))
        output_file=atoi(argv[10]);
    else if(!strcmp("-o", argv[11]))
        output_file=atoi(argv[12]);
    else if(!strcmp("-o", argv[13]))
        output_file=atoi(argv[14]);
    else if(!strcmp("-o", argv[15]))
        output_file=atoi(argv[16]);

    if(!strcmp("-N", argv[1]))
        number_of_nearest=atoi(argv[2]);
    else if(!strcmp("-N", argv[3]))
        number_of_nearest=atoi(argv[4]);
    else if(!strcmp("-N", argv[5]))
        number_of_nearest=atoi(argv[6]);
    else if(!strcmp("-N", argv[7]))
        number_of_nearest=atoi(argv[8]);
    else if(!strcmp("-N", argv[9]))
        number_of_nearest=atoi(argv[10]);
    else if(!strcmp("-", argv[11]))
        number_of_nearest=atoi(argv[12]);
    else if(!strcmp("-N", argv[13]))
        number_of_nearest=atoi(argv[14]);
    else if(!strcmp("-N", argv[15]))
        number_of_nearest=atoi(argv[16]);


    if(!strcmp("-R", argv[1]))
        R=atoi(argv[2]);
    else if(!strcmp("-R", argv[3]))
        R=atoi(argv[4]);
    else if(!strcmp("-R", argv[5]))
        R=atoi(argv[6]);
    else if(!strcmp("-R", argv[7]))
        R=atoi(argv[8]);
    else if(!strcmp("-R", argv[9]))
        R=atoi(argv[10]);
    else if(!strcmp("-R", argv[11]))
        R=atoi(argv[12]);
    else if(!strcmp("-R", argv[13]))
        R=atoi(argv[14]);
    else if(!strcmp("-R", argv[15]))
        R=atoi(argv[16]);

}