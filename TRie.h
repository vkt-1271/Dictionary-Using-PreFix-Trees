#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstring>
#include <string.h>
using namespace std;

const int alpha_size=26;

class Word
{
	public:
	string key;
	char meaning[800],synonym[800];	
};
class Node
{
	public:
	Node *children[alpha_size];
	bool endofword;
	Node()
	{
		endofword=false;
		for(int i=0;i<alpha_size;i++)
		children[i]=nullptr;
	}
};
bool Checking(string data)
{
	for(int i=0;i<data.length();i++)
	{
		int index=data[i]-'a';		//taking ascii value to find index of child node  
		if(index<0)
		return false;
	}	
	return true;
}
bool Searching_Existing_Words(Node *temp,string data)
{
	Node *Temp=temp;
	for(int i=0;i<data.length();i++)
	{
		int index=data[i]-'a'; 		//taking ascii value to find index of child node
		if(index<0) 
			return false;
		if(!Temp->children[index])
			return false;
			
		Temp=Temp->children[index];		// go to next node
	}
	string output_data;int f=0;
	if(Temp!=nullptr && Temp->endofword)
	{
		fstream V1;
		V1.open("AvailableWords.dat");
		while(getline(V1,output_data))
		{
			if(output_data==data)
			f=1;	
		}
		V1.close();	
	}
	if(f==1)
		return true;
	else
		return false;
}
class Dictionary
{
	public:
	
	Node *GetNode()  				//Getting New Node
	{
		Node *newnode=new Node();
		return newnode;
	}
	
	void Reading_File(Node *temp)   //Extracting Data from Files
	{
		string data;
		ifstream V1;
		
		V1.open("AvailableWords.dat",ios::app);
		while(!V1.eof())
		{
			getline(V1,data);
			Insertion(temp,data);
		}
		V1.close();
	}
	
	void Insertion(Node *temp,string data)   //Insertion
	{
		Node *Temp=temp;
		for(int i=0;i<data.length();i++)
		{
			int index=data[i]-'a';		//taking ascii value to find index of child node
			if(Temp->children[index]==nullptr)
			{
				Temp->children[index]=GetNode();	//making New Path if not already
			}
			Temp=Temp->children[index];	//go to next node
		}
		Temp->endofword=true;	//making Leaf Node
	}
	
	void Searching(Node *temp,string data) 		//Searching	
	{
		Node *Temp=temp;
		if(!Searching_Existing_Words(Temp,data))
		{
			cout<<"\n\nNot Available in Dictionary !"<<endl;
			return;
		}
		for(int i=0;i<data.length();i++)
		{
			int index=data[i]-'a';		//taking ascii value to find index of child node
			if(index<0) return;
			if(Temp->children[index]==nullptr)
			{
				cout<<"\n\nNot Available in Dictionary !"<<endl;
				return;
			}
			Temp=Temp->children[index];		// go to next node
		}
		
		string str1,str2;int z;
		char str3[400],str4[400];
		
		ifstream V1;
		V1.open("WithMeaning.dat");
		while(!V1.eof())
		{
			getline(V1,str1);
			z=str1.find(".");
			str2=str1.substr(0,z);
			strcpy(str3,str2.c_str());
			strcpy(str4,data.c_str());
			
			if(strcmp(str4,str3)==0)
			{
				cout<<"\n\nWord: "<<data;
				cout<<"\n\nMeaning: "<<str1.substr(z+1);
			}
		}
		V1.close();
	}
	
	bool Deletion(Node *temp,string data)		//Deleting Words
	{
		Node *Temp=temp;
		if(!Searching_Existing_Words(Temp,data))
			return false;
		for(int i=0;i<data.length();i++)
		{
			int index=data[i]-'a';		//taking ascii value to find index of child node
			if(index<0) 
				return false;
			if(!Temp->children[index])	
				return false;
			Temp=Temp->children[index];  // go to next node
		}
		string output_data;
		if(Temp!=nullptr && Temp->endofword)
		{
			Temp->endofword=false;
			
			ifstream Q1;
			ofstream Q2;
			
			Q1.open("AvailableWords.dat");
			Q2.open("temp.dat");
			
			while(getline(Q1,output_data))
			{
				if(output_data!=data)
					Q2<<output_data<<endl;
			}
			Q1.close();
			Q2.close();
			remove("AvailableWords.dat");
			rename("temp.dat","AvailableWords.dat");
			return true;
		}	
	}
	
