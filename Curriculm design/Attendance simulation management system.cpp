#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include <iomanip>   //setw()
#include <fstream>   //文件管理
using namespace std;


int CLASS;
static int pe;
const int tmax=200;    //学生最大个数

//定义基类Student
class Student {
	private:
		friend class StudentClock_op;         ///友元类
		int num;              //学号
		string name;         //名字
		string sex;          //性别
		int grade;          //出勤情况（分数体现）
		int count;          //缺课数
	public:

		Student(int n=0,string nam=" ",string s=" " ,int gra=0,int co=0);        //构造函数
		void set(int n,string nam,string s);
		void set2(int n,string nam,string s,int grade ,int count);                          //设置数据成员的值
		void input();
		void input2();                   //s输入缺勤学生学号                            //输入数据成员的值
		void output1();
		void output2();                                                 //输出数据成员的值
		int  getnum() {
			return num;    //获取学号
		}
		string getname() {
			return name;   //获取姓名
		}
		string getsex() {
			return sex;     //获取性别
		}
		int   getgrade () {
			return grade;   //获取考勤分数
		}
		int getcount() {
			return count;
		}	   //获取缺课数
};

//类外定义成员函数
Student::Student(int n,string nam,string s,int gra,int co) {
	num=n;
	name=nam;
	sex=s;
	grade=gra;
	count=co;
}
void Student::set(int n,string nam,string s) {
	num=n;
	name=nam;
	sex=s;
}
void Student::set2(int n,string nam,string s,int gra,int co) {
	num=n;
	name=nam;
	sex=s;
	grade=gra;
	count=co;
}
void Student::input() {
	cout<<"学号：";
	cin>>num;
	cout<<"姓名：";
	cin>>name;
	cout<<"性别：";
	cin>>sex;
}
void Student::input2() {
	cin>>num;
}

void Student::output1() {
	cout<<"  学号："<<setw(1)<<num;
	cout<<"  姓名： "<<setw(5)<<name;
	cout<<"  性别： "<<setw(1)<<sex;
}
void Student::output2() {
	cout<<"  学号："<<setw(1)<<num;
	cout<<"  姓名： "<<setw(1)<<name;
	cout<<"  性别： "<<setw(1)<<sex;
	cout<<"考勤分数:"<<setw(3)<<grade;
	cout<<"缺课数:"<<setw(3)<<count<<endl;
}


/*Student类结束*/

/*StudentInfo类,从Student类继承，学生基本信息与操作*/
class StudentInfo: public Student {
	public:
		StudentInfo(int n=0,string nam=" ",string s=" "):Student(n,nam,s) {
		}
		void input() {
			cout<<"请输入学生的信息："<<endl;
			Student::input();
		}
		void output() {
			Student::output1();
			cout<<endl;
		}
};
/*StudentInfo类结束*/

/*StudentInfo_op类,用来对学生信息进行管理*/
class StudentInfo_op {
		StudentInfo t[tmax];    //用数组t保存所有学生信息
		int top;                 //top表示数组中学生数目
	public:
		StudentInfo_op() {
			top=0;   //构造函数
		}
		/*以下是管理功能成员函数*/
		void add();                    //添加学生
		void show();                   //显示学生
		void total();                  //统计人数
		void modify();                   //修改功能菜单
		void modify_num();               //按学号修改
		void modify_name();              //按姓名修改
		void Delete();                 //删除功能菜单
		void Delete_num();             //按学号删除
		void Delete_name();            //按姓名删除
		void save();                   //保存文件
		void read();                   //读取文件

};
//类外定义成员函数
void StudentInfo_op::add() {        //添加学生
	if(top>=tmax) {
		cout<<"空间已满，不能添加!!!"<<endl;
		return;
	}
	StudentInfo te;
	cout<<"正在添加学生......"<<endl;
	te.input();
	t[top]=te;
	for(int i=0; i<top; i++) {
		if(te.getnum()==t[i].getnum()) {
			cout<<"该学号已存在，添加失败!"<<endl;
			return ;
		}
	}
	cout<<"添加成功!!!"<<endl;
	cout<<endl;
	top++;     // 调整学生个数
	pe++;      //统计添加多少人，考勤用
}

