#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Staff {
private:
	int number;
	string name;
	string gender;
	int age;

public:

    // 构造函数
    Staff(int num, string name, string gendar, int age) : 
        number(num), name(name), gender(gendar), age(age) {}

    // 虚析构函数，用于多态
    virtual ~Staff() {}

    // 显示职工信息
    virtual void display() const {
        std::cout << "姓名: " << name << "\t编号: " << number
            << "\t性别:" << gender << "\t年龄: " << age;
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

    //获取年龄
    int getAge() {
        return age;
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

    //修改年龄
    void setAge(int age) {
        this->age = age;
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

    //保存到文件
    virtual void saveToFile(ofstream& file) const {
        file << number << "," << name << "," << gender << "," << age << ",";
    }
};

// 派生类：教师
class Teacher : public Staff {
protected:
    string department;
    string major;
    string jobTitle;

public:
    //构造函数，用于初始化
    Teacher(int num, string name, string gender, int age, string dept, string maj, string title)
        : Staff(num, name, gender, age), department(dept), major(maj), jobTitle(title) {}

    //显示信息
    void display(){
        cout << "=== 老师 ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "系部: " << department << "\t";
        cout << "专业: " << major << "\t";
        cout << "职称: " << jobTitle << "\t";
        cout << endl;
    }

    //获取系部
    string getDept() {
        return department;
    }

    //获取专业
    string getMajor() {
        return major;
    }

    //获得职称
    string getTitle() {
        return jobTitle;
    }

    //修改专业
    void setMajor(string major) {
        this->major = major;
    }

    //修改系部
    void setDept(string dept) {
        this->department = dept;
    }

    //修改职称
    void setTitle(string title) {
        this->jobTitle = title;
    }

    //保存到文件
    void saveToFile(ofstream& file) {
        file << "T" << ",";
        Staff::saveToFile(file);
        file  << department << "," << major <<  "," << jobTitle << "," << endl;
    }
};

// 派生类：实验员
class LabAssistant : public Staff {
private:
    string lab;
    string position;

public:
    LabAssistant(int num, string name, string gender, int age, string lab, string pos)
        : Staff(num, name, gender, age), lab(lab), position(pos) {}

    void display(){
        cout << "=== 实验员 ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "实验室: " << lab << "\t";
        cout << "职务: " << position << "\t";
        cout << endl;
    }

    //获取实验室
    string getLab() {
        return lab;
    }

    //获取职务
    string getPos() {
        return position;
    }

    //修改职务
    void setPos(string pos) {
        this->position = pos;
    }

    //修改实验室
    void setLab(string lab) {
        this->lab = lab;
    }

    //保存到文件
    void saveToFile(ofstream& file) {
        file << "L" << ",";
        Staff::saveToFile(file);
        file << lab << "," << position << "," << endl;
    }
};

// 派生类：行政人员
class Administrator : public Staff {
private:
    string politicalStatus;
    string professionalTitle;

public:
    Administrator(int num, string name, string gender, int age, string pol, string prof)
        : Staff(num, name, gender, age), politicalStatus(pol), professionalTitle(prof) {}

    void display(){
        cout << "=== 行政人员 ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "政治面貌: " << politicalStatus << "\t";
        cout << "职称: " << professionalTitle << "\t";
        cout << endl;
    }

    //获取政治面貌
    string getPol() {
        return politicalStatus;
    }

    //获得职称
    string getTitle() {
        return professionalTitle;
    }

    //修改职称
    void setTitle(string title) {
        this->professionalTitle = title;
    }

    //修改政治面貌
    void setPol(string pol) {
        this->politicalStatus = pol;
    }

    //保存到文件
    void saveToFile(ofstream& file) {
        file << "A" << ",";        
        Staff::saveToFile(file);
        file  << politicalStatus << "," << professionalTitle << "," << endl;
    }
};

// 派生类：教师兼行政人员
class TeachingAdministrator : public Teacher {
private:
    string politicalStatus;

public:
    TeachingAdministrator(int num, string name, string gender, int age, string dept, string maj, string t, string pol)
        : Teacher(num, name, gender, age, dept, maj, t), politicalStatus(pol) {}

    void display() {
        cout << "=== 教师兼行政人员 ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "系部: " << department << "\t";
        cout << "专业: " << major << "\t";
        cout << "职称: " << jobTitle << "\t";
        cout << "政治面貌: " << politicalStatus << "\t";
        cout << endl;
    }

    //修改政治面貌
    void setPol(string pol) {
        this->politicalStatus = pol;
    }

    //保存到文件
    void saveToFile(ofstream& file) {
        file << "C" << ",";
        Staff::saveToFile(file);
        file << getDept() << "," << getMajor() << "," << getTitle() << "," << politicalStatus << "," << endl;
    }
};

vector<Staff*> staffList;
vector <Teacher*> teacherList;
vector<LabAssistant*> labList;
vector<Administrator*> adList;
vector<TeachingAdministrator*> taList;

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
    cout << "======== 1.教师 ==========" << endl;
    cout << "======== 2.实验员 ========" << endl;
    cout << "======== 3.行政人员 ======" << endl;
    cout << "======== 4.教师兼行政人员=" << endl;

    int choice;
    cin >> choice;

    int num;
    int age;
    string name;
    string gender;

    switch (choice) {
        case 1: {
            string dept, major, title;
            do {
                cout << "请输入教师的编号:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "该编号已存在，请重新输入" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "请输入教师的姓名:" ;
            cin >> name ;
            cout << "请输入教师的性别:" ;
            cin >> gender;;
            cout << "请输入教师的年龄:" ;
            cin >> age;
            cout << "请输入教师的系部:" ;
            cin >> dept;
            cout << "请输入教师的专业:" ;
            cin >> major;
            cout << "请输入教师的职称:" ;
            cin >> title;

            teacherList.push_back(new Teacher(num, name, gender, age, dept, major, title));
            staffList.push_back(new Teacher(num, name, gender, age, dept, major, title));
            break;
        }

        case 2:{
            string lab, position;
            do {
                cout << "请输入实验员的编号:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "该编号已存在，请重新输入" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "请输入实验员的姓名:";
            cin >> name;
            cout << "请输入实验员的性别:";
            cin >> gender;
            cout << "请输入实验员的年龄:";
            cin >> age;
            cout << "请输入实验员的实验室:";
            cin >> lab;
            cout << "请输入实验员的职称:";
            cin >> position;

            labList.push_back(new LabAssistant(num, name, gender, age, lab, position));
            staffList.push_back(new LabAssistant(num, name, gender, age, lab, position));
            break;
        }
        
        case 3: {
            string pol, prof;

            do {
            cout << "请输入行政人员的编号:";
            cin >> num;  
            
            if (!Staff::isUniqueNumber(num, staffList)) {
                cout << "该编号已存在，请重新输入" << endl;
            }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "请输入行政人员的姓名:";
            cin >> name;
            cout << "请输入行政人员的性别:";
            cin >> gender;
            cout << "请输入行政人员的年龄:";
            cin >> age;
            cout << "请输入行政人员的政治面貌:";
            cin >> pol;
            cout << "请输入行政人员的职务:";
            cin >> prof;

            adList.push_back(new Administrator(num, name, gender, age, pol, prof));
            staffList.push_back(new Administrator(num, name, gender, age, pol, prof));
            break;
        }

        case 4:{ 
            string dept, major, title;
            string pol, prof;

            do {
                cout << "请输入教师兼行政人员的编号:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "该编号已存在，请重新输入" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "请输入教师兼行政人员的姓名:";
            cin >> name;
            cout << "请输入教师兼行政人员的性别:";
            cin >> gender;
            cout << "请输入教师兼行政人员的年龄:";
            cin >> age;
            cout << "请输入教师兼行政人员的系部:";
            cin >> dept;
            cout << "请输入教师兼行政人员的专业:";
            cin >> major;
            cout << "请输入教师兼行政人员的职称:";
            cin >> title;
            cout << "请输入教师兼行政人员的政治面貌:";
            cin >> pol;

            taList.push_back(new TeachingAdministrator(num, name, gender, age, dept, major, title, pol));
            staffList.push_back(new TeachingAdministrator(num, name, gender, age, dept, major, title, pol));
            break; 
        }
        default:
            cout << "无效选择" << endl;
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
                if (Teacher* t = dynamic_cast<Teacher*>(staff)) {
                    t->display();
                }
                else if (LabAssistant* l = dynamic_cast<LabAssistant*>(staff)) {
                    l->display();
                }
                else if (Administrator* a = dynamic_cast<Administrator*>(staff)) {
                    a->display();
                }
                else if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
                    ta->display();
                }
                else {
                    staff->display(); // 基类的显示方法
                }
                found = true;
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

            for (const auto& staff : staffList) {
                if (staff->getName() == name) {
                    // 动态类型识别和显示
                    if (Teacher* t = dynamic_cast<Teacher*>(staff)) {
                        t->display();
                    }
                    else if (LabAssistant* l = dynamic_cast<LabAssistant*>(staff)) {
                        l->display();
                    }
                    else if (Administrator* a = dynamic_cast<Administrator*>(staff)) {
                        a->display();
                    }
                    else if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
                        ta->display();
                    }
                    found = true;
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
            if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
                ta->display();
                flag = true;
            }
            else if (LabAssistant* l = dynamic_cast<LabAssistant*>(staff)) {
                l->display();
                flag = true;
            }
            else if (Administrator* a = dynamic_cast<Administrator*>(staff)) {
                a->display();
                flag = true;
            }
            else if (Teacher* t = dynamic_cast<Teacher*>(staff)) {
                t->display();
                flag = true;
            }    
    }

    if (!flag) {
        cout << "记录为空" << endl;
    }
}

//编辑/修改
void change(int num) {
    Staff* staff = findStaffByNumber(num);
    if (!staff) {
        cout << "职员编号 " << num << " 不存在。" << endl;
        return;
    }

    cout << "正在编辑职员编号 " << num << " 的信息：" << endl;

    string newName, newGender;
    int newAge;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "输入新的姓名（留空表示不修改）：";
    getline(cin, newName);
    if (!newName.empty()) staff->setName(newName);

    cout << "输入新的性别（留空表示不修改）：";
    getline(cin, newGender);
    if (!newGender.empty()) staff->setGender(newGender);

    cout << "输入新的年龄（输入负数表示不修改）：";
    cin >> newAge;
    if (newAge >= 0) staff->setAge(newAge);

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
    if (Teacher* teacher = dynamic_cast<Teacher*>(staff)) {
        string newDept, newMajor, newTitle;
        cout << "输入新的系部（留空表示不修改）：";
        getline(cin, newDept);
        if (!newDept.empty()) teacher->setDept(newDept);

        cout << "输入新的专业（留空表示不修改）：";
        getline(cin, newMajor);
        if (!newMajor.empty()) teacher->setMajor(newMajor);

        cout << "输入新的职称（留空表示不修改）：";
        getline(cin, newTitle);
        if (!newTitle.empty()) teacher->setTitle(newTitle);
    }

    if (LabAssistant* labAssistant = dynamic_cast<LabAssistant*>(staff)) {
        string newLab, newPos;
        cout << "输入新的实验室（留空表示不修改）：";
        getline(cin, newLab);
        if (!newLab.empty()) labAssistant->setLab(newLab);

        cout << "输入新的职务（留空表示不修改）：";
        getline(cin, newPos);
        if (!newPos.empty()) labAssistant->setPos(newPos);
    }

    if (Administrator* admin = dynamic_cast<Administrator*>(staff)) {
        string newPol, newTitle;
        cout << "输入新的政治面貌（留空表示不修改）：";
        getline(cin, newPol);
        if (!newPol.empty()) admin->setPol(newPol);

        cout << "输入新的职称（留空表示不修改）：";
        getline(cin, newTitle);
        if (!newTitle.empty()) admin->setTitle(newTitle);
    }

    if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
        string newPol;
        cout << "输入新的政治面貌（留空表示不修改）：";
        getline(cin, newPol);
        if (!newPol.empty()) ta->setPol(newPol);
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
    cout << "2.教师人数" << endl;
    cout << "3.实验员人数" << endl;
    cout << "4.行政人员人数" << endl;
    cout << "5.教师兼行政人员人数" << endl;
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
        cout << "教师人数:" << teacherList.size() << endl;
        break; 
    }

    case 3: {
        cout << "实验员人数:" << labList.size() << endl;
        break;
    }

    case 4: {
        cout << "行政人员人数:" << adList.size() << endl;
        break;
    }

    case 5: {
        cout << "教师兼行政人员人数:" << taList.size() << endl;
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
    ofstream outFile("D:\\code_c++\\code_vs\\course design\\1\\staff_data.txt");
    if (!outFile) {
        cerr << "无法打开文件" << endl;
        return;
    }

    for (const auto& staff : staffList) {
        // 动态类型识别和显示
        if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
            ta->saveToFile(outFile);
        }
        else if (LabAssistant* l = dynamic_cast<LabAssistant*>(staff)) {
            l->saveToFile(outFile);
        }
        else if (Administrator* a = dynamic_cast<Administrator*>(staff)) {
            a->saveToFile(outFile);
        }
        else if (Teacher* t = dynamic_cast<Teacher*>(staff)) {
            t->saveToFile(outFile);
        }
    }

    cout << "保存成功！" << endl;
    outFile.close();
}

// 从文件中读取人员信息并加载到系统中
void readFromFile(vector<Staff*>& staffList, vector<Teacher*>& teacherList, vector<LabAssistant*>& labList,
    vector<Administrator*>& adList, vector<TeachingAdministrator*>& taList, const string& filename) {
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

        if (type == "T") { // 教师
            int number, age;
            string name, gender, department, major, jobTitle;
            char t;

            ss >> number >> t;
            getline(ss, name, ',');
            getline(ss, gender, ',');
            ss >> age >> t;
            getline(ss, department, ',');
            getline(ss, major, ',');
            getline(ss, jobTitle, ',');

            teacherList.push_back(new Teacher(number, name, gender, age, department, major, jobTitle));
            staffList.push_back(new Teacher(number, name, gender, age, department, major, jobTitle));
        }
        else if (type == "L") { // 实验员
            int number, age;
            string name, gender, lab, position;
            char t;

            ss >> number >> t;
            getline(ss, name, ',');
            getline(ss, gender, ',');
            ss >> age >> t;
            getline(ss, lab, ',');
            getline(ss, position, ',');

            labList.push_back(new LabAssistant(number, name, gender, age, lab, position));
            staffList.push_back(new LabAssistant(number, name, gender, age, lab, position));
        }
        else if (type == "A") { // 行政人员
            int number, age;
            string name, gender, politicalStatus, professionalTitle;
            char t;

            ss >> number >> t;
            getline(ss, name, ',');
            getline(ss, gender, ',');
            ss >> age >> t;
            getline(ss, politicalStatus, ',');
            getline(ss, professionalTitle, ',');

            adList.push_back(new Administrator(number, name, gender, age, politicalStatus, professionalTitle));
            staffList.push_back(new Administrator(number, name, gender, age, politicalStatus, professionalTitle));
        }
        else if (type == "C") { // 教师兼行政人员
            int number, age;
            string name, gender, department, major, jobTitle, politicalStatus;
            char t;

            ss >> number >> t;
            getline(ss, name, ',');
            getline(ss, gender, ',');
            ss >> age >> t;
            getline(ss, department, ',');
            getline(ss, major, ','); 
            getline(ss, jobTitle, ',');
            getline(ss, politicalStatus, ',');

            taList.push_back(new TeachingAdministrator(number, name, gender, age, department, major, jobTitle, politicalStatus));
            staffList.push_back(new TeachingAdministrator(number, name, gender, age, department, major, jobTitle, politicalStatus));
        }
    }

    inFile.close();
    cout << "从文件 " << filename << " 读取完毕。" << endl;
}

//主界面
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

//主函数
int main(){
    readFromFile(staffList, teacherList, labList, adList, taList, "D:\\code_c++\\code_vs\\course design\\1\\staff_data.txt");
    while (true) {
        mainInterface();
    }
	return 0;
}