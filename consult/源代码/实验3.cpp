// recursive.cpp : �������̨Ӧ�ó������ڵ㡣
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
		cout<<"E'->��"<<endl;
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
		cout<<"T'->��"<<endl;
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
			cout<<"����ı��ʽ���Ϸ�,���Ų�ƥ��"<<endl;
			exit(0);
		}
	}

	else{
		cout<<"����ı��ʽ���Ϸ�����������ȷ���ս����"<<endl;
		exit(0);
	}
}



int main(){

	cout<<"�������ʽ�ķ�Ϊ��"<<endl;
	cout<<"E->E+T|T"<<endl;
	cout<<"T->T*F|F"<<endl;
	cout<<"F->(E)|i"<<endl;
	cout<<endl;

	cout<<"������ݹ�֮����ķ�Ϊ��"<<endl;
	cout<<"E->TE'"<<endl;
	cout<<"E'->+TE'|��"<<endl;
	cout<<"T->FT'"<<endl;
	cout<<"T'->*FT'|��"<<endl;
	cout<<"F->(E)"<<endl;
	cout<<"F->i"<<endl;
	cout<<endl;

	cout<<"������Ҫ�����ľ���(��$��Ϊ������)��"<<endl;
	gets_s(a);
	E();
	if((a[k]=='$'))
		cout<<"����ı��ʽ�Ϸ�"<<endl;
	else
		cout<<"����ı��ʽ���Ϸ���û�н�����ʶ��"<<endl;
}

