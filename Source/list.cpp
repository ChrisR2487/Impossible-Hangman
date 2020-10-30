#include <fstream>
#include <cstdlib>
#include <iostream>
#include <random>
#include <time.h>
#include "list.h"

using namespace std;

list::list(string file) {
	ifstream inputFile;
	inputFile.open(file);

	size_t count;
	inputFile >> count;

	mFirst = NULL;
	for (int i = 0; i < count; i++) {
		string word;
		inputFile >> word;
		node* new_node = new node(word, mFirst);
		mFirst = new_node;
		mLength++;

	}
}

list::~list() {
	node* p = mFirst;
	while (p != NULL) {
		node* q = p->next();
		delete p;
		p = q;
	}
}

string list::word() {
	srand(time(NULL));

	assert(mFirst != NULL);
	int x = rand() % length();
	node* p = mFirst;
	for (int i = 0; i < x; i++) {
		p = p->next();
	}
	return p->word();
}


bool list::split(char guess) {

	list* lists[64];

	for (int i = 0; i < 64; i++) {
		lists[i] = new list();
	}

	while (mFirst != NULL) {
		node *q = mFirst;
		mFirst = mFirst->next();

		q->update_mask(guess);
		int index = q->get_mask(guess);
		q->set_next(lists[index]->first());
		lists[index]->mFirst = q;
		lists[index]->mLength++;
	}

	int best = 0;
	for (int i = 1; i < 64; i++) {
		if (lists[i]->length() > lists[best]->length()) {
			best = i;
		}
	}

	for (int i = 0; i < 64; i++) {
		if (i != best) {
			delete lists[i];
			lists[i] = NULL;
		}
	}

	mFirst = lists[best]->first();
	mLength = lists[best]->length();

	return (mFirst->mask().find(guess) != string::npos);
}