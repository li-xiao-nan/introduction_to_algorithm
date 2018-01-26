#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>

using std::string;
using std::vector;


class KmpImpl{
public:

	void Find(const string& target, const string& pattern);
	void GenMatchJumpTable(const string& pattern);
	void PrintMatchIndexs();
	void PrintPMT();

private:
	vector<int> match_jump_table_;
	string pattern_;
	string target_;
	vector<int> match_resutl_;
};


void KmpImpl::Find(const string& target, const string& pattern){
	target_ = target;
	pattern_ = pattern;
	match_jump_table_.resize(pattern_.length() + 1);

	GenMatchJumpTable(pattern_);
	PrintPMT();
	
	// beging to find 
	int target_len = target_.length();
	int pattern_len = pattern_.length(); 
	int begin_match_index = 0;
	while(begin_match_index < target_len - pattern_len){

		int next_forward_step = 1;
		int matched_chars_count = 0;
		for(int j = 0; j < pattern_len; j++){
			char target_char = target_[begin_match_index + j];
			char pattern_char = pattern_[j];
			bool matched = false;
			if(target_char == pattern_char){
				matched_chars_count++;
				matched = matched_chars_count == pattern_len;
			}
			
			if(matched){
				match_resutl_.push_back(begin_match_index);
			}

			if(target_char != pattern_char || matched){
				next_forward_step = match_jump_table_[matched_chars_count];
				std::cout<<"matched_chars_count:"<<matched_chars_count<<"; next_forward_step:"<<next_forward_step<<std::endl;
				break;
			}
			
		}

		begin_match_index += next_forward_step;
	}

}

void KmpImpl::GenMatchJumpTable(const string& pattern){
	int pattern_len = pattern.length();
	string sub_pattern = "";
	for(int sub_pattern_len = 0; sub_pattern_len <= pattern_len; sub_pattern_len++){
		sub_pattern = pattern.substr(0, sub_pattern_len);
		std::cout<<"sub_pattern_len:"<<sub_pattern_len<<std::endl;
		if(sub_pattern_len == 0 || sub_pattern_len == 1){
			match_jump_table_[sub_pattern_len] = 1;
			continue;
		}

		// max sub_pattern of the pattern's suffix
		int max_pattern_suffix = 0;
		for(int j = sub_pattern_len-1; j >= 1; j--){
			// sub_pattern_prefix --> [0,k] k<sub_pattern_len-1;
			// sub_pattern_suffix --> [k,sub_pattern_len-1] k>0; 
			string sub_pattern_prefix = sub_pattern.substr(0, j);
			string sub_pattern_suffix = sub_pattern.substr(sub_pattern_len - j, sub_pattern_len);
			std::cout<<"prefix:"<<sub_pattern_prefix<<"; "<<"suffix:"<<sub_pattern_suffix<<std::endl;
			if(sub_pattern_prefix == sub_pattern_suffix){
				max_pattern_suffix = j;
				break;	
			}
		} // for(int j = sub_pattern_len-1; j >= 1; j--)

		match_jump_table_[sub_pattern_len] = sub_pattern_len - max_pattern_suffix;

	} //for(int i = 0; i < pattern_len; i++)

}

void KmpImpl::PrintPMT(){
	int length = match_jump_table_.size();
	string separator = "  ";
	for(int i = 0; i < length; i++){
		std::cout<<i<<separator;
	}
	std::cout<<std::endl;

	for(int i = 0; i < length; i++){
		std::cout<<match_jump_table_[i]<<separator;
	}

	std::cout<<std::endl;
}

void KmpImpl::PrintMatchIndexs(){
	
	string separator = " ";
	std::cout<<"Pattern:"<<pattern_<<std::endl;
	int target_len = target_.length();
	int pattern_len = pattern_.length();
	for(int i = 0; i < target_len; i++){
		std::cout<<target_[i]<<separator;
	}
	std::cout<<std::endl;

	for(int i = 0; i < target_len; i++){
		const std::vector<int>::iterator iter = std::find(match_resutl_.begin(), match_resutl_.end(), i);
		if(iter != match_resutl_.end()){
			std::cout<<"^"<<separator;
		}else{
			std::cout<<separator<<separator;
		}
	}

	std::cout<<std::endl;
}

int main(int argc, char** argv){

	string target = "dbcababdabeababbabfg";
	string pattern = "aba";
	KmpImpl kmp;
	kmp.Find(target, pattern);
	kmp.PrintMatchIndexs();
}