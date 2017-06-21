#include <iostream>
#include<string>
#include <map>
#include <set>

class AutoMationMatch{
public:
	AutoMationMatch(std::string& target, std::string& pattern);
	void Find();
private:
	void GenAlphaSet();
	int caulateMaxSuffix(int  state, char next_letter);
	void GenJumpTable(std::string pattern, std::string alpha);
private:
	std::string target_;
	std::string pattern_;
	std::string alpha_;
	std::map<int, std::map<char, int> > transition_jump_table_;
};


AutoMationMatch::AutoMationMatch(std:  v:string& target, std::string& pattern)
		: target_(target)
		, pattern_(pattern){
	GenAlphaSet();
	GenJumpTable(pattern_, alpha_);
}

void AutoMationMatch::GenAlphaSet(){
	std::set<char> alpha_set;
	for(int i = 0; i<pattern_.length(); i++){
		alpha_set.insert(pattern_[i]);
	}
	std::set<char>::iterator iter;
	for(iter = alpha_set.begin(); iter != alpha_set.end(); iter++){
		alpha_  += *iter;
	}
	std::cout<<"====== alpha Table ======"<<std::endl<<alpha_<<std::endl;
}

void AutoMationMatch::GenJumpTable(std::string pattern, std::string alpha){
 	std::cout<<"====== Transition Jump Table ======"<<std::endl;
	std::cout<<"state    " ;
	for(int i = 0; i < alpha_.length(); i++){
		std::cout<<alpha_[i] <<"    ";
	}
	std::cout<<std::endl;	
	for(int state = 0; state < pattern_.length() + 1; state++){
		std::map<char, int> state_item;
		std::cout<<"  "<<state<<"      ";
		for(int i = 0; i < alpha_.length(); i++){
			char next_letter = alpha_[i];
			int correspond_state = caulateMaxSuffix(state, next_letter);
			state_item.insert(std::make_pair(next_letter, correspond_state));
			std::cout<<correspond_state<<"    ";
		}
		std::cout<<std::endl;
		transition_jump_table_.insert(std::make_pair(state, state_item));
	}
}

int AutoMationMatch::caulateMaxSuffix(int  state, char next_letter){
	// MaxSuffix ：  Pq最长后缀 pattern 的最长前缀
	std::string  Pq = pattern_.substr(0, state) + next_letter;
	int k = state + 1;
	int newState = k;
	for(; newState  > 0; newState--){
		int j = 0;
		for(; j < newState; j++){
			if( pattern_[j] != Pq[ j + (k - newState)]){
				break;
			} 
		}
		if (j == newState){
			break;
		}
	}
	return newState;
}

void AutoMationMatch::Find(){
	std::cout<<"begin to search......"<<std::endl;
	std::cout<<"Target:"<<target_<<std::endl;
	std::cout<<"Pattern:"<<pattern_<<std::endl;
	int currentState = 0;
	int target_length = target_.length();
	for(int i = 0; i < target_length; i++){
		char item = target_[i];
		std::map<char, int> state_map = transition_jump_table_[currentState];
		if(state_map.find(item) == state_map.end()){
			currentState = 0;
		}else{
			currentState = state_map[item];
		}
		if(currentState == pattern_.length()){
			std::cout<<"match one pattern, index:"<<(i+1+1) - pattern_.length()<<std::endl;
		}
	}
}
int main(){
	std::string pattern("abca");
	std::string target("abcabcdfabcabca");
	AutoMationMatch autoMationMatch(target, pattern);
	autoMationMatch.Find();
}