#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define getunique(v){sort(all(v));v.erase(unique(all(v)), v.end());}
using namespace std;
typedef long long int ll;

map<string, vector<string>> first_map;
map<string, vector<string>> productions;
map<string, vector<string>> follow_map;

string getString(char x) {
 string s(1, x);
 return s;
}

bool isterminal(string s) {
 string temp;
 temp = temp + s;
 if (productions.find(s) == productions.end()) {
  return true;
 } else {
  return false;
 }
}

void first(string str, std::vector<string> ans) {
 auto all_productions = productions[str]; // vector string  of all productions

 for (auto prod : all_productions) { // for all productions

  for (int i = 0; i < prod.length(); i++) {
   if (isterminal(getString(prod[i]))) {
    // found terminal in production then no need to calculate first of rest of the string
    string temp2;
    temp2 = temp2 + prod[i];

    ans.push_back(temp2);
    break;
   } else {

    if (first_map.find(getString(prod[i])) != first_map.end()) { // calculated  first  of the production already and it's stored in the map
     auto vstring = first_map[getString(prod[i])];
     bool epsilon_present = false;
     for (auto x : vstring) {
      if (x == "~") {
       epsilon_present = true;
      } else {
       ans.push_back(x);
      }
     }
     if (epsilon_present) {
     } else {
      break;
     }
    } else {
     vector<string> str2;
     first(getString(prod[i]), str2);

     auto vstring = first_map[getString(prod[i])];
     bool epsilon_present = false;
     for (auto x : vstring) {
      if (x == "~")
       epsilon_present = true;

      ans.push_back(x);
     }
     if (epsilon_present) {
     } else {
      break;
     }
    }
   }
  }
 }
 first_map[str] = ans;
}

void follow() {
 for (auto x : productions) {
  string nonTerminal = x.first; // first production under consideration

  for (auto y : productions) {
   vector<string> cur_varproductions;
   cur_varproductions = y.second;
   for (auto prod : cur_varproductions) { // for all productions
    int i;
    bool epsilon_present = false;

    for (i = 0; i < prod.length(); i++) {
     if (getString(prod[i]) == nonTerminal) { // our non terminal gets matched
      int j = i + 1;
      if (j == prod.length()) {
       vector<string> tempfol = follow_map[y.first];
       for (auto x : tempfol) {
        follow_map[getString(prod[i])].push_back(x);
       }
      }

      vector<string> temp; // will store all follow of current non terminal
      for (; j < prod.length(); j++) {
       bool check = isterminal(getString(prod[j]));
       if (check) {
        temp.push_back(getString(prod[j]));
        break;
       }
       vector<string> temp2 = first_map[getString(prod[j])];
       epsilon_present = false;
       for (auto x : temp2) {
        if (x == getString('~')) {
         epsilon_present = true;
        }
       }
       if (epsilon_present) {
        vector<string> temp3 = first_map[getString(prod[j])];
        for (auto x : temp3) {
         temp.push_back(x);
        }

        continue;
       } else {

        vector<string> temp3 = first_map[getString(prod[j])];
        for (auto x : temp3) {
         temp.push_back(x);
        }

        break;
       }
      }
      for (auto x : temp) {
       if (x != getString('~'))
        follow_map[getString(prod[i])].push_back(x);
      }
      if (j == prod.length() && epsilon_present) { // check for dollar
       vector<string> tempfol = follow_map[y.first];
       for (auto x : tempfol) {
        follow_map[getString(prod[i])].push_back(x);
       }
      }
     }
    }
   }
  }
 }
}

void print(map<string, vector<string>> printmap) {
 for (auto x : printmap) {
  cout << x.first << " : ";
  for (auto y : x.second) {
   cout << y << " ";
  }
  cout << "\n";
 }
}

map<pair<string, string>, string> parsing_table;
void print_p() {
 for (auto x : parsing_table) {
  auto pr = x.first;
  auto str = x.second;
  cout << pr.first << " " << pr.second << " : " << pr.first << " -> " << str;

  cout << "\n";
 }
}

