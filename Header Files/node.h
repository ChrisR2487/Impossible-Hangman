#ifndef JJB_NODE_H
#define JJB_NODE_H

#include <string>

using namespace std;

class node {
public:
	node(string target, node* next);

	void update_mask(char letter);

	void set_next(node* next) // TODO: Implement this method inline
	{
		mNextNode = next;
	}

	string word() const { return mWord; }
	string mask() const { return mMask; }
	node* next() const // TODO:  Implement this method inline
	{
		return mNextNode;
	}

	int get_mask(char letter) const;

	bool is_guessed() const { return mWord == mMask; }

private:
	string mWord;
	string mMask;
	// TODO: Add an instance variable to make this a linked list node
	node* mNextNode;
};

#endif