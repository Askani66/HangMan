#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

struct  word
{
	char letter;
	bool flag;
	int position;
	word *next;
	//word *prev;
};

struct node
{
	char data;
	bool flag;
	node *leftNode;
	node *rightnode;
};

void createLinkedList(char let, int pos);
void createBST(char let);
bool alphabetChecker(char a);
bool bstAlphabetChecker(char a);
char* trueFalseChecker(int pos);
void hangMan(int num);
void bstReset(node *temp);
void llRemove();
void inputWord();
void letterInput();
void dashAplhaPrint();
bool allTrueChecker();
void printWord();
void printHeader();
//void printBST(node *temp);

word *head = NULL;
word *tail = NULL;
node *root = NULL;
int countLetters = 0;
int chanceLeft = 6;
char playerOne[25];
char playerTwo[25];

int main() 
{
	char ext;
	char alphabet [26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };	

	for (int i = 0; i < 26; i++)
	{
		createBST(alphabet[i]);
	}	

	do
	{
		printHeader();
		cout << "Player One Please Enter Your Name: ";
		cin >> playerOne;
		cout << "Player Two Please Enter Your Name: ";
		cin >> playerTwo;
		inputWord();

		while (true)
		{
			hangMan(chanceLeft);
			cout << "\n" << "\t \t      ";
			dashAplhaPrint();

			if (allTrueChecker())
			{
				cout << "\n" << playerTwo << " Win" << endl;
				cout << playerOne << " Lost" << endl;
				bstReset(root);
				break;
			}

			if (chanceLeft <= 0)
			{
				cout << "\n" << playerTwo << " Lost" << endl;
				cout << playerOne << " Win" << endl;
				cout << "The word was: ";
				printWord();
				bstReset(root);
				break;
			}

			letterInput();
			system("CLS");
			cout << endl;
		}

		cout << endl;
		cout << "Do you want to continue? Y/N: ";
		cin >> ext;
		system("CLS");

	} while (ext != 'N' && ext != 'n');

	system("pause");
}


void createLinkedList(char let, int pos)
{
	word *temp = (word*)malloc(sizeof(word));

	(*temp).letter = let;
	(*temp).position = pos;
	(*temp).flag = false;
	(*temp).next = NULL;
	//(*temp).prev = NULL;

	if (head == NULL) 
	{
		head = temp;
		tail = temp;
	}
	else
	{
		//(*temp).prev = tail;
		(*tail).next = temp;
		tail = temp;
	}

	countLetters++;
}

void createBST(char let) 
{
	node *temp = (node*)malloc(sizeof(node));

	(*temp).data = let;
	(*temp).flag = false;
	(*temp).leftNode = NULL;
	(*temp).rightnode = NULL;

	if (root == NULL)
	{
		root = temp;
	}
	else
	{
		node *currentNode = root;
		node *childNode = NULL;

		while (currentNode != NULL)
		{
			childNode = currentNode;

			if (let < (*currentNode).data)
			{
				currentNode = (*currentNode).leftNode;
			}
			else if (let > (*currentNode).data)
			{
				currentNode = (*currentNode).rightnode;
			}

		}

		if (let > (*childNode).data)
		{
			(*childNode).rightnode = temp;
		}
		else if (let < (*childNode).data)
		{
			(*childNode).leftNode = temp;
		}

	}

}

bool alphabetChecker(char a) 
{
	word *temp = head;
	bool check = false;

	while (temp != NULL)
	{
		if (a == (*temp).letter) 
		{
			(*temp).flag = true;
			check = true;
		}

		temp = (*temp).next;
	}

	return check;
}

bool allTrueChecker() 
{
	word *temp = head;
	bool check = true;

	while (temp != NULL)
	{
		if ((*temp).flag == false) 
		{
			check = false;
		}

		temp = (*temp).next;
	}

	return check;
}

bool bstAlphabetChecker(char a)
{
	node *temp = root;

	while (temp != NULL)
	{
		if (a == (*temp).data)
		{
			if ((*temp).flag == false) 
			{
				(*temp).flag = true;
				return true;
			}
			else
			{
				break;
			}
		}
		else if (a < (*temp).data)
		{
			temp = (*temp).leftNode;
		}
		else if (a >(*temp).data)
		{
			temp = (*temp).rightnode;
		}

	}

	return false;
}

char* trueFalseChecker(int pos)
{
	word *temp = head;
	char a[2];

	while (temp != NULL)
	{
		if (pos == (*temp).position)
		{
			if ((*temp).flag == true)
			{
				a[0] = (*temp).letter;
				a[1] = '1';
				return a;
			}

			a[0] = (*temp).letter;
			a[1] = '0';
		}

		temp = (*temp).next;
	}

	return a;
}

void dashAplhaPrint() 
{
	for (int i = 0; i < countLetters; i++)
	{
		char* c = trueFalseChecker(i);

		if (*(c + 1) == '1')
		{
			cout << *(c + 0) << " ";
		}
		else
		{
			cout << "_" << " ";
		}

	}
}

