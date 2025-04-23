#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recurseFun(std::string& curr, const std::string& floating, std::set<std::string>& results, const std::set<std::string>& dict, size_t idx)
{
	if(idx == curr.length())
	{
		std::string temp = floating;
		for(size_t i = 0; i < curr.length(); i++)
		{
			size_t pos = temp.find(curr[i]);
			if(pos != std::string::npos)
			{
				temp.erase(pos, 1);
			}
		}
		if(temp.empty() && dict.find(curr) != dict.end())
		{
			results.insert(curr);
		}
		return;
	}

	if(curr[idx] != '-')
	{
		recurseFun(curr, floating, results, dict, idx + 1);
		return;
	}
	size_t blanks = 0;
	for(size_t i = idx; i < curr.length(); i++)
	{
		if(curr[i] == '-')
		{
			blanks++;
		}
	}

	if(blanks <= floating.size())
	{
		for(size_t i = 0; i < floating.size(); i++)
		{
			char c = floating[i];
			curr[idx] = c;
			std::string newFloating = floating;
			newFloating.erase(i, 1);
			recurseFun(curr, newFloating, results, dict, idx + 1);
			curr[idx] = '-';
		}
	}
	else
	{
		for(char c = 'a'; c <= 'z'; c++)
		{
			curr[idx] = c;
			size_t pos = floating.find(c);
			if(pos != string::npos)
			{	
				string newFloating = floating;
				newFloating.erase(pos, 1);
				recurseFun(curr, newFloating, results, dict, idx + 1);
			}
			else
			{
				recurseFun(curr, floating, results, dict, idx + 1);
			}
			curr[idx] = '-';
		}
	}
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		if(in.empty())
		{
			return {};
		}
		std::set<std::string> results;
		std::string curr = in;
		recurseFun(curr, floating, results, dict, 0);
		return results;

}

// Define any helper functions here