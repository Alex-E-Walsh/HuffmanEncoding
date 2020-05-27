#include <iostream>
#include <map>
#include <queue>
#include "bitstream.h"
using namespace std;




class HuffmanTree {
 private:
  class Huffnode {
   public:
    Huffnode* zero, *one, *parent;
    char symbol;
    float weight;
   public:
    //huffnode constructor.
    Huffnode(char sym, int freq) :
      zero(NULL), one(NULL), parent(NULL), symbol(sym), weight(freq) { }

    //huffnode merge constructor
    Huffnode(Huffnode* child1, Huffnode* child2) :
      zero(child1), one(child2), parent(NULL), symbol('\0'), weight(0) {
      if (child1 != NULL) {
        weight += child1->weight;
        child1->parent = this;
      }
      if (child2 != NULL) {
        weight += child2->weight;
        child2->parent = this;
      }
    }

  };

 Huffnode* root;
 public:

	HuffmanTree(istream& stream){ // read the stream
	   priority_queue<pair<float, Huffnode*> > queue;

	while(stream.tellg() != stream.end){
     string type;
     stream >> type; //read if node or leaf
	 stream.get(); //read the space char

     int freq;
     string sfreq;

		if(type == "LEAF:"){
			string symbol;
      		stream.getline(stream, symbol); //read the symbol and assign it to var symbol
      		stream.get(); //read space char
      		stream.getline(stream, sfreq); //read the freq string and assing to to sfreq
			stoi(sfreq, freq); // convert string sfreq to float
      		Huffnode* node = new Huffnode(symbol, freq);
		}

		else{ // is a node
			stream.getline(stream, sfreq); //read the freq string
      		stoi(sfreq, freq);
      		Huffnode* node = new Huffnode('\0', freq);
		}
    queue.push(pair<float, Huffnode*> (freq, node));

	}

	typename map<char, float>::const_iterator var;
	for(var = tree.begin(); var != tree.end(); ++var){
	   Huffnode *one = new Huffnode((*var).first, (*var).second);
	   queue.push(pair<float, Huffnode*>((*var).second, one));
	}

	while(!q.empty()){
	Huffnode *child1 = queue.top().second;
	queue.pop();
	Huffnode *child2 = queue.top().second;
	queue.pop();
	Huffnode *mergedNode = new Huffnode(child1, child2);


	q.push(pair<float, Huffnode*>(mergedNode->weight, mergedNode));
	root = mergedNode;
	}
	stream.seekg(stream.beg);
	}

	map<char, std::vector<int> > getEncodings(){
		getMappings();
    return total;
	}

	void getMappings(){ //recursive func
		typedef pair<char, std::vector<int> > entry;
    vector<int> vec;
		map<char, vector<int> > total;
    if(root->zero == NULL && root->one == NULL){ //base case
         total.insert(entry(root->symbol, vec));//add to map
         return;
    if(root->zero != NULL){
		    root = root->zero;
			  vec.push(0);
			  getMappings();
		   }
	  }
    if(root->one != NULL)
			root = root->zero;
			vec.pop();
			vec.push(1);
			getMappings();
	}
	HuffmanTree(const map<char, float>& tree){

	priority_queue<pair<float, Huffnode*> > q;
	typename map<char, float>::const_iterator var;

	for(var = tree.begin(); var != tree.end(); ++var){
		Huffnode *one = new Huffnode((*var).first, (*var).second);
		q.push(pair<float, Huffnode*>((*var).second, one));


	}
	while(!q.empty()){
	Huffnode *child1 = q.top().second;
	q.pop();
	Huffnode *child2 = q.top().second;
	q.pop();
	Huffnode *mergedNode = new Huffnode(child1, child2);


	q.push(pair<float, Huffnode*>(mergedNode->weight, mergedNode));
	root = mergedNode;
	}
	}

	void writeTree(ostream& os){
		if(root == NULL){
			return;
		}
		if(root->symbol != '\0'){
			cout<< "LEAF: " << root->symbol << root->weight  <<endl;
		}
		else{
			cout<< "NODE: " << root->weight <<endl;
		}
		root = root->zero;
		writeTree(os);
		root = root->one;
		writeTree(os);
	}

	char decode(ibitstream& ibit){
		int val = ibit.ibitstream::readBit();
		if(root->symbol != '\0'){
			return root->symbol;
		}
		if(val == 0){
			root = root->zero;
			decode(ibit);
		}
		else{
			root = root->one;
			decode(ibit);
		}
	}

};
class HuffmanEncoder : public HuffmanTree{
private:
  HuffmanTree* tree;
  char encoded_mssg;

public:
  HuffmanEncoder(HuffmanTree tree, istream& stream){
    tree = HuffmanTree::HuffmanTree(stream);
    map<char, vector<int>> encoded = tree.getEncodings();
    stream.seekg(0,ios::beg);

  }
  void writeEncodedText(obitstream& text){
    map<char, std::vector<int> > Mappings = getEncodings();
    while(text.get() != '\0'){
      char letter = text.get();
      cout << Mappings.find(letter)->second;
    }
    text.seekg(0,ios::beg);
  }

  void writeTree(ostream& input){
    HuffmanTree::writeTree(input);
  }

};

class HuffmanDecoder : public HuffmanTree{

  private:

    HuffmanTree* tree;
    char result;

  public:

    HuffmanDecoder(istream& i_var, ibitstream& ibit_var){
      tree = HuffmanTree::HuffmanTree(i_var);
      result = tree.decode(ibit_var);

           }

    void decodeText(ibitstream& ibit_st, ostream& o_st){
      o_st << decode(ibit_st);

    }

    void writeTree(ostream& var){
      tree->writeTree(var);

    }
  }