void StudentInfo_op::show() {       //显示学生信息
	if(top==0) {
		cout<<"没有信息!"<<endl;
		return;
	}
	for(int i=0; i<top; i++)
		t[i].output2();
	cout<<endl;
}

void StudentInfo_op::total() {       //统计学生数目
	cout<<"学生总人数为："<<top<<" 人"<<endl;
}
/*修改功能*/
void StudentInfo_op::modify() {        //修改子菜单
	if (top==0) {
		cout<<"没有学生信息!"<<endl;
		return;
	}
	int choice=1;
	do {
		cout<<"  _______________________编辑_______________________________"<<endl;
		cout<<"||                                                        ||"<<endl;
		cout<<"||        1 : 按学号       2 : 按姓名       0 :退出       ||"<<endl;
		cout<<"||                                                        ||"<<endl;
		cout<<"___________________________________________________________"<<endl;
		cout<<"请输入您的选择:";
		cin>>choice;
		switch(choice) {
			case 1:
				modify_num();
				//cout<<"按学号修改."<<endl;
				break;
			case 2:
				modify_name();
				//cout<<"按姓名修改."<<endl;
				break;
			case 0:
				cout<<"您已安全退出."<<endl;
				break;
			default:
				cout<<"没有此选项,请重选."<<endl;
				break;
		}
	} while(choice!=0);
}

void StudentInfo_op::modify_num() {      //按学号修改
	int x1;
	cout<<"请输入要编辑的学生的学号：";
	cin>>x1;
	for(int i=0; i<top; i++) {
		if(t[i].getnum()==x1) {
			t[i].output();
			cout<<endl;

			t[i].input();
			while(t[i].getnum()!=x1) {
				cout<<"学号不能修改！";
				t[i].input();
			}

			cout<<"修改成功!"<<endl;
			t[i].output();
			return;
		}
	}
	cout<<"该学生不存在!"<<endl;
}
void StudentInfo_op::modify_name() {   //按姓名修改
	string h1;
	cout<<"请输入要编辑的学生的姓名:";
	cin>>h1;
	for(int i=0; i<top; i++) {
		if(t[i].getname()==h1) {
			int n=t[i].getnum();
			t[i].output();
			cout<<endl;
			t[i].input();
			while(t[i].getnum()!=n) {
				cout<<"学号不能修改！";
				t[i].input();
			}
			cout<<"修改成功!"<<endl;
			t[i].output();
			return ;
		}
	}
	cout<<"该学生不存在!"<<endl;
}

