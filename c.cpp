//File for program utilities
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>
#include <cmath>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>    
using namespace std;

char intToChar(int number)
{
	string str = to_string(number);
	char const *num_char = str.c_str();
	return num_char[0];
}

int getHammingDistance(string first, string second)
{
	int len1 = first.size();
	int len2 = second.size();
	int _hammingDistance = 0;
	for(int i=0; i<min(len1, len2); i++){
		if(first[i] != second[i]){
			string j(1,first[i]);
			string k(1,second[i]);
			_hammingDistance += abs(stoi(j)-stoi(k));
		}
	}
	if(len1 != len2)
		_hammingDistance += abs(len1-len2);
	return _hammingDistance;
}

string decimalToBinary(int decimal) 
{
    string binary;
    while(decimal != 0) 
	{
		binary = ( decimal % 2 == 0 ? "0" : "1" ) + binary; 
		decimal /= 2;
	}
    return binary;
}

string fixedDecimalToBinary(int decimal, int size) 
{
    string binary = decimalToBinary(decimal);
	string zeros;
	int len = binary.length();
	for(int i=0; i<size-len; i++)
		zeros.push_back('0');
	return zeros.append(binary);
}

int binaryToDecimal(string binary){
	int decimal = stoi(binary, 0, 2);
	return decimal;
}

vector<int> getNearbyProbes(int key, int n, int size)
{
	string strkey = fixedDecimalToBinary(key, size);
	int len = strkey.length(); 
	int counter = 1;
	int replaced = 0;
	int hammingDistance = 1;
	vector<string> _nearbyProbes;
	_nearbyProbes.push_back(strkey);
	while(counter<n){
		string probe = strkey;
		for(int i=0; i<len; i++){
			if(probe[i] == '0')
				probe[i]='1';
			else if(probe[i] == '1')
				probe[i]='0';
			replaced++;
			if(replaced==hammingDistance && counter<=n){
				cout << counter << " " << probe << endl;
				if(find(_nearbyProbes.begin(), _nearbyProbes.end(), probe)==_nearbyProbes.end()){
					_nearbyProbes.push_back(probe);
					counter++;
					probe = strkey;
				}
				replaced = 0;
				// break;
			}
			else if(counter>n)
				break;
		}
		hammingDistance++;
	}

	int _size = _nearbyProbes.size();
	vector<int> nearbyProbes;
	for(int i=0; i<_size; i++)
		nearbyProbes.push_back(binaryToDecimal(_nearbyProbes[i]));
	return nearbyProbes;
}

int main(int argc, char *argv[]){
	vector<int> nearbyProbes = getNearbyProbes(3862, 19, 15);
	// cout << fixedDecimalToBinary(3862,15) << endl;
	// for(int i=0; i<nearbyProbes.size(); i++)
	// 	cout << fixedDecimalToBinary(nearbyProbes[i],15) << endl;
}	