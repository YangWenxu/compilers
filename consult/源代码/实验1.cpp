// morphology.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<iostream>
#include<string>
using namespace std;

/*�ж϶�����ַ��Ƿ�Ϊ��ĸ*/
bool isLetter(char c){
	if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
		return true;
	else
		return false;
}

/*�ж϶�����ַ��Ƿ�Ϊ����*/
bool isDigit(char c){
	if(c>='0'&&c<='9')
		return true;
	else
		return false;
}

/*�ж��Ƿ�Ϊ�ؼ���*/
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

/*�ж��Ƿ�Ϊ��Ŀ�����*/
bool isOperator(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='!'||c=='&'||c=='|'||c=='='||c=='>'||c=='<')
		return true;
	else
		return false;
}

/*�ж��Ƿ�Ϊ�ָ���*/
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
	cout<<"������Դ����"<<endl;
	gets_s(a);
	j=strlen(a);
	for(i =0;i<j;i++){
		ch =a[i];

		if(isLetter(ch)==true || isDigit(ch) ==true){
			str.append(1,ch);
		}

		else{
			//����������ĸ������ʱ�����
			int flag=0;
			if(isDigit(str[0])==true){
				 //�˽���
				if(str[0] =='0' && str.length()>1 && str[1]!='x'){     
					for(k =1;k<str.length();k++){      //�ж��Ƿ�����0~7������ַ�
						if(str[k]<'0' || str[k]>'7'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  �˽������ֳ���"<<endl;
				}

				//ʮ������
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
						cout<<"<2,"<<str<<"> ʮ���������ֳ���"<<endl;
				}


				//ʮ����
				else{
						for(k =1;k<str.length();k++){     
						if(str[k]<'0' || str[k]>'9'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  ʮ�������ֳ���"<<endl;
				}
			}


			else if(isLetter(str[0])==true){
				if(isKey(str.c_str())==true)
					cout<<"<3,"<<str<<"> �ؼ���"<<endl;
				else
					cout<<"<1,"<<str<<"> ����"<<endl;
			}
			str.clear();

			//��������
			if(isOperator(ch)){
				if((ch=='&' && a[i+1]=='&')||(ch=='+' && a[i+1]=='+')
					||(ch=='-' && a[i+1]=='-')||(ch=='|' && a[i+1]=='|')
					||(ch=='>' && a[i+1]=='=')||(ch=='<' && a[i+1]=='=')
					||(ch=='=' && a[i+1]=='=')||(ch=='!' && a[i+1]=='=')){
					cout<<"<4,"<<ch<<a[i+1]<<">  �����"<<endl;
					i++;
				}
				else
					cout<<"<4,"<<ch<<">  �����"<<endl;
			}

			//����ָ���
			if(isSeparator(ch)){
				cout<<"<5,"<<ch<<">  �ָ���"<<endl;
			}

			//����ַ�������
			if(ch =='"'){
				str.append(1,ch);
				for(k =i+1;k<j;k++){
					if(a[k] !='"'){
						str.append(1,a[k]);
					}
					else if(a[k] =='"'){
						str.append(1,a[k]);
						cout<<"<2,"<<str<<">  �ַ�������"<<endl;
						str.clear();
						break;
					}
				}
				i =k;
			}

			//����ַ�����
			if(ch ==39){
				str.append(1,ch);
				for(k =i+1;k<j;k++){
					if(a[k] !=39){
						str.append(1,a[k]);
					}
					else if(a[k] ==39){
						str.append(1,a[k]);
						cout<<"<2,"<<str<<">  �ַ�������"<<endl;
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
				 //�˽���
			if(str[0] =='0' && str.length()>1 && str[1]!='x'){     
					for(k =1;k<str.length();k++){      //�ж��Ƿ�����0~7������ַ�
						if(str[k]<'0' || str[k]>'7'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  �˽������ֳ���"<<endl;
				}

				//ʮ������
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
						cout<<"<2,"<<str<<"> ʮ���������ֳ���"<<endl;
				}


				//ʮ����
				else{
						for(k =1;k<str.length();k++){     
						if(str[k]<'0' || str[k]>'9'){
							cout<<"error	"<<str<<endl;
							flag =1;
							break;
						}
					}
					if(flag ==0)
						cout<<"<2,"<<str<<">  ʮ�������ֳ���"<<endl;
				}
			}
			else if(isLetter(str[0])==true){
				if(isKey(str.c_str())==true)
					cout<<"<3,"<<str<<"> �ؼ���"<<endl;
				else
					cout<<"<1,"<<str<<"> ����"<<endl;
			}
			str.clear();
	}
}

