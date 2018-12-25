// LL.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"


#include<iostream>
#include<string>
#include<stack>
using namespace std;

char showStack(stack<char> stackChars){
	while(!stackChars.empty()){
		cout<<stackChars.top();
		stackChars.pop();
	}
	return '\0';
}

char showString(char a[20],char *ip){
	char *t =ip;
	while(*t!='\0'){
		cout<<*t;
		t++;
	}
	return '\0';
}



int main(){
	int k =0;
	int i,j,r,n;
	char G[10][20];//原文法
	char P[10][20];
	char GG[10][20];//消除左递归后的文法
	char PP[10][20];

	string U;		//非终结符号
	string UU;		//消除左递归之后的非终结符号
	string u;		//终结符号
	string uu;		//消除左递归之后的终结符号

	memset(G,0,sizeof(G));
	memset(P,0,sizeof(P));
	memset(GG,0,sizeof(GG));
	memset(PP,0,sizeof(PP));

	//Init_grammer
	cout<<"请输入文法产生式的条数："<<endl;
	cin>>n;
	for(i=0;i<n;i++){
		cout<<"第"<<i+1<<"条文法为："<<endl;
		cin>>G[i];
	}
	for(i =0;G[i][0]!='\0';i++){
		P[k][0] =G[i][0];
		P[k][1] ='-';
		P[k][2] ='>';
		r =3;
		for(j =3;G[i][j]!='\0';j++){
			if(G[i][j]=='|'){
				k++;j++;
				P[k][0] =G[i][0];
				P[k][1] ='-';
				P[k][2] ='>';
				r =3;
				P[k][r] =G[i][j];
				r++;
			}
			else{
				P[k][r] =G[i][j];
				r++;
			}
		}
		k++;
	}
	for(i =0;P[i][0]!='\0';i++){
		if(U.find(P[i][0])==string::npos)
			U.append(1,P[i][0]);
	}

	for(i =0;P[i][0]!='\0';i++){
		for(j =3;P[i][j]!='\0';j++){
			if(u.find(P[i][j])==string::npos && U.find(P[i][j])==string::npos && P[i][j]!='#')
				u.append(1,P[i][j]);
		}
	}



	//判断是否存在左递归，若存在左递归即消除
	int flag =0;
	for(i =0;P[i][0]!='\0';i++){
		if(P[i][0] ==P[i][3]){    //存在左递归情况
				flag =1;
				break;
		}
	}

	if(flag){
		cout<<"该文法存在左递归情况！"<<endl;
		string ar,br;			//存放左递归相关式子
		char C ='A';
		int temp,m=0;
		int flagg;	//flagg =1表示某条规则有左递归情况
		for(i =0;U[i]!='\0';i++){
			flagg =0;
			for(j =0;P[j][0]!='\0';j++){
				if(P[j][0] ==U[i]){
					if(P[j][3]==U[i]){
						flagg =1;
						ar =br ='\0';
						for(temp =4;P[j][temp]!='\0';temp++)
							ar.append(1,P[j][temp]);
						/*if(P[j+1][3]==U[i])		
							ar.append(1,'|');*/
					}
					else{
						for(temp =3;P[j][temp]!='\0';temp++)
							br.append(1,P[j][temp]);
						if(P[j+1][0]==U[i] && P[j+1][3] ==U[i])
							br.append(1,'|');
					}
				}
			}
			if(flagg ==0){
				for(r =0;G[i][r]!='\0';r++)
					GG[m][r] =G[i][r];
					m++;
			}
			else{
				GG[m][0]=U[i];GG[m][1]='-';GG[m][2]='>';
				for(j=1;br[j]!='\0';j++){
					r= 3;
					GG[m][r] =br[j];
					r++;
				}
				while(U.find(C)!=string::npos)
					C++;
				GG[m][r]=C;m++;
				GG[m][0]=C;GG[m][1]='-';GG[m][2]='>';
				r= 3;
				for(j=1;ar[j]!='\0';j++){
					GG[m][r] =ar[j];
					r++;
				}
				GG[m][r]=C;GG[m][r+1] ='|';GG[m][r+2] ='#';
				m++;C++;
			}
		}
		cout<<"消除左递归之后的文法："<<endl;
		for(i=0;i<m;i++){
			for(j=0;GG[i][j]!='\0';j++)
				cout<<GG[i][j];
			cout<<endl;
		}
		cout<<endl;
	}

	else{
		cout<<"该文法不存在左递归情况"<<endl;
		for(i=0;i<n;i++){
			for(j=0;G[i][j]!='\0';j++)
				GG[i][j] =G[i][j];
		}
	}



	//整理消除左递归之后的文法
	k =0;
	for(i =0;GG[i][0]!='\0';i++){
		PP[k][0] =GG[i][0];
		PP[k][1] ='-';
		PP[k][2] ='>';
		r =3;
		for(j =3;GG[i][j]!='\0';j++){
			if(GG[i][j]=='|'){
				k++;j++;
				PP[k][0] =GG[i][0];
				PP[k][1] ='-';
				PP[k][2] ='>';
				r =3;
				PP[k][r] =GG[i][j];
				r++;
			}
			else{
				PP[k][r] =GG[i][j];
				r++;
			}
		}
		k++;
	}

	for(i =0;PP[i][0]!='\0';i++){                  //记录非终结符号
		if(UU.find(PP[i][0])==string::npos)
			UU.append(1,PP[i][0]);
	}

	for(i =0;PP[i][0]!='\0';i++){                  //记录非终结符号
		for(j =3;PP[i][j]!='\0';j++){
			if(uu.find(PP[i][j])==string::npos && UU.find(PP[i][j])==string::npos && PP[i][j]!='#')
				uu.append(1,PP[i][j]);
		}
	}


	//求解FIRST集
	string *FIRST =new string[10];
	int step1 =10,s,count;
	char ch,a;
	while(step1>0){
		step1--;
		for(i =k-1;i>=0;i--){
			r =UU.find(PP[i][0]);
			if(PP[i][3]=='#' && FIRST[r].find('#') ==string::npos)		//右部首符号为空
				FIRST[r].append(1,'#');
			else{
				for(j =3;PP[i][j]!='\0';j++){
					ch =PP[i][j];
					if(uu.find(ch)!=string::npos){                   //右部首符号为终结符号
						if(FIRST[r].find(ch)==string::npos){	
							FIRST[r].append(1,ch);
							break;
						}
						else 
							break;
					}

					if(UU.find(ch)!=string::npos){                  //右部首符号为非终结符号
						s =UU.find(PP[i][j]);
						for(count =0;FIRST[s][count]!='\0';count++){
							a =FIRST[s][count];
							if(a !='#' && FIRST[r].find(a) ==string ::npos)
								FIRST[r].append(1,a);
						}
						if(FIRST[s].find('#') !=string::npos && FIRST[r].find('#')==string::npos)
							FIRST[r].append(1,'#');
						if(FIRST[s].find('#')==string::npos)
							break;
					}
				}
			}
		}
	}
	cout<<"FIRST集："<<endl;
	for(i=0;UU[i]!='\0';i++)
		cout<<"FIRST("<<UU[i]<<")="<<FIRST[i]<<endl;
	cout<<endl;


	//求解FOLLOW集
	string *FOLLOW =new string[10];
	int step2 =10,t;
	FOLLOW[0].append(1,'$');
	while(step2>0){
		step2--;
		for(i =0;i<k;i++){
			for(j =3;PP[i][j]!='\0';j++){
				a =PP[i][j];
				if(UU.find(a)!=string::npos){
					if(PP[i][j+1] =='\0'){
						for(count =0;FOLLOW[UU.find(PP[i][0])][count]!='\0';count++){
							ch =FOLLOW[UU.find(PP[i][0])][count];
							if(FOLLOW[UU.find(PP[i][j])].find(ch)==string::npos)
								FOLLOW[UU.find(PP[i][j])].append(1,ch);
						}
					}

					if(PP[i][j+1]!='\0'){
						for(t =j+1;PP[i][t]!='\0';t++){
							ch =PP[i][t];

							//后跟终结符号
							if(uu.find(ch)!=string::npos && FOLLOW[UU.find(PP[i][j])].find(ch)==string::npos){
								FOLLOW[UU.find(PP[i][j])].append(1,ch);
								break;
							}

							//后跟非终结符号
							if(UU.find(ch)!=string::npos){
								for(r =0;FIRST[UU.find(ch)][r]!='\0';r++){
									a =FIRST[UU.find(ch)][r];		//将first[j+1]加入follow[j]
									if(a !='#' && FOLLOW[UU.find(PP[i][j])].find(a) ==string::npos)
										FOLLOW[UU.find(PP[i][j])].append(1,a);
								}

								//如果#属于first[j+1],将follow[x]加入follow[j]
								if(FIRST[UU.find(ch)].find('#') !=string::npos){
									for(int c =0;FOLLOW[UU.find(PP[i][0])][c]!='\0';c++){
										a =FOLLOW[UU.find(PP[i][0])][c];
										if(FOLLOW[UU.find(PP[i][j])].find(a)==string::npos)
											FOLLOW[UU.find(PP[i][j])].append(1,a);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<"FOLLOW集："<<endl;
	for(i=0;UU[i]!='\0';i++)
		cout<<"FOLLOW("<<UU[i]<<")="<<FOLLOW[i]<<endl;
	cout<<endl;


	//求解SELECT集
	string *SELECT =new string[10];
	for(i =0;i<k;i++){
		for(j =3;PP[i][j]!='\0';j++){
			//右部首为终结符号
			if(uu.find(PP[i][j])!=string::npos && SELECT[i].find(PP[i][j])==string::npos){
				SELECT[i].append(1,PP[i][j]);
				break;			
			}

			//右部首为非终结符号且其FIRST集不包括‘#’
			if(UU.find(PP[i][j])!=string::npos && FIRST[UU.find(PP[i][j])].find('#')==string::npos){
				for(count =0;FIRST[UU.find(PP[i][j])][count]!='\0';count++){
					a =FIRST[UU.find(PP[i][j])][count];
					if(SELECT[i].find(a)==string::npos)
						SELECT[i].append(1,a);
				}
				break;
			}

			//右部首为非终结符号且其FIRST集包括‘#’
			if(UU.find(PP[i][j])!=string::npos && FIRST[UU.find(PP[i][j])].find('#')!=string::npos){
				for(count =0;FIRST[UU.find(PP[i][j])][count]!='\0';count++){
					a =FIRST[UU.find(PP[i][j])][count];
					if(SELECT[i].find(a)==string::npos && a!='#')
						SELECT[i].append(1,a);
				}
			}

			if(PP[i][j]=='#'||PP[i][j]=='\0'){
				for(count =0;FOLLOW[UU.find(PP[i][0])][count]!='\0';count++){
						a= FOLLOW[UU.find(PP[i][0])][count];
						if(SELECT[i].find(a)==string::npos){
							SELECT[i].append(1,a);
						}
					}
				break;
			}
		}
	}
	cout<<"SELECT集："<<endl;
	for(i =0;i<k;i++){
		cout<<"SELECT("<<PP[i]<<")="<<SELECT[i]<<endl;
	}
	cout<<endl;

	//构造预测分析表
	string forecastTable[10][10];
	cout<<"预测分析表："<<endl;
	for(j =1;j<(uu.length()+1);j++)
		forecastTable[0][j] =uu[j-1];
	forecastTable[0][j]='$';
	for(i =1;i<(UU.length()+1);i++)
		forecastTable[i][0] =UU[i-1];
	for(i =0;i<k;i++){
		for(n =0;SELECT[i][n]!='\0';n++){
			if(SELECT[i][n]=='$')
				forecastTable[UU.find(PP[i][0])+1][uu.length()+1]=PP[i];
			else
				forecastTable[UU.find(PP[i][0])+1][uu.find(SELECT[i][n])+1]=PP[i];
		}
	}
	for(i=0;i<(UU.length()+1);i++){
		cout<<"		"<<endl;
		for(j=0;j<(uu.length()+2);j++)
			cout<<forecastTable[i][j]<<"	";
		cout<<endl;
	}


	//根据预测分析表判断表达式是否合法
	uu.append(1,'$');
	cout<<"请输入需要判断的表达式(以$作为结束符)：";
	char  exp_statement[20];
	cin>>exp_statement;
	cout<<"分析栈		余留字符串		所用产生式 "<<endl;
	char *ip =exp_statement;
	stack<char> stackChars;
	stackChars.push('$');
	stackChars.push(UU[0]);
	char X =stackChars.top();
	while(X !='$'){
		if(X ==*ip){
			cout<<showStack(stackChars)<<"		";
			cout<<showString(exp_statement,ip)<<"			匹配";
			cout<<X<<"="<<*ip<<endl;
			stackChars.pop();
			ip++;
		}

		else if(X == '#'){
			stackChars.pop();

		}

		else if(UU.find(*ip)==string::npos && uu.find(*ip)==string::npos){
			cout<<"error!"<<endl;
			break;
		}

		else if(uu.find(X)!=string::npos && X!='#'){
			cout<<"error!"<<endl;
			break;
		}

		else if(forecastTable[UU.find(X)+1][uu.find(*ip)+1].empty()){
			cout<<"error!"<<endl;
			break;
		}

		else if(!forecastTable[UU.find(X)+1][uu.find(*ip)+1].empty()){
			cout<<showStack(stackChars)<<"		";
			cout<<showString(exp_statement,ip)<<"			应用";
			cout<<forecastTable[UU.find(X)+1][uu.find(*ip)+1]<<endl;
			for(i =0;i<k;i++){
				if(PP[i][0]==X && SELECT[i].find(*ip)!=string::npos){
					stackChars.pop();
					for(j =0;PP[i][j]!='\0';j++){}
					for(r =j;r>3;r--){
						stackChars.push(PP[i][r-1]);
					}
					break;
				}
			}
		}
		X =stackChars.top();
	}

	if(X =='$'){
		cout<<showStack(stackChars)<<"		";
		cout<<showString(exp_statement,ip)<<"			";
		cout<<"成功"<<endl;
		cout<<"该表达式符合文法"<<endl;
	}
}