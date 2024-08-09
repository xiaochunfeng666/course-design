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

    // ���캯��
    Staff(int num, string name, string gendar, int age) : 
        number(num), name(name), gender(gendar), age(age) {}

    // ���������������ڶ�̬
    virtual ~Staff() {}

    // ��ʾְ����Ϣ
    virtual void display() const {
        std::cout << "����: " << name << "\t���: " << number
            << "\t�Ա�:" << gender << "\t����: " << age;
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
    int getAge() {
        return age;
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

    //�޸�����
    void setAge(int age) {
        this->age = age;
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

    //���浽�ļ�
    virtual void saveToFile(ofstream& file) const {
        file << number << "," << name << "," << gender << "," << age << ",";
    }
};

// �����ࣺ��ʦ
class Teacher : public Staff {
protected:
    string department;
    string major;
    string jobTitle;

public:
    //���캯�������ڳ�ʼ��
    Teacher(int num, string name, string gender, int age, string dept, string maj, string title)
        : Staff(num, name, gender, age), department(dept), major(maj), jobTitle(title) {}

    //��ʾ��Ϣ
    void display(){
        cout << "=== ��ʦ ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "ϵ��: " << department << "\t";
        cout << "רҵ: " << major << "\t";
        cout << "ְ��: " << jobTitle << "\t";
        cout << endl;
    }

    //��ȡϵ��
    string getDept() {
        return department;
    }

    //��ȡרҵ
    string getMajor() {
        return major;
    }

    //���ְ��
    string getTitle() {
        return jobTitle;
    }

    //�޸�רҵ
    void setMajor(string major) {
        this->major = major;
    }

    //�޸�ϵ��
    void setDept(string dept) {
        this->department = dept;
    }

    //�޸�ְ��
    void setTitle(string title) {
        this->jobTitle = title;
    }

    //���浽�ļ�
    void saveToFile(ofstream& file) {
        file << "T" << ",";
        Staff::saveToFile(file);
        file  << department << "," << major <<  "," << jobTitle << "," << endl;
    }
};

// �����ࣺʵ��Ա
class LabAssistant : public Staff {
private:
    string lab;
    string position;

public:
    LabAssistant(int num, string name, string gender, int age, string lab, string pos)
        : Staff(num, name, gender, age), lab(lab), position(pos) {}

    void display(){
        cout << "=== ʵ��Ա ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "ʵ����: " << lab << "\t";
        cout << "ְ��: " << position << "\t";
        cout << endl;
    }

    //��ȡʵ����
    string getLab() {
        return lab;
    }

    //��ȡְ��
    string getPos() {
        return position;
    }

    //�޸�ְ��
    void setPos(string pos) {
        this->position = pos;
    }

    //�޸�ʵ����
    void setLab(string lab) {
        this->lab = lab;
    }

    //���浽�ļ�
    void saveToFile(ofstream& file) {
        file << "L" << ",";
        Staff::saveToFile(file);
        file << lab << "," << position << "," << endl;
    }
};

// �����ࣺ������Ա
class Administrator : public Staff {
private:
    string politicalStatus;
    string professionalTitle;

public:
    Administrator(int num, string name, string gender, int age, string pol, string prof)
        : Staff(num, name, gender, age), politicalStatus(pol), professionalTitle(prof) {}

    void display(){
        cout << "=== ������Ա ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "������ò: " << politicalStatus << "\t";
        cout << "ְ��: " << professionalTitle << "\t";
        cout << endl;
    }

    //��ȡ������ò
    string getPol() {
        return politicalStatus;
    }

    //���ְ��
    string getTitle() {
        return professionalTitle;
    }

    //�޸�ְ��
    void setTitle(string title) {
        this->professionalTitle = title;
    }

    //�޸�������ò
    void setPol(string pol) {
        this->politicalStatus = pol;
    }

    //���浽�ļ�
    void saveToFile(ofstream& file) {
        file << "A" << ",";        
        Staff::saveToFile(file);
        file  << politicalStatus << "," << professionalTitle << "," << endl;
    }
};

// �����ࣺ��ʦ��������Ա
class TeachingAdministrator : public Teacher {
private:
    string politicalStatus;

public:
    TeachingAdministrator(int num, string name, string gender, int age, string dept, string maj, string t, string pol)
        : Teacher(num, name, gender, age, dept, maj, t), politicalStatus(pol) {}

    void display() {
        cout << "=== ��ʦ��������Ա ===" << "\t";
        Staff::display();
        cout << "\t";
        cout << "ϵ��: " << department << "\t";
        cout << "רҵ: " << major << "\t";
        cout << "ְ��: " << jobTitle << "\t";
        cout << "������ò: " << politicalStatus << "\t";
        cout << endl;
    }

    //�޸�������ò
    void setPol(string pol) {
        this->politicalStatus = pol;
    }

    //���浽�ļ�
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
    cout << "======== 1.��ʦ ==========" << endl;
    cout << "======== 2.ʵ��Ա ========" << endl;
    cout << "======== 3.������Ա ======" << endl;
    cout << "======== 4.��ʦ��������Ա=" << endl;

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
                cout << "�������ʦ�ı��:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "�ñ���Ѵ��ڣ�����������" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "�������ʦ������:" ;
            cin >> name ;
            cout << "�������ʦ���Ա�:" ;
            cin >> gender;;
            cout << "�������ʦ������:" ;
            cin >> age;
            cout << "�������ʦ��ϵ��:" ;
            cin >> dept;
            cout << "�������ʦ��רҵ:" ;
            cin >> major;
            cout << "�������ʦ��ְ��:" ;
            cin >> title;

            teacherList.push_back(new Teacher(num, name, gender, age, dept, major, title));
            staffList.push_back(new Teacher(num, name, gender, age, dept, major, title));
            break;
        }

        case 2:{
            string lab, position;
            do {
                cout << "������ʵ��Ա�ı��:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "�ñ���Ѵ��ڣ�����������" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "������ʵ��Ա������:";
            cin >> name;
            cout << "������ʵ��Ա���Ա�:";
            cin >> gender;
            cout << "������ʵ��Ա������:";
            cin >> age;
            cout << "������ʵ��Ա��ʵ����:";
            cin >> lab;
            cout << "������ʵ��Ա��ְ��:";
            cin >> position;

            labList.push_back(new LabAssistant(num, name, gender, age, lab, position));
            staffList.push_back(new LabAssistant(num, name, gender, age, lab, position));
            break;
        }
        
        case 3: {
            string pol, prof;

            do {
            cout << "������������Ա�ı��:";
            cin >> num;  
            
            if (!Staff::isUniqueNumber(num, staffList)) {
                cout << "�ñ���Ѵ��ڣ�����������" << endl;
            }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "������������Ա������:";
            cin >> name;
            cout << "������������Ա���Ա�:";
            cin >> gender;
            cout << "������������Ա������:";
            cin >> age;
            cout << "������������Ա��������ò:";
            cin >> pol;
            cout << "������������Ա��ְ��:";
            cin >> prof;

            adList.push_back(new Administrator(num, name, gender, age, pol, prof));
            staffList.push_back(new Administrator(num, name, gender, age, pol, prof));
            break;
        }

        case 4:{ 
            string dept, major, title;
            string pol, prof;

            do {
                cout << "�������ʦ��������Ա�ı��:";
                cin >> num;

                if (!Staff::isUniqueNumber(num, staffList)) {
                    cout << "�ñ���Ѵ��ڣ�����������" << endl;
                }
            } while (!Staff::isUniqueNumber(num, staffList));
            cout << "�������ʦ��������Ա������:";
            cin >> name;
            cout << "�������ʦ��������Ա���Ա�:";
            cin >> gender;
            cout << "�������ʦ��������Ա������:";
            cin >> age;
            cout << "�������ʦ��������Ա��ϵ��:";
            cin >> dept;
            cout << "�������ʦ��������Ա��רҵ:";
            cin >> major;
            cout << "�������ʦ��������Ա��ְ��:";
            cin >> title;
            cout << "�������ʦ��������Ա��������ò:";
            cin >> pol;

            taList.push_back(new TeachingAdministrator(num, name, gender, age, dept, major, title, pol));
            staffList.push_back(new TeachingAdministrator(num, name, gender, age, dept, major, title, pol));
            break; 
        }
        default:
            cout << "��Чѡ��" << endl;
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
                    staff->display(); // �������ʾ����
                }
                found = true;
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

            for (const auto& staff : staffList) {
                if (staff->getName() == name) {
                    // ��̬����ʶ�����ʾ
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
        cout << "��¼Ϊ��" << endl;
    }
}

//�༭/�޸�
void change(int num) {
    Staff* staff = findStaffByNumber(num);
    if (!staff) {
        cout << "ְԱ��� " << num << " �����ڡ�" << endl;
        return;
    }

    cout << "���ڱ༭ְԱ��� " << num << " ����Ϣ��" << endl;

    string newName, newGender;
    int newAge;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "�����µ����������ձ�ʾ���޸ģ���";
    getline(cin, newName);
    if (!newName.empty()) staff->setName(newName);

    cout << "�����µ��Ա����ձ�ʾ���޸ģ���";
    getline(cin, newGender);
    if (!newGender.empty()) staff->setGender(newGender);

    cout << "�����µ����䣨���븺����ʾ���޸ģ���";
    cin >> newAge;
    if (newAge >= 0) staff->setAge(newAge);

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
    if (Teacher* teacher = dynamic_cast<Teacher*>(staff)) {
        string newDept, newMajor, newTitle;
        cout << "�����µ�ϵ�������ձ�ʾ���޸ģ���";
        getline(cin, newDept);
        if (!newDept.empty()) teacher->setDept(newDept);

        cout << "�����µ�רҵ�����ձ�ʾ���޸ģ���";
        getline(cin, newMajor);
        if (!newMajor.empty()) teacher->setMajor(newMajor);

        cout << "�����µ�ְ�ƣ����ձ�ʾ���޸ģ���";
        getline(cin, newTitle);
        if (!newTitle.empty()) teacher->setTitle(newTitle);
    }

    if (LabAssistant* labAssistant = dynamic_cast<LabAssistant*>(staff)) {
        string newLab, newPos;
        cout << "�����µ�ʵ���ң����ձ�ʾ���޸ģ���";
        getline(cin, newLab);
        if (!newLab.empty()) labAssistant->setLab(newLab);

        cout << "�����µ�ְ�����ձ�ʾ���޸ģ���";
        getline(cin, newPos);
        if (!newPos.empty()) labAssistant->setPos(newPos);
    }

    if (Administrator* admin = dynamic_cast<Administrator*>(staff)) {
        string newPol, newTitle;
        cout << "�����µ�������ò�����ձ�ʾ���޸ģ���";
        getline(cin, newPol);
        if (!newPol.empty()) admin->setPol(newPol);

        cout << "�����µ�ְ�ƣ����ձ�ʾ���޸ģ���";
        getline(cin, newTitle);
        if (!newTitle.empty()) admin->setTitle(newTitle);
    }

    if (TeachingAdministrator* ta = dynamic_cast<TeachingAdministrator*>(staff)) {
        string newPol;
        cout << "�����µ�������ò�����ձ�ʾ���޸ģ���";
        getline(cin, newPol);
        if (!newPol.empty()) ta->setPol(newPol);
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
    cout << "2.��ʦ����" << endl;
    cout << "3.ʵ��Ա����" << endl;
    cout << "4.������Ա����" << endl;
    cout << "5.��ʦ��������Ա����" << endl;
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
        cout << "��ʦ����:" << teacherList.size() << endl;
        break; 
    }

    case 3: {
        cout << "ʵ��Ա����:" << labList.size() << endl;
        break;
    }

    case 4: {
        cout << "������Ա����:" << adList.size() << endl;
        break;
    }

    case 5: {
        cout << "��ʦ��������Ա����:" << taList.size() << endl;
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
    ofstream outFile("D:\\code_c++\\code_vs\\course design\\1\\staff_data.txt");
    if (!outFile) {
        cerr << "�޷����ļ�" << endl;
        return;
    }

    for (const auto& staff : staffList) {
        // ��̬����ʶ�����ʾ
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

    cout << "����ɹ���" << endl;
    outFile.close();
}

// ���ļ��ж�ȡ��Ա��Ϣ�����ص�ϵͳ��
void readFromFile(vector<Staff*>& staffList, vector<Teacher*>& teacherList, vector<LabAssistant*>& labList,
    vector<Administrator*>& adList, vector<TeachingAdministrator*>& taList, const string& filename) {
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

        if (type == "T") { // ��ʦ
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
        else if (type == "L") { // ʵ��Ա
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
        else if (type == "A") { // ������Ա
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
        else if (type == "C") { // ��ʦ��������Ա
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

//������
int main(){
    readFromFile(staffList, teacherList, labList, adList, taList, "D:\\code_c++\\code_vs\\course design\\1\\staff_data.txt");
    while (true) {
        mainInterface();
    }
	return 0;
}