/*删除功能*/
void StudentInfo_op:: Delete() {           //删除子菜单
	if (top==0) {
		cout<<"没有学生信息!"<<endl;
		return;
	}
	int choice;
	do {
		cout<<" ___________________删除__________________________________  "<<endl;
		cout<<"||                                                        ||"<<endl;
		cout<<"||       1 : 按学号        2 : 按姓名       0 :退出       ||"<<endl;
		cout<<"||                                                        ||"<<endl;
		cout<<"____________________________________________________________"<<endl;
		cout<<"请输入您的选择:";
		cin>>choice;
		switch(choice) {
			case 1:
				Delete_num();
				break;
			case 2:
				Delete_name();
				break;
			case 0:
				cout<<"您已安全退出."<<endl;
				break;
			default:
				cout<<"没有此选项,请重选."<<endl;
				break;
		}
	} while(choice!=0);
}
void StudentInfo_op:: Delete_num() {        ///按学号进行删除
	int i;
	char c1;
	int f1;
	cout<<"请输入要删除的学生学号:";
	cin>>f1;
	for( i=0; i<top; i++) {                //查找该学号
		if(t[i].getnum()==f1) {
			t[i].output();
			break;
		}
	}
	if(i>=top) {
		cout<<"无此学生!";
		return ;
	}

	cout<<"是否删除此项（是:y/Y,否：n/N）:";
	cin>>c1;
	if(c1=='y'||c1=='Y') {
		for(int k=i; k<top-1; k++) {
			t[k]=t[k+1];               //从i开始，后往前覆盖
		}
		cout<<"删除成功!"<<endl;
		top--;                         //人数减一
		return ;
	} else
		cout<<"没有删除该学生!"<<endl;
}
void StudentInfo_op:: Delete_name() {                ///按学号进行删除
	int i;
	char c3;
	string r;
	cout<<"请输入要删除的学生姓名:";                //查找该姓名
	cin>>r;
	for( i=0; i<top; i++) {
		if(t[i].getname()==r) {
			t[i].output();
			break;
		}
	}
	if(i>=top) {
		cout<<"无此学生!";
		return ;
	}

	cout<<"是否删除此项（是:y/Y,否：n/N）:";
	cin>>c3;
	if(c3=='y'||c3=='Y') {
		for(int k=i; k<top-1; k++) {                 //删除
			t[k]=t[k+1];
		}
		cout<<"删除成功!"<<endl;
		top--;                                       //人数减一
		return ;
	} else
		cout<<"没有删除该学生!"<<endl;
}
/* 文件管理 */
void StudentInfo_op::save() {     ///保存信息至文件
	ofstream out("D:\\1\\学生管理.txt",ios::out);    //假设文件保存为D盘根目录下
	if (!out) {
		cerr<<" 打开失败!"<<endl;
		return;
	}
	for (int i=0; i<top; i++) {
		out<<t[i].getnum()<<"\t";		//写进磁盘保存，以下同理
		out<<t[i].getname()<<"\t";
		out<<t[i].getsex()<<"\t";         //<<endl        <<endl
		out<<t[i].getgrade()<<"\t";
		out<<t[i].getcount()<<"\t"<<endl;
	}
	cout<<"保存成功!"<<endl;
	cout<<endl;
	out.close();
}



void StudentInfo_op::read() {      ///从文件读取信息
	ifstream in("D:\\学生管理.txt",ios::in);
	int num;
	string sex;
	string name;
	int grade;
	int count;
	if (!in) {
		cerr<<"打开失败!"<<endl;
		return ;
	}
	int i=0;
	while(in>>num>>name>>sex>>grade>>count  ) { //这种方法可以忽略文件最后的空行，避免while(!in.eof())产生的错误
		t[i].set2(num,name,sex,grade,count ); //
		i++;
	}
	top=i;
	cout<<"读取成功!"<<endl;
	in.close();
}



/*学生基本信息与操作子菜单*/
void StudentInfoMenu() {
	StudentInfo_op a;    //定义学生管理类型对象a
	int choice=1;
	while(choice!=0) {
		cout<< "                              ***学生***                                   "<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"|  1.添加   2.修改  3.统计  4.删除  5.显示  6.保存 7.读取  0.返回         |"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"输入您操作的选项：";
		cin>>choice;
		switch(choice) {
			case 1:
				a.add();
				break;
			case 2:
				a.modify();
				break;
			case 3:
				a.total();
				break;
			case 4:
				a.Delete();
				break;
			case 5:
				a.show();
				break;
			case 6:
				a.save();
				break;
			case 7:
				a.read();
				break;
			case 0:
				cout<<"退出成功!"<<endl;
				break;
			default:
				cout<<"无此选项,请重试!"<<endl;
				break;
		}
	}
}


class StudentClock: public Student {
	public:
		StudentClock(int n=0,string nam=" ",string s=" ",int gra=0,int co=0):Student(n,nam,s,gra,co) {
		}
		void input() {
			cout<<"请输入学生的信息："<<endl;
			Student::input();
		}
		void output() {
			Student::output2();
			cout<<endl;
		}
		void save();
		void mark();
};

class StudentClock_op {
		StudentClock t[tmax];    //用数组t保存所有学生信息
		int top;                 //top表示数组中学生数目
	public:
		StudentClock_op() {
			top=0;   //构造函数
		}
		void start();
		void save();
		void mark();

};

