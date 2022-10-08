#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

map<char, vector<int>> m;
map<pair<char, char>, int> parseTable;
vector<string> v;
vector<char> nt;
vector<char> t;
map<char, set<char>> first;
map<char, set<char>> follow;
bool isLL1 = true;
ofstream dot;
int pos = 0;
char startSym;
string op=" ";
void find_follow(char);
int n_c=0;

//-----------------------DOT FILE------------------------------------------

void getdot(){

	dot<<"Graph G{\n";
	dot<<"node[color=\"#242038\",shape=square]\n";

}


void gendot(char l,char r,int cnt){
	dot<<l<<(cnt)<<"--"<<r<<cnt+1<<"\n";
	/*string sp="";
	sp+= l+"--";
	sp+= r+"\n";
	op+=sp;
	cout<<sp<<endl;
*/
}



//-------------------- VALIDATE STRING ------------------------------

bool validateString(string s){
	getdot();
	stack<char> st;
	st.push('$');
	st.push(startSym);
	for (auto ch = s.begin(); ch != s.end(); ch++)
	{
		if (find(t.begin(),t.end(),*ch) == t.end())
		{
			cout << "Invalid String"<<endl;
		return false;
		}
	}

	int ptr = 0;

	bool accept = true;

	while(!st.empty()&&ptr<s.length()){
		if (s[ptr] == st.top())
		{
			st.pop();
			ptr += 1;
			n_c--;
//			cout<<"1"<<endl;
		}
		else if (!isupper(st.top()))
		{
			cout << "Terminal not found" << endl;
			accept = false;
//			cout<<"2"<<endl;
			break;
		}
		else{
//			cout<<"3"<<endl;
			char top_st = st.top();
			char top_s = s[ptr];

			int val = parseTable[make_pair(top_st, top_s)];
//			cout<<"sent "<<top_st<<" "<<top_s<<" "<<val<<endl;
			if (val == 0)
			{
				cout << "No production found in parse table"<<endl;
				accept = false;
				break;
			}

			st.pop();
			string to_push = v[val - 1];
//			cout<<"to_push : "<<to_push<<endl;
			if (to_push[0] == '@')
			{	n_c--;
				continue;
			}

			for (auto ch = to_push.rbegin(); ch != to_push.rend(); ch++)
			{
				st.push(*ch);
			}
			for (auto ch = to_push.begin(); ch != to_push.end(); ch++)
                        {
                                gendot(top_st,(*ch),n_c);
                        }
			n_c++;

		}
	}
	dot<<"}\n";
	//cout<<op<<endl;
	if (accept)
	{
		cout << "Input string is accepted\n";
		return true;
	}
	else
	{
		cout << "Input string is rejected\n";
		return false;
	}
}

//------------------------	PARSE TABLE ------------------------------


void printPT()
{
	cout << "Parsing Table: \n";
	cout << "    ";
	for (auto i = t.begin(); i != t.end(); ++i)
	{
		cout << *i << "  ";
	}
	cout << "\n";
	for (auto row = nt.begin(); row != nt.end(); row++)
	{
		cout << *row << "   ";
		for (int col = 0; col < t.size(); ++col)
		{
			pair<char, char> row_num(*row, t[col]);
			// getPTvalue(*row);
			if (!parseTable[row_num])
			{
				cout << "-  ";
				continue;
			}
			cout << parseTable[row_num] << "  ";
		}
		cout << "\n";
	}
	cout << "\n";

	if(isLL1){
		cout << "The Grammar is LL1 Accepted" << endl;
	}else{
		cout << "The Grammar is not LL1 Accepted" << endl;
	}

}

//--------------------------FIRST AND FOLLOW ----------------------

void find_first(char non_term)
{
	// cout << "finding " << non_term << endl;
	int cnt = m[non_term][0];
	int p = m[non_term][1];

	for (int i = p; i < cnt + p; i++)
	{
		for (char c : v[i])
		{
			if (!isupper(c))
			{
				// cout << c << endl;
				first[non_term].insert(c);
				if(c!='@'){
					if (parseTable[make_pair(non_term, c)]!=0){
						cout << "Collision at [" << non_term << "][" << c << "] for production " << i + 1 << " and " << parseTable[make_pair(non_term, c)] << "\n";
						isLL1 = false;
					}else{
						parseTable[make_pair(non_term, c)] = i + 1;
					}
				}
				else
				{
					find_follow(non_term);
					// cout << "eps " << non_term << endl;
					for (char o : follow[non_term])
					{
						// cout << o << endl;
						if (parseTable[make_pair(non_term, o)]!=0){
                                                cout << "Collision at [" << non_term << "][" << o <<endl;
                                                isLL1 = false;
                                        }else{
                                                parseTable[make_pair(non_term, o)] = i + 1;
                                        }

						
					}
				}
				break;
			}
			else
			{
				if (first[c].empty())
				{
					find_first(c);
				}

				if (first[c].find('@') == first[c].end())
				{
					first[non_term].insert(first[c].begin(), first[c].end());
					for (char o : first[c])
					{
						parseTable[make_pair(non_term, o)] = i + 1;
					}
					break;
				}

				set<char> temp(first[c].begin(), first[c].end());

				if ((find(v[i].begin(), v[i].end(), c) - v[i].begin()) + 1 != v[i].size() - 1)
				{
					temp.erase('@');
				}
				
				first[non_term].insert(temp.begin(), temp.end());
				
				for (char o : first[non_term])
				{
					// cout << o << endl;
					// cout << non_term << endl;
					parseTable[make_pair(non_term, o)] = i + 1;
				}
			}
		}
	}
}

