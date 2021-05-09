/*
	@Suyogya Rayamajhi
	@CSCI-313
	@Date: 04/11/21
    Homework 2 Program 6
    Use a stack to pass in a string and reverse each word in the string.
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

void wordreverse (stack <char>& ,string& ,int& ,int ); // function definitions
string reverse(string ,int );

int main() 
{
  string str;
    
    ifstream iFile;
    iFile.open("input.txt"); // input file opening
    
    ofstream oFile;
    oFile.open("output.txt"); // output file opening
    
    while(getline(iFile,str)) // reading the input file
    {
       oFile<<reverse(str,str.length())<<endl; // line by line reversal of the inpput file is written to the output file
    }
    oFile.close(); // closing the files 
    iFile.close();
    
}

// taking our stack that contains all the characters, the final string, word size, and the position of the current letter
void wordreverse (stack <char> &word,string &str,int& size,int pos)
{
    for(int i = pos-size; i<pos; i++) // j = "first letter of the current word", pos = "entire string index", size = "word size"
    {
        str[i]=word.top(); // final string is made by adding char to char
        word.pop(); // popping the element to move to next char
    }
    size =0; // word size reset to 0
}

string reverse(string str, int length)
{
    string finalstr = str; // copying the string 
    int count=0; // word size 
    stack<char> word; // a stack of type 'word'
    
    //goes through the entire string
    for(int i = 0; i <length; i++){ // traversing the entire string
        if(str[i]!=' '&&str[i]!=','&&str[i]!='.'&&str[i]!='"')
        { // looking for a space, comma or quotations in order to not push the character into our word stack
            word.push(str[i]);
            count++; // each char add increases the word size
        }
        // condition if space, comma, period or quotation is found
        else if(str[i]==' '||str[i]==','||str[i]=='.'||str[i]!='"')
            // we finalize our word by the above stated characters. 
            wordreverse(word,finalstr,count,i); // we reverse the order of the word to preserve it
        if(i==length-1) // reversing the final word
            wordreverse(word,finalstr,count,i+1);
    }
    cout<<finalstr<<endl; // returning the final string
    return finalstr;
}