void StudentClock_op::mark() {
	//StudentClock d;
	StudentClock c;
	for(int i=0; i<CLASS; i++) {
		cout<<"请输入第"<<i+1<<"节课缺勤的学生学号并以0结束"<<endl;
		for(int j=0; j<pe; j++) {                      ///每次添加记录的人数控制上限输入
			c.input2();
			if(c.getnum()==0)
				break;
		}
	}
	for(int i=0; i<pe; i++) {
		if(c.getnum()==t[i].getnum()) {
			t[i].count++;
			//return ;
		}
		t[i].grade=100-t[i].count;
	}
	fstream out("D:\\学生管理.txt",ios::out |ios::in); //|ios::binary 
	if (!out) {
		cerr<<" 打开失败!"<<endl;
		return;
	}
	//	out.seekp(10,ios::beg);
	for (int i=0; i<pe; i++) {        //top3 
	out.seekg(10,ios::cur);   
		out<<t[i].getgrade()<<"\t";
		out<<t[i].getcount()<<endl;
	}
 
// 	fstream out("D:\\学生管理.txt",ios::out |ios::app);  
//	if (!out) {
//		cerr<<" 打开失败!"<<endl;
//		return;
//	}
//	//	out.seekp(10,ios::beg);
//	for (int i=0; i<pe; i++) {        //top3 
//	out.seekp(10,ios::beg);
//		out<<t[i].getgrade()<<"\t"<<t[i].getcount()<<endl;
//		//out<<t[i].getcount()<<endl;
//	}

}


void start() {
	cout<< "                              ***考勤模拟开始***                           "<<endl;
	cout<<"######################################"<<endl;
	cout<<"\t请输入课程节数："<<endl;
	cout<<"######################################"<<endl;
	cin>>CLASS;

	StudentClock_op e;
	e.mark();
	cout<<"#######################################"<<endl;
	cout<<"#               考勤完毕              #"<<endl;
	cout<<"#######################################"<<endl;

}
//*学生考勤模拟子菜单*/
void StudentClockMenu() {

	int choice=1;
	while(choice!=0) {
		cout<< "                       ***学生考勤菜单***                                 "<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"|             1.开始                             0.返回                   |"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"输入您操作的选项：";
		cin>>choice;
		switch(choice) {
			case 1:
				start();
				break;
			case 0:
				cout<<"退出成功!"<<endl;
				break;
			default:
				cout<<"无此选项,请重试!"<<endl;
				break;
		}
	}
}




class StudentSearch:public Student {
	public:
		StudentSearch(int n=0,string nam="",string s="",int gra=0,int co=0  ):Student(n,nam,s,gra,co ) { ///             ////带默认参数
		}
		void input() {
			cout<<"请输入学生的信息："<<endl;
			Student::input();
		}
		void output2() {
			Student::output2();
			cout<<endl;
		}

};



/*StudentSarch_op类,用来查询学生出勤管理*/
class StudentSearch_op {
		StudentSearch p[tmax];    //用数组t保存所有学生信息
		int tot;                 //top表示数组中学生数目
	public:
		StudentSearch_op() {
			tot=0;   //构造函数
		}
		/*功能成员函数*/
		void show();                   //显示学生
		void total();                  //统计人数
		void read2();                   //读取文件
		void search();
		void search_num();
		void search_name();
};

void StudentSearch_op::show() {       //显示学生信息
	if(tot==0) {
		cout<<"没有信息!"<<endl;
		return;
	}
	for(int i=0; i<tot; i++)
		p[i].output2();  ///output1()
	cout<<endl;
}
void StudentSearch_op::total() {       //统计学生数目
	cout<<"学生总人数为："<<tot<<" 人"<<endl;
}
/* 文件管理 */
void StudentSearch_op::read2() {      ///从文件读取信息
	ifstream in("D:\\学生管理.txt",ios::in);
	int num;
	string sex;
	string name;
	int grade;
	int count;
	if (!in) {
		cerr<<"打开失败!"<<endl;
		return ;
	}
	int i=0;
	while(in>>num>>name>>sex>>grade>>count) { //这种方法可以忽略文件最后的空行，避免while(!in.eof())产生的错误>>gra>>co
		p[i].set2 (num,name,sex,grade,count );             //     无法读取   用set2后相当于重新设置数据成员？？
		i++;
	}
	tot=i;
	cout<<"读取成功!"<<endl;
	in.close();
}
/*查找功能*/
void StudentSearch_op::search() {            //查找子菜单
	if(tot==0) {
		cout<<"没有学生信息!"<<endl;
		return ;
	}
	int choice;
	do {
		cout<<"                 ***查找***                                 "<<endl;
		cout<<"____________________________________________________________"<<endl;
		cout<<"||       1 ： 按编号       2 :按姓名       0 :退出        ||"<<endl;
		cout<<"||                                                        ||"<<endl;
		cout<<"------------------------------------------------------------"<<endl;
		cout<<"请输入您的选择:";
		cin>>choice;
		switch(choice) {
			case 1:
				search_num();
				break;
			case 2:
				search_name();
				break;
			case 0:
				cout<<"您已安全退出."<<endl;
				break;
			default:
				cout<<"没有此选项,请重选."<<endl;
				break;
		}
	} while(choice!=0);
}

