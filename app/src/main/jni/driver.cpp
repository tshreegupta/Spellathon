#include "com_example_tanushree_spellathon_MyNDK.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <jni.h>
#include <fstream>
using namespace std;
#include <android/log.h>
#define MAXLEN 7
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isLeaf is true if the node represents
    // end of a word
    bool isLeaf;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isLeaf = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}
TrieNode *T = getNode();

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isLeaf = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isLeaf);
}

/* Following function is needed for library function qsort(). */
int compare(const void *a, const void * b)
{
    return ( *(char *)a - *(char *)b );
}

// A utility function two swap two characters a and b
void swap(char* a, char* b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// This function finds the index of the smallest character
// which is greater than 'first' and is present in str[l..h]
int findCeil(char str[], char first, int l, int h)
{
    // initialize index of ceiling element
    int ceilIndex = l;

    // Now iterate through rest of the elements and find
    // the smallest character greater than 'first'
    for (int i = l+1; i <= h; i++)
        if (str[i] > first && str[i] < str[ceilIndex])
            ceilIndex = i;

    return ceilIndex;
}

// Print all permutations of str in sorted order
string sortedPermutations(char str[])
{
    // Get size of string
    int size = strlen(str);
    return "abhi";
    // Sort the string in increasing order
    qsort(str, size, sizeof( str[0] ), compare);
    if(T==NULL)
    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "Tree not found"); //TODO: include more logs
    // Print permutations one by one
    bool isFinished = false;
    while (!isFinished)
    {
        // print this permutation
        static int x = 1;
        //printf("%d  %s \n", x++, str);
 		if(search(T, str))
 		{
    		//cout<<str<<endl;
    		return str;
    	}
        // Find the rightmost character which is smaller than its next
        // character. Let us call it 'first char'
        int i;
        for (i = size - 2; i >= 0; --i)
            if (str[i] < str[i+1])
                break;

        // If there is no such chracter, all are sorted in decreasing order,
        // means we just printed the last permutation and we are done.
        if (i == -1)
            isFinished = true;
        else
        {
            // Find the ceil of 'first char' in right of first character.
            // Ceil of a character is the smallest character greater than it
            int ceilIndex = findCeil(str, str[i], i + 1, size - 1);

            // Swap first and second characters
            swap(&str[i], &str[ceilIndex]);

            // Sort the string on right of 'first char'
            qsort(str + i + 1, size - i - 1, sizeof(str[0]), compare);
        }
    }
    return NULL;
}

string solve(string s)
{
    char *str = new char[100];
    int i=0;
    do{
     	str[i] = tolower(s[i]);
    }while(str[i++]!='\0');
    s = sortedPermutations(str);
    return s;
}

void train()
{
	ifstream input("words_eng.txt");
    string train_string;

    while(input >> train_string)
    {
        int i=0;
        char *str = new char[100];
        do{
        	str[i] = tolower(train_string[i]);
        }while(str[i++]!='\0');
        //cout<<"inserting : "<<str<<endl;
    	insert(T, str);
    }
}
/*
int main(int argc, char **argv)
{
	string s = argv[1];
	train();
    cout<<solve(s);
	//sortedPermutations( s );
    cout<<endl<<"------------"<<endl;
    return 0;
}
*/
JNIEXPORT jstring JNICALL Java_com_example_tanushree_spellathon_MyNDK_getMyString(JNIEnv *env, jobject, jstring str){
   const char * chr =(*env).GetStringUTFChars(str,NULL);
   if(chr==NULL)
    return (*env).NewStringUTF("SOMETHING WRONG WITH YOUR CODE");
   const char * s = solve(chr).c_str();
   return (*env).NewStringUTF(s);
  }

JNIEXPORT void JNICALL Java_com_example_tanushree_spellathon_MyNDK_dictionary
  (JNIEnv *, jobject)
  {
      train();
      return;
  }
