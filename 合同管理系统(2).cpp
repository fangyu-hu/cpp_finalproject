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
		long long int num; //��ͬ��� 
		string u,v; //u->�׷� v->�ҷ� 
		string sum; //����
		long long int sy,sm,sd; //��ʼʱ�� 
		long long int ey,em,ed; //����ʱ�� 
		long long int money;	//��� 
		long long int yy,mm,dd; //ǩ������
		bool operator < (const Contract &t) const{
			return num<t.num;
		}//��Ƕ�ȽϺ�����num��С���� 
		long long int nn(){
			return yy*520+mm*40+dd;
		}
		long long int ee(){
			return ey*520+em*40+ed;
		}
};
set<Contract> con;

set<pair<long long int,long long int> >srt;//first->yy*520+mm*40+dd,second->num�������� 
set<pair<long long int,long long int> >ddt;//first->ey*520+em*40+ed,second->num�������� 
multiset<long long int> cnt; // yy*20+mm 

char csu[10010],csv[10010]; 
void read(){ //���ļ��ж�ȡ��Ҫ���ļ���ԭ�е�����ȷ�ģ� 
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

void clr(){ //����ļ� 
	fout.close();
	fstream emp("Contracts' Imformation.txt",ios::out); //���ļ�ת��Ϊֻ���룬������� 
	emp.close();
	fout.open("Contracts' Imformation.txt");
	return;
}

void ffout(Contract now){
	fout<<now.num<<" \n";
	fout<<"�׷���"<<now.u<<"    "<<"�ҷ���"<<now.v<<endl;
	fout<<now.sum;
	fout<<"��ͬ��Чʱ�䣺"<<now.sy<<'.'<<now.sm<<'.'<<now.sd<<"��"<<now.ey<<'.'<<now.em<<'.'<<now.ed<<endl;
	fout<<"��ͬ��"<<now.money<<endl;
	fout<<"ǩ�����ڣ�"<<now.yy<<'.'<<now.mm<<'.'<<now.dd<<endl;
	fout<<endl;
	return;
}

void ccout(Contract now){
	cout<<now.num<<" \n";
	cout<<"�׷���"<<now.u<<"    "<<"�ҷ���"<<now.v<<endl;
	cout<<now.sum;
	cout<<"��ͬ��Чʱ�䣺"<<now.sy<<'.'<<now.sm<<'.'<<now.sd<<"��"<<now.ey<<'.'<<now.em<<'.'<<now.ed<<endl;
	cout<<"��ͬ��"<<now.money<<endl;
	cout<<"ǩ�����ڣ�"<<now.yy<<'.'<<now.mm<<'.'<<now.dd<<endl;
	cout<<endl;
	return;
}

void prt(bool flag){ //0-������ļ� 1-�������Ļ 
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(flag) ccout(now);
		else ffout(now);
	} 
	return;
}

void upd(){ //�����ļ����ݣ�����д�룩	
	clr();
	prt(0); 
	return;
} 

void del(long long int numb){
	//ɾ����ͬ - ���ú�ͬ�ţ���ͬ��ӦΨһ��
	//set��erase����
	Contract now; 
	now.num=numb;
	if(con.erase(now)){
		srt.erase(make_pair(now.nn(),now.num));
		ddt.erase(make_pair(now.ee(),now.num));
		cnt.erase(now.yy*20+now.mm);
		return;
	}
	bool flag;
	printf("��ѧ�Ų�����\n�������루1�� ���ز˵���0��\n�����룺");
	cin>>flag;
	if(flag){
		cin>>numb;
		del(numb);
	}
	return;
}

void add(long long int numb){ //������Ϣ 
	Contract now;
	now.num=numb;
	printf("������׷���");
	cin>>now.u;
	printf("�������ҷ���");
	cin>>now.v;	
	printf("�������ͬ���ݣ��������ո񼰻��з�");
	cin>>now.sum;
	printf("�������ͬ��Ч���޵Ŀ�ʼʱ�䣬�������Կո����");
	cin>>now.sy>>now.sm>>now.sd; 
	printf("�������ͬ��Ч���޵Ľ���ʱ�䣬�������Կո����");
	cin>>now.ey>>now.em>>now.ed; 	
	printf("�������ͬ���");
	cin>>now.money;
	printf("�������ͬ��ǩ��ʱ�䣬�������Կո����");
	cin>>now.yy>>now.mm>>now.dd; 	
	con.insert(now);
	srt.insert(make_pair(now.nn(),now.num));
	ddt.insert(make_pair(now.ee(),now.num));
	cnt.insert(now.yy*20+now.mm);
	return;
}

