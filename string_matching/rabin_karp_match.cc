#include  <iostream>
#include <string.h>
int char2Int(char c){
	return c ;
}

bool isEqual(char *target, char* pattern, int index){
	int patternLen = strlen(pattern);
	for(int i = 0; i< patternLen; i++){
		//std::cout<<"target[" << index + i<<"] = "<< target[index + i]<<"; "<<"pattern["<<i<<"] = "<<pattern[i]<<std::endl;
		if(target[index + i] != pattern[i]){
			return false;
		}
	}
	return true;
}
void rkMatch(char* target,  char* pattern,  int base, int mode){
	int targetLen = strlen(target);
	int patternLen = strlen(pattern);
	std::cout<<"targetLen:"<<targetLen<<std::endl;
	std::cout<<"patternLen:"<<patternLen<<std::endl;

	int h =  1;
	for (int i = 0; i < patternLen - 1; i++){
		h = (h*10)%mode ;
	}
	std::cout<<"moded h:"<< h <<std::endl;
	// compute  pattern and  t0 's  mode value
	int p_mode = 0;
	int t_0_mode = 0;
	int p_value = 0;
	int t_0_value = 0;
	for( int i = 0; i < patternLen; i++){
		p_value = (p_value * base + char2Int(pattern[i]))%mode;
		t_0_value = (t_0_value * base + char2Int(target[i]))%mode;
	}
	p_mode = p_value;
	t_0_mode = t_0_value;
	
	std::cout << "p_value:"<<p_value<<"; p_mode"<<p_mode<<std::endl;
	std::cout << "t_0_value:" << t_0_value << "; t_0_mode:" << t_0_mode << std::endl;

	int t_index_mode = t_0_mode;
	for(int i = 0; i < (targetLen - patternLen + 1); i++){

		if(t_index_mode == p_mode){
			if(isEqual(target, pattern, i )){
				std::cout<<"matched ,index:" << i <<std::endl;
			}	
		}

		if( i < targetLen - patternLen)
		{	std::cout<<"t_index_mode:"<<t_index_mode<<std::endl;
			std::cout<<"target[i]*h:"<<char2Int(target[i])*h<<std::endl;
			t_index_mode =  (base * (t_index_mode  - char2Int(target[i]) * h ) + char2Int(target[i + patternLen])) % mode;
		 	if(t_index_mode < 0){
		 		t_index_mode = t_index_mode + mode;
		 	}
		}
		std::cout<<i<<" : "<<t_index_mode<<std::endl; 
	} 
}


int main(int argc, char const *argv[])
{
	char target[] = "stringtestlixiaonanonlyfortestlixiaonan";
	char pattern[] = "lixiaonan";
	rkMatch(target, pattern, 10, 13);
	return 0;
}