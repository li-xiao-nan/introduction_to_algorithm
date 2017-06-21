#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using std::cout;
using std::set;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;


class DpLcs{
public:
	DpLcs(string& left, string& right);
	void GenerateLcsTab();
	void PrintLcs(int letf_index, int right_lindex);
	void GenerateLcs(int left_index, int right_lindex);
private:
	string left_;
	int left_string_len_;
	string right_;
	int right_string_len_;
	map< pair<int, int>, int> sub_lcs_tab_;
	// base left string index
	map<pair<int, int>, string> match_char_index_;
};

DpLcs::DpLcs(string& left, string& right)
		: left_(left)
		, right_(right)
		, left_string_len_(left_.length())
		, right_string_len_(right_.length()){
GenerateLcsTab();
PrintLcs(left_string_len_, right_string_len_);
cout<<endl;
GenerateLcs(left_string_len_, right_string_len_);
}

void DpLcs::GenerateLcsTab(){
	for(int i = 0; i < left_string_len_; i++){
		pair<int , int> item = make_pair(i, 0);
		sub_lcs_tab_[item] = 0;

		item = make_pair(0, i);
		sub_lcs_tab_[item] = 0;
	}

	for(int i = 1; i <=left_string_len_; i++){
		char current_left_char = left_[i -1];
		for(int j = 1; j <= right_string_len_; j++){
			char current_right_char = right_[j - 1];
			pair<int, int> current_lcs_item = make_pair(i, j);
			if(current_left_char == current_right_char){
				sub_lcs_tab_[current_lcs_item] = sub_lcs_tab_[make_pair(i - 1, j-1)] + 1;
				match_char_index_[current_lcs_item] = "equal";
			}else{
				if(sub_lcs_tab_[make_pair(i - 1, j)] > sub_lcs_tab_[make_pair(i, j - 1)]){
					sub_lcs_tab_[current_lcs_item]  = sub_lcs_tab_[make_pair(i - 1, j)];
					match_char_index_[current_lcs_item] = "left";
				}else{
					sub_lcs_tab_[current_lcs_item]  = sub_lcs_tab_[make_pair(i, j-1)];
					match_char_index_[current_lcs_item] = "right";
				}
			}
		}
	}

	cout<<endl;
	cout<<"    ";
	for(int i = 0; i <= left_string_len_; i++){
		cout<<i<<"    ";
	}
	cout<<endl;
	for(int i = 0; i <= right_string_len_; i++){
		cout<<i<<"   ";
		for(int j = 0; j <= left_string_len_; j++){
			cout<<sub_lcs_tab_[make_pair(j, i)]<<"    ";
		}
		cout<<endl;	
	}

}
void DpLcs::GenerateLcs(int left_index, int right_index){
	if(left_index == 0 || right_index == 0)
		return;
	char left_current_char = left_[left_index - 1];
	char right_current_char = right_[right_index - 1];
	if(left_current_char == right_current_char){
		GenerateLcs(left_index-1, right_index-1);
		cout<<left_current_char<<" ";
	}else{
		if(sub_lcs_tab_[make_pair(left_index-1, right_index)] > sub_lcs_tab_[make_pair(left_index, right_index -1)]){
			GenerateLcs(left_index - 1, right_index);
		}else{
			GenerateLcs(left_index, right_index - 1);
		}
	}
}

void DpLcs::PrintLcs(int left_index, int right_index){
	if(left_index <= 0 || right_index <= 0){
		return ;
	}
	string state = match_char_index_[make_pair(left_index, right_index)];
	if(state == "left"){
		PrintLcs(left_index-1, right_index);
	}else if (state == "right"){
		PrintLcs(left_index, right_index-1);
	}else{
		PrintLcs(left_index-1, right_index-1);
		cout<<"("<<left_index<<":"<<left_[left_index - 1]<<");  ";
	}
}

int main(int argc, char* argv[]){
	string right = "abcbdab";
	string left = "bdcaba";
	DpLcs dplcs(left, right);
}