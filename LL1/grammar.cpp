#include <cstdlib>
#include <fstream>
#include "functions.cpp"
extern ofstream dot;
extern bool isLL1;

int main(int argc, char const *argv[])
{
	//string s = "S-> aA|bB|cCS , A-> aAB|f|@ , B-> bB|fC|@ , C-> cC|f";
	fstream grammar_file;
	grammar_file.open(argv[1], ios::in);
	string l;
	getline(grammar_file, l);
	if (grammar_file.fail())
	{
		cout << "Error in opening grammar file\n";
		return 2;
	}
	grammar_file.close();
	//fstream dot;
	dot.open("g.dot");
	divide_nt(l);
	getNT();
	getT();
	printM();
        printV();

	getFirsts();
	 printFirst();
	getFollows();
	getFollows();
	 printFollow();
	printPT();

	if(isLL1){
	string s;
	cout<<"Enter the string to check for the above Grammar\n";
	cin>>s;
	bool str_valid=validateString(s);
	cout << endl;
	dot.close();
	if(str_valid){
//	system("dot -Tsvg g.dot -o output.svg ");
//	system("xdg-open output.svg");
	}	
	}

	return 0;
}

// split,isspace,isdigit,isalpha,
