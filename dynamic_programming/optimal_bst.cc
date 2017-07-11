#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::pair;
using std::vector;
using std::make_pair;

class OptimalBst{
public:
	OptimalBst(const vector<float>& key_list, const vector<float>& virtual_key_list);
	void GenOptimalBstInfo();
	void ConstructOptimalBst(int beg, int end, int root);
private:
	vector<float> key_list_;
	vector<float> virtual_key_list_;
	map<pair<int, int>, float> sub_bst_probability_;
	map<pair<int, int>, float> sub_bst_root_;
	map<pair<int, int>, float> sum_probability_;
	int key_count_;
	int virtual_key_count_;
};

OptimalBst::OptimalBst(const vector<float>& key_list, const vector<float>& virtual_key_list){
	key_count_ = key_list.size();
	virtual_key_count_ = virtual_key_list.size();

	key_list_.push_back(0);
	for(int i = 0; i < key_list.size(); i++){
		key_list_.push_back(key_list[i]);
	}

	for(int i = 0; i < virtual_key_list.size(); i++){
		virtual_key_list_.push_back(virtual_key_list[i]);
	}
	for( int i = 0; i<key_list_.size(); i++){
		std::cout<<key_list_[i]<<";";
	}
	std::cout<<std::endl;
	std::cout<<"key list size:"<<key_list_.size()<<"; virtual key list size"<<virtual_key_list_.size()<<std::endl;
	GenOptimalBstInfo();
	std::cout<<std::endl;
	pair<int ,int> key = make_pair(1, key_count_);
	int root = sub_bst_root_[key];
	ConstructOptimalBst(1, key_count_, root);
	std::cout<<std::endl;
}

void OptimalBst::GenOptimalBstInfo(){
	for(int i = 1 ; i <= key_count_; i++){
		pair<int, int> map_key = make_pair(i, i-1);
		sub_bst_probability_[map_key] = virtual_key_list_[i - 1];
		sum_probability_[map_key] = virtual_key_list_[i - 1];
	}

	// 为了方便数组索引计数，在key_list_数组 index = 0的位置放置了填充位，源key_list_的大小为key_list_size_.size() -1;
	// 基于次设置，key_list的迭代遍历可以按照正常的逻辑进行
	for(int sub_bst_length = 1; sub_bst_length <= key_count_; sub_bst_length++){
		std::cout<<"sub_bst_length:"<<sub_bst_length<<std::endl;
		for(int i = 1; i <   key_list_.size() - sub_bst_length+ 1; i++){
			int beg = i;
			int end = i + sub_bst_length -1;
			pair<int, int> current_key = make_pair(beg, end);
			//w[i, j]  = w[i, j-1] + pj + qj
			float current_sum_probability = sum_probability_[make_pair(beg, end-1)] + key_list_[end] + virtual_key_list_[end];
			sum_probability_[current_key] = current_sum_probability;
			float min_sum_probability = 100000;
			int min_root  = 0;
			for(int r = beg; r <= end; r++){
				pair<int, int> left_map_key = make_pair(beg, r -1);
				pair<int, int> right_map_key = make_pair(r+1, end);
				float bst_probability = sub_bst_probability_[left_map_key] + sub_bst_probability_[right_map_key] + current_sum_probability;
				if(bst_probability <min_sum_probability){
					min_sum_probability = bst_probability;
					min_root = r;
				} 
			}
			sub_bst_probability_[current_key] = min_sum_probability;
			sub_bst_root_[current_key] = min_root;
				std::cout<<"root["<<beg<<","<<end<<"]:"<<min_root<<std::endl;
		}
	}
}

void OptimalBst::ConstructOptimalBst(int beg, int end, int root){
	if( beg >= end)
		return ;

	if(beg == 1 && end == key_count_){
		std::cout<<"K"<<root<<" is root"<<std::endl;;
	}

	int left_end = root - 1;
	int right_beg = root +1;

	if(left_end == beg){
		std::cout<<"K"<<left_end<<" is "<<"K"<<root<<" left child"<<std::endl;
		
		std::cout<<"d"<<left_end - 1<<" is "<<"K"<<left_end<<" left child"<<std::endl;
		std::cout<<"d"<<left_end + 1<<" is "<<"K"<<left_end<<" right child"<<std::endl;
	}else{
		pair<int, int> left_key = make_pair(beg, left_end);
		int left_root = sub_bst_root_[left_key];
		std::cout<<"K"<<left_root<<" is "<<"K"<<root<<" left child"<<std::endl;
		ConstructOptimalBst(beg, left_end, left_root);

	}

	if(right_beg == end){
		std::cout<<"K"<<right_beg<<" is "<<"K"<<root<<" right child"<<std::endl;
		std::cout<<"d"<<right_beg - 1<<"is "<<"K"<<right_beg<<" left child"<<std::endl;
		std::cout<<"d"<<right_beg + 1<<"is "<<"K"<<right_beg<<" right child"<<std::endl;
	}else{
		pair<int, int> right_key = make_pair(right_beg, end);
		int right_root = sub_bst_root_[right_key];
		std::cout<<"K"<<right_root<<" is "<<"K"<<root<<" right child"<<std::endl;
		ConstructOptimalBst(right_beg, end, right_root);
	}
}

int main(int argc, char* argv[]){
	float key_array[] = {0.15f, 0.1f, 0.05f, 0.1f, 0.2f};
	float virtual_key_array[] = {0.05f, 0.1f, 0.05f, 0.05f, 0.05f, 0.10f};
	vector<float> key (key_array, key_array + sizeof(key_array)/sizeof(float));
	vector<float> virtual_key (virtual_key_array, virtual_key_array + sizeof(virtual_key_array)/sizeof(float));
	OptimalBst optimalBst(key, virtual_key);
	return 0;
}