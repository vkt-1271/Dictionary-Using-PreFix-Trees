#include <iostream>
#include <vector>
using namespace std;

#define clear_screen system("cls")
#define pause_screen system("pause")

void outputNumberOfTabs(int n)
{
	while(n--)
  	{
    	cout<<'\t';
  	}
}
void outputNumberOfBox(int n)
{
	while(n--)
  	{
    	cout<<"\xB2";
  	}
}
void printProgramName(const string str)
{
	cout<<"\n\t\t*******************************************************************\n";
  	cout<<"\t\t\t  "<<str<<" ";
  	cout<<"\n\t\t*******************************************************************\n";
}
void createBox(vector<string> s)
{
	printProgramName("| Welcome To The DICTIONARY Using \"TRIE\" Tree |");
	int maxLength=0;
	for(int i=0;i<s.size();i++)
	{
	    if(s[i].length()>maxLength)
	    {
	      maxLength=s[i].length();
	    }
  	}
	int dLength=maxLength+4+3; // 3 for spaces
	cout<<endl;
	
	outputNumberOfTabs(3);
	
	outputNumberOfBox(dLength);cout<<endl;
	
	outputNumberOfTabs(3);// empty line
	outputNumberOfBox(2);
  	
	for(int i=0;i<maxLength+3;i++) // additional 3 spaces  // 2 before text and 1 after text
  	{	 
		cout<<' ';
  	}
  	outputNumberOfBox(2);
  	for(int i=0;i<s.size();i++)
	{
    	cout<<endl;
    	outputNumberOfTabs(3);
    	outputNumberOfBox(2);
		cout<<"  "<<s[i];
    	int spaces=maxLength-s[i].length()+1;
    	while(spaces--)
    	{
      		cout<<' ';
    	}
    	outputNumberOfBox(2);
   	}
	cout<<endl;
	outputNumberOfTabs(3);
	outputNumberOfBox(2);
	for(int i=0;i<maxLength+3;i++)
	{
		cout<<' ';
	}
  	outputNumberOfBox(2);
  	cout<<endl;

	outputNumberOfTabs(3);
	outputNumberOfBox(dLength);
	cout<<"\n";	
	s.erase(s.begin(),s.end());
}
void End()
{
	clear_screen;
	printProgramName("               | THANK-YOU |");
	exit(0);
}
int choice(int x)
{
	char choise;
	fflush(stdin);
	cin>>choise;
	while(choise<'1' || choise>'1'+x-1)
	{
		cout<<"\n\t\tWrong Choice!\n\n";
		cout<<"\n\t\tEnter your choice : ";
		fflush(stdin);
		cin>>choise;
	}
	return choise-'0';
}
