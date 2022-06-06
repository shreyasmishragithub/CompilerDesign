#include <bits/stdc++.h>
using namespace std;

int start(char c) {
    if(c == 'a' || c == 'b')
        return 0;
    else if (c == 'c')
        return 1;
    else
        return -1;
}

int state1(char c) {
    if(c == 'a' || c == 'b')
        return 2;
    else if (c == 'c')
        return 1;
    else
        return -1;
}

int state2(char c) {
    if(c == 'a' || c == 'b' || c == 'c')
        return 2;

    return -1;
}

bool isAccepted(string s) {
    int len = s.size();
    int dfa = 0;

    for(int i = 0; i < len; i++) {
        if(dfa == 0)
            dfa = start(s[i]);

        else if(dfa == 1)
            dfa = state1(s[i]);

        else if(dfa == 2)
            dfa = state2(s[i]);

        else
            return false;
    }

    if(dfa == 0 || dfa == 1)
        return true;

    return false;
}

int main() {
    cout << "Name : Shreyas Mishra\n";
    cout << "Roll No. : UE193104\n\n";
    string str;
    cin >> str;

    if(isAccepted(str))
        cout << "Accepted\n";
    else
        cout << "Not Accepted\n";
}