void chg(long long int numb){ //���/�޸ĺ�ͬ 
	Contract now;
	int flag=0;
	now.num=numb;
	set<Contract>::iterator tmp=con.find(now);
	if(tmp==con.end()){
		add(now.num);
		return;
	}
	printf("�˺�ͬ����Ѵ��ڣ�������ϢΪ��\n");
	now= *tmp;
	ccout(now);
	puts("---------") ;
	puts("9��ȫ���޸�");
	puts("0�������޸�");
	puts("1����ͬ���"); 
	puts("2����ͬ����"); 
	puts("3���׷�  4���ҷ�"); 
	puts("5����ʼʱ��  6������ʱ��"); 
	puts("7����ͬ���"); 
	puts("8��ǩ������");
	puts("������Ҫ�޸ĵĲ���Ϊ��"); 
	cin>>flag;
	if(!flag) return; 
	del(numb);
	switch(flag){
		case 9:{
			add(numb);
			break;
		}
		case 1:{
			cout<<"�������µĺ�ͬ���:";
			cin>>now.num;
			break;
		}
		case 2:{
			cout<<"�������µĺ�ͬ����:";
			cin>>now.sum;
			break;
		}
		case 3:{
			cout<<"�������µļ׷�:";
			cin>>now.u;
			break;
		}
		case 4:{
			cout<<"�������µ��ҷ�:";
			cin>>now.v;
			break;
		}
		case 5:{
			cout<<"�������µĿ�ʼʱ�䣬�������Կո����:";
			cin>>now.sy>>now.sm>>now.sd;
			break;
		}
		case 6:{
			cout<<"�������µĽ���ʱ�䣬�������Կո����:";
			cin>>now.ey>>now.em>>now.ed;
			break;
		}
		case 7:{
			cout<<"�������µĺ�ͬ���:";
			cin>>now.money;
			break;
		}
		case 8:{
			cout<<"�������µ�ǩ��ʱ�䣬�������Կո����:";
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

Contract qry(long long int numb){ //ͨ��ѧ�Ŷ�ȡ�������� 
	Contract now;
	now.num=numb;
	set<Contract>::iterator it=con.find(now);
	now= *it;
	return now;
}

void fndu(string nam){ //���ݼ׷�����Ѱ�� 
	//��������ȫ����ͬ 
	bool flag=true;
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(now.u==nam){
			flag=false;
			ccout(now);
		}
	} 
	if(flag) cout<<"�������Ը�����Ϊ�׷��ĺ�ͬ\n"; 
	return; 
} 

void fndv(string nam){ //�����ҷ�����Ѱ�� 
	//��������ȫ����ͬ 
	bool flag=true;
	set<Contract>::iterator i; 
	for(i=con.begin();i!=con.end();i++){
		Contract now= *i;
		if(now.v==nam){
			flag=false;
			ccout(now);
		}
	} 
	if(flag) cout<<"�������Ը�����Ϊ�ҷ��ĺ�ͬ\n"; 
	return; 
} 

void see(){	//���к�ͬ���
	//����srt��ð�˳���ѧ�ţ������Դ�find�����ҵ���Ӧ��Ϣ����� 
	set<pair<long long int,long long int> >::iterator i; 
	for(i=srt.begin();i!=srt.end();i++){
		pair<long long int,long long int>now= *i;
		ccout(qry(now.second));
	} 
	return;
}

void dte(){	//��ѯ���յ��ں�ͬ 
	SYSTEMTIME st;
	GetLocalTime(&st);
	long long int nowy=st.wYear,nowm=st.wMonth,nowd=st.wDay;
	cout<<"����ʱ�䣺 "<<nowy<<"�� "<<nowm<<"�� "<<nowd<<"�� \n\n"; 
	pair<long long int,long long int> now=make_pair(nowy*520+nowm*40+nowd,-1);
	set<pair<long long int,long long int> >::iterator it=ddt.lower_bound(now);
	now= *it;
	if(it==ddt.end() || now.first!=nowy*520+nowm*40+nowd){
		cout<<"�����޵��ں�ͬ\n";
		return;
	}
	cout<<"���յ��ں�ͬ���£�\n\n";
	while(it!=ddt.end() && now.first!=nowy*520+nowm*40+nowd){
		ccout(qry(now.second));
		it++;
		now=*it;
	}
	return;
} 

void query(long long int qy,long long int qm){	//����Ȼ��Ϊ��λ���
	//����cnt���count�������� 
	cout<<"����ǩ����ͬ����Ϊ��";
	cout<<cnt.count(qy*20+qm);
	return;
}

long long int CNT=0,t,n;
string s;
void menu(){ //���˵� 
	system("CLS"); //����
	putchar('\n');
	puts("��ӭʹ�ú�ͬ����ϵͳ\n����Ŀ¼��\n"); 
	puts("1�����ļ��ж�ȡ��Ϣ"); 
	puts("2������/�޸ĺ�ͬ"); 
	puts("3��ɾ����ͬ�����պ�ͬ��ţ�"); 
	puts("4�����к�ͬ�������ǩ������������ʾ��");
	puts("5����ѯ��Ȼ��ǩ����ͬ����"); 
	puts("6����ѯ��ͬ��Ϣ�����պ�ͬ��ţ�");
	puts("7����ѯ��ͬ��Ϣ�����ռ׷���");
	puts("8����ѯ��ͬ��Ϣ�������ҷ���");
	puts("9����ѯ���յ��ں�ͬ");
	puts("0�������ļ����˳�ϵͳ");
	puts("\n�����빦��ǰ����ţ�"); 
	cin>>t;
	system("CLS"); 
	putchar('\n');
	switch(t){
		case 0:{
			puts("�ļ����ڱ���");
			upd(); 
			return; 
		}
		case 1:{
			puts("1�����ļ��ж�ȡ��Ϣ\n"); 
			read();
			return;	
		}
		case 2:{
			puts("2������/�޸ĺ�ͬ\n");
			printf("�������ͬ��ţ�");
			cin>>n; 
			chg(n);
			return;	
		}
		case 3:{
			puts("3��ɾ����ͬ�����պ�ͬ��ţ�\n"); 
			printf("�������ͬ��ţ�");
			cin>>n;
			del(n);
			return;	
		}
		case 4:{
			puts("4�������к�ͬ�������ǩ������������ʾ��\n");
			see();
			return;	
		}
		case 5:{
			puts("5����ѯ��Ȼ��ǩ����ͬ����\n"); 
			printf("����������·ݣ��Կո����");
			int qy,qm; 
			cin>>qy>>qm;
			query(qy,qm);
			return;	
		}
		case 6:{
			puts("6����ѯ��ͬ��Ϣ�����պ�ͬ��ţ�\n");
			printf("�������ͬ��ţ�");
			cin>>n;
			Contract now;
			now.num=n;
			set<Contract>::iterator it=con.find(now);
			if(it==con.end()) cout<<"�ú�ͬ��Ų�����";
			else ccout(*it);
			return;
		}
		case 7:{
			puts("7����ѯ��ͬ��Ϣ�����ռ׷���\n");
			printf("������׷����֣�");
			cin>>s;
			fndu(s);
			return;
		}
		case 8:{
			puts("7����ѯ��ͬ��Ϣ�������ҷ���\n");
			printf("�������ҷ����֣�");
			cin>>s;
			fndv(s);
			return;
		}
		case 9:{
			puts("9����ѯ���յ��ں�ͬ\n");
			dte();
			return;
		}			
		default:{
			puts("�����������������\n");
			return;
		}		
	}
} 

int main(){
	system("title ��ͬ����ϵͳĿ¼");
	do{
		menu();
		puts("\n\n�������\n�밴������������˵�\n");
		system("pause"); 
	}while(t);
	puts("-\n-\n-\n�ļ��ѱ��棬��лʹ�ã��ټ�");
	puts("�밴������˳�"); 
	system("pause");
	return 0;
}
