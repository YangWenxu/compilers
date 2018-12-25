#include "stdafx.h"

#include<iostream>
#include<string>
#define MAXS 100
using namespace std;

string NODE; //结点集合
string CHANGE; //终结符集合
int N; //NFA边数
struct edge {
	string first;
	string change;
	string last;
};
struct chan {
	string ltab;
	string jihe[MAXS];
};
void kong(int a) {
	int i;
	for(i=0; i<a; i++)
		cout<<' ';
}
//排序
void paixu(string &a) {
	int i,j;
	char b;
	for(j=0; j<a.length(); j++)
		for(i=0; i<a.length(); i++)
			if(NODE.find(a[i])>NODE.find(a[i+1])) {
				b=a[i];
				a[i]=a[i+1];
				a[i+1]=b;
			}
}
void eclouse(char c,string &he,edge b[]) {
	int k;
	for(k=0; k<N; k++) {
		if(c==b[k].first[0])
			if(b[k].change=="*") {
				if(he.find(b[k].last)==string::npos)
					he.append(b[k].last);
				eclouse(b[k].last[0],he,b);
			}
	}
}
void move(chan &he,int m,edge b[]) {
	int i,j,k,l;
	k=he.ltab.length();
	l=he.jihe[m].length();
	for(i=0; i<k; i++)
		for(j=0; j<N; j++)
			if((CHANGE[m]==b[j].change[0])&&(he.ltab[i]==b[j].first[0]))
				if(he.jihe[m].find(b[j].last[0])==string::npos)			//把通过输入量可以达到的状态节点归入jihe【】中 
					he.jihe[m].append(b[j].last);
}
//输出
void show(int len,int h,chan *t) {
	int i,j,m;
	cout<<"   "<<"\t";
	for(i=0; i<len; i++)
		cout<<CHANGE[i]<<"\t";
	cout<<endl<<"-------------------------"<<endl;
	for(i=0; i<h; i++) {
		cout<<' '<<t[i].ltab;
		m=t[i].ltab.length();
		for(j=0; j<len; j++) {
			kong(8-m);		//起到制表功能的函数 
			m=t[i].jihe[j].length();
			cout<<t[i].jihe[j];
		}
		cout<<endl;
	}
}



