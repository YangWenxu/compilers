#include "stdafx.h"

#include<iostream>
#include<string>
#define MAXS 100
using namespace std;

string NODE; //��㼯��
string CHANGE; //�ս������
int N; //NFA����
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
//����
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
				if(he.jihe[m].find(b[j].last[0])==string::npos)			//��ͨ�����������Դﵽ��״̬�ڵ����jihe������ 
					he.jihe[m].append(b[j].last);
}
//���
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
			kong(8-m);		//���Ʊ��ܵĺ��� 
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
	cout<<"������NFA������Ϣ����� ����[��Ϊ*] �յ㣩����#������"<<endl;
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
	/*for(i=0; i<MAXS; i++) {			//b����Ϊ��
		cin>>b[i].first;
		if(b[i].first=="#") break;
		cin>>b[i].change>>b[i].last;
	}*/
	N=11;			//��¼����
	for(i=0; i<N; i++) {					
		if(NODE.find(b[i].first)==string::npos)				
			NODE.append(b[i].first);
		if(NODE.find(b[i].last)==string::npos)				
			NODE.append(b[i].last);
		if((CHANGE.find(b[i].change)==string::npos)&&(b[i].change!="*"))	
			CHANGE.append(b[i].change);
	}
	len=CHANGE.length();
	cout<<"�����������̬���ǣ�"<<endl;
	cin>>endnode;
	for(i=0; i<endnode.length(); i++)				
		if(NODE.find(endnode[i])==string::npos) {
			cout<<"������̬���ڼ����У�����"<<endl;
			return 0;
		}

//���������ж��Ƿ�ΪNFA
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
	if(flag1==1) cout<<"����һ��NFA��"<<endl;
	else cout<<"����һ��DFA��"<<endl;
//���������ж��Ƿ�ΪNFA


	chan *t=new chan[MAXS];
	t[0].ltab=b[0].first;
	h=1;
	eclouse(b[0].first[0],t[0].ltab,b); //��e-clouse
	for(i=0; i<h; i++) {
		for(k=0; k<len; k++) {
			move(t[i],k,b); //��move(I,a)��ת����һ����ĸ 
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
	cout<<endl<<"״̬ת���������£�"<<endl;
	show(len,h,t); //���״̬ת������
	
//״̬��������
	string *d=new string[h];
	NODE.erase();
	cout<<endl<<"��������"<<endl;
	for(i=0; i<h; i++) {
		sta=t[i].ltab;
		t[i].ltab.erase();
		t[i].ltab='A'+i;
		NODE+=t[i].ltab;
		cout<<'{'<<sta<<"}="<<t[i].ltab<<endl;
		for(j=0; j<endnode.length(); j++)			//��ѭ�������ҳ��ս�ڵ� 
			if(sta.find(endnode[j])!=string::npos)
				d[1]=ednode+=t[i].ltab;				// ���ս�ڵ��ltab����ednode�� 
		for(k=0; k<h; k++)
			for(m=0; m<len; m++)
				if(sta==t[k].jihe[m])			//��jihe�����滻Ϊ������ 
					t[k].jihe[m]=t[i].ltab;
	}
	for(i=0; i<NODE.length(); i++)
		if(ednode.find(NODE[i])==string::npos)
			d[0]+=NODE[i];				//d[0]�д���Ƿ��ս�ڵ㣬[1]�д�����ս�ڵ� 
	endnode=ednode;						//����дendcode����ednode����Ϣ�����endnode�� 
	cout<<endl<<"DFA���£�"<<endl;
	show(len,h,t); //���DFA

	
	
	
	cout<<"������̬Ϊ��"<<endnode<<endl;
//DFA��С��
	m=2;
	sta.erase();
	flag=0;
	for(i=0; i<m; i++) {
		for(k=0; k<len; k++) {
			y=m;
			for(j=0; j<d[i].length(); j++) {				//����ͬһ��d�����е�����Ԫ�� ��������ɺ��ʹsta��� 
				for(n=0; n<y; n++) {
					if(d[n].find(t[NODE.find(d[i][j])].jihe[k])<d[n].length()||t[NODE.find(d[i][j])].jihe[k].length()==0) {
						if(t[NODE.find(d[i][j])].jihe[k].length()==0)
							x=m;
						else
							x=n;			//��������������ж�����ͬһ��d�����ĸ����ţ�ͨ����ͬ���������Ƿ񵽴�ͬһ��d���� 						
						if(!sta.length()) {
							sta+=x+48;				//ASCII���48��0 
						} else if(sta[0]!=x+48) {
							d[m]+=d[i][j];
							flag=1;
							d[i].erase(j,1);
							j--;     //���ڲ����˱��ų���ȥ��Ԫ�أ�����ѭ����jҪ���� 
						}
						break; //����n
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
	cout<<endl<<"���ϻ��֣�";
	for(i=0; i<m; i++)
		cout<<"{"<<d[i]<<"} ";
	cout<<endl;


//״̬��������
	chan *md=new chan[m];
	NODE.erase();
	cout<<endl<<"��������"<<endl;
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
	cout<<endl<<"��С��DFA���£�"<<endl;
	show(len,m,md);
	cout<<"������̬Ϊ��"<<endnode<<endl;
	return 0;
}

