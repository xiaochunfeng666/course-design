#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//����
class Staff {
private:
	int number;
	string name;
	string gender;
	string department;
	string level;

public:
	//���캯��
	Staff(int number, string name, string gender, string department, string level)
		:number(number), name(name), gender(gender), department(department), level(level) {}

	//��������
	virtual ~Staff() {}

	//���㹤�ʵĺ���
	virtual double calculateSalary()const { return 0; }

	//��ʾ
	virtual void display() const {
		cout << "���:" << number << "\t" << "����:" << name << "\t" << "�Ա�:" << gender << "\t"
			<< "���ڲ���:" << department << "\t" << "����:" << level << "\t";
	}

	// �жϱ���Ƿ�Ψһ
	static bool isUniqueNumber(int num, const vector<Staff*>& staffList) {
		for (const auto& staff : staffList) {
			if (staff->getNumber() == num) {
				// �ҵ���ͬ��ţ���Ψһ
				return false;
			}
		}

		// û���ҵ���ͬ��ţ�Ψһ
		return true;
	}

	//��ȡ���
	int getNumber() {
		return number;
	}

	//��ȡ����
	string getName() {
		return name;
	}

	//��ȡ�Ա�
	string getGender() {
		return gender;
	}

	//��ȡ����
	string getDepartment() {
		return department;
	}

	//��ȡ����
	string getLevel() {
		return level;
	}

	//�޸ı��
	void setNumber(int num) {
		this->number = num;
	}

	//�޸�����
	void setName(string name) {
		this->name = name;
	}

	//�޸��Ա�
	void setGender(string g) {
		this->gender = g;
	}

	//�޸Ĳ���
	void setDept(string dept) {
		this->department = dept;
	}

	//�޸ļ���
	string setLevel(string level) {
		this->level = level;
	}

	//���浽�ļ�
	virtual void saveToFile(ofstream& file) const {
		file << number << "," << name << "," << gender << "," << department << "," << level << ",";
	}
};

//����
class Manager :public Staff {
private:
	int teamSize;

public:
	Manager(int id, string name, string gender, string department, string level, int teamSize)
		:Staff(id, name, gender, department, level), teamSize(teamSize) {}

	double calculateSalary() const override {
		//��������
		double const baseSalary = 5000.00;
		//�Ŷ���������
		double teamBonus = teamSize * 100.00;
		return baseSalary + teamBonus;
	}

	//����Ŷ�����
	int getTeamSize() {
		return teamSize;
	}

	//�޸��Ŷ�����
	void setTeamSize(int n) {
		this->teamSize = n;
	}

	//���浽�ļ�
	void saveToFile(ofstream& file) {
		file << "M" << ",";
		Staff::saveToFile(file);
		file << teamSize << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "===����===" << "\t";
		Staff::display();
		cout << "�Ŷ�����:" << teamSize << "\t" << "����:" << calculateSalary() << endl;
	}
};

//������Ա
class Technician :public Staff {
private:
	string skillSet;

public:
	Technician(int id, string name, string gender, string department, string level, string skillSet)
		: Staff(id, name, gender, department, level), skillSet(skillSet) {}

	double calculateSalary() {
		double const baseSalary = 6000.00;
		double skillBonus = skillSet == "ר��" ? 1000.00 : 500.00;
		return baseSalary + skillBonus;
	}

	string getSkillSet() {
		return skillSet;
	}

	void setSkillSet(string s) {
		this->skillSet = s;
	}

	void saveToFile(ofstream& file) {
		file << "T" << ",";
		Staff::saveToFile(file);
		file << skillSet << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "==������Ա==" << "\t";
		Staff::display();
		cout << "ְԱˮƽ:" << skillSet << "\t" << "����:" << calculateSalary() << endl;
	}
};

//������Ա
class SalesPerson :public Staff{
public:
	//ҵ��
	double sales;

	SalesPerson(int id, string name, string gender, string department, string level, double sales)
		: Staff(id, name, gender, department, level), sales(sales) {}

	double calculateSalary() {
		double const baseSalary = 3000.00;
		double commission = sales * 0.05;
		return baseSalary + commission;
	}

	double getSales() {
		return sales;
	}

	void setSales(double sales) {
		this->sales = sales;
	}

	void saveToFile(ofstream& file) {
		file << "S" << ",";
		Staff::saveToFile(file);
		file << sales << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "==������Ա==" << "\t";
		Staff::display();
		cout << "ҵ��:" << sales << "\t" << "����:" << calculateSalary() << endl;
	}
};

