#include <bits/stdc++.h>
using namespace std;
class TrieNode {        //Class for the trie node.
	public :
	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {       //Constructor of the class.
		this -> data = data;
		children = new TrieNode*[26];
		for(int i = 0; i < 26; i++) {
			children[i] = NULL;
		}
		isTerminal = false;
	}
};

class Trie {        //Trie class.
	TrieNode *root;

	public :
    int count;

	Trie() {        //Constructor of the trie class.
		root = new TrieNode('\0');
		this -> count = 0;
	}

	bool insertWord(TrieNode *root, string word) {         //Function for inserting words in the trie.
		// Base case
		if(word.size() == 0) {
			if (!root->isTerminal) {
				root -> isTerminal = true;
				return true;
			} else {
				return false;
			}
		}

		// Small Calculation
		int index = word[0] - 'a';
		TrieNode *child;
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		// Recursive call
		return insertWord(child, word.substr(1));
	}

	// For user
	void insertWord(string word) {
		if (insertWord(root, word)) {
			this->count++;
		}
	}

    void print(TrieNode *root,string s,string pattern){         //Printing the suggested words.
        if(root==nullptr)
            return ;
        if(root->isTerminal==true){
            cout<<(pattern+s)<<"\n";
        }
        for(int i=0;i<26;++i)
            if(root->children[i]!=nullptr){
                s+=root->children[i]->data;
                print(root->children[i],s,pattern);
                s=s.substr(0,s.size()-1);
            }
    }

    void autoComplete(string pattern,TrieNode *root,string lol){
        if(lol.length()==0){
            int f=1;
            for(int i=0;i<26;++i)
                if(root->children[i]!=nullptr){
                    f=0;
                    break;
                }
            if(f==0){
                string s="";
                print(root,s,pattern);}
                return ;
        }
        int index=lol[0]-'a';
        if(root->children[index]!=nullptr)
            if(root->children[index]->data==lol[0])
                autoComplete(pattern,root->children[index],lol.substr(1));      //Recursive calls.
        else
            return ;
    }

    void autoComplete(vector<string> input, string pattern) {       //Auto complete function for user.
        for(int i=0;i<input.size();++i)
            insertWord(input[i]);
        string lol=pattern;
        autoComplete(pattern,root,lol);
    }
};
int main(){
    Trie trie;
	vector<string> input;
	cout<<"Enter the strings and press -1 to stop giving the input: "<<"\n";
	string s;
	cin>>s;
	while(s!="-1"){
        input.push_back(s);     //Taking input in the vector.
        cin>>s;
	}
	cout<<"Enter the string for auto completion: "<<"\n";
	string pattern;
	cin>>pattern;
	cout<<"Suggestions for auto completion are: "<<"\n";
	trie.autoComplete(input,pattern);
	return 0;
}
