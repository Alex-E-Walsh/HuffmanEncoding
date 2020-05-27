
#include "huffmantree.h"
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char** argv) {

int num;
char choice;
ifstream inFile;
ofstream outFile;
string infilename = "", outfilename = "", Bits = "", BitsS = "", mn = "";

int osize = 0;

cout<< "Would you like to (e)Encode or (d)Decode a file?" << endl;
cout<< "Enter your choice (e) or (d)";
cin >> choice;

userInterface(choice){
case 'e';

cout << "What is the name of the file you want to encode?:"<< endl;
cin >> infilename;

outfilename = "newEncodedFile.txt";

cout<< "Name of Input File: " << infilename << endl;
cout << "Name of Output File: " << outfilename << endl;

inFile.open(infilename);

//checks to see if inFile opens, if file doesn't exists it fails and exits
if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
}


HuffmanEncoder* encoded = HuffmanTree::HuffmanEncoder(inFile); //taking inFile and constructing a HuffmanEncoder tree hopefully

//encoding it?

outFile.open(outFile.c_str());

outFile << encoded.writeEncodedText(); << endl;


break;

case 'd';

cout << "What is the name of the file you want to decode?:"<< endl;
cin >> infilename;

outfilename = "newDecodedFile.txt";

cout<< "Name of Input File: " << infilename << endl;
cout << "Name of Output File: " << outfilename << endl;


inFile.open(infilename);

//checks to see if inFile opens, if file doesn't exists it fails and exits
if (!inFile) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
}

HuffmanDecoder decoded = HuffmanTree::HuffmanDecoder(inFile);

outFile.open(outFile.c_str());

outFile << decoded.writeEncodedText(); <<endl;

}


}