//���۾���
class SalesManager :public SalesPerson {
private:
	int teamSize;

public:
	SalesManager(int id, string name, string gender, string department, string level, double sales, int teamSize)
		: SalesPerson(id, name, gender, department, level, sales), teamSize(teamSize) {}

	double calculateSalary() {
		double const baseSalary = 5000.00;
		double commission = sales * 0.05;
		double teamBonus = teamSize * 100.00;
		return baseSalary + commission + teamBonus;
	}

	//����Ŷ�����
	int getTeamSize() {
		return teamSize;
	}

	//�޸��Ŷ�����
	void setTeamSize(int n) {
		this->teamSize = n;
	}

	void saveToFile(ofstream& file) {
		file << "C" << ",";
		Staff::saveToFile(file);
		file << teamSize << "," << sales << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "==���۾���==" << "\t";
		Staff::display();
		cout << "ҵ��:" << sales << "\t" << "�Ŷ�����:" << teamSize << "\t" << "����:" << calculateSalary() << endl;
	}
};

vector<Staff*> staffList;
vector<Manager*> managerList;
vector<Technician*> technicianList;
vector<SalesPerson*> salesPersonList;
vector<SalesManager*> salesManagerList;

// ����ְԱ
Staff* findStaffByNumber(int num) {
	for (auto& staff : staffList) {
		if (staff->getNumber() == num) {
			return staff;
		}
	}

	cout << "δ�ҵ���ְ��" << endl;
	return nullptr; // δ�ҵ�
}

