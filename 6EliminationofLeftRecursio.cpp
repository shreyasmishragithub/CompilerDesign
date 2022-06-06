#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <bits/stdc++.h>
#include<iostream>
using namespace std;
int n = 1, i = 0, j = 0, k = 0;
char a[10][10];
int main()
{
    printf("Name :Shreyas Mishra\n");
    printf("ROll No : UE193104 \n");
    int i = 0, z;
    char c;

    printf("Enter the production:\n");
    for (i = 0; i < n; i++)
        cin >> a[i];
    c = a[0][0];
    if (a[0][2] == c)
    {
        printf("Left recursion found: \n");
        printf("%c' -> ", c);
        for (k = 3; k < strlen(a[0]) && a[0][k] != '|'; k++)
        {
            cout << a[0][k];
        }
        cout << c << "'"
             << " | e"
             << "\n";
        n = k;
        i = 0;
        cout << c << " ->";
        for (k = n + 1; k < strlen(a[0]) && a[0][k] != '\0'; k++)
        {
            cout << a[0][k];
        }
        cout << c << "'"
             << "\n";
    }
    else
    {
        printf("No left recursion!!");
    }
    return 0;
}

