// morphology.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<string>
using namespace std;

/*判断读入的字符是否为字母*/
bool isLetter(char c){
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
		return true;
	else
		return false;
}

/*判断读入的字符是否为数字*/
bool isDigit(char c){
	if(c>='0'&&c<='9')
		return true;
	else
		return false;
}

/*判断是否为关键字*/
bool isKey(const char *string){
	if(!strcmp(string ,"int")||!strcmp(string,"char")||!strcmp(string,"void")
		||!strcmp(string ,"if")||!strcmp(string ,"else")||!strcmp(string ,"switch")
		||!strcmp(string ,"case")||!strcmp(string ,"default")||!strcmp(string ,"while")
		||!strcmp(string ,"while")||!strcmp(string ,"do")||!strcmp(string ,"for")
		||!strcmp(string ,"break")||!strcmp(string ,"continue")||!strcmp(string ,"return"))
		return true;
	else
		return false;
}

/*判断是否为单目运算符*/
bool isOperator(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='!'||c=='&'||c=='|'||c=='='||c=='>'||c=='<')
		return true;
	else
		return false;
}

/*判断是否为分隔符*/
bool isSeparator(char c){
	if(c ==',' || c==':'  || c==';' || c=='('  || c==')' || c=='{'  || c=='}')
		return true;
	else
		return false;
}

void main(){
	char a[500],ch;
	string str;
	int i,j,k;
	cout<<"请输入源程序："<<endl;
	gets_s(a);
	j=strlen(a);
	for(i =0;i<j;i++){
		ch =a[i];

		if(isLetter(ch)==true || isDigit(ch) ==true){
			str.append(1,ch);
		}

		else{
			//当遇到非字母和数字时先输出
			int flag=0;
			if(isDigit(str[0])==true){
				 //八进制
				if(str[0] =='0' && str.length()>1 && str[1]!='x'){     
					for(k =1;k<str.length();k++){      //判断是否输入0~7以外的字符
						if(str[k]<'0' || str[k]>'7'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  八进制数字常量"<<endl;
				}

				//十六进制
				else if(str[0]=='0' && str[1]== 'x'){
					for(k =2;k<str.length();k++){      
						if((str[k]>='0' && str[k]<='9') ||(str[k]>='A' && str[k]<='F') || (str[k]>='a' && str[k]<='f')){}
						else{
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<"> 十六进制数字常量"<<endl;
				}


				//十进制
				else{
						for(k =1;k<str.length();k++){     
						if(str[k]<'0' || str[k]>'9'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  十进制数字常量"<<endl;
				}
			}


			else if(isLetter(str[0])==true){
				if(isKey(str.c_str())==true)
					cout<<"<3,"<<str<<"> 关键字"<<endl;
				else
					cout<<"<1,"<<str<<"> 变量"<<endl;
			}
			str.clear();

			//输出运算符
			if(isOperator(ch)){
				if((ch=='&' && a[i+1]=='&')||(ch=='+' && a[i+1]=='+')
					||(ch=='-' && a[i+1]=='-')||(ch=='|' && a[i+1]=='|')
					||(ch=='>' && a[i+1]=='=')||(ch=='<' && a[i+1]=='=')
					||(ch=='=' && a[i+1]=='=')||(ch=='!' && a[i+1]=='=')){
					cout<<"<4,"<<ch<<a[i+1]<<">  运算符"<<endl;
					i++;
				}
				else
					cout<<"<4,"<<ch<<">  运算符"<<endl;
			}

			//输出分隔符
			if(isSeparator(ch)){
				cout<<"<5,"<<ch<<">  分隔符"<<endl;
			}

			//输出字符串常量
			if(ch =='"'){
				str.append(1,ch);
				for(k =i+1;k<j;k++){
					if(a[k] !='"'){
						str.append(1,a[k]);
					}
					else if(a[k] =='"'){
						str.append(1,a[k]);
						cout<<"<2,"<<str<<">  字符串常量"<<endl;
						str.clear();
						break;
					}
				}
				i =k;
			}

			//输出字符常量
			if(ch ==39){
				str.append(1,ch);
				for(k =i+1;k<j;k++){
					if(a[k] !=39){
						str.append(1,a[k]);
					}
					else if(a[k] ==39){
						str.append(1,a[k]);
						cout<<"<2,"<<str<<">  字符串常量"<<endl;
						str.clear();
						break;
					}
				}
				i =k;
			}
		}
	}

	if(!str.empty()){
		int flag=0;
		if(isDigit(str[0])==true){
				 //八进制
			if(str[0] =='0' && str.length()>1 && str[1]!='x'){     
					for(k =1;k<str.length();k++){      //判断是否输入0~7以外的字符
						if(str[k]<'0' || str[k]>'7'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  八进制数字常量"<<endl;
				}

				//十六进制
				else if(str[0]=='0' && str[1]== 'x'){
					for(k =2;k<str.length();k++){      
						if((str[k]>='0' && str[k]<='9') ||(str[k]>='A' && str[k]<='F') || (str[k]>='a' && str[k]<='f')){}
						else{
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<"> 十六进制数字常量"<<endl;
				}


				//十进制
				else{
						for(k =1;k<str.length();k++){     
						if(str[k]<'0' || str[k]>'9'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  十进制数字常量"<<endl;
				}
			}
			else if(isLetter(str[0])==true){
				if(isKey(str.c_str())==true)
					cout<<"<3,"<<str<<"> 关键字"<<endl;
				else
					cout<<"<1,"<<str<<"> 变量"<<endl;
			}
			str.clear();
	}
}

