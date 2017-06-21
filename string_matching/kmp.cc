#include <iostream>
#include <string>
#include <map>

using std::string;
using std::map;
using std::cout;
using std::endl;

class KmpMatch{
public:
	KmpMatch(string& target, string& pattern);
	void Find();
private:
	void GeneratePmt();
	int CaulateMatchSuffix(string sub_pattern);
	int GetSubPatternMatchCount(string sub_pattern);
private:
	string target_;
	string pattern_;
	std::map<string, int> pattern_match_table_;
};

KmpMatch::KmpMatch(string& target, string& pattern)
	: target_(target)
	, pattern_(pattern){

	GeneratePmt();
	Find();
}

void KmpMatch::GeneratePmt(){
	int pattern_len = pattern_.length();
	int sub_pattern_len = 2;
	cout<<"====== Pattern Match Table ======"<<endl;
	// info output
	cout<<"SubPattern    ";
	for(int i = sub_pattern_len - 1; i <= pattern_len; i++){
		cout<<i<<"    ";
	}
	cout<<endl;
	cout<<"Matched       ";
	int current_suffix_value = 0;
	int pre_suffix_value = 0;
	pattern_match_table_.insert(std::make_pair(pattern_.substr(0, 1), 0));
	std::cout<<0<<"    ";
	for(; sub_pattern_len <= pattern_len; sub_pattern_len++){
		string sub_pattern = pattern_.substr(0, sub_pattern_len);
		if(pattern_[pre_suffix_value] == pattern_[sub_pattern_len-1]){
			current_suffix_value = pre_suffix_value + 1;
		}else{
			current_suffix_value = 0;
		}
		pattern_match_table_.insert(std::make_pair(sub_pattern, current_suffix_value));
		pre_suffix_value = current_suffix_value;
		std::cout<<current_suffix_value<<"    ";
	}
	std::cout<<endl;
}

int KmpMatch::CaulateMatchSuffix(string sub_pattern){
	/*
	int sub_pattern_len = sub_pattern.length();
	for(int i = 1; i <= sub_pattern_len; i++){
		int sub_sub_string_len = sub_pattern_len - i;
		string presuffix = sub_pattern.substr(0, sub_sub_string_len);
		string suffix = sub_pattern.substr(i, sub_sub_string_len);
		if(presuffix == suffix){
			return sub_sub_string_len;
		}
	}
	return 0;
	*/

}

int KmpMatch::GetSubPatternMatchCount(string sub_pattern){
	return pattern_match_table_[sub_pattern];
}

void KmpMatch::Find(){
	cout<<"begin to find......"<<endl;
	std::cout<<"Target: "<< target_<<std::endl;
	std::cout<<"Pattern:"<<pattern_<<std::endl;
	int target_len = target_.length();
	int pattern_len = pattern_.length();
	for(int i = 0; i < (target_len - pattern_len) + 1; ){
		int j = 0;
		for(; j < pattern_len; j++){
			if(target_[i + j] != pattern_[j]){
				int match_count  = j ;
				if(j == 0){
					i++;
				}else{
					string match_string = pattern_.substr(0,match_count);
					std::cout<<"match_string:"<<match_string<<std::endl;
					int pre_suffix_match_count = GetSubPatternMatchCount(match_string);
					int forward_count = match_count - pre_suffix_match_count;
					std::cout<<"forward_count:"<<forward_count<<std::endl;
					i += forward_count;
				}
				break;
			}
		}
		if(j == pattern_len){
			cout<<"match pattern, index:"<<i+1<<std::endl;
			string match_string = pattern_.substr(0, j);
			int pre_suffix_match_count = GetSubPatternMatchCount(match_string);
			int forward_count = pattern_len - pre_suffix_match_count;
			i += forward_count;
		}
	}
}

int main(){
	string pattern = "ababaca";
	string target = "abcababcababaca";
	KmpMatch kmpMatch(target, pattern);
}