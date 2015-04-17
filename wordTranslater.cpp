#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

ifstream& open_file(ifstream &in,const string &file){
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
} 

int main(int argc,char **argv){
  map<string,string> trans_map;
  string key,value;
  if(argc!=3)
	  throw runtime_error("wrong number of arguments");
  ifstream fin;
  //打开词典对照文件
  if(!open_file(fin,argv[1]))
	  throw runtime_error("no transformation file");
  while(fin>>key>>value)
	  trans_map.insert(make_pair(key,value));
  ifstream input;
  //打开要翻译的文件
  if(!open_file(input,argv[2]))
	  throw runtime_error("no input file");
  string line,word;
  while(getline(input,line)){
	  istringstream is(line);
	  //如果是第一个单词的话，就不输出空格
	  bool firstword = true;
	  while(is>>word){
		  if(trans_map.count(word))  
			  word = trans_map[word];
		  if(firstword)
			  firstword = false;
		  else
			  cout<<" ";
		  cout<<word;
	}
	  cout<<endl;
  }
  return 0;
}