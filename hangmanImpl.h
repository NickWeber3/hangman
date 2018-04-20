#ifndef _HANGMANIMPL_H_
#define _HANGMANIMPL_H_

#include <string>
#include <vector>
#include <set>

using namespace std;

class CurrentGame {
private:
	string chosenWord;
	int attemptsLeft;
	vector<char> lettersGuessed;
	set<char> correctLetters;
	int gameStatus;

public:
	CurrentGame(string word_in);
	void playGame();
	void printHangman();
	int checkGameStatus();
	void printWord();
	void printGuessedLetters();
};



#endif 