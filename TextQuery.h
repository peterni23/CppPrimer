#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<iostream>
#include<sstream>
#include<utility>

using namespace std;

class TextQuery{
public:
	typedef std::vector<std::string>::size_type line_no;//行号
	//以下为接口
	//
	void read_file(ifstream &is){
		store_file(is);
	    build_map();
	}
	//store_file函数从文本文件读入文本，每次读入一行.并将文本存储在vector中
	
	set<line_no> run_query(const string&str) const;
	string  text_line(line_no) const;
	ifstream & open_file(ifstream &in,const string &file);
private:
	//以下为容器
   vector<string> lines_of_text;//存储输入文本
   map<string,set<line_no> > word_map;//关联每个单词和存储其行号的set
   void store_file(ifstream &is);
//这个函数创建map，关联每个单词和其行号。 string-set.set里存这个单词出现的行号
   void build_map();

};

ifstream& TextQuery::open_file(ifstream &fin,const string &file){
	fin.close();
	fin.clear();
	fin.open(file.c_str());
	return fin;
} 

void TextQuery::store_file(ifstream &is){
	string line;
	while(getline(is,line))
	 lines_of_text.push_back(line);
}

void TextQuery::build_map(){
	//ix就是行号。第几行
	for(line_no ix = 0;ix!=lines_of_text.size();ix++){
	    string line = lines_of_text[ix];
		istringstream stream(line);
		string word;
		while(stream>>word){
		//如果没有读到过这个单词，先新建set,再插入。如果已经读到过了，直接插入。
	    word_map[word].insert(ix);  
	}
}
}

set<TextQuery::line_no> 
	TextQuery::run_query(const string &str) const{
	map<string, set<line_no> >::const_iterator loc = word_map.find(str);
	if(loc==word_map.end())
		return set<line_no>();
	else
		return loc->second;
}		


string TextQuery::text_line(line_no lo)const{
	if(lo>lines_of_text.size())
		throw out_of_range("line number out of range");
	else
     	return lines_of_text[lo];
}
