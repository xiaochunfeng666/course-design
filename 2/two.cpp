#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//基类
class Staff {
private:
	int number;
	string name;
	string gender;
	string department;
	string level;

public:
	//构造函数
	Staff(int number, string name, string gender, string department, string level)
		:number(number), name(name), gender(gender), department(department), level(level) {}

	//析构函数
	virtual ~Staff() {}

	//计算工资的函数
	virtual double calculateSalary()const { return 0; }

	//显示
	virtual void display() const {
		cout << "编号:" << number << "\t" << "姓名:" << name << "\t" << "性别:" << gender << "\t"
			<< "所在部门:" << department << "\t" << "级别:" << level << "\t";
	}

	// 判断编号是否唯一
	static bool isUniqueNumber(int num, const vector<Staff*>& staffList) {
		for (const auto& staff : staffList) {
			if (staff->getNumber() == num) {
				// 找到相同编号，不唯一
				return false;
			}
		}

		// 没有找到相同编号，唯一
		return true;
	}

	//获取编号
	int getNumber() {
		return number;
	}

	//获取姓名
	string getName() {
		return name;
	}

	//获取性别
	string getGender() {
		return gender;
	}

	//获取部门
	string getDepartment() {
		return department;
	}

	//获取级别
	string getLevel() {
		return level;
	}

	//修改编号
	void setNumber(int num) {
		this->number = num;
	}

	//修改姓名
	void setName(string name) {
		this->name = name;
	}

	//修改性别
	void setGender(string g) {
		this->gender = g;
	}

	//修改部门
	void setDept(string dept) {
		this->department = dept;
	}

	//修改级别
	string setLevel(string level) {
		this->level = level;
	}

	//保存到文件
	virtual void saveToFile(ofstream& file) const {
		file << number << "," << name << "," << gender << "," << department << "," << level << ",";
	}
};

//经理
class Manager :public Staff {
private:
	int teamSize;

public:
	Manager(int id, string name, string gender, string department, string level, int teamSize)
		:Staff(id, name, gender, department, level), teamSize(teamSize) {}

	double calculateSalary() const override {
		//基础工资
		double const baseSalary = 5000.00;
		//团队人数补贴
		double teamBonus = teamSize * 100.00;
		return baseSalary + teamBonus;
	}

	//获得团队人数
	int getTeamSize() {
		return teamSize;
	}

	//修改团队人数
	void setTeamSize(int n) {
		this->teamSize = n;
	}

	//保存到文件
	void saveToFile(ofstream& file) {
		file << "M" << ",";
		Staff::saveToFile(file);
		file << teamSize << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "===经理===" << "\t";
		Staff::display();
		cout << "团队人数:" << teamSize << "\t" << "工资:" << calculateSalary() << endl;
	}
};

//技术人员
class Technician :public Staff {
private:
	string skillSet;

public:
	Technician(int id, string name, string gender, string department, string level, string skillSet)
		: Staff(id, name, gender, department, level), skillSet(skillSet) {}

	double calculateSalary() {
		double const baseSalary = 6000.00;
		double skillBonus = skillSet == "专家" ? 1000.00 : 500.00;
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
		cout << "==技术人员==" << "\t";
		Staff::display();
		cout << "职员水平:" << skillSet << "\t" << "工资:" << calculateSalary() << endl;
	}
};

//销售人员
class SalesPerson :public Staff{
public:
	//业绩
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
		cout << "==销售人员==" << "\t";
		Staff::display();
		cout << "业绩:" << sales << "\t" << "工资:" << calculateSalary() << endl;
	}
};

//销售经理
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

	//获得团队人数
	int getTeamSize() {
		return teamSize;
	}

	//修改团队人数
	void setTeamSize(int n) {
		this->teamSize = n;
	}

	void saveToFile(ofstream& file) {
		file << "C" << ",";
		Staff::saveToFile(file);
		file << teamSize << "," << sales << "," << calculateSalary() << "," << endl;
	}

	void display() {
		cout << "==销售经理==" << "\t";
		Staff::display();
		cout << "业绩:" << sales << "\t" << "团队人数:" << teamSize << "\t" << "工资:" << calculateSalary() << endl;
	}
};

