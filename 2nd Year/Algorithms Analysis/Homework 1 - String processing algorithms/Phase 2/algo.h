#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


void DetermineLPS(char* word, int M, int* lps); 
  
// Displays the first occurence of word[] in txt[] 
void KMPSearch(char* word, char* txt, char outpath[]) 
{ 
    ofstream fout(outpath);

    int M = strlen(word); 
    int N = strlen(txt); 
  
    // lps[] holds either the longest prefix or the longest suffix 
    int lps[M]; 
  
    // First, we determine the lps array 
    DetermineLPS(word, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for word[] 
    int ok = 0;
    while (i < N) { 
        if (word[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            cout<<"Found pattern at index "<<i - j<<"\n"; 
            cout<<"(Indexing starts from zero.)"<<"\n";
            fout<<"Found pattern at index "<<i - j<<"\n"; 
            fout<<"(Indexing starts from zero.)"<<"\n";
            ok = 1;
            break;
            j = lps[j - 1]; 
        } 
  
        // mismatch after j matches 
        else if (i < N && word[j] != txt[i]) { 
            
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    }
    if(ok == 0)
    {
        cout<<"Pattern not found"<<"\n";
        fout<<"Pattern not found";
    }
} 
   
void DetermineLPS(char* word, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    int i = 1; 
    while (i < M) { 
        if (word[i] == word[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else
        { 
            if (len != 0) { 
                len = lps[len - 1]; 
            } 
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 



// Utility function that finds the minimum of three numbers
int min(int x, int y, int z) { return min(min(x, y), z); }
 
void editDistDP(char str1[], char str2[], int m, int n, char outpath[])
{
    ofstream fout(outpath);

    // Create a table to store results of subproblems
    int dp[m + 1][n + 1];
 
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            
            if (i == 0)
                dp[i][j] = j; 
 
          
            else if (j == 0)
                dp[i][j] = i; 
 
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
 
            else
                dp[i][j]
                    = 1
                      + min(dp[i][j - 1], // Insert
                            dp[i - 1][j], // Remove
                            dp[i - 1][j - 1]); // Replace
        }
    }
 
    if(dp[m][n] == 1)
    {
        cout<<"Only ";
        cout<<dp[m][n];
        cout<<" transformation required."<<"\n";

        fout<<"Only ";
        fout<<dp[m][n];
        fout<<" transformation required."<<"\n";
    }
    else
    {
        cout<<dp[m][n];
        cout<<" transformations required."<<"\n";

        fout<<dp[m][n];
        fout<<" transformations required."<<"\n";
    }
}
  
