#include <iostream>
#include <map>
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

void FindLongestSequence(int sequence[]){
	vector<int> longest_sub_sequence;
	int count = sizeof(sequence) / sizeof(int);
	for(int i = 1; i < count; i++){
		 int next = sequence[i];
		 int sub_sequence_count = longest_sub_sequence.size();
		 int  sub_sequence_end  = sequence[longest_sub_sequence[sub_sequence_count - 1]]
		 if(next > sub_sequence_end){
		 	longest_sub_sequence.push_back(i);
		 }else{
		 	int sub_sequence_end_index = longest_sub_sequence[sub_sequence_count - 1];
		 	int other_count = i - sub_sequence_end_index;
		 	if(other_count > sub_sequence_count){
		 		int j = sub_sequence_end_index + 2
		 		for(; j <= i; j++){
		 			if(sequence[j - 1] > sequence[j]){
		 				break;
		 			}
		 		}
		 	}
		 }
	}
}