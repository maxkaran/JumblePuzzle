/*
 * Jumble.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: Max
 */

#include "jumble.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//________________________________________EXCEPTION_____________________________________________________________________
BadJumbleException::BadJumbleException(const string& message){
	this->message= message;
}
string BadJumbleException::what() const{
	return message;
}

//____________________________________________Main Class________________________________________________________________
//accessors
int JumblePuzzle::getColPos(){
	return colPos;
}
int JumblePuzzle::getRowPos(){
	return rowPos;
}
char JumblePuzzle::getDirection(){
	return direction;
}
string JumblePuzzle::getDifficulty(){
	return difficulty;
}
string JumblePuzzle::getWord(){
	return hiddenword;
}
charArrayPtr* JumblePuzzle::getJumble(){
	return jumble;
}
int JumblePuzzle::getSize(){
	return size;
}

//constructors
JumblePuzzle::JumblePuzzle(string word, string difficulty){
	if (word.length() < 3 || word.length() > 10)
			throw BadJumbleException("Size of the word to hide must be between 3 and 10!"); //Size of word must be between 3 and 10


	if (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
		throw BadJumbleException("This is not a valid difficulty!must choose from difficulties : \"easy\", \"medium\" or \"hard\" ");

	this->difficulty = difficulty;
	hiddenword = word;

	if(word ==  "hard")
		size = 4*word.length();
	else if(word == "medium")
		size = 3*word.length();
	else
		size = 2*word.length();

	srand(time(nullptr));
	//generate table of random lowercase characters
	jumble = new char*[size];
	for(int i=0;i<size;i++){
		jumble[i]= new char[size];
		for(int j=0;j<size;j++){
			jumble[i][j] = 'a' + rand()%26;
		}
	}

	//choose a random direction
	int random = rand()%4;
	if(random == 1)
		direction = 'n';
	else if(random == 2)
		direction = 's';
	else if(random == 3)
		direction = 'e';
	else
		direction = 'w';

	//Hide hidden word
	if(direction=='s'){
		colPos = rand()%size;
		rowPos = rand()%(size-hiddenword.length());
		for(int i=0;i<hiddenword.length();i++){
			jumble[rowPos+i][colPos] = hiddenword[i];
		}
	}else if(direction == 'n'){
		colPos = rand()%size;
		rowPos = (rand()%size-hiddenword.length())+hiddenword.length();
		for(int i=0;i<hiddenword.length();i++){
					jumble[rowPos-i][colPos] = hiddenword[i];
		}
	}else if(direction == 'w'){
		colPos = rand()%(size - hiddenword.length())+hiddenword.length();
		rowPos = rand()%size;
		for(int i=0;i<hiddenword.length();i++){
					jumble[rowPos][colPos-i] = hiddenword[i];
		}
	}else{
		colPos = rand()%(size-hiddenword.length());
		rowPos = rand()%size;
		for(int i=0;i<hiddenword.length();i++){
					jumble[rowPos][colPos+i] = hiddenword[i];
		}
	}

}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp){
	colPos= jp.colPos;
	rowPos= jp.rowPos;
	direction= jp.direction;
	difficulty= jp.difficulty;
	//now must copy the values into jumble from other JumblePuzzle
	jumble = new charArrayPtr[jp.size];
	for (int j = 0; j < jp.size; j++)
		jumble[j] = new char[jp.size];
	for (int y = 0; y < jp.size; y++) {
		for (int x = 0; x < jp.size + 1; x++) {
			jumble[y][x] = jp.jumble[y][x];
		}
	}

	size = jp.size;
}

//Overload the assignment operator
JumblePuzzle& JumblePuzzle::operator =(const JumblePuzzle& rhs){
	if(this == &rhs)
		return *this;

	//since jumble is stored on the heap, it must be deleted before it is reassigned
	for(int i=0;i<this->size;i++){
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;

	this->colPos= rhs.colPos;
	this->rowPos= rhs.rowPos;
	this->direction= rhs.direction;
	this->difficulty= rhs.difficulty;
	this->size = rhs.size;

	jumble = new charArrayPtr[rhs.size];
	for (int j = 0; j < rhs.size; j++)
		jumble[j] = new char[rhs.size];
	for (int y = 0; y < rhs.size; y++) {
		for (int x = 0; x < rhs.size + 1; x++) {
			jumble[y][x] = rhs.jumble[y][x];
		}
	}

	return *this;
}

JumblePuzzle::~JumblePuzzle(){
	for(int i=0;i<size;++i){
		delete[] jumble[i];
		jumble[i] = nullptr;
	}
	delete[] jumble;
	jumble = nullptr;
}
