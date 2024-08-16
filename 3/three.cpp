#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//����
class Resource {
private:
	int number;
	string title;
	string author;
	string level;

public:
	//���캯��
	Resource(int number, string title, string author, string level)
		:number(number), title(title), author(author), level(level) {}

	virtual ~Resource(){}

	//��ʾ
	virtual void display() const {
		cout << "���:" << number << "\t" << "����:" << title << "\t"
			<< "����:" << author << "\t" << "����:" << level << "\t";
	}

	//��ñ��
	int getNumber() {
		return number;
	}

	//��ñ���
	string getTitle() {
		return title;
	}

	//�������
	string getAuthor() {
		return author;
	}

	//�������
	string getLevel() {
		return level;
	}

	//�޸ı��
	void setNumber(int number) {
		this->number = number;
	}

	void setTitle(string title) {
		this->title = title;
	}

	void setAuthor(string author) {
		this->author = author;
	}

	void setLevel(string level) {
		this->level = level;
	}


	// �жϱ���Ƿ�Ψһ
	static bool isUniqueNumber(int num, const vector<Resource*>& resourceList) {
		for (const auto& staff : resourceList) {
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
		file << number << "," << title << "," << author << "," << level << ",";
	}
};

//ͼ��
class Book :public Resource {
private:
	string publisher;
	int IBSN;
	int pages;

public:
	Book(int number,string title,string author,string level,string publisher,int IBSN,int pages)
		:Resource(number,title,author,level),publisher(publisher),IBSN(IBSN),pages(pages){}

	void display() {
		cout << "===ͼ��===" << "\t";
		Resource::display();
		cout << "������:" << publisher << "\t" << "IBSN��:" 
			<< IBSN << "\t" << "ҳ��:" << pages << endl;
	}

	string getPublisher() {
		return publisher;
	}

	int getIBSN() {
		return IBSN;
	}

	int getPages() {
		return pages;
	}

	void setPublisher(string publisher){
		this->publisher = publisher;
	}

	void setIBSN(int IBSN) {
		this->IBSN = IBSN;
	}

	void setPages(int pages) {
		this->pages = pages;
	}

	//���浽�ļ�
	void saveToFile(ofstream& file) {
		file << "B" << ",";
		Resource::saveToFile(file);
		file << publisher << "," << IBSN << "," << pages << "," << endl;
	}
};

//��Ƶ����
class Discs :public Resource {
private:
	string producer;
	int year;
	double time;

public:
	Discs(int number,string title,string author,string level,string producer,int year,double time)
		:Resource(number, title, author, level),producer(producer),year(year),time(time){}

	void display() {
		cout << "==��Ƶ����==" << "\t";
		Resource::display();
		cout << "��Ʒ��:" << producer << "\t" << "��Ʒ���:" << year 
			<< "\t" << "��Ƶʱ��:" << time << endl;
	}

	string getProducer() {
		return producer;
	}

	int getYear() {
		return year;
	}

	double getTime() {
		return time;
	}

	void setProducer(string procuder) {
		this->producer = producer;
	}

	void setYear(int year) {
		this->year = year;
	}

	void setTime(double time) {
		this->time = time;
	}

	void saveToFile(ofstream& file) {
		file << "D" << ",";
		Resource::saveToFile(file);
		file << producer << "," << year << "," << time << endl;
	}

};

//ͼ��
class Picture :public Resource {
private:
	string nationality;
	int length;
	int width;

public:
	Picture(int number,string title, string author,string level,string nationality,int length,int width)
		:Resource(number,title,author,level),nationality(nationality),length(length),width(width){}

	void display() {
		cout << "==ͼ��==" << "\t";
		Resource::display();
		cout << "��Ʒ����:" << nationality << "\t" << "����:" << 
			length << "\t" << "���:" << width << endl;
	}

	string getNationality() {
		return nationality;
	}

	int getLength() {
		return length;
	}

