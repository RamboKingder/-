#include <iostream>
#include<string>
using namespace std;

class curriculum {
private:
	string name;
	int grade;
	int credit;
public:
	void createcurriculum(string NewName, int NewCredit) {  //创建一个新的课程
		name = NewName;
		credit = NewCredit;
	}
	string showname() {   // 返回课程名称
		return name;
	}
	void gradeinput() {   // 输入成绩
		cin >> grade;
	}
	void modifygrade() {  //修改成绩
		cout<<"请输入新的成绩：";
		cin >> grade;
	}
	int showgrade() {   //返回成绩
		return grade;
	}
	int showcredit() {   //返回学分
		return credit;
	}
};

class basicinformation {  // 学生基本信息类
protected:
	string name;
	string number;
	char sex;
	string phonenumber;
public:
	int curriculumnumber;
	curriculum curr[100];//Composition
	basicinformation(string NewName, string NewNumber, char NewSex, string NewPhone):
	name(NewName),number(NewNumber),sex(NewSex),phonenumber(NewPhone), curriculumnumber(0){}
	void modifyphonenumber() {   //修改电话号码
		cin >> phonenumber;
	}
	void showschoolreport() {     //输出成绩单
		printf("姓名：%s\n", name.c_str());
		printf("学号：%s\t", number.c_str());
		if (sex == 'F')
			cout<<"性别：女\n";
		else
			cout<<"性别: 男\n";
		for (int i = 0; i < curriculumnumber; i++)
			printf("%d:%s\t%d\n", i + 1, curr[i].showname().c_str(), curr[i].showgrade());
	}
	void weightaveragescore() {  //输出加权平均分
		printf("姓名：%s\n", name.c_str());
		printf("学号：%s\t", number.c_str());
		if (sex == 'F')
			cout<<"性别：女\n";
		else
			cout<<"性别: 男\n";
		int score = 0;
		int sumweight = 0;
		for (int i = 0; i < curriculumnumber; i++) {
			score += curr[i].showcredit()*curr[i].showgrade();
			sumweight += curr[i].showcredit();
		}
		if (sumweight == 0) throw sumweight;
		double ans = 1.0*score / sumweight;
		printf("平均成绩：%lf\n", ans);
	}
};

class SeniorHighStudent :public basicinformation {//高中生类
private:
	string idealuniversity;
	int grade;
	int classNo;
public:
	SeniorHighStudent(string IDEL, int Grade, int ClassNo, string name, string number, char sex, string phonenumber) :
		basicinformation(name, number, sex, phonenumber) {
		idealuniversity = IDEL;
		grade = Grade;
		classNo = ClassNo;
	}
	void newcurriculum() { //添加新的课程及成绩
		string NewName;
		cout<<"请输入课程名称：";
		cin >> NewName;
		printf("请输入课程的成绩：");
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, 1);
	}
	void modifyIdealschool() {
		cin >> idealuniversity;
	}
};

class undergraduate :public basicinformation {//本科生类
public:
	void newcurriculum() {
		string NewName;
		int NewCredit;
		printf("请输入课程名称：");
		cin >> NewName;
		printf("请输入课程的学分：");
		cin >> NewCredit;
		printf("请输入课程的成绩：");
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, NewCredit);
	}
};

class graduatestudent :public basicinformation {//研究生类
private:
	string researchdirection;
	string tutor;
public:
	graduatestudent(string NewDirection, string NewTotur, string name, string number, char sex, string phonenumber) :
		basicinformation(name, number, sex, phonenumber) {
		researchdirection = NewDirection;
		tutor = NewDirection;
	}
	void newcurriculum() {
		string NewName;
		int NewCredit;
		cout<<"请输入课程名称：";
		cin >> NewName;
		cout<<"请输入课程的学分：";
		cin >> NewCredit;
		cout<<"请输入课程的成绩：";
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, NewCredit);
	}
};

void showInterface() {
	printf("\tMENU\n");
	printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
	printf("|  1.修改学生信息              |\n");
	printf("|  2.添加学生成绩              |\n");
	printf("|  3.修改学生成绩              |\n");
	printf("|  4.输出学生成绩单            |\n");
	printf("|  5.输出学生平均分            |\n");
	printf("|  6.退出系统                  |\n");
	printf("|                              |\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("请选择你需要执行的操作的序号：");
}

void showagain() {
	printf("\n\t请按任意键返回主页面\n");
	getchar();
	getchar();
	system("cls");    //清空屏幕
	showInterface();

}

void exitsys() {
	exit(0);
}

int main(void) {//测试部分函数，以高中生数据的相关操作为例
	string A, B, D, G;
	char C;
	int E, F;
	cout<<"请输入学生姓名:";
	cin >> A;
	cout<<"请输入学生学号：";
	cin >> B;
	cout<<"请输入性别（M:男 F:女）：";
	cin >> C;
	cout<<"请输入学生的电话：";
	cin >> D;
	cout<<"请输入年级和班级：";
	cin >> E >> F;
	cout<<"请输入该学生的理想大学：";
	cin >> G;
	SeniorHighStudent student(G, E, F, A, B, C, D);
	system("cls");
	showInterface();
	int option = 1;
	while (scanf("%d", &option) != EOF)
		switch (option) {
		case 1:
			printf("\t请输入新的电话号码：");
			student.modifyphonenumber();
			printf("\t请输入新的理想学校：");
			student.modifyIdealschool();
			break;
		case 2:
			student.newcurriculum();
			break;
		case 3:
			system("cls");
			for (int i = 0; i < student.curriculumnumber; i++) {
				printf("\t%d  %s\t %d\n", i + 1, student.curr[i].showname().c_str(), student.curr[i].showgrade());
			}
			printf("\t请输入你需要修改的课程编号：");
			int tmp;
			scanf("%d", &tmp);
			student.curr[tmp - 1].modifygrade();
			break;
		case 4:
			student.showschoolreport();
			break;
		case 5:
			student.weightaveragescore();
			break;
		case 6:
			exitsys();
			break;
		}
	showagain();
	student.showschoolreport();
	student.weightaveragescore();
	try {
		student.weightaveragescore();
	}
	catch (int)
	{
		cout << "sumweight is zero" << endl;
	}
	return 0;
}