#include <limits.h>
#include <iostream>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

struct Matrix{
	Matrix(int row, int column){
		row_  = row;
		column_ = column;
	}
	int row_;
	int column_;
};
class FullParenthesized{
public:
	FullParenthesized(Matrix matrixs[], int length);
private:
	void GenerateFTTable();
	int MatrixMultiplyOPCount(const Matrix& left, const Matrix& right);
	void PrintTableInfo();
private:
	vector<Matrix> matrixs_;
	int matrix_count_;
	map< pair<int, int>, int> fp_table_;
	map< pair<int, int>, int> fp_key_table_;
};

FullParenthesized::FullParenthesized(Matrix matrix[], int length){
	matrix_count_ = length;
	cout<<"matrix_count_:"<<matrix_count_<<std::endl;
	for(int i = 0; i<matrix_count_; i++){
		matrixs_.push_back(matrix[i]);
	}

	//core functions call
	GenerateFTTable();
	PrintTableInfo();
}

int FullParenthesized::MatrixMultiplyOPCount(const Matrix& left, const Matrix& right){
	int left_matrix_row = left.row_;
	int left_matrix_column = left.column_;
	int right_matrix_row = right.row_;
	int right_matrix_column = right.column_;

	if(left_matrix_column != right_matrix_row){
		cout<<"error: left matrix column not equal with right matrix' row"<<endl;
	}
	return left_matrix_row * left_matrix_column * right_matrix_column;
}

void FullParenthesized::GenerateFTTable(){
	for(int i = 0; i < matrix_count_; i++){
		fp_table_[std::make_pair(i, i)] = 0;
	}

	for(int sub_count = 2; sub_count <= matrix_count_; sub_count++){
		for(int i = 0; i < matrix_count_ - sub_count + 1; i++){
			int left_index = i;
			int right_index = i + sub_count-1;

			// 计算对于矩阵序列left_index -> right_index 最优加全括号的K值
			std::pair<int, int> ft_pair = std::make_pair(left_index, right_index);
			fp_table_[ft_pair] = INT_MAX; 
			for(int k = 1; k < sub_count; k++){
				std::pair<int, int> left_ft_pair = std::make_pair(left_index, left_index + k -1);
				std::pair<int, int> right_ft_pair = std::make_pair(left_index + k, right_index);
				int left_ft_count = fp_table_[left_ft_pair];
				int right_ft_count = fp_table_[right_ft_pair];
				int min_count = left_ft_count + right_ft_count +   matrixs_[left_index].row_ * matrixs_[left_index + k -1].column_ * matrixs_[right_index].column_;
				if(min_count < fp_table_[ft_pair]){
					fp_table_[ft_pair] = min_count;
					fp_key_table_[ft_pair] = k;
				}                                                                                                                                                
			} // for(int k = 1; k < sub_count; k++)
			cout<<"m["<<left_index<<","<<right_index<<"]="<<fp_table_[ft_pair]<<",";
			cout<<"s["<<left_index<<","<<right_index<<"]="<<fp_key_table_[ft_pair]<<";"<<endl;
		} // for(int i = 0; i < matrix_count_ - sub_count + 1; i++)
	} // for(int sub_count = 2; sub_count <= matrix_count_; sub_count++)

}

void FullParenthesized::PrintTableInfo(){
}
int main(int argc, char* argv[]){
	Matrix matrix_array[6] = {Matrix(30, 35), Matrix(35, 15), Matrix(15, 5), Matrix(5, 10), Matrix(10, 20), Matrix(20, 25)};
	FullParenthesized fullParenthesized(matrix_array, sizeof(matrix_array)/sizeof(Matrix                                                                       ));
}