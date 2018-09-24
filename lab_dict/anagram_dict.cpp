/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>
#include <map>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	std::vector <std::string> store;
	ifstream wordsFile(filename);
	string word;
	if (wordsFile.is_open()) 
	{
    		/* Reads a line from words into word until the file ends. */
   		while (getline(wordsFile, word)) 
        		store.push_back(word);
	}
	for (auto &content : store)
	{
		auto flag = dict.find(content);
		if (flag == dict.end())
		{
			std::vector <std::string> store;
    			store.push_back(content);
			dict.insert(std::pair<string, std::vector<string>>(content, store));
		}
	/*	else
		{
			std::vector <std::string> temp;
			temp = dict[vectorIt];
	*/		
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
	for (auto &content : words)
	{
		auto flag = dict.find(content);
		if (flag == dict.end())
		{
			std::vector <std::string> store;
    			store.push_back(content);
			dict.insert(std::pair<string, std::vector<string>>(content, store));
		}	
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	std::vector<std::string> retval;
	auto temp = dict.find(word);
	if (temp == dict.end())
		return vector<string>();
	else
	{
		for (auto & elem : dict)
		{
			if (check_anagram(elem.first, word) == true)
				retval.push_back(elem.first);
		}
	}
	return retval;
}

bool AnagramDict::check_anagram(std::string s1, std::string s2) const
{
	if (s1.length() != s2.length())
		return false;
  	std::sort(s1.begin(), s1.end());
  	std::sort(s2.begin(), s2.end());
	if (s1 != s2)
		return false;
  	return true;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	std::vector<vector<std::string>> store;
	std::vector<std::string> temp;
	for (auto &content: dict)
	{
		temp = get_anagrams(content.first);
		if (temp.size() >= 2)
		{
			store.push_back(temp);
			for (size_t i = 0; i < temp.size(); i++)
			{
				std::cout << temp[i] << std::endl;
			}
		}
	}
	return store;
}

