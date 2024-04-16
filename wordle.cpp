#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void computeKnownCharacters(string in, string floating, set<string>& ret, const set<string>& dict, set<string>& knownCharacters);
void computeUnknownCharacters(string in, set<string>& out, size_t indexToInsert, const set<string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> ret;
    set<string> knownCharacters;
    computeKnownCharacters(in, floating, ret, dict, knownCharacters);
    
    set<string>::iterator it;
    for (it = knownCharacters.begin(); it != knownCharacters.end(); ++it)
    {
        computeUnknownCharacters(*it, ret, 0, dict);
    }
    
    return ret;
}

void computeKnownCharacters(string in, string floating, set<string>& ret, const set<string>& dict, set<string>& knownCharacters)
{
    if (floating.size() == 0)
    {
        //cout << in << endl; //Testing purposes
        //computeUnknownCharacters(in, ret, 0, dict);
        knownCharacters.insert(in);
        return;
    }
    
    for (unsigned int i = 0; i < in.size(); i++)
    {
        string copyOfIn = in;
        if (copyOfIn[i] != '-') continue;
        copyOfIn[i] = floating[0];
        computeKnownCharacters(copyOfIn, floating.substr(1), ret, dict, knownCharacters);
    }
}

void computeUnknownCharacters(string in, set<string>& out, size_t indexToInsert, const set<string>& dict)
{
    if (indexToInsert >= in.size())
    {
        if (dict.find(in) != dict.end()) out.insert(in);
        return;
    }
    if (in[indexToInsert] != '-')
    {
        computeUnknownCharacters(in, out, indexToInsert + 1, dict);
        return;
    }
    
    for (int i = 0; i < 26; i++)
    {
        char c = 'a' + i;
        in[indexToInsert] = c;
        computeUnknownCharacters(in, out, indexToInsert + 1, dict);
    }
}
