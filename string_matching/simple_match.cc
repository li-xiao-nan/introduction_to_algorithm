#include <iostream>
#include <string.h>

void simpleMatch(char* targetStr, char* patternStr){
	int  targetLen  =  strlen(targetStr);
	int patternLen = strlen(patternStr);

	for(int targetIndex = 0; targetIndex <=targetLen - patternLen; targetIndex++){
		int targetSubIndex = targetIndex;
		int patternIndex = 0;
		for(;  patternIndex < patternLen; patternIndex++ ){
			if( targetStr [targetSubIndex + patternIndex] != patternStr[patternIndex]){
				break;
			}
		}
		if( patternIndex ==  patternLen){
			std::cout<<"find one match ,the index is:"<<  targetIndex <<std::endl;
		}
	}
}


int main(int argc, char const *argv[])
{
	char target[] = "stringtestlixiaonanonlyfortestlixiaonan";
	char pattern[] = "lixiaonan";
	simpleMatch(target, pattern);
	return 0;
}