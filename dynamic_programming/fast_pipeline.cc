#include <iostream>
#include <map>

using std::map;

class FastWay{
public:
	FastWay(int consum_time_array[][7], int switch_line_time[][7]);
	void CollectFastWayInfo();
	void ComputeFastWay();
	void ComputeExpendTime();
private:
	// pipeline1 相关数据结构
	map<int, int> fast_way_map_[2];
	int consum_time_array_1_[7];
	int switch_line_time_1_[7];
	// pipeline2 相关数据结构
	map<int, int> fast_way_map_2_;
	int consum_time_array_2_[7];
	int switch_line_time_2_[7];
	int pipeline_count_;
	int station_count_;
	//fastway
	int fast_way[7];
	int expend_time_;
	int fast_way_02[7];
	int expend_time_02_;
};

FastWay::FastWay(int consum_time_array[][7], int switch_line_time[][7]){
	expend_time_ = 0;
	expend_time_02_ = 0;
	pipeline_count_ = 2;
	station_count_ = 7;
	for(int i = 0; i < station_count_; i++){
		consum_time_array_1_[i] = consum_time_array[0][i];
		switch_line_time_1_[i] = switch_line_time[0][i];

		consum_time_array_2_[i] = consum_time_array[1][i];
		switch_line_time_2_[i] = switch_line_time[1][i];
	}

	CollectFastWayInfo();
	ComputeFastWay();
	ComputeExpendTime();
}

void FastWay::CollectFastWayInfo(){
	// 流水线的站计数从0开始,第0站对应进入流水线前的流程
	// 流水线第一站是固定的，无法调整
	for(int i = 0; i < 2; i++){
		fast_way_map_[0][i] = 1;
		fast_way_map_[1][i] = 2;
	}
	int enter_pipeline1_time = consum_time_array_1_[0];
	int enter_pipeline2_time = consum_time_array_2_[0];

	// pipeline 01
	for(int i = 2; i < 7; i++){
		int pre_index = i - 1;
		int pipeline1_nextstation_expend = consum_time_array_1_[pre_index];
		int pipeline2_nextstation_expend = consum_time_array_2_[pre_index] + switch_line_time_2_[pre_index];
		if(pipeline1_nextstation_expend <= pipeline2_nextstation_expend){
			fast_way_map_[0][i] = 1;
		}else{
			fast_way_map_[0][i] = 2;
		}
	}

	// pipeline 02
	for(int i = 2; i < station_count_; i++){
		int pre_index = i - 1;
		int pipeline1_nextstation_expend = consum_time_array_1_[pre_index] + switch_line_time_1_[pre_index];
		int pipeline2_nextstation_expend = consum_time_array_2_[pre_index];		
		
		if(pipeline1_nextstation_expend <= pipeline2_nextstation_expend){
			fast_way_map_[1][i] = 1;
		}else{
			fast_way_map_[1][i] = 2;
		}
	}

	// print result
	for(int i = 0; i < station_count_; i++){
		std::cout<<i<<"    ";
	}
	std::cout<<std::endl;
	std::cout<<"1    1    ";
	// pipeline 01
	for(int i = 2; i < station_count_; i++){
		std::cout<<fast_way_map_[0][i]<<"    ";
	}
	std::cout<<std::endl;
	// pipeline 02
	std::cout<<"1    1    ";
	for(int i = 2; i < station_count_; i++){
		std::cout<<fast_way_map_[1][i]<<"    ";
	}
	std::cout<<std::endl;
}

void FastWay::ComputeFastWay(){
	fast_way[0] = 1;
	fast_way[1] = 1;
	fast_way_02[0] = 1;
	fast_way_02[1] = 1;
	//pipeline 1
	int line_no = 1;
	std::cout<<std::endl;
	for(int i = 6; i>=2; i--){
		fast_way[i] = line_no;
		if(line_no == 1){
			line_no = fast_way_map_[0][i];
		}else{
			line_no  = fast_way_map_[1][i];
		}
	}

	// pipeline 2
	line_no = 2;
	for(int i = 6; i >=2; i--){
		fast_way_02[i] = line_no;
		if(line_no == 1){
			line_no = fast_way_map_[0][i];
		}else{
			line_no  = fast_way_map_[1][i];
		}	
	}

	for(int i = 0; i < 7; i++){
		std::cout<<i<<"    ";
	}
	std::cout<<std::endl;
	for(int i = 0; i < 7; i++){
		std::cout<<fast_way[i]<<"    ";
	}

	std::cout<<std::endl;
	for(int i = 0; i < 7; i++){
		std::cout<<fast_way_02[i]<<"    ";
	}
	std::cout<<std::endl;
}

void FastWay::ComputeExpendTime(){
	int pre_line_no = 1;
	int current_line_no;
	for(int i = 0; i < station_count_; i++){
		current_line_no = fast_way[i];
		
		if(current_line_no == 1){
			expend_time_ += consum_time_array_1_[i];
		}else{
			expend_time_ += consum_time_array_2_[i];
		}
		
		if(pre_line_no != current_line_no){
			if(pre_line_no == 1){
				expend_time_ += switch_line_time_1_[i];
			}else{
				expend_time_ += switch_line_time_2_[i];
			}
		}
		pre_line_no = current_line_no;
	}
	std::cout<<"line1 expend time is :"<<expend_time_<<std::endl;
}

int main(int argc, char* argv[]){
	int consum_time_array[2][7] = {
		{2, 7, 9, 3, 4, 8, 4},
		{4, 8, 5, 6, 4, 5, 7}
	};

	int switch_line_time[2][7] = {
		{0, 2, 3, 1, 3, 4, 0},
		{0, 2, 1, 2, 2, 1, 0}
	};

	FastWay fast_way(consum_time_array, switch_line_time);
}