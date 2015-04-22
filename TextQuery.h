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
	typedef std::vector<std::string>::size_type line_no;//�к�
	//����Ϊ�ӿ�
	//
	void read_file(ifstream &is){
		store_file(is);
	    build_map();
	}
	//store_file�������ı��ļ������ı���ÿ�ζ���һ��.�����ı��洢��vector��
	
	set<line_no> run_query(const string&str) const;
	string  text_line(line_no) const;
	ifstream & open_file(ifstream &in,const string &file);
private:
	//����Ϊ����
   vector<string> lines_of_text;//�洢�����ı�
   map<string,set<line_no> > word_map;//����ÿ�����ʺʹ洢���кŵ�set
   void store_file(ifstream &is);
//�����������map������ÿ�����ʺ����кš� string-set.set���������ʳ��ֵ��к�
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
	//ix�����кš��ڼ���
	for(line_no ix = 0;ix!=lines_of_text.size();ix++){
	    string line = lines_of_text[ix];
		istringstream stream(line);
		string word;
		while(stream>>word){
		//���û�ж�����������ʣ����½�set,�ٲ��롣����Ѿ��������ˣ�ֱ�Ӳ��롣
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