string checkwhichprod(string nonTerminal, string temp) {
 string ans;
 auto vecstring = productions[nonTerminal];
 for (int i = 0; i < vecstring.size(); i++) {
  auto str = vecstring[i];
  for (auto letter : str) {
   if (isterminal(getString(letter))) {
    if (temp == getString(letter))
     return str;
    else
     break;
   } else {
    auto vectstrtemp = first_map[getString(letter)];
    for (auto x : vectstrtemp) {
     if (x == temp)
      return str;
    }
   }
  }
 }
 return "";
}
string startSymbol;
void constructParsingTable() {
 for (auto x : first_map) {
  auto nonTerminal = x.first;
  auto firstofcurnonTerminal = x.second;
  for (auto temp : firstofcurnonTerminal) {
   if (temp == getString('~')) { // first contains epsilon
    auto vecfollow = follow_map[nonTerminal];

    for (auto x : vecfollow) {
     auto pr = make_pair(nonTerminal, x);
     auto prodstr = getString('~');
     if (parsing_table.find(pr) == parsing_table.end()) {
      parsing_table[pr] = prodstr;
     } else {
      cout << "Not an ll1 parser\n";
     }
    }

    continue;
   }

   auto pr = make_pair(nonTerminal, temp);
   auto prodstr = productions[nonTerminal];
   if (prodstr.size() == 1) { // single productions

    if (parsing_table.find(pr) == parsing_table.end()) {
     parsing_table[pr] = prodstr[0];
    } else {

     cout << "Not an ll1 parser 2\n";
    }
   } else {

    auto str = checkwhichprod(nonTerminal, temp);
    if (parsing_table.find(pr) == parsing_table.end()) {
     parsing_table[pr] = str;
    } else {
     cout << "Not an ll1 parser   3\n";
    }
   }
  }
 }
}

void printstack(stack<string> stk) {
 if (stk.empty())
  return;
 auto temp = stk.top();
 stk.pop();
 printstack(stk);
 cout << temp;
}

bool parseString(string input) {
 stack<string> stk;
 stk.push("$");
 stk.push(startSymbol);
 for (int i = 0; i < input.length();) {
  string str = stk.top();
  // cout<<"stack top = "<<str<<" ";
  printstack(stk);
  cout << "  ";
  stk.pop();
  cout << "input = ";
  for (int j = i; j < input.length(); j++) {
   cout << input[j];
  }
  cout << "\t";
  if (str == getString(input[i]) && str == "$") {
   return true;
  } else if (str == getString(input[i])) {
   i++;
   cout << "\n";
  } else {
   auto pr = make_pair(str, getString(input[i]));
   if (parsing_table.find(pr) != parsing_table.end()) {
    auto temp = parsing_table[pr];
    cout << pr.first << " " << temp << "\n";
    for (int i = temp.length() - 1; i >= 0; i--) {
     if (getString(temp[i]) != getString('~'))
      stk.push(getString(temp[i]));
    }
   } else {
    return false;
   }
  }
 }
 return false;
}
int main() {
 cout << "Name : Shreyas Mishra\n";
 cout << "Roll No. : UE193104\n\n";
 cout << "Enter number of productions : ";
 int n;
 cin >> n;
 string nonTerm, pr;
 for (int i = 0; i < n; i++) {
  cin >> nonTerm >> pr;

  productions[nonTerm].push_back(pr);
  if (!(i && 1)) {
   startSymbol = nonTerm;
   follow_map[nonTerm].push_back(getString('$'));
  }
 }

 vector<string> temp;

 for (auto x : productions) { // finding first
  first(x.first, temp);
 }
 for (auto x : first_map) {
  vector<string> temp2;
  temp2 = x.second;
  getunique(temp2);
  first_map[x.first] = temp2;
 }
 follow();
 for (auto x : follow_map) {
  vector<string> temp2;
  temp2 = x.second;
  getunique(temp2);
  follow_map[x.first] = temp2;
 }
 follow();
 for (auto x : follow_map) {
  vector<string> temp2;
  temp2 = x.second;
  getunique(temp2);
  follow_map[x.first] = temp2;
 }

 cout << "First of the productions\n";
 print(first_map);
 cout << "Follow of the productions\n";
 print(follow_map);
 cout << "printing parsing table\n";
 constructParsingTable();
 print_p();

 cout << "input string to parse\n";
 string parsestr;
 cin >> parsestr;
 parsestr += "$";
 bool ans = parseString(parsestr);

 if (ans)
  cout << "String parsed succesfully";
 else
  cout << "String not part of language\n";
}

