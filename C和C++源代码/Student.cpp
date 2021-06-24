#include <iostream>
#include<string>
using namespace std;

class curriculum {
private:
	string name;
	int grade;
	int credit;
public:
	void createcurriculum(string NewName, int NewCredit) {  //����һ���µĿγ�
		name = NewName;
		credit = NewCredit;
	}
	string showname() {   // ���ؿγ�����
		return name;
	}
	void gradeinput() {   // ����ɼ�
		cin >> grade;
	}
	void modifygrade() {  //�޸ĳɼ�
		cout<<"�������µĳɼ���";
		cin >> grade;
	}
	int showgrade() {   //���سɼ�
		return grade;
	}
	int showcredit() {   //����ѧ��
		return credit;
	}
};

class basicinformation {  // ѧ��������Ϣ��
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
	void modifyphonenumber() {   //�޸ĵ绰����
		cin >> phonenumber;
	}
	void showschoolreport() {     //����ɼ���
		printf("������%s\n", name.c_str());
		printf("ѧ�ţ�%s\t", number.c_str());
		if (sex == 'F')
			cout<<"�Ա�Ů\n";
		else
			cout<<"�Ա�: ��\n";
		for (int i = 0; i < curriculumnumber; i++)
			printf("%d:%s\t%d\n", i + 1, curr[i].showname().c_str(), curr[i].showgrade());
	}
	void weightaveragescore() {  //�����Ȩƽ����
		printf("������%s\n", name.c_str());
		printf("ѧ�ţ�%s\t", number.c_str());
		if (sex == 'F')
			cout<<"�Ա�Ů\n";
		else
			cout<<"�Ա�: ��\n";
		int score = 0;
		int sumweight = 0;
		for (int i = 0; i < curriculumnumber; i++) {
			score += curr[i].showcredit()*curr[i].showgrade();
			sumweight += curr[i].showcredit();
		}
		if (sumweight == 0) throw sumweight;
		double ans = 1.0*score / sumweight;
		printf("ƽ���ɼ���%lf\n", ans);
	}
};

class SeniorHighStudent :public basicinformation {//��������
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
	void newcurriculum() { //����µĿγ̼��ɼ�
		string NewName;
		cout<<"������γ����ƣ�";
		cin >> NewName;
		printf("������γ̵ĳɼ���");
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, 1);
	}
	void modifyIdealschool() {
		cin >> idealuniversity;
	}
};

class undergraduate :public basicinformation {//��������
public:
	void newcurriculum() {
		string NewName;
		int NewCredit;
		printf("������γ����ƣ�");
		cin >> NewName;
		printf("������γ̵�ѧ�֣�");
		cin >> NewCredit;
		printf("������γ̵ĳɼ���");
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, NewCredit);
	}
};

class graduatestudent :public basicinformation {//�о�����
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
		cout<<"������γ����ƣ�";
		cin >> NewName;
		cout<<"������γ̵�ѧ�֣�";
		cin >> NewCredit;
		cout<<"������γ̵ĳɼ���";
		curr[curriculumnumber].gradeinput();
		curr[curriculumnumber++].createcurriculum(NewName, NewCredit);
	}
};

void showInterface() {
	printf("\tMENU\n");
	printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
	printf("|  1.�޸�ѧ����Ϣ              |\n");
	printf("|  2.���ѧ���ɼ�              |\n");
	printf("|  3.�޸�ѧ���ɼ�              |\n");
	printf("|  4.���ѧ���ɼ���            |\n");
	printf("|  5.���ѧ��ƽ����            |\n");
	printf("|  6.�˳�ϵͳ                  |\n");
	printf("|                              |\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("��ѡ������Ҫִ�еĲ�������ţ�");
}

void showagain() {
	printf("\n\t�밴�����������ҳ��\n");
	getchar();
	getchar();
	system("cls");    //�����Ļ
	showInterface();

}

void exitsys() {
	exit(0);
}

int main(void) {//���Բ��ֺ������Ը��������ݵ���ز���Ϊ��
	string A, B, D, G;
	char C;
	int E, F;
	cout<<"������ѧ������:";
	cin >> A;
	cout<<"������ѧ��ѧ�ţ�";
	cin >> B;
	cout<<"�������Ա�M:�� F:Ů����";
	cin >> C;
	cout<<"������ѧ���ĵ绰��";
	cin >> D;
	cout<<"�������꼶�Ͱ༶��";
	cin >> E >> F;
	cout<<"�������ѧ���������ѧ��";
	cin >> G;
	SeniorHighStudent student(G, E, F, A, B, C, D);
	system("cls");
	showInterface();
	int option = 1;
	while (scanf("%d", &option) != EOF)
		switch (option) {
		case 1:
			printf("\t�������µĵ绰���룺");
			student.modifyphonenumber();
			printf("\t�������µ�����ѧУ��");
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
			printf("\t����������Ҫ�޸ĵĿγ̱�ţ�");
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