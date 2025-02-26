#include<set>
#include<map>
#include<queue>
#include<ctime> 
#include<vector>
#include<cstdio>
#include<cstring>
#include<fstream> 
#include<iostream>
#include<windows.h>
using namespace std;
#define inf 0x7fffffff
ofstream fout("Contracts' Imformation.txt");

class Contract{
	public:
		long long int num; //合同编号 
		string u,v; //u->甲方 v->乙方 
		string sum; //内容
		long long int sy,sm,sd; //开始时间 
		long long int ey,em,ed; //结束时间 
		long long int money;	//金额 
		long long int yy,mm,dd; //签订日期
		bool operator < (const Contract &t) const{
			return num<t.num;
		}//内嵌比较函数，num从小到大 
		long long int nn(){
			return yy*520+mm*40+dd;
		}
		long long int ee(){
			return ey*520+em*40+ed;
		}
};
set<Contract> con;

set<pair<long long int,long long int> >srt;//first->yy*520+mm*40+dd,second->num方便排序 
set<pair<long long int,long long int> >ddt;//first->ey*520+em*40+ed,second->num方便排序 
multiset<long long int> cnt; // yy*20+mm 

char csu[10010],csv[10010]; 
void read(){ //从文件中读取（要求文件中原有的是正确的） 
	fout.close();
	FILE *fle=fopen("Contracts' Imformation.txt","r");
	Contract now;
	int n;
	while(1){
		fscanf(fle,"%lld",&now.num);
		if(feof(fle)) break;
		fscanf(fle,"%s %s",csu,csv); 
		now.u=csu,now.v=csv;
		fscanf(fle,"%lld",&now.sum);
		fscanf(fle,"%lld %lld %lld",&now.sy,&now.sm,&now.sd);
		fscanf(fle,"%lld %lld %lld",&now.ey,&now.em,&now.ed);
		fscanf(fle,"%lld",&now.money);
		fscanf(fle,"%lld %lld %lld",&now.yy,&now.mm,&now.dd);
		srt.insert(make_pair(now.nn(),now.num));
		ddt.insert(make_pair(now.ee(),now.num));
		cnt.insert(now.yy*20+now.mm);
	}
	fclose(fle);
	fout.open("Contracts' Imformation.txt"); 
	return;
} 

void clr(){ //清空文件 
	fout.close();
	fstream emp("Contracts' Imformation.txt",ios::out); //把文件转换为只输入，变相清空 
	emp.close();
	fout.open("Contracts' Imformation.txt");
	return;
}

void ffout(Contract now){
	fout<<now.num<<" \n";
	fout<<"甲方："<<now.u<<"    "<<"乙方："<<now.v<<endl;
	fout<<now.sum;
	fout<<"合同生效时间："<<now.sy<<'.'<<now.sm<<'.'<<now.sd<<"—"<<now.ey<<'.'<<now.em<<'.'<<now.ed<<endl;
	fout<<"合同金额："<<now.money<<endl;
	fout<<"签订日期："<<now.yy<<'.'<<now.mm<<'.'<<now.dd<<endl;
	fout<<endl;
	return;
}

void ccout(Contract now){
	cout<<now.num<<" \n";
	cout<<"甲方："<<now.u<<"    "<<"乙方："<<now.v<<endl;
	cout<<now.sum;
	cout<<"合同生效时间："<<now.sy<<'.'<<now.sm<<'.'<<now.sd<<"—"<<now.ey<<'.'<<now.em<<'.'<<now.ed<<endl;
	cout<<"合同金额："<<now.money<<endl;
	cout<<"签订日期："<<now.yy<<'.'<<now.mm<<'.'<<now.dd<<endl;
	cout<<endl;
	return;
}

void prt(bool flag){ //0-输出到文件 1-输出到屏幕 
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(flag) ccout(now);
		else ffout(now);
	} 
	return;
}

void upd(){ //更新文件内容（重新写入）	
	clr();
	prt(0); 
	return;
} 

