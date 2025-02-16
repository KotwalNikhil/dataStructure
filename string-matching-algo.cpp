#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void run() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin); //file input.txt is opened in reading mode i.e "r"
	freopen("output.txt","w",stdout);  //file output.txt is opened in writing mode i.e "w"
	#endif
}

vector<int> rabin_karp(const string& s, const string& pattern) {
	int P = pattern.size();
	int S = s.size();
	int m = 1e9 + 9; 
	int p = 31;


	vector<long long> pow(max(P,S), 1);
	for(int i=1;i<pow.size();i++) {
		pow[i] = (pow[i-1] * p) %m;
	}

	// hash of pattern
	int h_p = 0;
	for(int i=0;i<P;i++) {
		h_p = (h_p + (pattern[i] - 'a' + 1) * pow[i]) % m;
	}

	// pattern on the s
	std::vector<int> v(S + 1, 0);
	for(int i =0;i<S;i++) {
		v[i+1] = (v[i] + (s[i] - 'a' + 1) * pow[i]) % m;
	}

	std::vector<int> ans;
	for(int i=0;i + P <= S; i++) {
		int curr_hash = (v[i + P] - v[i] + m ) %m;
		if (curr_hash == h_p * pow[i] % m){
			ans.push_back(i);
		}
	}

	return ans;
}

void contruct_lps(string const& pattern, vector<int>& lps) {
	int len =0;
	int i =1;
	lps[0] = 0;
	while(i<pattern.size()) {
		if(pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if(len == 0) {
				lps[i] = 0;
				i++;
			}
			else {
				len = lps[len - 1];
			}
		}
	}
}

vector<int> kmp(const string& s, const string& p) {
	int n = s.size();
	int m = p.size();
	vector<int>lps(m);
	contruct_lps(p, lps);
	vector<int>ans;

	int i=0, j=0;
	while(i<n) {
		if(s[i] == p[j]){
			i++;
			j++;

			if(j==m){
				ans.push_back(i-j);
				j= lps[j-1];
			}
		}
		else {
			if(j>0){
				j= lps[j-1];
			}
			else {
				i++;
			}
		}
	}
	return ans;
}
	

int main()
{
	run();
  string s="aaaaa";
  string p="aaa";
  vector<int>occ = rabin_karp(s,p);
  vector<int>occ2 = kmp(s,p);
  for(auto it:occ2)cout<<it<<" ";
   
   



    return 0;
}