vector<Staff*> staffList;
vector<Manager*> managerList;
vector<Technician*> technicianList;
vector<SalesPerson*> salesPersonList;
vector<SalesManager*> salesManagerList;

// 查找职员
Staff* findStaffByNumber(int num) {
	for (auto& staff : staffList) {
		if (staff->getNumber() == num) {
			return staff;
		}
	}

	cout << "未找到该职工" << endl;
	return nullptr; // 未找到
}

//添加
void add() {
	cout << "===== 加入的人员类别 =====" << endl;
	cout << "======== 1.经理 ==========" << endl;
	cout << "======== 2.技术人员 ======" << endl;
	cout << "======== 3.销售人员 ======" << endl;
	cout << "======== 4.销售经理 ======" << endl;

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
			cout << "请输入经理的编号:";
			cin >> number;

			if (!Staff::isUniqueNumber(number, staffList)) {
				cout << "该编号已存在，请重新输入" << endl;
			}
		} while (!Staff::isUniqueNumber(number, staffList));
		cout << "请输入经理的姓名:";
		cin >> name;
		cout << "请输入经理的性别:";
		cin >> gender;
		cout << "请输入经理的所在部门:";
		cin >> department;
		cout << "请输入经理的级别:";
		cin >> level;
		cout << "请输入经理的团队人数:";
		cin >> teamSize;

		managerList.push_back(new Manager(number, name, gender, department, level, teamSize));
		staffList.push_back(new Manager(number, name, gender, department, level, teamSize));
		break;
	}
		  
	case 2: {

		string skillSet;

		  do {
			  cout << "请输入技术人员的编号:";
			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "该编号已存在，请重新输入" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "请输入技术人员的姓名:";
		  cin >> name;
		  cout << "请输入技术人员的性别:";
		  cin >> gender;
		  cout << "请输入技术人员的所在部门:";
		  cin >> department;
		  cout << "请输入技术人员的级别:";
		  cin >> level;
		  cout << "请输入技术人员的水平:(专家/学徒)";
		  cin >> skillSet;

		  technicianList.push_back(new Technician(number, name, gender, department, level, skillSet));
		  staffList.push_back(new Technician(number, name, gender, department, level, skillSet));
		  break;
	}

	case 3: {

		double sales;

		  do {
			  cout << "请输入销售人员的编号:";

			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "该编号已存在，请重新输入" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "请输入销售人员的姓名:";
		  cin >> name;
		  cout << "请输入销售人员的性别:";
		  cin >> gender;
		  cout << "请输入销售人员的所在部门:";
		  cin >> department;
		  cout << "请输入销售人员的级别:";
		  cin >> level;
		  cout << "请输入销售人员的业绩:";
		  cin >> sales;

		  salesPersonList.push_back(new SalesPerson(number, name, gender, department, level, sales));
		  staffList.push_back(new SalesPerson(number, name, gender, department, level, sales));
		  break;
	  }

	case 4: {
		int teamSize;
		double sales;

		  do {
			  cout << "请输入经理的编号:";
			  cin >> number;

			  if (!Staff::isUniqueNumber(number, staffList)) {
				  cout << "该编号已存在，请重新输入" << endl;
			  }
		  } while (!Staff::isUniqueNumber(number, staffList));
		  cout << "请输入销售经理的姓名:";
		  cin >> name;
		  cout << "请输入销售经理的性别:";
		  cin >> gender;
		  cout << "请输入销售经理的所在部门:";
		  cin >> department;
		  cout << "请输入销售经理的级别:";
		  cin >> level;
		  cout << "请输入销售经理的团队人数:";
		  cin >> teamSize;
		  cout << "请输入销售经理的业绩:";
		  cin >> sales;

		  salesManagerList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
		  staffList.push_back(new SalesManager(number, name, gender, department, level, sales, teamSize));
		  break;
	  }

	}
}