void del(long long int numb){
	//删除合同 - 利用合同号（合同号应唯一）
	//set的erase函数
	Contract now; 
	now.num=numb;
	if(con.erase(now)){
		srt.erase(make_pair(now.nn(),now.num));
		ddt.erase(make_pair(now.ee(),now.num));
		cnt.erase(now.yy*20+now.mm);
		return;
	}
	bool flag;
	printf("该学号不存在\n重新输入（1） 返回菜单（0）\n请输入：");
	cin>>flag;
	if(flag){
		cin>>numb;
		del(numb);
	}
	return;
}

void add(long long int numb){ //插入信息 
	Contract now;
	now.num=numb;
	printf("请输入甲方：");
	cin>>now.u;
	printf("请输入乙方：");
	cin>>now.v;	
	printf("请输入合同内容，不包含空格及换行符");
	cin>>now.sum;
	printf("请输入合同有效期限的开始时间，年月日以空格隔开");
	cin>>now.sy>>now.sm>>now.sd; 
	printf("请输入合同有效期限的结束时间，年月日以空格隔开");
	cin>>now.ey>>now.em>>now.ed; 	
	printf("请输入合同金额");
	cin>>now.money;
	printf("请输入合同的签订时间，年月日以空格隔开");
	cin>>now.yy>>now.mm>>now.dd; 	
	con.insert(now);
	srt.insert(make_pair(now.nn(),now.num));
	ddt.insert(make_pair(now.ee(),now.num));
	cnt.insert(now.yy*20+now.mm);
	return;
}

void chg(long long int numb){ //添加/修改合同 
	Contract now;
	int flag=0;
	now.num=numb;
	set<Contract>::iterator tmp=con.find(now);
	if(tmp==con.end()){
		add(now.num);
		return;
	}
	printf("此合同编号已存在，存在信息为：\n");
	now= *tmp;
	ccout(now);
	puts("---------") ;
	puts("9、全部修改");
	puts("0、无需修改");
	puts("1、合同编号"); 
	puts("2、合同内容"); 
	puts("3、甲方  4、乙方"); 
	puts("5、开始时间  6、结束时间"); 
	puts("7、合同金额"); 
	puts("8、签订日期");
	puts("请问需要修改的部分为："); 
	cin>>flag;
	if(!flag) return; 
	del(numb);
	switch(flag){
		case 9:{
			add(numb);
			break;
		}
		case 1:{
			cout<<"请输入新的合同编号:";
			cin>>now.num;
			break;
		}
		case 2:{
			cout<<"请输入新的合同内容:";
			cin>>now.sum;
			break;
		}
		case 3:{
			cout<<"请输入新的甲方:";
			cin>>now.u;
			break;
		}
		case 4:{
			cout<<"请输入新的乙方:";
			cin>>now.v;
			break;
		}
		case 5:{
			cout<<"请输入新的开始时间，年月日以空格隔开:";
			cin>>now.sy>>now.sm>>now.sd;
			break;
		}
		case 6:{
			cout<<"请输入新的结束时间，年月日以空格隔开:";
			cin>>now.ey>>now.em>>now.ed;
			break;
		}
		case 7:{
			cout<<"请输入新的合同金额:";
			cin>>now.money;
			break;
		}
		case 8:{
			cout<<"请输入新的签订时间，年月日以空格隔开:";
			cin>>now.yy>>now.mm>>now.dd;
			break;
		}
	} 
	con.insert(now);
	srt.insert(make_pair(now.nn(),now.num));
	ddt.insert(make_pair(now.ee(),now.num));
	cnt.insert(now.yy*20+now.mm);
	return;
}

Contract qry(long long int numb){ //通过学号读取完整数据 
	Contract now;
	now.num=numb;
	set<Contract>::iterator it=con.find(now);
	now= *it;
	return now;
}

void fndu(string nam){ //根据甲方名字寻找 
	//完整遍历全部合同 
	bool flag=true;
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(now.u==nam){
			flag=false;
			ccout(now);
		}
	} 
	if(flag) cout<<"不存在以该名字为甲方的合同\n"; 
	return; 
} 

void fndv(string nam){ //根据乙方名字寻找 
	//完整遍历全部合同 
	bool flag=true;
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(now.v==nam){
			flag=false;
			ccout(now);
		}
	} 
	if(flag) cout<<"不存在以该名字为乙方的合同\n"; 
	return; 
} 