void getFirsts()
{
	for (auto i = nt.begin(); i != nt.end(); i++)
	{
		if (first[*i].empty())
		{
			find_first(*i);
		}
	}
}

void printFirst()
{

	cout << "FIRST" << endl;
	for (auto i = first.begin(); i != first.end(); i++)
	{
		cout << i->first << " : { ";
		for (char j : i->second)
		{
			cout << j << "  ";
		}
		cout << " }" << endl;
	}
}

int count_char(string s, char c)
{
	// cout << "returning count : " << count(s.begin(), s.end(), c) << endl;
	return (int)count(s.begin(), s.end(), c);
}

void find_follow(char non_term)
{
	// cout << "following " << non_term << endl;

	for (auto it = m.begin(); it != m.end(); ++it)
	{
		int cnt = m[it->first][0];
		int p = m[it->first][1];
		for (int i = p; i < cnt + p; i++)
		{
			string s = v[i];

			int cp = s.find(non_term);
			// cout << cp << endl;
			if (cp == -1)
			{
				continue;
			}

			int count = count_char(s, non_term);
			int next = cp + 1;
			while (count--)
			{
				int j=next;
				for (j = next; j < s.length(); j++)
				{
					if (!isupper(s[j]))
					{
						follow[non_term].insert(s[j]);
						break;
					}
					if(first[s[j]].empty())
					find_first(s[j]);

					set<char> firsts_copy(first[s[j]]);

					if (firsts_copy.find('@') == firsts_copy.end())
					{
						follow[non_term].insert(firsts_copy.begin(), firsts_copy.end());
						break;
					}
					firsts_copy.erase('@');
					follow[non_term].insert(firsts_copy.begin(), firsts_copy.end());
				}
				if(j==s.length()){
				next=j;
				}
				if (count != 0)
				{
					string sub = s.substr(next);
					next = sub.find(non_term) + next + 1;
					// cout << next << endl;
				}
			}

			if (next >= s.length())
			{
				if (follow[it->first].empty() && it->first != non_term)
				{
					find_follow(it->first);
				}
				else
				{
					follow[it->first].insert('$');
				}
				follow[non_term].insert(follow[it->first].begin(), follow[it->first].end());
				// for (char o : follow[non_term])
				// {
				// 	cout << o << endl;
				// 	parseTable[make_pair(non_term, o)] = i+1;
				// }
			}
		}
	}
}

void getFollows()

{
	for (auto i = nt.begin(); i != nt.end(); i++)
	{
		if (follow[*i].empty())
		{
			find_follow(*i);
		}
	}
}

void printFollow()
{

	cout << "Follow" << endl;
	for (auto i = follow.begin(); i != follow.end(); i++)
	{
		cout << i->first << " : { ";
		for (char j : i->second)
		{
			cout << j << "  ";
		}
		cout << " }" << endl;
	}
}

//------------------- get grammar tokens -----------------
void getNT()
{
	for (char i : nt)
	{
		cout << i << " ";
	}
	cout << endl;
}

void getT()
{
	// int pos = find(t.begin(), t.end(), "@")-t.begin();
	// remove(t.begin(), t.end(), '@');
	for (string s : v)
	{

		for (char i : s)
		{
			if ((find(t.begin(), t.end(), i) == t.end()) && (find(nt.begin(), nt.end(), i) == nt.end()))
			{
				t.push_back(i);
			}
		}
	}
	t.erase(remove(t.begin(), t.end(), '@'), t.end());
	sort(t.begin(), t.end());
	t.push_back('$');

	for (char i : t)
	{
		cout << i << " ";
	}
	cout << endl;
}

void add_to_map(string s)
{

	int l = s.find(">");
	string sub = s.substr(l + 1);
	char ch = s[0];
	char *tok = strtok(&*sub.begin(), "|");
	int cnt = 0;
	while (tok != NULL)
	{
		cnt++;
		v.push_back(tok);
		tok = strtok(NULL, "|");
	}

	vector<int> a(2);
	a[0] = cnt;
	a[1] = pos;
	pos += cnt;
	if (find(nt.begin(), nt.end(), ch) == nt.end())
	{
		nt.push_back(ch);
	}
	m[ch] = a;
}

void printV()
{
	for (string i : v)
	{
		cout << i << endl;
	}
}

void printM()
{
	for (auto i = m.begin(); i != m.end(); i++)
	{
		cout << i->first << " : { ";
		for (int j : i->second)
		{
			cout << j << "  ";
		}
		cout << " }" << endl;
	}
}

void divide_nt(string s)
{
	startSym = s[0];
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	vector<string> str;
	char *token = strtok(&*s.begin(), ",");
	while (token != NULL)
	{
		str.push_back(token);

		token = strtok(NULL, ",");
	}

	for (string a : str)
	{
		add_to_map(a);
	}
}
