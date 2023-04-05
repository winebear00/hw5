#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
//#include <string> //I add this 
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void permuteFloatLetter (string floating, set<string>& floatCombo, int startIndex);
void guessWords (string word, string prefix, const set<string>& dict, set<string>& wordList);
void makeList(const string& in, set<string>& floating, const set<string>& dict, set<string>& wordList);



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string>wordList; //hold valid english words
    set<string>floatCombo; //hold floating combination 
    int dashCount=0; //count dashes 
    for (int i=0; i<(int)in.size(); i++)
    {
        if (in[i]=='-')
        {
            dashCount++; 
        }
    }
    if (dashCount==0 && (dict.find(in)!=dict.end()))
    {
        wordList.insert(in);
        return wordList; 
    }
    string emptySpot(dashCount-floating.size(), '-'); //fill in the rest empty spot with '-'
    string newfloat=floating + emptySpot; 
    permuteFloatLetter(newfloat, floatCombo, 0); 
    makeList(in, floatCombo, dict, wordList);
    return wordList; 
}

// Define any helper functions here
void permuteFloatLetter (string floating, set<string>& floatCombo, int startIndex)
{
    int length=floating.size(); //get the size of the floating string 
    if (length==0) //when there is no floating letter 
    {
        return; 
    }
    if (startIndex==length-1)
    {
        floatCombo.insert(floating);
    }
    else 
    {
        for (int i=startIndex; i<length; i++)
        {
            char temp=floating[startIndex];
            floating[startIndex]=floating[i];
            floating[i]=temp; 
            permuteFloatLetter(floating, floatCombo, startIndex+1); 
        }
    }
}

    void guessWords (string word, string prefix, const set<string>& dict, set<string>& wordList)
    {
        if (word.size()==0)
        {
            if (dict.find(prefix)!=dict.end())
            {
                wordList.insert(prefix);
            }
            return; 
        }
        if (word[0]=='-') //the first letter is empty 
        {
            for (char letter='a'; letter<='z'; ++letter)
            {
               guessWords(word.substr(1, word.size()), prefix+letter, dict, wordList); 
            }
        }
        else 
        {
            guessWords(word.substr(1, word.size()), prefix+word[0], dict, wordList);
        }
    }
 
    void makeList(const string& in, set<string>& floating, const set<string>& dict, set<string>& wordList)
    {
        if (floating.empty()==true) //when no floating combination 
        {
            return; 
        } 
        string word=in; 
        string floatingCombo= (*(floating.begin()));
        floating.erase(floatingCombo); //remove this combo from the floating set 
        for (int i=0; i<(int)word.size(); i++)
        {
            if (word[i]!='-') //find the fixed letter 
            {
                floatingCombo=floatingCombo.substr(0,i)+word[i]+floatingCombo.substr(i, word.size());
            }
        }
        guessWords(floatingCombo, "", dict, wordList); 
        makeList(in, floating, dict, wordList);
    }
