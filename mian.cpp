#include "TextQuery.h"
#include<iostream>
#include<string>
#include<fstream>
#include<utility>
#include<set>

using namespace std;

string make_plural(size_t count,const string &str1,const string &str2){
   
	return (count==1)? str1:str1+str2;

}

void print_result(const set<TextQuery::line_no> &se,const TextQuery &tq,const string &str){
	//先输出多少行
	typedef set<TextQuery::line_no>::size_type set_no;
	set_no count = se.size();
	cout<<str<<" 出现了 "<<count<<" "<<make_plural(count,"time","s")<<endl;
	for(set<TextQuery::line_no>::const_iterator it = se.begin();it!=se.end();it++)
		cout<<"\t"<<"（第"<<(*it)+1<<"行）  "<<tq.text_line(*it)<<endl;
}


int main(int agrc,char **argv){
	ifstream ifs;
	TextQuery tq;
	if(!tq.open_file(ifs,argv[1]))
	  throw runtime_error("no input file");
	tq.read_file(ifs);

	while(true){
	    cout<<"enter words to look for,or type q to quit."<<endl;
		string str;
		cin>>str;
		if(!cin||str=="q")
	 		break;
		set<TextQuery::line_no> result = tq.run_query(str);
		if(result.size()==0)
			cout<<"word not found!"<<endl;
		else
			print_result(result,tq,str);
	}//while
}//main