	int getWidth() {
		return width;
	}

	void setNationality(string nationality) {
		this->nationality = nationality;
	}

	void setLength(int length) {
		this->length = length;
	}

	void setWidth(int width) {
		this->width = width;
	}

	void saveToFile(ofstream& file) {
		cout << "P" << ",";
		Resource::saveToFile(file);
		file << nationality << "," << length << "," << width << "," << endl;
	}
};

vector<Resource*> resourceList;
vector<Book*> bookList;
vector<Discs*> discsList;
vector<Picture*> pictureList;

// ͨ����Ų���
Resource* findResourceByNumber(int num) {
	for (auto& resource : resourceList) {
		if (resource->getNumber() == num) {
			return resource;
		}
	}

	cout << "δ�ҵ�������" << endl;
	return nullptr; // δ�ҵ�
}

//���
void add() {
	cout << "===== �������ϵ���� =====" << endl;
	cout << "======== 1.ͼ�� ==========" << endl;
	cout << "======== 2.��Ƶ���� ======" << endl;
	cout << "======== 3.ͼ�� ==========" << endl;

	int choice;
	cin >> choice;

	int number;
	string title;
	string author;
	string level;

	switch (choice)  {
	case 1: {
		string publisher;
		int IBSN;
		int pages;

		do {
			cout << "������ͼ��ı��:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "�ñ���Ѵ��ڣ�����������" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "������ͼ��ı���:";
		cin >> title;
		cout << "������ͼ�������:";
		cin >> author;
		cout << "������ͼ���������δ����/һ��/����/��ͯ:";
		cin >> level;
		cout << "������ͼ��ĳ�����:";
		cin >> publisher;
		cout << "������ͼ���IBSN:";
		cin >> IBSN;
		cout << "������ͼ���ҳ��:";
		cin >> pages;
		
		bookList.push_back(new Book(number, title, author, level, publisher, IBSN, pages));
		resourceList.push_back(new Book(number, title, author, level, publisher, IBSN, pages));
		break;
	}

	case 2: {
		string producer;
		int year;
		double time;

		do {
			cout << "��������Ƶ���̵ı��:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "�ñ���Ѵ��ڣ�����������" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "��������Ƶ���̵ı���:";
		cin >> title;
		cout << "��������Ƶ���̵�����:";
		cin >> author;
		cout << "��������Ƶ���̵�������δ����/һ��/����/��ͯ:";
		cin >> level;
		cout << "��������Ƶ���̵ĳ�Ʒ��:";
		cin >> producer;
		cout << "��������Ƶ���̵ĳ�Ʒ���:";
		cin >> year;
		cout << "��������Ƶ���̵���Ƶʱ��:";
		cin >> time;

		discsList.push_back(new Discs(number, title, author, level, producer, year, time));
		resourceList.push_back(new Discs(number, title, author, level, producer, year, time));
		break;
	}

	case 3: {
		string nationality;
		int length;
		int width;

		do {
			cout << "������ͼ���ı��:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "�ñ���Ѵ��ڣ�����������" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "������ͼ���ı���:";
		cin >> title;
		cout << "������ͼ��������:";
		cin >> author;
		cout << "������ͼ����������δ����/һ��/����/��ͯ:";
		cin >> level;
		cout << "������ͼ���ĳ�Ʒ�����:";
		cin >> nationality;
		cout << "������ͼ���ĳ�:";
		cin >> length;
		cout << "������ͼ���Ŀ�:";
		cin >> width;

		pictureList.push_back(new Picture(number, title, author, level, nationality, length, width));
		resourceList.push_back(new Picture(number, title, author, level, nationality, length, width));
		break;
	}
	}
}

//��ѯ
void search() {
	int choice;
	cout << "��ѡ���ѯ��ʽ��" << endl;
	cout << "1. ���ݱ����ѯ" << endl;
	cout << "2. ���ݱ�Ų�ѯ" << endl;
	cout << "3. ��������ѯ" << endl;
	cin >> choice;

	//��¼�Ƿ��ҵ�
	bool found = false;

	switch (choice) {
	case 1: {
		string t;
		cout << "���������: ";
		// ����֮ǰ�Ļ��з������������ַ�
		cin.ignore();
		getline(cin, t);

		//�����������ҵ�ʱ�˳�
		for (const auto& resource : resourceList) {
			if (resource->getTitle() == t) {
				// ��̬����ʶ�����ʾ
				if (Book* t = dynamic_cast<Book*>(resource)) {
					t->display();
				}
				else if (Discs* l = dynamic_cast<Discs*>(resource)) {
					l->display();
				}
				else if (Picture* a = dynamic_cast<Picture*>(resource)) {
					a->display();
				}
				else {
					resource->display(); // �������ʾ����
				}
				found = true;
				cout << endl;
				break;
			}
		}

		if (!found) {
			cout << "�ñ��ⲻ����" << endl;
		}
		break;
	}
	case 2: {
		int num;
		cout << "��������: ";
		cin >> num;

		//�����������ҵ�ʱ�˳�
		for (const auto& resource : resourceList) {
			if (resource->getNumber() == num) {
				// ��̬����ʶ�����ʾ
				if (Book* t = dynamic_cast<Book*>(resource)) {
					t->display();
				}
				else if (Discs* l = dynamic_cast<Discs*>(resource)) {
					l->display();
				}
				else if (Picture* a = dynamic_cast<Picture*>(resource)) {
					a->display();
				}
				else {
					resource->display(); // �������ʾ����
				}
				found = true;
				cout << endl;
				break;
			}
		}

		if (!found) {
			cout << "�ñ�Ų�����" << endl;
		}
		break;
	}
	case 3: {
		string t;
		cout << "���������(ͼ��/��Ƶ����/ͼ��: ";
		// ����֮ǰ�Ļ��з������������ַ�
		cin.ignore();
		getline(cin, t);

		if (t == "ͼ��") {
			if (bookList.empty()) {
				cout << "�����û����Ʒ��" << endl;
				break;
			}

			for (auto& book : bookList) {
				book->display();
			}
		}
		else if (t == "��Ƶ����") {
			if (discsList.empty()) {
				cout << "�����û����Ʒ��" << endl;
				break;
			}

			for (auto& discs : discsList) {
				discs->display();
			}
		}
		else if (t == "ͼ��") {
			if (pictureList.empty()) {
				cout << "�����û����Ʒ��" << endl;
				break;
			}

			for (auto& picture : pictureList) {
				picture->display();
			}
		}
		else {
			cout << "������������" << endl;
			break;
		}
		break;
	}
	default:
		cout << "��Ч��ѡ��" << endl;
	}
}

//��ʾ
void show() {
	bool flag = false;

	//�����������ҵ�ʱ�˳�
	for (const auto& resource : resourceList) {
		if (Book* t = dynamic_cast<Book*>(resource)) {
			t->display();
			flag = true;
		}
		else if (Discs* l = dynamic_cast<Discs*>(resource)) {
			l->display();
			flag = true;
		}
		else if (Picture* a = dynamic_cast<Picture*>(resource)) {
			a->display();
			flag = true;
		}
	}

	if (!flag) {
		cout << "��¼Ϊ��" << endl;
	}
}

//�޸�
void change(int num) {
	Resource* resource = findResourceByNumber(num);
	if (!resource) {
		cout << "���ϱ�� " << num << " �����ڡ�" << endl;
		return;
	}

	cout << "���ڱ༭���ϱ�� " << num << " ����Ϣ��" << endl;

	string newTitle, newAuthor,  newLevel;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "�����µı��⣨���ձ�ʾ���޸ģ���";
	getline(cin, newTitle);
	if (!newTitle.empty()) { resource->setTitle(newTitle); }

	cout << "�����µ����ߣ����ձ�ʾ���޸ģ���";
	getline(cin, newAuthor);
	if (!newAuthor.empty()) { resource->setAuthor(newAuthor); }

	cout << "�����µ����������ձ�ʾ���޸ģ���";
	getline(cin, newLevel);
	if (!newLevel.empty()) { resource->setLevel(newLevel); }

	// ������뻺����
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// ������Ƿ���Ҫ�޸�
	int newNumber;
	cout << "�����µı�ţ�����-1��ʾ���޸ģ���";
	cin >> newNumber;
	if (newNumber != -1) {
		if (Resource::isUniqueNumber(newNumber, resourceList)) {
			// �޸ı��
			resource->setNumber(newNumber);
		}
		else {
			cout << "�µı�� " << newNumber << " �Ѿ����ڣ���ʹ���������" << endl;
		}
	}


	// ������뻺����
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// �ض��ڸ���������޸�
	if (Book* book = dynamic_cast<Book*>(resource)) {
		string newPublisher;
		int newIBSN, newPages;

		cout << "�����µĳ����磨���ձ�ʾ���޸ģ���";
		getline(cin, newPublisher);
		if (!newPublisher.empty()) { book->setPublisher(newPublisher); }

		// ������뻺����
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "�����µ�IBSN��������ʾ���޸ģ���";
		cin >> newIBSN;
		if (newIBSN > 0) { book->setIBSN(newIBSN); }

		cout << "�����µ�ҳ����������ʾ���޸ģ���";
		cin >> newPages;
		if (newPages > 0) { book->setPages(newPages); }
	}

	if (Discs* discs = dynamic_cast<Discs*>(resource)) {
		string newProducer;
		int newYear;
		double newTime;

		cout << "�����µĳ�Ʒ�ߣ����ձ�ʾ���޸ģ���";
		getline(cin, newProducer);
		if (!newProducer.empty()) { discs->setProducer(newProducer); }

		cout << "�����µ���ݣ�������ʾ���޸ģ���";
		cin >> newYear;
		if (newYear > 0) { discs->setYear(newYear); }

		cout << "�����µ�ʱ�䣨������ʾ���޸ģ���";
		cin >> newTime;
		if (newTime > 0) { discs->setTime(newTime); }
	}

	if (Picture* picture = dynamic_cast<Picture*>(resource)) {
		string newNationality;
		int newLength, newWidth;

		cout << "�����µĳ�Ʒ���������ձ�ʾ���޸ģ���";
		getline(cin, newNationality);
		if (!newNationality.empty()) { picture->setNationality(newNationality); }

		cout << "�����µĳ���������ʾ���޸ģ���";
		cin >> newLength;
		if (newLength > 0) { picture->setLength(newLength); }

		cout << "�����µĿ�������ʾ���޸ģ���";
		cin >> newWidth;
		if (newWidth > 0) { picture->setWidth(newWidth); }
	}

	cout << "��Ϣ�Ѹ��¡�" << endl;
}

//ɾ��
void deleteStaff() {
	if (resourceList.empty()) {
		cout << "��Ʒ��Ϊ��" << endl;
		return;
	}

	int num;
	cout << "������ѡ��ɾ������Ʒ���" << endl;

	cin >> num;
	bool found = false;

	// �������Ҳ�ɾ��
	for (auto it = resourceList.begin(); it != resourceList.end(); ++it) {
		if ((*it)->getNumber() == num) {
			delete* it; // �ͷ��ڴ�
			resourceList.erase(it); // ���б���ɾ��
			//ͼ��
			for (auto t = bookList.begin();t != bookList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					bookList.erase(t);
					found = true;
					break;
				}
			}
			//��Ƶ����
			for (auto t = discsList.begin();t != discsList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					discsList.erase(t);
					found = true;
					break;
				}
			}
			// ͼ��
			for (auto t = pictureList.begin();t != pictureList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					pictureList.erase(t);
					found = true;
					break;
				}
			}
			cout << "ɾ���ɹ���" << endl;
			break;
		}
	}

	if (!found) {
		cout << "δ�ҵ����Ϊ " << num << " ��Ա����¼��" << endl;
	}
		
}

//ͳ��
void count() {
	cout << "��������Ҫͳ�Ƶ�����" << endl;
	cout << "1.��Ʒ����" << endl;
	cout << "2.ͼ������" << endl;
	cout << "3.��Ƶ��������" << endl;
	cout << "4.ͼ������" << endl;
	

	int choice;
	cin >> choice;

	switch (choice) {
	case 1: {
		cout << "��Ʒ����:" << resourceList.size() << endl;
		break;
	}

	case 2: {
		cout << "ͼ������:" << bookList.size() << endl;
		break;
	}

	case 3: {
		cout << "��Ƶ��������:" << discsList.size() << endl;
		break;
	}

	case 4: {
		cout << "ͼ������:" << pictureList.size() << endl;
		break;
	}
	}
}

//���浽�ļ�
void saveToFile() {
	ofstream outFile("D:\\code_c++\\code_vs\\course design\\3\\data.txt");
	if (!outFile) {
		cerr << "�޷����ļ�" << endl;
		return;
	}

	for (const auto& resource : resourceList) {
		// ��̬����ʶ�����ʾ
		if (Book* ta = dynamic_cast<Book*>(resource)) {
			ta->saveToFile(outFile);
		}
		else if (Discs* l = dynamic_cast<Discs*>(resource)) {
			l->saveToFile(outFile);
		}
		else if (Picture* a = dynamic_cast<Picture*>(resource)) {
			a->saveToFile(outFile);
		}
	}

	cout << "����ɹ���" << endl;
	outFile.close();
}

// ���ļ��ж�ȡ��Ա��Ϣ�����ص�ϵͳ��
void readFromFile(vector<Resource*>& resourceList, vector<Book*>& bookList, vector<Discs*>& discsList,
	vector<Picture*>& pictureList, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "�޷����ļ� " << filename << endl;
		return;
	}

