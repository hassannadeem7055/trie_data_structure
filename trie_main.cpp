// trie data structure to implement fast word validation

#include <iostream> 
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

//  word validation using tries data structure

struct d_node{

  map<char, d_node*> children;
  bool isCompleteWord = false;
};

class dict{
  d_node *d;

  public:
  dict(){
    d = new d_node();
  }
  
  void add_word(string word){

    d_node *temp = d;

    int i=0;
    char ch = word[i];
    while (temp->children.count(ch)){
      temp = temp->children[ch];
      ch=word[++i];
    }

    while (i<word.size()){
      temp->children[ch] = new d_node();
      temp=temp->children[ch];
      ch=word[++i];
    }
    temp->isCompleteWord=true;

  }

  void validate_string (string sentence){
    
    vector<string>  words;
    boost::split(words, sentence, boost::is_any_of(" "), boost::token_compress_on);

  
    for (auto w : words){
      d_node *temp = d;
      bool match = 1;
      for (auto letter : w){
        if (temp->children.count(letter))   temp=temp->children[letter];
        else {match = 0;  break;  };
      }
      cout<<"WORD \"" << w << "\"\t -->";
      if (temp->isCompleteWord && match){
        cout<<" MATCHED\n";
      } else  cout<<" NOT MATCHED\n";
      
    }

  }
};



int main() {

  dict d;
  d.add_word("cat");

  d.add_word("cots");
  d.add_word("tree");
  d.add_word("wild");
  d.add_word("amazon");

  string s = "cat caats in cots cot are good with climbing trrees in the wild forests of amazon";
  d.validate_string(s);


}