void StudentSearch_op::search_num() {                      //按编号进行查找
	int y1;
	cout<<"请输入要查询学生的编号：";
	cin>>y1;
	for(int i=0; i<tot; i++) {
		if(p[i].getnum()==y1) {
			cout<<"找到这个学生了，其信息为："<<endl;
			p[i].output2();   ///output1()
			return;
		}
	}
	cout<<"该学生不存在!"<<endl;
}
void StudentSearch_op::search_name() {                    //按姓名进行查找
	string s1;
	cout<<"请输入要查询的学生姓名：";
	cin>>s1;
	for(int i=0; i<tot; i++) {
		if(p[i].getname()==s1) {
			cout<<"找到这个学生了，其信息为："<<endl;
			p[i].output2(); ///output1()
			return;
		}
	}
	cout<<"该学生不存在!"<<endl;
}



/* 学生出勤情况查询子菜单 */
void StudentSearchMenu() {

	StudentSearch_op c;    //定义学生出勤查询管理类型对象c
	int choice=1;
	while(choice!=0) {
		cout<< "              ***学生出勤情况查询子菜单***                                 "<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"|             1.查询   2.统计   3.显示   4.读取  0.返回                   |"<<endl;
		cout<<"|                                                                         |"<<endl;
		cout<<"——————————————————————————————————————"<<endl;
		cout<<"输入您操作的选项：";
		cin>>choice;
		switch(choice) {
			case 1:
				c.search();
				break;
			case 2:
				c.total();
				break;
			case 3:
				c.show();
				break;
			case 4:
				c.read2();
				break;
			case 0:
				cout<<"退出成功!"<<endl;
				break;
			default:
				cout<<"无此选项,请重试!"<<endl;
				break;
		}
	}
}



int main() {


	cout<<"                  ###     欢迎进入学生考勤系统      ###            "<<endl;

	int choice=2;
	do {
		cout<<"                       ***主菜单***                            "<<endl;
		cout<<"————————————————————————————————"<<endl;
		cout<<"||         请选择所需功能，输入对应数字：                      ||"<<endl;
		cout<<"||        0:退出                                               ||"<<endl;
		cout<<"||        1:学生基本信息与操作                                 ||"<<endl;
		cout<<"||        2:学生考勤模拟                                       ||"<<endl;
		cout<<"||        3:学生出勤情况查询                                   ||"<<endl;
		cout<<"————————————————————————————————"<<endl;
		cout<<"请输入您的选择:";
		cin>>choice;
		switch(choice) {
			case 1:
				StudentInfoMenu();        //cout<<"您已经进入学生信息录入子系统！"<<endl;
				break;
			case 2:
				StudentClockMenu();
				//cout<<"您已经进入学生考勤模拟子系统！"<<endl;
				break;
			case 3:
				StudentSearchMenu();// cout<<"您已经进入出勤情况查询子系统！"<<endl;
				break;
			case 0:
				cout<<"您已安全退出系统."<<endl;
				break;
			default:
				cout<<"没有此选项，请重选;"<<endl;
				break;
		}
	} while(choice!=0);
	cout<<"                     ***欢迎您使用本系统!***          "<<endl;
	return 0;
}





