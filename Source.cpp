#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <locale>
#include <cmath>
#include <iterator>
using namespace std;
vector<string>board;
vector<vector<string> >boggle;
stringstream theboss;
set<string>righta;
void check(string test,set <string>& righta,set <string>& dictionary)
{
		if (dictionary.count(test)==1)
		{
			righta.insert(test);
		}
}
bool stringtest(string test,set <string>& dictionary)
{
	//cout<<"size: "<<dictionary.size()<<endl;
	set<string> ::iterator check;
	check = dictionary.lower_bound(test);
	if (check == dictionary.end())
	{
	return false;
	}
	string temp= *check;
	//cout<<temp;
	if (temp.substr(0, test.size())==test)
	{
	return true;
	}
	else
	return false;
}
void the_loop(vector<vector<string> > &boggle, int i, int j, string test, set<string>& righta, int how_many_tiles2, vector<vector<bool> >&check_visited,set <string>& dictionary)
{
	//cout<<how_many_tiles2<<endl;
	if (i<0 || j<0 || i>=how_many_tiles2 || j>=how_many_tiles2)
	{
		//cout<<"fdaf"<<endl;
		return;
	}

	if (check_visited[i][j] == true)
	{
		return;
	}

	test = test + boggle[i][j];
	//cout<<test;
	if (stringtest(test,dictionary) == 0)
	{
		return;
	}
	check(test, righta,dictionary);
	check_visited[i][j] = true;
	the_loop(boggle, i + 1, j, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i, j + 1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i + 1, j+1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i, j - 1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i - 1, j + 1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i + 1, j - 1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i - 1, j - 1, test, righta, how_many_tiles2, check_visited,dictionary);
	the_loop(boggle, i - 1, j, test, righta, how_many_tiles2, check_visited,dictionary);
	check_visited[i][j] = false;
}
void couting(set<string>righta, ofstream &output)
{
while(!righta.empty())
	{
		output << *righta.begin();
		output << endl;
		righta.erase(righta.begin());
	}
}
void intializebool(vector<vector<bool> > &check_visited, int how_many_tiles2)
{
for (int i = 0; i < how_many_tiles2; i++)
	{
		vector<bool> insert;
		for (int j = 0; j < how_many_tiles2; j++)
		{
			insert.push_back(false);
		}
		check_visited.push_back(insert);
	}
}
void outputthings(int how_many_tiles2, ofstream &output, vector<vector<string> > &boggle)
{
	for ( int s = 0; s < how_many_tiles2; s++)
	{
		for (int f = 0; f < how_many_tiles2; f++)
		{
			output << boggle[s][f]<<" ";
		}
		output << endl;
	}
}
void resize(vector<vector<string> > &boggle, int how_many_tiles2)
{
	boggle.resize(how_many_tiles2);
	for (int f = 0; f < how_many_tiles2; f++)
	{
		boggle[f].resize(how_many_tiles2);
	}
}
void insertdictionary(ifstream &in_file,string word,set <string>&dictionary)
{
	while (in_file >> word)
	{
	if(word.size()>=4)
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		dictionary.insert(word);
	}
	}
}


int main(int argc, char *argv[])
{
	cout<<"NOW STARTING";
	set <string> dictionary;
	string word;

	ifstream in_file;
	in_file.open(argv[1]);
	insertdictionary(in_file,word,dictionary);
	in_file.close();
	string word2;
	ifstream in_file2;
	in_file2.open(argv[2]);
	int how_many_tiles = 0;
	stringstream ss;
	while (getline(in_file2, word2))
	{
			transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
			stringstream ss;
			string word3;
			ss << word2;
			while (ss >> word3)
			{
			 theboss<<word3<<" ";
			how_many_tiles++;
			}
	}
	in_file2.close();
	int how_many_tiles2 = sqrt(how_many_tiles);
	resize(boggle, how_many_tiles2);
	string answer;
		for (int s = 0; s < how_many_tiles2; s++)
		{
			for (int f = 0; f < how_many_tiles2; f++)
			{
				theboss >> answer;
				boggle[s][f] = answer;
				board.push_back(answer);
			}
		}
		ofstream output;
		output.open(argv[3]);
	outputthings(how_many_tiles2, output, boggle);
	string test="";
	string test1;
	vector<vector<bool> >check_visited;
	intializebool(check_visited, how_many_tiles2);

	for (int i = 0; i < how_many_tiles2; i++)
	{
		for (int j = 0; j < how_many_tiles2; j++)
		{
				the_loop(boggle, i, j, test, righta, how_many_tiles2, check_visited,dictionary);

		}
	}
	output<<endl;
	couting(righta, output);
	output.close();

	return 0;
}