//���
void add() {
	cout << "===== �������Ա��� =====" << endl;
	cout << "======== 1.���� ==========" << endl;
	cout << "======== 2.������Ա ======" << endl;
	cout << "======== 3.������Ա ======" << endl;
	cout << "======== 4.���۾��� ======" << endl;

	int choice;
	cin >> choice;

	int number;
	string name;
	string gender;
	string department;
	string level;

	switch (choice) {
	case 1: {
		
		int teamSize;

		do {
			cout << "�����뾭��ı��:";
			cin >> number;

			if (!Staff::isUniqueNumber(number, staffList)) {
				cout << "�ñ���Ѵ��ڣ�����������" << endl;
			}
		} while (!Staff::isUniqueNumber(number, staffList));
		cout << "�����뾭�������:";
		cin >> name;
		cout << "�����뾭����Ա�:";
		cin >> gender;
		cout << "�����뾭������ڲ���:";
		cin >> department;
		cout << "�����뾭��ļ���:";
		cin >> level;
		cout << "�����뾭����Ŷ�����:";
		cin >> teamSize;

		managerList.push_back(new Manager(number, name, gender, department, level, teamSize));
		staffList.push_back(new Manager(number, name, gender, department, level, teamSize));
		break;
	}
		  
	case 2: {

		string skillSet;

		  do {
			  cout << "�����뼼����Ա�ı��:";
			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "�ñ���Ѵ��ڣ�����������" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "�����뼼����Ա������:";
		  cin >> name;
		  cout << "�����뼼����Ա���Ա�:";
		  cin >> gender;
		  cout << "�����뼼����Ա�����ڲ���:";
		  cin >> department;
		  cout << "�����뼼����Ա�ļ���:";
		  cin >> level;
		  cout << "�����뼼����Ա��ˮƽ:(ר��/ѧͽ)";
		  cin >> skillSet;

		  technicianList.push_back(new Technician(number, name, gender, department, level, skillSet));
		  staffList.push_back(new Technician(number, name, gender, department, level, skillSet));
		  break;
	}

	case 3: {

		double sales;

		  do {
			  cout << "������������Ա�ı��:";

			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "�ñ���Ѵ��ڣ�����������" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "������������Ա������:";
		  cin >> name;
		  cout << "������������Ա���Ա�:";
		  cin >> gender;
		  cout << "������������Ա�����ڲ���:";
		  cin >> department;
		  cout << "������������Ա�ļ���:";
		  cin >> level;
		  cout << "������������Ա��ҵ��:";
		  cin >> sales;

		  salesPersonList.push_back(new SalesPerson(number, name, gender, department, level, sales));
		  staffList.push_back(new SalesPerson(number, name, gender, department, level, sales));
		  break;
	  }

	case 4: {
		int teamSize;
		double sales;

		  do {
			  cout << "�����뾭��ı��:";
			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "�ñ���Ѵ��ڣ�����������" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "���������۾��������:";
		  cin >> name;
		  cout << "���������۾�����Ա�:";
		  cin >> gender;
		  cout << "���������۾�������ڲ���:";
		  cin >> department;
		  cout << "���������۾���ļ���:";
		  cin >> level;
		  cout << "���������۾�����Ŷ�����:";
		  cin >> teamSize;
		  cout << "���������۾����ҵ��:";
		  cin >> sales;

		  salesManagerList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
		  staffList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
		  break;
	  }

	}
}

//��ѯ
void search() {
	int choice;
	cout << "��ѡ���ѯ��ʽ��" << endl;
	cout << "1. ���ݱ�Ų�ѯ" << endl;
	cout << "2. ����������ѯ" << endl;
	cin >> choice;

	//��¼�Ƿ��ҵ�
	bool found = false;

	switch (choice) {
	case 1: {
		int num;
		cout << "������Ա�����: ";
		cin >> num;

		//�����������ҵ�ʱ�˳�
		for (const auto& staff : staffList) {
			if (staff->getNumber() == num) {
				// ��̬����ʶ�����ʾ
				if (Manager* t = dynamic_cast<Manager*>(staff)) {
					t->display();
				}
				else if (Technician* l = dynamic_cast<Technician*>(staff)) {
					l->display();
				}
				else if (SalesPerson* a = dynamic_cast<SalesPerson*>(staff)) {
					a->display();
				}
				else if (SalesManager* ta = dynamic_cast<SalesManager*>(staff)) {
					ta->display();
				}
				else {
					staff->display(); // �������ʾ����
				}
				found = true;
				cout << endl;
				break;
			}
		}
		break;
	}
	case 2: {
		string name;
		cout << "������Ա������: ";
		// ����֮ǰ�Ļ��з������������ַ�
		cin.ignore();
		getline(cin, name);

		//�����������ҵ�ʱ�˳�
		for (const auto& staff : staffList) {
			if (staff->getName() == name) {
				// ��̬����ʶ�����ʾ
				if (Manager* t = dynamic_cast<Manager*>(staff)) {
					t->display();
				}
				else if (Technician* l = dynamic_cast<Technician*>(staff)) {
					l->display();
				}
				else if (SalesPerson* a = dynamic_cast<SalesPerson*>(staff)) {
					a->display();
				}
				else if (SalesManager* ta = dynamic_cast<SalesManager*>(staff)) {
					ta->display();
				}
				else {
					staff->display(); // �������ʾ����
				}
				found = true;
				cout << endl;
				break;
			}
		}
		break;
	}

	default:
		cout << "��Ч��ѡ��" << endl;
	}

	if (!found) {
		cout << "δ�ҵ���ؼ�¼" << endl;
	}
}

//��ʾ
void show() {
	bool flag = false;

	//�����������ҵ�ʱ�˳�
	for (const auto& staff : staffList) {
		// ��̬����ʶ�����ʾ
		if (SalesManager* ta = dynamic_cast<SalesManager*>(staff)) {
			ta->display();
			flag = true;
		}
		else if (Technician* l = dynamic_cast<Technician*>(staff)) {
			l->display();
			flag = true;
		}
		else if (SalesPerson* a = dynamic_cast<SalesPerson*>(staff)) {
			a->display();
			flag = true;
		}
		else if (Manager* t = dynamic_cast<Manager*>(staff)) {
			t->display();
			flag = true;
		}
	}

	if (!flag) {
		cout << "��¼Ϊ��" << endl;
	}
}

//�޸�
void change(int num) {
	Staff* staff = findStaffByNumber(num);
	if (!staff) {
		cout << "ְԱ��� " << num << " �����ڡ�" << endl;
		return;
	}

	cout << "���ڱ༭ְԱ��� " << num << " ����Ϣ��" << endl;

	string newName, newGender, newDept, newLevel;
	int newAge;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "�����µ����������ձ�ʾ���޸ģ���";
	getline(cin, newName);
	if (!newName.empty()) { staff->setName(newName); }

	cout << "�����µ��Ա����ձ�ʾ���޸ģ���";
	getline(cin, newGender);
	if (!newGender.empty()) { staff->setGender(newGender); }

	cout << "�����µ����ڲ��ţ����ձ�ʾ���޸ģ���";
	getline(cin, newDept);
	if (!newDept.empty()) { staff->setGender(newDept); }

	cout << "�����µļ������ձ�ʾ���޸ģ���";
	getline(cin, newGender);
	if (!newLevel.empty()) { staff->setGender(newLevel); }

	// ������뻺����
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// ������Ƿ���Ҫ�޸�
	int newNumber;
	cout << "�����µı�ţ�����-1��ʾ���޸ģ���";
	cin >> newNumber;
	if (newNumber != -1) {
		if (Staff::isUniqueNumber(newNumber, staffList)) {
			// �޸ı��
			staff->setNumber(newNumber);
		}
		else {
			cout << "�µı�� " << newNumber << " �Ѿ����ڣ���ʹ���������" << endl;
		}
	}


	// ������뻺����
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// �ض��ڸ���������޸�
	if (Manager* manager = dynamic_cast<Manager*>(staff)) {
		int newTeamSize;

		cout << "�����µ��Ŷ�������������ʾ���޸ģ���";
		cin >> newTeamSize;
		if (newTeamSize > 0) { manager->setTeamSize(newTeamSize); }
	}

	if (Technician* technician = dynamic_cast<Technician*>(staff)) {
		string newSkillSet;
		cout << "�����µ�ְԱˮƽ�����ձ�ʾ���޸ģ���";
		getline(cin, newSkillSet);
		if (!newSkillSet.empty()) { technician->setSkillSet(newSkillSet); }
	}

	if (SalesPerson* salesPerson= dynamic_cast<SalesPerson*>(staff)) {
		double newSales;
		
		cout << "�����µ�ҵ����������ʾ���޸ģ���";
		cin >> newSales;
		if (newSales > 0) { salesPerson->setSales(newSales); }
	}

	if (SalesManager* salesManager = dynamic_cast<SalesManager*>(staff)) {
		int newTeamSize;
		double newSales;
		
		cout << "�����µ�ҵ����������ʾ���޸ģ���";
		cin >> newSales;
		if (newSales > 0) { salesManager->setSales(newSales); }

		cout << "�����µ��Ŷ�������������ʾ���޸ģ���";
		cin >> newTeamSize;
		if (newTeamSize > 0) { salesManager->setTeamSize(newTeamSize); }
	}

	cout << "��Ϣ�Ѹ��¡�" << endl;
}

//ɾ��
void deleteStaff() {
	if (staffList.empty()) {
		cout << "��¼Ϊ��" << endl;
		return;
	}

	int choice;
	cout << "������ѡ��ɾ���ķ�ʽ" << endl;
	cout << "1.���ݱ��ɾ��" << endl;
	cout << "2.��������ɾ��" << endl;

	cin >> choice;
	bool found = false;

	switch (choice) {
	case 1: {
		int num;
		cout << "������Ա�����: ";
		cin >> num;

		// �������Ҳ�ɾ��
		for (auto it = staffList.begin(); it != staffList.end(); ++it) {
			if ((*it)->getNumber() == num) {
				delete* it; // �ͷ��ڴ�
				staffList.erase(it); // ���б���ɾ��
				found = true;
				cout << "ɾ���ɹ���" << endl;
				break;
			}
		}

		if (!found) {
			cout << "δ�ҵ����Ϊ " << num << " ��Ա����¼��" << endl;
		}
		break;
	}

	case 2: {
		string name;
		cout << "������Ա������: ";
		cin.ignore(); // ����֮ǰ�Ļ��з������������ַ�
		getline(cin, name);

		// �������Ҳ�ɾ��
		for (auto it = staffList.begin(); it != staffList.end(); ++it) {
			if ((*it)->getName() == name) {
				delete* it; // �ͷ��ڴ�
				staffList.erase(it); // ���б���ɾ��
				found = true;
				cout << "ɾ���ɹ���" << endl;
				break;
			}
		}

		if (!found) {
			cout << "δ�ҵ�����Ϊ " << name << " ��Ա����¼��" << endl;
		}
		break;
	}
	default:
		cout << "δѡ��ɾ����Ա" << endl;
	}
}

//ͳ��
void count() {
	cout << "��������Ҫͳ�Ƶ�����" << endl;
	cout << "1.ְ������" << endl;
	cout << "2.��������" << endl;
	cout << "3.������Ա����" << endl;
	cout << "4.������Ա����" << endl;
	cout << "5.���۾�������" << endl;
	cout << "6.��������" << endl;
	cout << "7.Ů������" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1: {
		cout << "ְ������:" << staffList.size() << endl;
		break;
	}

	case 2: {
		cout << "��ʦ����:" << managerList.size() << endl;
		break;
	}

	case 3: {
		cout << "ʵ��Ա����:" << technicianList.size() << endl;
		break;
	}

	case 4: {
		cout << "������Ա����:" << salesPersonList.size() << endl;
		break;
	}

	case 5: {
		cout << "��ʦ��������Ա����:" << salesManagerList.size() << endl;
		break;
	}

	case 6: {
		int num = 0;
		for (auto& staff : staffList) {
			if (staff->getGender() == "��") {
				++num;
			}
		}
		cout << "��������:" << num << endl;
		break;
	}

	case 7: {
		int num = 0;
		for (auto& staff : staffList) {
			if (staff->getGender() == "Ů") {
				++num;
			}
		}
		cout << "Ů������:" << num << endl;
		break;
	}
	}
}

//���浽�ļ�
void saveToFile() {
	ofstream outFile("your file name");
	if (!outFile) {
		cerr << "�޷����ļ�" << endl;
		return;
	}

	for (const auto& staff : staffList) {
		// ��̬����ʶ�����ʾ
		if (SalesManager* ta = dynamic_cast<SalesManager*>(staff)) {
			ta->saveToFile(outFile);
		}
		else if (Technician* l = dynamic_cast<Technician*>(staff)) {
			l->saveToFile(outFile);
		}
		else if (SalesPerson* a = dynamic_cast<SalesPerson*>(staff)) {
			a->saveToFile(outFile);
		}
		else if (Manager* t = dynamic_cast<Manager*>(staff)) {
			t->saveToFile(outFile);
		}
	}

	cout << "����ɹ���" << endl;
	outFile.close();
}

// ���ļ��ж�ȡ��Ա��Ϣ�����ص�ϵͳ��
void readFromFile(vector<Staff*>& staffList, vector<Manager*>& managerList, vector<Technician*>& technicainList,
	vector<SalesPerson*>& salesPersonList, vector<SalesManager*>& salesManagerList, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "�޷����ļ� " << filename << endl;
		return;
	}

	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string type;
		getline(ss, type, ',');

		//����
		if (type == "M") { 
			int number, teamSize;
			string name, gender, department, level;
			char t;

			ss >> number >> t;
			getline(ss, name, ',');
			getline(ss, gender, ',');
			getline(ss, department, ',');
			getline(ss, level, ',');
			ss >> teamSize >> t;

			managerList.push_back(new Manager(number, name, gender, department, level, teamSize));
			staffList.push_back(new Manager(number, name, gender, department, level, teamSize));
		}

		//������Ա
		else if (type == "T") { 
			int number;
			string name, gender, department, level, skillSet;
			char t;

			ss >> number >> t;
			getline(ss, name, ',');
			getline(ss, gender, ',');
			getline(ss, department, ',');
			getline(ss, level, ',');
			getline(ss, skillSet, ',');

			technicianList.push_back(new Technician(number, name, gender, department, level, skillSet));
			staffList.push_back(new Technician(number, name, gender, department, level, skillSet));
		}

		//������Ա
		else if (type == "S") { 
			int number;
			string name, gender, department, level;
			double sales;
			char t;

			ss >> number >> t;
			getline(ss, name, ',');
			getline(ss, gender, ',');
			getline(ss, department, ',');
			getline(ss, level, ',');
			ss >> sales >> t;

			salesPersonList.push_back(new SalesPerson(number, name, gender, department, level, sales));
			staffList.push_back(new SalesPerson(number, name, gender, department, level, sales));
		}

		//���۾���
		else if (type == "C") { 
			int number, teamSize;
			string name, gender, department, level;
			double sales;
			char t;

			ss >> number >> t;
			getline(ss, name, ',');
			getline(ss, gender, ',');
			getline(ss, department, ',');
			getline(ss, level, ',');
			ss >> teamSize >> t >> sales >> t;

			salesManagerList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
			staffList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
		}
	}

	inFile.close();
	cout << "���ļ� " << filename << " ��ȡ��ϡ�" << endl;
}

//������
void mainInterface() {
	cout << "====== ��ӭʹ�ø�У��Ա��Ϣ����ϵͳ ======" << endl;
	cout << "================ 1.��� ==================" << endl;
	cout << "================ 2.��ѯ ==================" << endl;
	cout << "================ 3.��ʾ ==================" << endl;
	cout << "================ 4.�༭ ==================" << endl;
	cout << "================ 5.ɾ�� ==================" << endl;
	cout << "================ 6.ͳ�� ==================" << endl;
	cout << "================ 7.�˳� ==================" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		add();
		break;

	case 2:
		search();
		break;

	case 3:
		show();
		break;

	case 4:
		cout << "��������Ҫ�޸ĵ�ְԱ���" << endl;
		int num;
		cin >> num;

		change(num);
		break;

	case 5:
		deleteStaff();
		break;

	case 6:
		count();
		break;

	case 7:
		saveToFile();
		exit(0);
		break;
	}
}

int main() {
	readFromFile(staffList, managerList, technicianList, salesPersonList, salesManagerList, "your file name");
	while (true) {
		mainInterface();
	}
	return 0;
}