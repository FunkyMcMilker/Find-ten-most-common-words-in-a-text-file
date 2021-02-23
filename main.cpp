
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

class CommonWords
{
public:
  int occures;
  string word;

    CommonWords (int occures, string word)
  {
    this->occures = occures;
    this->word = word;
  }
  bool operator < (CommonWords other)
  {
    if (this->occures < other.occures)
      {
	return true;
      }
    else
      {
	return false;
      }
  }


};

//command line param!
int
main (int argc, char **args)
{
  vector < string > words;
  deque < CommonWords > topTenWords;
  string word = "";
  string lastWord = "";
  int possition = 0;
  int counter = 0;
  int largestcount = 0;
  if (argc != 2)
    {
      cout << "No!\n";
      return 1;
    }
  string fname = args[1];
  cout << "You want file: " << fname << "\n";
  ifstream input (fname);
  if (input.is_open ())
    {
      cout << "ok!\n";
    }
  else
    {
      cout << "Could not open\n";
    }

  //loop to read contents of the txt doc into a vector word by word
  while (input >> word)
    {
      words.push_back (word);

    }
  sort (words.begin (), words.end ());

  // iteration over the words vector to find the most common words
  for (int x = 1; x < words.size (); x++)
    {
      if (words[x] == words[x - 1])
	{
	  counter++;
	  if (counter >= largestcount)
	    {
	      largestcount = counter;
	      if (topTenWords.size () < 10 && words[x] != lastWord)
		{
		  CommonWords newWord (counter, words[x]);
		  topTenWords.push_front (newWord);
		  largestcount = topTenWords[0].occures;
		  lastWord = topTenWords[0].word;
		}
	      else if (topTenWords[0].occures < counter
		       && words[x] != lastWord)
		{
		  topTenWords.pop_front ();
		  CommonWords newWord (counter, words[x]);
		  topTenWords.push_front (newWord);
		  largestcount = topTenWords[0].occures;
		  lastWord = topTenWords[0].word;
		}
	      sort (topTenWords.begin (), topTenWords.end ());
	    }
	}
      else
	{
	  counter = 0;
	}

    }
  int rank = 1;
  for (int j = topTenWords.size () - 1; j >= 0; j--)
    {
      cout << rank << " : " << topTenWords[j].
	word << " occures " << topTenWords[j].occures << " times " << endl;
      rank++;
    }
  return 0;
}
