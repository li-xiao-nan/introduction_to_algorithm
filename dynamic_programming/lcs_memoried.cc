#include <iostream>
#include <map>
#include <string>
#include <limits.h>

using std::string;
using std::map;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

#define INVALID_VALUE -1

class LcsMemorize{
public:
	LcsMemorize(string& left, string right);
	int GenSubLcsLengthMap(int left_length, int right_length);
private:
	void InitializeMap();
	void PrintLcsMap();
	void GenerateLcs(int left_index, int right_index);
private:
	string left_;
	string right_;
	int left_length_;
	int right_length_;
	map<pair<int, int>, int> sub_lcs_length_map_;
};

LcsMemorize::LcsMemorize(string& left, string right)
	: left_(left)
	, right_(right)
	, left_length_(left_.length())
	, right_length_(right_.length()){
	InitializeMap();
	GenSubLcsLengthMap(left_length_, right_length_);
	PrintLcsMap();
	cout<<endl;
	GenerateLcs(left_length_, right_length_);
	cout<<endl;
}
void LcsMemorize::InitializeMap(){
	for(int i = 0; i <= left_length_; i++){
		for(int j = 0; j <= right_length_; j++){
			pair<int, int> item = make_pair(i, j);
			sub_lcs_length_map_[item] = INVALID_VALUE;
			if(i == 0 || j == 0){

				sub_lcs_length_map_[item] = 0;
			}
		}
	}
	PrintLcsMap();
	cout<<endl<<endl;
}
int  LcsMemorize::GenSubLcsLengthMap(int left_index, int right_index){
	pair<int, int> next_pair = make_pair(left_index, right_index);
	if(left_index == 0 || right_index == 0){
		cout<<"reach the bottom"<<endl;
		return sub_lcs_length_map_[next_pair];
	}

	char left_key = left_[left_index - 1];
	char right_key = right_[right_index - 1];
	char current_lcs;
	if(left_key == right_key){
		pair<int, int> pre_pair = make_pair(left_index - 1, right_index - 1);
		if(sub_lcs_length_map_[pre_pair] != INVALID_VALUE){
			sub_lcs_length_map_[next_pair] = sub_lcs_length_map_[pre_pair] + 1;
		}else{
			sub_lcs_length_map_[next_pair] = GenSubLcsLengthMap(left_index - 1, right_index - 1) + 1;
		}
	}else{
		pair<int, int> left_pre_pair = make_pair(left_index - 1, right_index);
		pair<int, int> right_pre_pair = make_pair(left_index, right_index - 1);
		int left_lcs_length;
		int right_lcs_length;
		if(sub_lcs_length_map_[left_pre_pair] != INVALID_VALUE){
			left_lcs_length = sub_lcs_length_map_[left_pre_pair];
		}else{
		 	left_lcs_length = GenSubLcsLengthMap(left_index - 1, right_index);
		}

		if(sub_lcs_length_map_[right_pre_pair] != INVALID_VALUE){
			right_lcs_length = sub_lcs_length_map_[right_pre_pair];
		 }else{
			right_lcs_length = GenSubLcsLengthMap(left_index, right_index - 1);	
		}

		if(left_lcs_length >= right_lcs_length){
			sub_lcs_length_map_[next_pair] = left_lcs_length;
		}else{
			sub_lcs_length_map_[next_pair] = right_lcs_length;
		}
	}
	return sub_lcs_length_map_[next_pair];
}

void LcsMemorize::PrintLcsMap(){

	cout<<endl;
	cout<<"     ";
	for(int i = 0; i <= left_length_; i++){
		if(i > 0){
			cout<<"    "<<left_[i - 1];
		}else{
			cout<<"    "<<i;
		}
	}
	cout<<endl;
	for(int i = 0; i <= right_length_; i++){
		if(i > 0){
			cout<<"    "<<right_[i - 1];
		}else{
			cout<<"    "<<i;
		}
		for(int j = 0; j <= left_length_; j++){
			if(sub_lcs_length_map_[make_pair(j, i)] == -1){
				cout<<"   "<<sub_lcs_length_map_[make_pair(j, i)];
			}else{
				cout<<"    "<<sub_lcs_length_map_[make_pair(j, i)];
			}
		}
		cout<<endl;	
	}
}
void LcsMemorize::GenerateLcs(int left_index, int right_index){
	if(left_index == 0 || right_index == 0)
		return;
	char left_current_char = left_[left_index - 1];
	char right_current_char = right_[right_index - 1];
	if(left_current_char == right_current_char){
		GenerateLcs(left_index-1, right_index-1);
		cout<<left_current_char<<" ";

	}else{
		if(sub_lcs_length_map_[make_pair(left_index-1, right_index)] > sub_lcs_length_map_[make_pair(left_index, right_index -1)]){
			GenerateLcs(left_index - 1, right_index);
		}else{
			GenerateLcs(left_index, right_index - 1);
		}
	}
}
int main(int argc, char* argv[]){
	string right = "abcbdab";
	string left = "bdcaba";
	LcsMemorize lcsMemorize(left, right);
}