int main() {
	edge *b=new edge[MAXS];
	int i,j,k,m,n,h,x,y,len;
	bool flag;
	string jh[MAXS],endnode,ednode,sta;
	cout<<"请输入NFA各边信息（起点 条件[空为*] 终点），以#结束："<<endl;
	b[0].first="0";b[0].change="*";b[0].last="1";
	b[1].first="1";b[1].change="*";b[1].last="2";
	b[2].first="1";b[2].change="*";b[2].last="4";
	b[3].first="2";b[3].change="a";b[3].last="3";
	b[4].first="3";b[4].change="*";b[4].last="7";
	b[5].first="4";b[5].change="b";b[5].last="5";
	b[6].first="5";b[6].change="a";b[6].last="6";
	b[7].first="6";b[7].change="*";b[7].last="7";
	b[8].first="7";b[8].change="*";b[8].last="1"; 
	b[9].first="7";b[9].change="*";b[9].last="8";
	b[10].first="0";b[10].change="*";b[10].last="8";
	/*for(i=0; i<MAXS; i++) {			//b数组为边
		cin>>b[i].first;
		if(b[i].first=="#") break;
		cin>>b[i].change>>b[i].last;
	}*/
	N=11;			//记录边数
	for(i=0; i<N; i++) {					
		if(NODE.find(b[i].first)==string::npos)				
			NODE.append(b[i].first);
		if(NODE.find(b[i].last)==string::npos)				
			NODE.append(b[i].last);
		if((CHANGE.find(b[i].change)==string::npos)&&(b[i].change!="*"))	
			CHANGE.append(b[i].change);
	}
	len=CHANGE.length();
	cout<<"结点中属于终态的是："<<endl;
	cin>>endnode;
	for(i=0; i<endnode.length(); i++)				
		if(NODE.find(endnode[i])==string::npos) {
			cout<<"所输终态不在集合中，错误！"<<endl;
			return 0;
		}

//以下用于判断是否为NFA
	int flag1;
	for(i=0; i<N; i++) {
		if(b[i].change=="*"){
			flag1 =1;
			break;
		}
		for(j=i; i<N; i++) {
			if((b[i].first==b[j].first&&b[i].change==b[j].change)||b[i].change=="*") {
				flag1=1;
				break;
			}
			flag1=0;
		}
		if (flag1==1) break;
	}
	if(flag1==1) cout<<"这是一个NFA！"<<endl;
	else cout<<"这是一个DFA！"<<endl;
//以上用于判断是否为NFA


	chan *t=new chan[MAXS];
	t[0].ltab=b[0].first;
	h=1;
	eclouse(b[0].first[0],t[0].ltab,b); //求e-clouse
	for(i=0; i<h; i++) {
		for(k=0; k<len; k++) {
			move(t[i],k,b); //求move(I,a)，转到下一个字母 
			for(j=0; j<t[i].jihe[k].length(); j++)
				eclouse(t[i].jihe[k][j],t[i].jihe[k],b); 
		}
		for(j=0; j<len; j++) {
			paixu(t[i].jihe[j]); 
			for(k=0; k<h; k++) {	
				flag=operator==(t[k].ltab,t[i].jihe[j]);
				if(flag)
					break;
			}
			if(!flag&&t[i].jihe[j].length())			
				t[h++].ltab=t[i].jihe[j];
		}
	}
	cout<<endl<<"状态转换矩阵如下："<<endl;
	show(len,h,t); //输出状态转换矩阵
	
//状态重新命名
	string *d=new string[h];
	NODE.erase();
	cout<<endl<<"重命名："<<endl;
	for(i=0; i<h; i++) {
		sta=t[i].ltab;
		t[i].ltab.erase();
		t[i].ltab='A'+i;
		NODE+=t[i].ltab;
		cout<<'{'<<sta<<"}="<<t[i].ltab<<endl;
		for(j=0; j<endnode.length(); j++)			//此循环用于找出终结节点 
			if(sta.find(endnode[j])!=string::npos)
				d[1]=ednode+=t[i].ltab;				// 把终结节点的ltab存入ednode中 
		for(k=0; k<h; k++)
			for(m=0; m<len; m++)
				if(sta==t[k].jihe[m])			//把jihe【】替换为新名字 
					t[k].jihe[m]=t[i].ltab;
	}
	for(i=0; i<NODE.length(); i++)
		if(ednode.find(NODE[i])==string::npos)
			d[0]+=NODE[i];				//d[0]中存的是非终结节点，[1]中存的是终结节点 
	endnode=ednode;						//重新写endcode，把ednode的信息存入很endnode中 
	cout<<endl<<"DFA如下："<<endl;
	show(len,h,t); //输出DFA

	
	
	
	cout<<"其中终态为："<<endnode<<endl;
//DFA最小化
	m=2;
	sta.erase();
	flag=0;
	for(i=0; i<m; i++) {
		for(k=0; k<len; k++) {
			y=m;
			for(j=0; j<d[i].length(); j++) {				//遍历同一个d【】中的所有元素 ，遍历完成后会使sta清空 
				for(n=0; n<y; n++) {
					if(d[n].find(t[NODE.find(d[i][j])].jihe[k])<d[n].length()||t[NODE.find(d[i][j])].jihe[k].length()==0) {
						if(t[NODE.find(d[i][j])].jihe[k].length()==0)
							x=m;
						else
							x=n;			//这个机制是用于判断属于同一个d【】的各符号，通过相同的输入量是否到达同一个d【】 						
						if(!sta.length()) {
							sta+=x+48;				//ASCII码表48是0 
						} else if(sta[0]!=x+48) {
							d[m]+=d[i][j];
							flag=1;
							d[i].erase(j,1);
							j--;     //由于擦除了被排除出去的元素，所以循环量j要减减 
						}
						break; //跳出n
					}//if 
				}//n
			}//j
			if(flag) {
				m++;
				flag=0;
			}
			sta.erase();
		}//k
	}//i
	cout<<endl<<"集合划分：";
	for(i=0; i<m; i++)
		cout<<"{"<<d[i]<<"} ";
	cout<<endl;


//状态重新命名
	chan *md=new chan[m];
	NODE.erase();
	cout<<endl<<"重命名："<<endl;
	for(i=0; i<m; i++) {
		md[i].ltab='A'+i;
		NODE+=md[i].ltab;
		cout<<"{"<<d[i]<<"}="<<md[i].ltab<<endl;
	}
	for(i=0; i<m; i++)
		for(k=0; k<len; k++)
			for(j=0; j<h; j++) {
				if(d[i][0]==t[j].ltab[0]) {
					for(n=0; n<m; n++) {
						if(!t[j].jihe[k].length())
							break;
						else if(d[n].find(t[j].jihe[k])<d[n].length()) {
							md[i].jihe[k]=md[n].ltab;
							break;
						}
					}
					break;
				}
			}
	ednode.erase();
	cout<<"endnode:"<<endnode<<endl;
	for(i=0; i<m; i++)
		for(j=0; j<endnode.length(); j++)
			if(d[i].find(endnode[j])<d[i].length()&&ednode.find(md[i].ltab))
				if(ednode.find(md[i].ltab)>ednode.length())
				ednode+=md[i].ltab;
	endnode=ednode;
	cout<<endl<<"最小化DFA如下："<<endl;
	show(len,m,md);
	cout<<"其中终态为："<<endnode<<endl;
	return 0;
}