//查询
void search() {
	int choice;
	cout << "请选择查询方式：" << endl;
	cout << "1. 根据编号查询" << endl;
	cout << "2. 根据姓名查询" << endl;
	cin >> choice;

	//记录是否找到
	bool found = false;

	switch (choice) {
	case 1: {
		int num;
		cout << "请输入员工编号: ";
		cin >> num;

		//挨个遍历，找到时退出
		for (const auto& staff : staffList) {
			if (staff->getNumber() == num) {
				// 动态类型识别和显示
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
					staff->display(); // 基类的显示方法
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
		cout << "请输入员工姓名: ";
		// 忽略之前的换行符或其他残留字符
		cin.ignore();
		getline(cin, name);

		//挨个遍历，找到时退出
		for (const auto& staff : staffList) {
			if (staff->getName() == name) {
				// 动态类型识别和显示
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
					staff->display(); // 基类的显示方法
				}
				found = true;
				cout << endl;
				break;
			}
		}
		break;
	}

	default:
		cout << "无效的选择" << endl;
	}

	if (!found) {
		cout << "未找到相关记录" << endl;
	}
}

//显示
void show() {
	bool flag = false;

	//挨个遍历，找到时退出
	for (const auto& staff : staffList) {
		// 动态类型识别和显示
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
		cout << "记录为空" << endl;
	}
}

//修改
void change(int num) {
	Staff* staff = findStaffByNumber(num);
	if (!staff) {
		cout << "职员编号 " << num << " 不存在。" << endl;
		return;
	}

	cout << "正在编辑职员编号 " << num << " 的信息：" << endl;

	string newName, newGender, newDept, newLevel;
	int newAge;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "输入新的姓名（留空表示不修改）：";
	getline(cin, newName);
	if (!newName.empty()) { staff->setName(newName); }

	cout << "输入新的性别（留空表示不修改）：";
	getline(cin, newGender);
	if (!newGender.empty()) { staff->setGender(newGender); }

	cout << "输入新的所在部门（留空表示不修改）：";
	getline(cin, newDept);
	if (!newDept.empty()) { staff->setGender(newDept); }

	cout << "输入新的级别（留空表示不修改）：";
	getline(cin, newGender);
	if (!newLevel.empty()) { staff->setGender(newLevel); }

	// 清除输入缓冲区
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 检查编号是否需要修改
	int newNumber;
	cout << "输入新的编号（输入-1表示不修改）：";
	cin >> newNumber;
	if (newNumber != -1) {
		if (Staff::isUniqueNumber(newNumber, staffList)) {
			// 修改编号
			staff->setNumber(newNumber);
		}
		else {
			cout << "新的编号 " << newNumber << " 已经存在，请使用其他编号" << endl;
		}
	}


	// 清除输入缓冲区
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 特定于各派生类的修改
	if (Manager* manager = dynamic_cast<Manager*>(staff)) {
		int newTeamSize;

		cout << "输入新的团队人数（负数表示不修改）：";
		cin >> newTeamSize;
		if (newTeamSize > 0) { manager->setTeamSize(newTeamSize); }
	}

	if (Technician* technician = dynamic_cast<Technician*>(staff)) {
		string newSkillSet;
		cout << "输入新的职员水平（留空表示不修改）：";
		getline(cin, newSkillSet);
		if (!newSkillSet.empty()) { technician->setSkillSet(newSkillSet); }
	}

	if (SalesPerson* salesPerson= dynamic_cast<SalesPerson*>(staff)) {
		double newSales;
		
		cout << "输入新的业绩（负数表示不修改）：";
		cin >> newSales;
		if (newSales > 0) { salesPerson->setSales(newSales); }
	}

	if (SalesManager* salesManager = dynamic_cast<SalesManager*>(staff)) {
		int newTeamSize;
		double newSales;
		
		cout << "输入新的业绩（负数表示不修改）：";
		cin >> newSales;
		if (newSales > 0) { salesManager->setSales(newSales); }

		cout << "输入新的团队人数（负数表示不修改）：";
		cin >> newTeamSize;
		if (newTeamSize > 0) { salesManager->setTeamSize(newTeamSize); }
	}

	cout << "信息已更新。" << endl;
}

//删除
void deleteStaff() {
	if (staffList.empty()) {
		cout << "记录为空" << endl;
		return;
	}

	int choice;
	cout << "请输入选择删除的方式" << endl;
	cout << "1.根据编号删除" << endl;
	cout << "2.根据姓名删除" << endl;

	cin >> choice;
	bool found = false;

	switch (choice) {
	case 1: {
		int num;
		cout << "请输入员工编号: ";
		cin >> num;

		// 遍历查找并删除
		for (auto it = staffList.begin(); it != staffList.end(); ++it) {
			if ((*it)->getNumber() == num) {
				delete* it; // 释放内存
				staffList.erase(it); // 从列表中删除
				found = true;
				cout << "删除成功！" << endl;
				break;
			}
		}

		if (!found) {
			cout << "未找到编号为 " << num << " 的员工记录。" << endl;
		}
		break;
	}

	case 2: {
		string name;
		cout << "请输入员工姓名: ";
		cin.ignore(); // 忽略之前的换行符或其他残留字符
		getline(cin, name);

		// 遍历查找并删除
		for (auto it = staffList.begin(); it != staffList.end(); ++it) {
			if ((*it)->getName() == name) {
				delete* it; // 释放内存
				staffList.erase(it); // 从列表中删除
				found = true;
				cout << "删除成功！" << endl;
				break;
			}
		}

		if (!found) {
			cout << "未找到姓名为 " << name << " 的员工记录。" << endl;
		}
		break;
	}
	default:
		cout << "未选择删除人员" << endl;
	}
}

//统计
void count() {
	cout << "请输入需要统计的类型" << endl;
	cout << "1.职工总数" << endl;
	cout << "2.经理人数" << endl;
	cout << "3.技术人员人数" << endl;
	cout << "4.销售人员人数" << endl;
	cout << "5.销售经理人数" << endl;
	cout << "6.男生人数" << endl;
	cout << "7.女生人数" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1: {
		cout << "职工总数:" << staffList.size() << endl;
		break;
	}

	case 2: {
		cout << "教师人数:" << managerList.size() << endl;
		break;
	}

	case 3: {
		cout << "实验员人数:" << technicianList.size() << endl;
		break;
	}

	case 4: {
		cout << "行政人员人数:" << salesPersonList.size() << endl;
		break;
	}

	case 5: {
		cout << "教师兼行政人员人数:" << salesManagerList.size() << endl;
		break;
	}

	case 6: {
		int num = 0;
		for (auto& staff : staffList) {
			if (staff->getGender() == "男") {
				++num;
			}
		}
		cout << "男生人数:" << num << endl;
		break;
	}

	case 7: {
		int num = 0;
		for (auto& staff : staffList) {
			if (staff->getGender() == "女") {
				++num;
			}
		}
		cout << "女生人数:" << num << endl;
		break;
	}
	}
}