	int number;
	string title, author, level;
	char t;

	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string type;
		getline(ss, type, ',');

		//ͼ��
		if (type == "B") {
			string publisher;
			int IBSN, pages;

			ss >> number >> t;
			getline(ss, title, ',');
			getline(ss, author, ',');
			getline(ss, level, ',');
			getline(ss, publisher, ',');
			ss >> IBSN >> t >> pages >> t;

			bookList.push_back(new Book(number, title, author, level, publisher, IBSN, pages));
			resourceList.push_back(new Book(number, title, author, level, publisher, IBSN, pages));
		}

		//��Ƶ����
		else if (type == "D") {
			string name;
			int year;
			double time;
		
			ss >> number >> t;
			getline(ss, title, ',');
			getline(ss, author, ',');
			getline(ss, level, ',');
			getline(ss, name, ',');
			ss >> year >> t >> time >> t;

			discsList.push_back(new Discs(number, title, author, level, name, year, time));
			resourceList.push_back(new  Discs(number, title, author, level, name, year, time));
		}

		//ͼ��
		else if (type == "P") {
			string nationality;
			int length, width;

			ss >> number >> t;
			getline(ss, title, ',');
			getline(ss, author, ',');
			getline(ss, level, ',');
			getline(ss, nationality, ',');
			ss >> length >> t >> width;

			pictureList.push_back(new Picture(number, title, author, level, nationality, length, width));
			resourceList.push_back(new Picture(number, title, author, level, nationality, length, width));
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
		cout << "��������Ҫ�޸ĵ����ϱ��" << endl;
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
	readFromFile(resourceList, bookList, discsList, pictureList
		, "D:\\code_c++\\code_vs\\course design\\3\\data.txt");
	while (true) {
		mainInterface();
	}
	return 0;
}