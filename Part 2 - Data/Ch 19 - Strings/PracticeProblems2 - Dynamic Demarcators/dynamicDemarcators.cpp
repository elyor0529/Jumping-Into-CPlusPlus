#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<string>& input);
vector<char> getPotentialDemarcators(const vector<string>& input);
void removeCharacterIfNotPresent(const vector<string>& input, char character, vector<char>& potentialDemarcators);
bool isValidDemarcator(char character, vector<char> potentialDemarcatorsBase);
bool charIsInVector(char character, vector<char>& characters);
int charIsInString(char character, const string& str);

int main()
{
	vector<string> input = 
	{
		"Alex Allain, webmaster@cprogramming.com",
		"John Smith, john@nowhere.com",
		"Foo Bar, foo@bar.com"
	};
	
	print(input);

	vector<char> potentialDemarcators = getPotentialDemarcators(input);

	int choice = 0;
	int maxChoice = potentialDemarcators.size();
	if (maxChoice == 0)
	{
		cout << "No possible demarcators were found in the file.\n";
		return 1;
	}
	bool validChoice = false;	
	while (!validChoice)
	{
		cout << "Please enter the number for the desired demarcator:\n";
		int i = 1;
		for (vector<char>::iterator itr = potentialDemarcators.begin(), end = potentialDemarcators.end(); itr != end; ++itr)
		{
			cout << i << ": " << *itr << '\n';
			i++;
		}
		choice = 0;
		cin >> choice;
		validChoice = ((0 < choice) && (choice <= maxChoice));
	}
	cout << '\n';

	cout << "The demarcator used in this file is: " << "'" << potentialDemarcators[choice - 1] << "'" << endl;
}

void print(const vector<string>& input)
{
	vector<string> potentialDemarcators;
	for (vector<string>::const_iterator itr = input.begin(), end = input.end(); itr != end; ++itr)
	{
		cout << *itr << endl;
	}
	cout << '\n';
}


vector<char> getPotentialDemarcators(const vector<string>& input)
{
	vector<char> potentialDemarcators;
	vector<char> potentialDemarcatorsBase;
	if (input.size() == 0)
	{
		return potentialDemarcators;
	}

	// 1. Find list of all non-alphanumeric characters
	string firstLine = input[0];
	for (int i = 0; i < firstLine.length(); i++)
	{
		if (isValidDemarcator(firstLine[i], potentialDemarcatorsBase))
		{
			potentialDemarcatorsBase.push_back(firstLine[i]);
			potentialDemarcators.push_back(firstLine[i]);
		}
	}

	// 2. For each line, if a character from the list is not present, remove the character
	for (vector<char>::iterator itrChar = potentialDemarcatorsBase.begin(), endChar = potentialDemarcatorsBase.end();
		itrChar != endChar;
		++itrChar)
	{
		removeCharacterIfNotPresent(input, *itrChar, potentialDemarcators);
	}
	return potentialDemarcators;
}

void removeCharacterIfNotPresent(const vector<string>& input, char character, vector<char>& potentialDemarcators)
{
	for (vector<string>::const_iterator itr = input.begin(), end = input.end();
		itr != end;
		++itr)
	{
		if (charIsInString(character, *itr) == 0)
		{
			const char removeChar = character;
			potentialDemarcators.erase(
				remove(potentialDemarcators.begin(), potentialDemarcators.end(), removeChar),
				potentialDemarcators.end());
		}
	}
}

bool isValidDemarcator(char character, vector<char> potentialDemarcatorsBase)
{
	return (!isalnum(character) &&  // Character is not alphanumeric
		(character != ' ') &&		// Character is not blank
		!charIsInVector(character, potentialDemarcatorsBase)); // Character is unique
}

bool charIsInVector(char character, vector<char>& characters)
{
	for (vector<char>::iterator itrChar = characters.begin(), endChar = characters.end();
		itrChar != endChar;
		++itrChar)
	{
		if (character == *itrChar)
		{
			return true;
		}
	}
	return false;
}

int charIsInString(char character, const string& str)
{
	int i = 0;
	int numberOfOccurrences = 0;
	for (i = str.find(character, 0); // Starting value.
		i != string::npos; // Terminating condion. string::npos is a special integer value that indicates that no substring was found.
		i = str.find(character, i)) // Current variable for the loop.
	{
		numberOfOccurrences++;

		// Move past last discovered instance to avoid finding the same string again
		i++;
	}
	return numberOfOccurrences;
}