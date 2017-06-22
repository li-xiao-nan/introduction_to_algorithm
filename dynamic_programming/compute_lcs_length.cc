#include <iostream>
#include <string>
#include <memory>
using std::string;
/**
 * 按照题目的要求使用2 * min（m, n)大小的数组实现LCS的长度
 */
int ComputeLcsLength(string long_string, string short_string){
	int long_len = long_string.length();
	int short_len = short_string.length();
	int array_len = short_len + 1;
	int* lcs[2];
	std::cout<<"array_len:"<<array_len<<std::endl;
	lcs[0] = new int[array_len];
	lcs[1] = new int[array_len];
	int current_row = 0;
	for(int i = 0; i < array_len; i++){
		lcs[0][i] = 0;
	}
	lcs[1][0] = 0;

	for(int i = 1;  i <= long_len; i++){
		char long_current_char = long_string[i - 1];
		current_row = 1;
		for( int j = 1; j <= short_len; j++){
			char short_current_char = short_string[j - 1];
			if( long_current_char == short_current_char){
				lcs[current_row][j] = lcs[current_row -1][j - 1] + 1;
			}else{
				int pre_row = lcs[current_row - 1][j];
				int pre_col = lcs[current_row][j - 1];
				if(pre_row >= pre_col){
					lcs[current_row][j] = pre_row;
				}else{
					lcs[current_row][j] = pre_col;
				}
			}
		} // for
		//讲lcs[1][]内的数据拷贝至lcs[0][]内
		for(int i = 0; i < short_len+1; i++){
			lcs[0][i] = lcs[1][i];
		}
	} // for
	int count  = lcs[0][array_len - 1];
	delete [] lcs[0];
	delete [] lcs[1];
	std::cout<<"lcs length:"<<count<<std::endl;
	return count;
}
//使用min（m, n)长度的数组，完成LCS长度的计算
int ComputeLcsLength02(string long_string, string short_string){
	int long_string_length = long_string.length();
	int short_string_length = short_string.length();
	int tab_length = short_string_length + 1;
	int* sub_lcs_tab = new int[tab_length];
	sub_lcs_tab[0] = 0;
	int forward_step = 0;
	for(int i = 1; i <= long_string_length; i++){
		int pre_lcs_len = -1;
		char current_long_char = long_string[i];
		for(int j = 1; j <= short_string_length; j++){
			char current_short_char = short_string[j];
			int current_lcs_len = 0;
			if(current_long_char == current_short_char){
				current_lcs_len = sub_lcs_tab[j - 1] + 1;
			}else{
				int pre_row_lcs = sub_lcs_tab[j - 1];
				int pre_col_lcs = pre_lcs_len;
				if(pre_row_lcs >= pre_col_lcs){
					current_lcs_len = pre_row_lcs;
				}else{
					current_lcs_len = pre_col_lcs;
				}
			}
			if(pre_lcs_len == -1){
				pre_lcs_len = current_lcs_len;
			}else{
				sub_lcs_tab[j - 1] = pre_lcs_len;
				pre_lcs_len = current_lcs_len;
			}
		} // for (int j .......)
		sub_lcs_tab[tab_length] = pre_lcs_len;

	} // for(int i ........)
	std::cout<<"NO.02 algothrim: lcs_len:"<<sub_lcs_tab[tab_length]<<std::endl;
}
int main(int argc, char* argv[]){
	string right = "abcbdab";
	string left = "bdcaba";
	ComputeLcsLength(right, left);
	ComputeLcsLength02(right, left);
}