//保存到文件
void saveToFile() {
	ofstream outFile("your file name");
	if (!outFile) {
		cerr << "无法打开文件" << endl;
		return;
	}

	for (const auto& staff : staffList) {
		// 动态类型识别和显示
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

	cout << "保存成功！" << endl;
	outFile.close();
}

// 从文件中读取人员信息并加载到系统中
void readFromFile(vector<Staff*>& staffList, vector<Manager*>& managerList, vector<Technician*>& technicainList,
	vector<SalesPerson*>& salesPersonList, vector<SalesManager*>& salesManagerList, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "无法打开文件 " << filename << endl;
		return;
	}

	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string type;
		getline(ss, type, ',');

		//经理
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

		//技术人员
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

		//销售人员
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

		//销售经理
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
	cout << "从文件 " << filename << " 读取完毕。" << endl;
}

//主函数
void mainInterface() {
	cout << "====== 欢迎使用高校人员信息管理系统 ======" << endl;
	cout << "================ 1.添加 ==================" << endl;
	cout << "================ 2.查询 ==================" << endl;
	cout << "================ 3.显示 ==================" << endl;
	cout << "================ 4.编辑 ==================" << endl;
	cout << "================ 5.删除 ==================" << endl;
	cout << "================ 6.统计 ==================" << endl;
	cout << "================ 7.退出 ==================" << endl;

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
		cout << "请输入需要修改的职员编号" << endl;
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