#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

bool isValid(char guess) { //evaluates whether or not the input is valid
	if (guess >= 'a' && guess <= 'z') { 
		return true;
	}

	return false;
}

bool hasGuessed(bool arr[], int index) { //evaluates if the letter guessed has already been used

	if (arr[index] == true) {
		return true;
	}
	return false;
}

bool isPresent(string word, char guess) { //returns whether or not the letter is present in the mystery word
	for (int i = 0; i < word.length(); i++) {
		if (guess == word.at(i)) {
			return true;
		}
	}
		return false;
}

bool gameOver(string word, string proxy, int missed) { //states the conditions for when the game ends
	if (word == proxy || missed == 8) {
		return true;
	}

	return false;
}

string createProxy(string hiddenWord, int wordLength) { 
	
	for (int i = 0; i < wordLength; i++) {
		hiddenWord += '*'; //adds 1 asterisk for every letter present in the hiddenWord
	}

	return hiddenWord;
}

string updateProxy(string proxy, string word, char guess, int missed) { //updates the proxy value with the correcttly guessed letters showing
	
	string temp = proxy;

	for (int i = 0; i < proxy.length(); i++) {
		if (guess == word.at(i)) {
			proxy.at(i) = guess;
		}
	}

	return proxy;
}

string getWord(vector <string>& wordBank) { //randomly picks a word from the list and returns it
	
	srand(time(0));

	int index = (rand() % wordBank.size());

	return wordBank[index];
}

void initializeArray(bool arr[]) { //sets the boolean array to false indicating no letter has been guessed yet
	
	for (int i = 0; i < 26; i++) {
		arr[i] = false;
	}
}

void checkLetter(char guess, string word, string proxy, int missed, bool arr[]) { //checks to see if the 

	if (isValid(guess))	{

		int index = (int)guess - 97;
			arr[index] = true;
	}

	else {
		cout << "The input you entered was out of range!" << endl;
	}
}

void createWordBank(vector<string>& wordBank) {

	//Pushes back words into the wordBank

	wordBank.push_back("hangman");
	wordBank.push_back("encyclopedia");
	wordBank.push_back("pizza");
	wordBank.push_back("behemoth");
	wordBank.push_back("wildebeest");
	wordBank.push_back("programming");
	wordBank.push_back("rhythm");
	wordBank.push_back("github");
	wordBank.push_back("linux");
	wordBank.push_back("processing");
	wordBank.push_back("diaphragm");
}

void generateHangman(int missed) {

	//generates Hangman based on how many incorrect guesses
	switch (missed)
	{
	case 1:
	{
		cout << "  ___ " << endl;
		cout << " |   |" << endl;
		cout << " |    " << endl;
		cout << " |    " << endl;
		cout << " |    " << endl;
		cout << "_|___ " << endl;
		cout << endl;
		break;
	}
	case 2:
	{
		cout << "  ___   " << endl;
		cout << " |   |  " << endl;
		cout << " |   0  " << endl;
		cout << " |       " << endl;
		cout << " |       " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}
	case 3:
	{
		cout << "  ___  " << endl;
		cout << " |   |  " << endl;
		cout << " |  _0 " << endl;
		cout << " |       " << endl;
		cout << " |       " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}
	case 4:
	{
		cout << "  ___   " << endl;
		cout << " |   |  " << endl;
		cout << " |  _0_ " << endl;
		cout << " |       " << endl;
		cout << " |       " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}
	case 5:
	{
		cout << "  ___  " << endl;
		cout << " |   |  " << endl;
		cout << " |  _0_ " << endl;
		cout << " |   |  " << endl;
		cout << " |      " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}
	case 6:
	{
		cout << "  ___  " << endl;
		cout << " |   |  " << endl;
		cout << " |  _0_ " << endl;
		cout << " |   |  " << endl;
		cout << " |  /    " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}

	case 7:
	{
		cout << "  ___   " << endl;
		cout << " |   |  " << endl;
		cout << " |  _0_ " << endl;
		cout << " |   |  " << endl;
		cout << " |  / \\ " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}

	case 8:
	{
		cout << "  ___   " << endl;
		cout << " |   |  " << endl;
		cout << " |  _X_ " << endl;
		cout << " |   |  " << endl;
		cout << " |  / \\ " << endl;
		cout << "_|___    " << endl;
		cout << endl;
		break;
	}

	default:
	{}

	}
}

void startGame() {

	vector<string> wordBank;
	string word;
	string proxy = "";
	char repeat;
	char guess;
	bool arr[26];
	int missed = 0;

	initializeArray(arr);
	createWordBank(wordBank);

	word = getWord(wordBank);
	proxy = createProxy(proxy, word.length());
	
	do {
		cout << "Currently Known letters in word: " << proxy << endl;
		cout << "Amount of misses " << missed << endl;
		cout << "Input a letter you think is in the word: ";
		cin >> guess;

		int index = (int)guess - 97; //converts the character into its ASCII code 
									//then subtracts 97 to get its index in bool array;

		if (hasGuessed(arr, index) || !isPresent(word, guess))	{

			missed++;
		}

		else {
			checkLetter(guess, word, proxy, missed, arr);
			proxy = updateProxy(proxy, word, guess, missed);
		}

		cout << endl;

		generateHangman(missed);

	} while (!gameOver(word, proxy, missed));

	if (gameOver(word, proxy, missed) && missed < 8)
	{
		cout << "You have won the game!" << endl;
	}

	else {
		cout << "You have lost the game" << endl;
	}

	cout << "Do you want to play again (y/n): ";
	cin >> repeat;

	if (repeat == 'y') {
		startGame();
	}
}

int main() {

	startGame();

	return 0;
}
