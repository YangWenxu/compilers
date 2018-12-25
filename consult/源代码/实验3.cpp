// recursive.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

char a[20];
int k =0;
void E();
void E1();
void T();
void T1();
void F();


void E(){
	cout<<"E->TE'"<<endl;
	T();
	E1();
}

void E1(){
	if(a[k]=='+'){
		cout<<"E'->+TE'"<<endl;
		k++;
		T();
		E1();
		
	}

	else{
		cout<<"E'->ε"<<endl;
	}
}

void T(){
	cout<<"T->FT'"<<endl;
	F();
	T1();
}

void T1(){
	if(a[k]=='*'){
		cout<<"T'->*FT'"<<endl;
		k++;
		F();
		T1();
	}

	else{
		cout<<"T'->ε"<<endl;
	}
}

void F(){
	if(a[k]=='i'){
		cout<<"F->i"<<endl;
		k++;
	}

	else if(a[k]== '('){
		k++;
		cout<<"F->(E)"<<endl;
		E();
		if(a[k]==')'){
			k++;
		}

		else{
			cout<<"输入的表达式不合法,括号不匹配"<<endl;
			exit(0);
		}
	}

	else{
		cout<<"输入的表达式不合法，请输入正确的终结符号"<<endl;
		exit(0);
	}
}



int main(){

	cout<<"给定表达式文法为："<<endl;
	cout<<"E->E+T|T"<<endl;
	cout<<"T->T*F|F"<<endl;
	cout<<"F->(E)|i"<<endl;
	cout<<endl;

	cout<<"消除左递归之后的文法为："<<endl;
	cout<<"E->TE'"<<endl;
	cout<<"E'->+TE'|ε"<<endl;
	cout<<"T->FT'"<<endl;
	cout<<"T'->*FT'|ε"<<endl;
	cout<<"F->(E)"<<endl;
	cout<<"F->i"<<endl;
	cout<<endl;

	cout<<"请输入要分析的句子(以$作为结束符)："<<endl;
	gets_s(a);
	E();
	if((a[k]=='$'))
		cout<<"输入的表达式合法"<<endl;
	else
		cout<<"输入的表达式不合法，没有结束标识符"<<endl;
}

