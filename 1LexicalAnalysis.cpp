#include <bits/stdc++.h>
using namespace std;
unordered_set<string> keywords= {"void","main","using", "namespace", "int", "include",
                                 "iostream", "cin", "cout", "return", "float", "double", "string"
                                };
unordered_set<char> punctuators= { '!', '%', '^','&','*', '(', ')', '-','+', '=', '{',
                                   '}', '|', '~','[',']','\\', ';', ':','<','>','?',',', '/','#', '"'
                                 };
unordered_set<string> op= {"<<","+","-","", "/", "^","&&","||",
                           "=","==","&","|","%","++","--", "+=","-=", "/=", "=","%="
                          };
bool isPuncatuator(char ch) {
 if (punctuators.find(ch)!=punctuators.end()) return true;
 else return false;
}
bool isKeyword(string str) {
 if (keywords.find(str)!=keywords.end()) return true;
 else return false;
}
bool isOperator(string str) {
 if (op.find(str)!=op.end()) return true;
 else return false;
}
int main() {
 fstream file;
 string s, filename;
 filename = "lexical.txt";
 file.open(filename.c_str());
 int aa= 0, bb= 0, dd= 0, cc= 0, o = 0, c = 0;
 cout<<"Shreyas Mishra"<<"\n"<<"UE193104"<<"\n";
 while (file >> s) {
  if (s == "#include<bits/stdc++.h>") {
   cout << s << " is a header" << endl;
  } else if (isOperator(s)) {
   cout << s << " is an operator" << endl;
   o++;
   s = "";
  } else if (isKeyword(s)) {
   cout << s << " is a keyword\n";
   aa++;
   s = "";
  } else if (s.length()==1 && isPuncatuator(s[0])) {
   cout << s << " is a punctuator" << endl;
   cc++;
  } else if (isdigit(s[0])) {
   int x = 0;
   if (!isdigit(s[x++]))
    continue;
   else {
    cout << s << " is a constant" << endl;
    c++;
    s = "";
   }
  } else {
   cout << s << " is an identifier" << endl;
   bb++;
   s = "";
  }
 }
 cout << "Nubmer of keywords = "<< aa<<"\n"
      <<"Nubmer of constants = "<< c <<"\n"
      <<"Nubmer of identifiers = "<< bb<<"\n"
      <<"Nubmer of punctuators = "<< cc<<"\n"
      << "Nubmer of op = "<<o <<"\n";
}