	void SyNONym(Node *temp,string data) 		// Finding Similar Meaning Words
	{
		Node *Temp=temp;
		if(!Searching_Existing_Words(Temp,data))
		{
			cout<<"\n\nNot Available in Dictionary !"<<endl;
			return;
		}
		for(int i=0;i<data.length();i++)
		{
			int index=data[i]-'a';	//taking ascii value to find index of child node
			if(index<0) return;
			if(Temp->children[index]==nullptr)
			{
				cout<<"\n\nNot Available in Dictionary !"<<endl;
				return;
			}
			Temp=Temp->children[index];  // go to next node
		}
		
		string str1,str2;int z;
		char str3[400],str4[400];
		
		ifstream V1;
		V1.open("WithSynonym.dat");
		while(!V1.eof())
		{
			getline(V1,str1);
			z=str1.find(".");
			str2=str1.substr(0,z);
			strcpy(str3,str2.c_str());
			strcpy(str4,data.c_str());
			
			if(strcmp(str4,str3)==0)
			{
				cout<<"\n\nWord: "<<data;
				cout<<"\n\nSynonym: "<<str1.substr(z+1);
			}
		}
		V1.close();
	}
	
	void Print_PreFix_Searching(Node *temp,char Allwords[],int index,string data) //Prints Complete written Prefix words 
	{
		Node *Temp=temp;
		if(Temp!=nullptr && Temp->endofword==true)
		{ 
			// If node is non-empty and leaf node(Temp->endofword==true),
			//it indicates end of string, so a null character is added
    		// and string is displayed
			
			cout<<"\n"<<data; //data prints searched prefix for every available word
			//with that prefix. 
			
			Allwords[index]='\0';
			cout<<Allwords<<endl;
		}
		for(int i=0;i<alpha_size;i++)
		{
			// if non-nullptr child is found So, add parent key to Allwords
        	// call the Print_PreFix_Searching function recursively for child node
			if(Temp->children[i]!=nullptr)
			{
				Allwords[index]=i+'a';  //'a' represents parent key
				Print_PreFix_Searching(Temp->children[i],Allwords,index+1,data);
			}
		}	
	}
	
	void PreFix_Searching(Node *temp,string data)			//Prefix-Searching
	{
		Node *Temp=temp;
		char Allwords[50];	
		for(int i=0;i<data.length();i++)
		{
			int index=data[i]-'a';		//taking ascii value to find index of child node
			if(index<0) return;
			if(Temp->children[index]==nullptr)		// no string in the Trie has this prefix
			{
				cout<<"\n\nNo Any Word is present in Dictionary with this Pre-Fix"<<endl;
				return;
			}
			Temp=Temp->children[index];		// go to next node
		}
		Print_PreFix_Searching(Temp,Allwords,0,data); //called for Printing Prefix's
	}
	
	void Print_Dictionary_Alphabetically(Node *temp,char Allwords[],int index) 		//Prints Complete Dictionary
	{
		Node *Temp=temp;
		if(Temp!=nullptr && Temp->endofword==true)
		{ 
			// If node is non-empty and leaf node(Temp->endofword==true),
			//it indicates end of string, so a null character is added
    		// and string is displayed
			Allwords[index]='\0';
			cout<<Allwords<<endl<<"\t->  ";
		}
		for(int i=0;i<alpha_size;i++)
		{
			// if non-nullptr child is found So, add parent key to Allwords
        	// call the Print_Dictionary_Alphabetically function recursively for child node
			if(Temp->children[i]!=nullptr)
			{
				Allwords[index]=i+'a';  //'a' represents parent key
				Print_Dictionary_Alphabetically(Temp->children[i],Allwords,index+1);
			}
		}
	}
};
