#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<string>

using namespace std;

int main()
{
	vector<string> vec;
	vec.push_back("1314 haha");
	vec.push_back("4");
	vector<string> vec2;
	vec2.push_back("1314 haha");
	auto iter = back_inserter(vec2);
	*iter = "hello";
	//reset
	//fill(vec.begin(),vec.end(),string("1314"));

	bool bRet = equal(vec2.begin(),vec2.end(),vec.begin());
	//auto sum = accumulate(vec.begin(),vec.end(),string(""));
	cout<<"bRet"<<bRet<<endl;
	getchar();
	return 0;
}