void see(){	//所有合同浏览
	//借用srt获得按顺序的学号，利用自带find函数找到对应信息并输出 
	set<pair<long long int,long long int> >::iterator i; 
	for(i=srt.begin();i!=srt.end();i++){
		pair<long long int,long long int>now= *i;
		ccout(qry(now.second));
	} 
	return;
}

void dte(){	//查询今日到期合同 
	SYSTEMTIME st;
	GetLocalTime(&st);
	long long int nowy=st.wYear,nowm=st.wMonth,nowd=st.wDay;
	cout<<"今日时间： "<<nowy<<"年 "<<nowm<<"月 "<<nowd<<"日 \n\n"; 
	pair<long long int,long long int> now=make_pair(nowy*520+nowm*40+nowd,-1);
	set<pair<long long int,long long int> >::iterator it=ddt.lower_bound(now);
	now= *it;
	if(it==ddt.end() || now.first!=nowy*520+nowm*40+nowd){
		cout<<"今日无到期合同\n";
		return;
	}
	cout<<"今日到期合同如下：\n\n";
	while(it!=ddt.end() && now.first!=nowy*520+nowm*40+nowd){
		ccout(qry(now.second));
		it++;
		now=*it;
	}
	return;
} 

void query(long long int qy,long long int qm){	//以自然月为单位输出
	//运用cnt里的count函数即可 
	cout<<"该月签订合同数量为：";
	cout<<cnt.count(qy*20+qm);
	return;
}

long long int CNT=0,t,n;
string s;
void menu(){ //主菜单 
	system("CLS"); //清屏
	putchar('\n');
	puts("欢迎使用合同管理系统\n功能目录：\n"); 
	puts("1、从文件中读取信息"); 
	puts("2、新增/修改合同"); 
	puts("3、删除合同（按照合同编号）"); 
	puts("4、所有合同浏览（以签订日期排序显示）");
	puts("5、查询自然月签订合同数量"); 
	puts("6、查询合同信息（按照合同编号）");
	puts("7、查询合同信息（按照甲方）");
	puts("8、查询合同信息（按照乙方）");
	puts("9、查询今日到期合同");
	puts("0、保存文件并退出系统");
	puts("\n请输入功能前的序号："); 
	cin>>t;
	system("CLS"); 
	putchar('\n');
	switch(t){
		case 0:{
			puts("文件正在保存");
			upd(); 
			return; 
		}
		case 1:{
			puts("1、从文件中读取信息\n"); 
			read();
			return;	
		}
		case 2:{
			puts("2、新增/修改合同\n");
			printf("请输入合同编号：");
			cin>>n; 
			chg(n);
			return;	
		}
		case 3:{
			puts("3、删除合同（按照合同编号）\n"); 
			printf("请输入合同编号：");
			cin>>n;
			del(n);
			return;	
		}
		case 4:{
			puts("4、将所有合同浏览（以签订日期排序显示）\n");
			see();
			return;	
		}
		case 5:{
			puts("5、查询自然月签订合同数量\n"); 
			printf("请输入年份月份，以空格隔开");
			int qy,qm; 
			cin>>qy>>qm;
			query(qy,qm);
			return;	
		}
		case 6:{
			puts("6、查询合同信息（按照合同编号）\n");
			printf("请输入合同编号：");
			cin>>n;
			Contract now;
			now.num=n;
			set<Contract>::iterator it=con.find(now);
			if(it==con.end()) cout<<"该合同编号不存在";
			else ccout(*it);
			return;
		}
		case 7:{
			puts("7、查询合同信息（按照甲方）\n");
			printf("请输入甲方名字：");
			cin>>s;
			fndu(s);
			return;
		}
		case 8:{
			puts("7、查询合同信息（按照乙方）\n");
			printf("请输入乙方名字：");
			cin>>s;
			fndv(s);
			return;
		}
		case 9:{
			puts("9、查询今日到期合同\n");
			dte();
			return;
		}			
		default:{
			puts("输入错误，请重新输入\n");
			return;
		}		
	}
} 

int main(){
	system("title 合同管理系统目录");
	do{
		menu();
		puts("\n\n运行完成\n请按任意键返回主菜单\n");
		system("pause"); 
	}while(t);
	puts("-\n-\n-\n文件已保存，感谢使用，再见");
	puts("请按任意键退出"); 
	system("pause");
	return 0;
}
