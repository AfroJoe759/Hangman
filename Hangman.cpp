#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

bool isValid(char guess) {
	if (guess >= 'a' && guess <= 'z') {
		return true;
	}

	return false;
}

bool hasGuessed(bool arr[], int index) {

	if (arr[index] == true) {
		return true;
	}
	return false;
}

bool isPresent(string word, char guess) {
	for (int i = 0; i < word.length(); i++) {
		if (guess == word.at(i)) {
			return true;
		}
	}
		return false;
}

bool gameOver(string word, string proxy, int missed) {
	if (word == proxy || missed == 8) {
		return true;
	}

	return false;
}

string createProxy(string hiddenWord, int wordLength) {
	
	for (int i = 0; i < wordLength; i++) {
		hiddenWord += '*';
	}

	return hiddenWord;
}

string updateProxy(string proxy, string word, char guess, int missed) {
	
	string temp = proxy;

	for (int i = 0; i < proxy.length(); i++) {
		if (guess == word.at(i)) {
			proxy.at(i) = guess;
		}
	}

	if (temp == proxy)
	{
		missed++;
	}

	return proxy;
}

string getWord(vector <string>& wordBank) {
	
	srand(time(0));

	int index = (rand() % wordBank.size());

	return wordBank[index];
}

void initializeArray(bool arr[]) {
	
	for (int i = 0; i < 26; i++) {
		arr[i] = false;
	}
}

void checkLetter(char guess, string word, string proxy, int missed, bool arr[]) {

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

		int index = (int)guess - 97;

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
