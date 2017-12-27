/*
 * Jumble.h
 *
 *  Created on: Nov 11, 2017
 *      Author: Max
 */

#pragma once

#include <string>
using namespace std;

typedef char* charArrayPtr;

class BadJumbleException{
public:
	BadJumbleException(const string&);
	string what() const;
private:
	string message;
};

class JumblePuzzle{

private:
	string hiddenword;
	string difficulty;
	int rowPos, colPos, size;
	char direction;
	charArrayPtr* jumble;

public:


	JumblePuzzle(string word, string diff); //constructor
	JumblePuzzle(const JumblePuzzle&); //copy constructor
	~JumblePuzzle(); //destructor
	JumblePuzzle& operator=(const JumblePuzzle& jp); //overload the assignment operator
	int getRowPos();
	int getColPos();
	int getSize();
	char getDirection();
	charArrayPtr* getJumble();
	string getWord();
	string getDifficulty();


};