void letterInput() 
{
	bool loop = true;
	char a;

	while (loop)
	{
		cout << "\nEnter Alphabet: ";
		cin >> a;

		if (bstAlphabetChecker(a))
		{
			if (alphabetChecker(a) == false)
			{
				chanceLeft--;
				//cout << chanceLeft << endl;
			}

			loop = false;
		}
		else
		{
			cout << "alphabet already Enter" << endl;
		}
	}
}

void inputWord() 
{
	char wrd[50];
	countLetters = 0;
	chanceLeft = 6;
	cout << playerOne << " Please Enter a Word: ";
	cin >> wrd;

	llRemove();

	for (int i = 0; i < (unsigned)strlen(wrd); i++)
	{
		createLinkedList(wrd[i], i);
	}

	system("CLS");
}

void hangMan(int num) 
{
	printHeader();
	switch (num)
	{

	case 6:

		cout << "\t \t \t" <<"________" << endl;
		cout << "\t \t \t" << "|      | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "_________" << endl;

		break;

	case 5:

		cout << "\t \t \t" << "________" << endl;
		cout << "\t \t \t" << "|      | " << endl;
		cout << "\t \t \t" << "O      | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "_________" << endl;

		break;

	case 4:

		cout << "\t \t \t" << "________" << endl;
		cout << "\t \t \t" << "|      | " << endl;
		cout << "\t \t \t" << "O      | " << endl;
		cout << "\t \t \t" << "|      | " << endl;
		cout << "\t \t \t" << "       | " << endl;
		cout << "\t \t \t" << "_________" << endl;

		break;

	case 3:

		cout << "\t \t \t" << "________  "<< endl;
		cout << "\t \t \t" << " |      | " << endl;
		cout << "\t \t \t" << " O      | " << endl;
		cout << "\t \t \t" << "/|      | " << endl;
		cout << "\t \t \t" << "        | " << endl;
		cout << "\t \t \t" << "__________" << endl;

		break;

	case 2:
		
		cout << "\t \t \t" << "________  " << endl;
		cout << "\t \t \t" << " |      | " << endl;
		cout << "\t \t \t" << " O      | " << endl;
		cout << "\t \t \t" << "/|\\     | " << endl;
		cout << "\t \t \t" << "        | " << endl;
		cout << "\t \t \t" << "__________" << endl;

		break;

	case 1:

		cout << "\t \t \t" << "________  " << endl;
		cout << "\t \t \t" << " |      | " << endl;
		cout << "\t \t \t" << " O      | " << endl;
		cout << "\t \t \t" << "/|\\     | " << endl;
		cout << "\t \t \t" << "/       | " << endl;
		cout << "\t \t \t" << "__________" << endl;

		break;

	case 0:

		cout << "\t \t \t" << "________  " << endl;
		cout << "\t \t \t" << " |      | " << endl;
		cout << "\t \t \t" << " O      | " << endl;
		cout << "\t \t \t" << "/|\\     | " << endl;
		cout << "\t \t \t" << "/ \\     | " << endl;
		cout << "\t \t \t" << "__________" << endl;

		break;

	default:
		break;

	}

	cout << "\n" << "\t \t      " << chanceLeft << " chance left" << endl;

}

void bstReset(node *temp)
{

	if (temp != NULL)
	{
		bstReset((*temp).leftNode);
		(*temp).flag = false;
		bstReset((*temp).rightnode);
	}
}

void llRemove() 
{
	word *temp = head;

	while (temp != NULL)
	{
		temp = head;
		head = (*head).next;
		free(temp);
		temp = head;
	}
}

void printWord()
{
	word* temp = head;

	while (temp != NULL)
	{
		cout << (*temp).letter;
		temp = (*temp).next;
	}

}

void printHeader() 
{
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "        _   _                  ___  ___                                  " << endl;
	cout << "       | | | |                 |  \\/  |                                 " << endl;
	cout << "       | |_| | __ _ _ __   __ _| .  . | __ _ _ __                        " << endl;
	cout << "       |  _  |/ _` | '_ \\ / _` | |\\/| |/ _` | '_ \\                    " << endl;
	cout << "       | | | | (_| | | | | (_| | |  | | (_| | | | |                      " << endl;
	cout << "       \\_| |_/\\__,_|_| |_|\\__, \\_|  |_/\\__,_|_| |_|                 " << endl;
	cout << "                           __/ |                                         " << endl;
	cout << "                          |___/                                          " << endl;
	cout << "-------------------------------------------------------------------------" << endl;
}


///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*
void printBST(node *temp)
{
	if (temp != NULL)
	{
		printBST((*temp).leftNode);
		cout << (*temp).data << " ";
		cout << (*temp).flag << endl;
		printBST((*temp).rightnode);

	}
}
*/

