/*
We need to count pairs of words where one word is both a prefix and a suffix of the other.
*/



class Node {
public:
    Node* links[26];
    bool contains(char c){return links[c-'a'] != NULL;}
    void put(char c, Node* node){links[c-'a'] = node;}

    Node* next(char c){return links[c-'a'];}
};

class Trie{

    Node* root;

public:
    Trie(){root = new Node();}

    void insert(string word){
        Node* node = root;
        for(char c:word){
            if(!node->contains(c)){
                node->put(c, new Node());
            }
            node = node->next(c);
        }
    }

    bool checkPrefix(string& word) {
        Node* node = root;
        for(char c:word){
            if(!node->contains(c)){
                return false;
            }
            node = node->next(c);
        }
        return true;
    }
};

class Solution {
public:
    
    int countPrefixSuffixPairs(vector<string>& words) {

        int n = words.size();
        int ans=0;

        for(int i=0;i<n;i++) {
                Trie a,b;
                string s1= words[i];
                a.insert(s1);
                reverse(s1.begin(), s1.end());
                b.insert(s1);
            for(int j=0;j<i;j++) {
                string s2= words[j];
                reverse(s2.begin(), s2.end());
                

                if(a.checkPrefix(words[j]) && b.checkPrefix(s2) )ans++;
            }
        }

        return ans;
    }
};



/**

A Trie is a tree-like structure where each node represents a character. When we insert words into a Trie, common prefixes are shared, allowing for efficient prefix lookups. For example, if we store "bat" and "ball", the Trie would look like this:

      (root)
       |
       b
       |
       a
      / \
     t   l
          \
           l

           Notice how "b" and "a" are shared to save space.

Tries are useful in everyday examples like autocomplete, dictionaries, and word games:

    Autocomplete: When you type "ca" on your phone, it suggests words like "cat", "car", or "can". It does this by looking up all the words that start with "ca" in a Trie.
    Dictionaries: If you’re searching for words that begin with "app", a Trie quickly finds options like "apple", "apply", and "application" without going through the whole list.
    Word Games: In games like Scrabble or Boggle, Tries help check if a word is real or suggest possible words from your letters. Some puzzles, like Sudoku, use them too.

When inserting a word into the prefix Trie, we are essentially storing all possible prefixes of that word. For example, if the word is "abzdcabz", we add the following prefixes to the Trie: ["a", "ab", "abz", "abzd", "abzdc", "abzdca", "abzdcab", "abzdcabz"]. This allows us to quickly determine if any other word starts with the same prefix.

For suffixes, rather than directly storing and checking suffixes (which would require reversing and checking repeatedly for every comparison), we use a trick to convert them to a prefix Trie:

    Reverse the word.
    Insert the reversed word into a separate Trie.

By treating the reversed word as a prefix, the suffix-checking problem is reduced to a prefix-matching problem. This allows us to use the same Trie structure for both tasks.

**/
