#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstring>
#include <string.h>
#include "UI.h"
#include "TRie.h"
using namespace std;

#define clear_screen system("cls")
#define pause_screen system("pause")

void Menu()
{
	clear_screen;
	Dictionary D; 					//Object
	Node *Root=D.GetNode();			//Root Node for Whole TRIE Tree
	D.Reading_File(Root);			//Reading File
	string input_data;              //used as Input
	Word W;							//Object
	
	vector<string> menu;
	menu.push_back("1-> Insert A New Word");
	menu.push_back("2-> Search Any(Available) Word");
	menu.push_back("3-> Delete Any(Available) Word");
	menu.push_back("4-> Find Synonym Of Any(Available) Word");
	menu.push_back("5-> Searching Via \"Prefix\"");
	menu.push_back("6-> Print All Available Words In Dictionary In Alphabetical Order");
	menu.push_back("7-> Exit");	
	createBox(menu);

	cout<<"\n__________________________\n";
	cout<<"\n\tEnter your choice : ";
	int x=choice(7);
	if(x==1) //Inserting
	{
		clear_screen;
		string word1;
		cout<<"\tEnter a Word to Add into the Dictionary: ";
		cin>>word1;
		if(!Checking(word1))
		{
			cout<<"\n\nInValid Word !"<<endl<<endl;
			pause_screen;
			Menu();	
		}
		if(Searching_Existing_Words(Root,word1))
		{
			cout<<"\n\nAlready Present in Dictionary"<<endl<<endl;
			pause_screen;
			Menu();	
		}
		W.key=word1;
		cout<<"\n\nEnter the Meaning: ";fflush(stdin);
		gets(W.meaning);
		ofstream V2;
		V2.open("WithMeaning.dat",ios::app);
		V2<<W.key+"."+W.meaning;
		V2<<endl;
		
		cout<<"\n\nEnter the Synonym: ";
		gets(W.synonym);
		ofstream V3;
		V3.open("WithSynonym.dat",ios::app);
		V3<<W.key+"."+W.synonym;
		V3<<endl;
		
		ofstream V4;
		V4.open("AvailableWords.dat",ios::app);
		V4<<W.key;
		V4<<endl;
		
		D.Insertion(Root,W.key);
		V2.close();
		V3.close();
		V4.close();
		
		cout<<endl<<endl;
		pause_screen;
		Menu();
	}
	else if(x==2) //Searching
	{
		clear_screen;
		cout<<"\tEnter Word to be Search: ";
		cin>>input_data;
		D.Searching(Root,input_data);
		cout<<endl<<endl;
		pause_screen;
		Menu();
	}
	else if(x==3) //Deleting
	{
		clear_screen;
		cout<<"\tEnter Word would you like to delete?: ";
		cin>>input_data;
		if(D.Deletion(Root,input_data))
			cout<<"\n\nSuccessFully Deleted !"<<endl;
		else
			cout<<"\n\nNo Such Word Exists"<<endl;
			
		cout<<endl<<endl;	
		pause_screen;
		Menu();
	}
	else if(x==4) //Synonyms
	{
		clear_screen;
		cout<<"\tEnter word to Find its Synonym: ";
		cin>>input_data;
		D.SyNONym(Root,input_data);
		cout<<endl<<endl;
		pause_screen;
		Menu();
	}
	else if(x==5)  //Prefix Searching
	{
		clear_screen;
		cout<<"\tEnter Word would you like to use as a prefix: ";
		cin>>input_data;
		if(!Checking(input_data)) //Checking if Word Exist or Not
		{
			cout<<"\n\nInValid Word !"<<endl<<endl;
			pause_screen;
			Menu();	
		}
		D.PreFix_Searching(Root,input_data);
		cout<<endl<<endl;
		pause_screen;
		Menu();
	}
	else if(x==6) //Display Dictionary
	{
		clear_screen;
		char Allwords[52]={0};
		cout<<"\tAll The Words of Dictionary"<<endl;
		D.Print_Dictionary_Alphabetically(Root,Allwords,0);
		cout<<endl<<endl;
		pause_screen;
		Menu();
	}
	else if(x==7) //End
	{
		End();
	}
}
int main()
{
	Menu();
}
