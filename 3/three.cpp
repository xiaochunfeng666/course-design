#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//基类
class Resource {
private:
	int number;
	string title;
	string author;
	string level;

public:
	//构造函数
	Resource(int number, string title, string author, string level)
		:number(number), title(title), author(author), level(level) {}

	virtual ~Resource(){}

	//显示
	virtual void display() const {
		cout << "编号:" << number << "\t" << "标题:" << title << "\t"
			<< "作者:" << author << "\t" << "评级:" << level << "\t";
	}

	//获得编号
	int getNumber() {
		return number;
	}

	//获得标题
	string getTitle() {
		return title;
	}

	//获得作者
	string getAuthor() {
		return author;
	}

	//获得评级
	string getLevel() {
		return level;
	}

	//修改编号
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


	// 判断编号是否唯一
	static bool isUniqueNumber(int num, const vector<Resource*>& resourceList) {
		for (const auto& staff : resourceList) {
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
		file << number << "," << title << "," << author << "," << level << ",";
	}
};

//图书
class Book :public Resource {
private:
	string publisher;
	int IBSN;
	int pages;

public:
	Book(int number,string title,string author,string level,string publisher,int IBSN,int pages)
		:Resource(number,title,author,level),publisher(publisher),IBSN(IBSN),pages(pages){}

	void display() {
		cout << "===图书===" << "\t";
		Resource::display();
		cout << "出版社:" << publisher << "\t" << "IBSN号:" 
			<< IBSN << "\t" << "页数:" << pages << endl;
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

	//保存到文件
	void saveToFile(ofstream& file) {
		file << "B" << ",";
		Resource::saveToFile(file);
		file << publisher << "," << IBSN << "," << pages << "," << endl;
	}
};

//视频光盘
class Discs :public Resource {
private:
	string producer;
	int year;
	double time;

public:
	Discs(int number,string title,string author,string level,string producer,int year,double time)
		:Resource(number, title, author, level),producer(producer),year(year),time(time){}

	void display() {
		cout << "==视频光盘==" << "\t";
		Resource::display();
		cout << "出品者:" << producer << "\t" << "出品年份:" << year 
			<< "\t" << "视频时长:" << time << endl;
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

//图画
class Picture :public Resource {
private:
	string nationality;
	int length;
	int width;

public:
	Picture(int number,string title, string author,string level,string nationality,int length,int width)
		:Resource(number,title,author,level),nationality(nationality),length(length),width(width){}

	void display() {
		cout << "==图画==" << "\t";
		Resource::display();
		cout << "出品国籍:" << nationality << "\t" << "长度:" << 
			length << "\t" << "宽度:" << width << endl;
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

// 通过编号查找
Resource* findResourceByNumber(int num) {
	for (auto& resource : resourceList) {
		if (resource->getNumber() == num) {
			return resource;
		}
	}

	cout << "未找到该资料" << endl;
	return nullptr; // 未找到
}

//添加
void add() {
	cout << "===== 加入资料的类别 =====" << endl;
	cout << "======== 1.图书 ==========" << endl;
	cout << "======== 2.视频光盘 ======" << endl;
	cout << "======== 3.图画 ==========" << endl;

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
			cout << "请输入图书的编号:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "该编号已存在，请重新输入" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "请输入图书的标题:";
		cin >> title;
		cout << "请输入图书的作者:";
		cin >> author;
		cout << "请输入图书的评级（未评级/一般/成人/儿童:";
		cin >> level;
		cout << "请输入图书的出版社:";
		cin >> publisher;
		cout << "请输入图书的IBSN:";
		cin >> IBSN;
		cout << "请输入图书的页数:";
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
			cout << "请输入视频光盘的编号:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "该编号已存在，请重新输入" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "请输入视频光盘的标题:";
		cin >> title;
		cout << "请输入视频光盘的作者:";
		cin >> author;
		cout << "请输入视频光盘的评级（未评级/一般/成人/儿童:";
		cin >> level;
		cout << "请输入视频光盘的出品者:";
		cin >> producer;
		cout << "请输入视频光盘的出品年份:";
		cin >> year;
		cout << "请输入视频光盘的视频时长:";
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
			cout << "请输入图画的编号:";
			cin >> number;

			if (!Resource::isUniqueNumber(number, resourceList)) {
				cout << "该编号已存在，请重新输入" << endl;
			}
		} while (!Resource::isUniqueNumber(number, resourceList));
		cout << "请输入图画的标题:";
		cin >> title;
		cout << "请输入图画的作者:";
		cin >> author;
		cout << "请输入图画的评级（未评级/一般/成人/儿童:";
		cin >> level;
		cout << "请输入图画的出品轨国籍:";
		cin >> nationality;
		cout << "请输入图画的长:";
		cin >> length;
		cout << "请输入图画的宽:";
		cin >> width;

		pictureList.push_back(new Picture(number, title, author, level, nationality, length, width));
		resourceList.push_back(new Picture(number, title, author, level, nationality, length, width));
		break;
	}
	}
}

//查询
void search() {
	int choice;
	cout << "请选择查询方式：" << endl;
	cout << "1. 根据标题查询" << endl;
	cout << "2. 根据编号查询" << endl;
	cout << "3. 根据类别查询" << endl;
	cin >> choice;

	//记录是否找到
	bool found = false;

	switch (choice) {
	case 1: {
		string t;
		cout << "请输入标题: ";
		// 忽略之前的换行符或其他残留字符
		cin.ignore();
		getline(cin, t);

		//挨个遍历，找到时退出
		for (const auto& resource : resourceList) {
			if (resource->getTitle() == t) {
				// 动态类型识别和显示
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
					resource->display(); // 基类的显示方法
				}
				found = true;
				cout << endl;
				break;
			}
		}

		if (!found) {
			cout << "该标题不存在" << endl;
		}
		break;
	}
	case 2: {
		int num;
		cout << "请输入编号: ";
		cin >> num;

		//挨个遍历，找到时退出
		for (const auto& resource : resourceList) {
			if (resource->getNumber() == num) {
				// 动态类型识别和显示
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
					resource->display(); // 基类的显示方法
				}
				found = true;
				cout << endl;
				break;
			}
		}

		if (!found) {
			cout << "该编号不存在" << endl;
		}
		break;
	}
	case 3: {
		string t;
		cout << "请输入类别(图书/视频光盘/图画: ";
		// 忽略之前的换行符或其他残留字符
		cin.ignore();
		getline(cin, t);

		if (t == "图书") {
			if (bookList.empty()) {
				cout << "该类别没有物品！" << endl;
				break;
			}

			for (auto& book : bookList) {
				book->display();
			}
		}
		else if (t == "视频光盘") {
			if (discsList.empty()) {
				cout << "该类别没有物品！" << endl;
				break;
			}

			for (auto& discs : discsList) {
				discs->display();
			}
		}
		else if (t == "图画") {
			if (pictureList.empty()) {
				cout << "该类别没有物品！" << endl;
				break;
			}

			for (auto& picture : pictureList) {
				picture->display();
			}
		}
		else {
			cout << "输入的类别有误" << endl;
			break;
		}
		break;
	}
	default:
		cout << "无效的选择" << endl;
	}
}

//显示
void show() {
	bool flag = false;

	//挨个遍历，找到时退出
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
		cout << "记录为空" << endl;
	}
}

//修改
void change(int num) {
	Resource* resource = findResourceByNumber(num);
	if (!resource) {
		cout << "资料编号 " << num << " 不存在。" << endl;
		return;
	}

	cout << "正在编辑资料编号 " << num << " 的信息：" << endl;

	string newTitle, newAuthor,  newLevel;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "输入新的标题（留空表示不修改）：";
	getline(cin, newTitle);
	if (!newTitle.empty()) { resource->setTitle(newTitle); }

	cout << "输入新的作者（留空表示不修改）：";
	getline(cin, newAuthor);
	if (!newAuthor.empty()) { resource->setAuthor(newAuthor); }

	cout << "输入新的评级（留空表示不修改）：";
	getline(cin, newLevel);
	if (!newLevel.empty()) { resource->setLevel(newLevel); }

	// 清除输入缓冲区
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 检查编号是否需要修改
	int newNumber;
	cout << "输入新的编号（输入-1表示不修改）：";
	cin >> newNumber;
	if (newNumber != -1) {
		if (Resource::isUniqueNumber(newNumber, resourceList)) {
			// 修改编号
			resource->setNumber(newNumber);
		}
		else {
			cout << "新的编号 " << newNumber << " 已经存在，请使用其他编号" << endl;
		}
	}


	// 清除输入缓冲区
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 特定于各派生类的修改
	if (Book* book = dynamic_cast<Book*>(resource)) {
		string newPublisher;
		int newIBSN, newPages;

		cout << "输入新的出版社（留空表示不修改）：";
		getline(cin, newPublisher);
		if (!newPublisher.empty()) { book->setPublisher(newPublisher); }

		// 清除输入缓冲区
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "输入新的IBSN（负数表示不修改）：";
		cin >> newIBSN;
		if (newIBSN > 0) { book->setIBSN(newIBSN); }

		cout << "输入新的页数（负数表示不修改）：";
		cin >> newPages;
		if (newPages > 0) { book->setPages(newPages); }
	}

	if (Discs* discs = dynamic_cast<Discs*>(resource)) {
		string newProducer;
		int newYear;
		double newTime;

		cout << "输入新的出品者（留空表示不修改）：";
		getline(cin, newProducer);
		if (!newProducer.empty()) { discs->setProducer(newProducer); }

		cout << "输入新的年份（负数表示不修改）：";
		cin >> newYear;
		if (newYear > 0) { discs->setYear(newYear); }

		cout << "输入新的时间（负数表示不修改）：";
		cin >> newTime;
		if (newTime > 0) { discs->setTime(newTime); }
	}

	if (Picture* picture = dynamic_cast<Picture*>(resource)) {
		string newNationality;
		int newLength, newWidth;

		cout << "输入新的出品国籍（留空表示不修改）：";
		getline(cin, newNationality);
		if (!newNationality.empty()) { picture->setNationality(newNationality); }

		cout << "输入新的长（负数表示不修改）：";
		cin >> newLength;
		if (newLength > 0) { picture->setLength(newLength); }

		cout << "输入新的宽（负数表示不修改）：";
		cin >> newWidth;
		if (newWidth > 0) { picture->setWidth(newWidth); }
	}

	cout << "信息已更新。" << endl;
}

//删除
void deleteStaff() {
	if (resourceList.empty()) {
		cout << "物品库为空" << endl;
		return;
	}

	int num;
	cout << "请输入选择删除的物品编号" << endl;

	cin >> num;
	bool found = false;

	// 遍历查找并删除
	for (auto it = resourceList.begin(); it != resourceList.end(); ++it) {
		if ((*it)->getNumber() == num) {
			delete* it; // 释放内存
			resourceList.erase(it); // 从列表中删除
			//图书
			for (auto t = bookList.begin();t != bookList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					bookList.erase(t);
					found = true;
					break;
				}
			}
			//视频光盘
			for (auto t = discsList.begin();t != discsList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					discsList.erase(t);
					found = true;
					break;
				}
			}
			// 图画
			for (auto t = pictureList.begin();t != pictureList.end();++t) {
				if ((*t)->getNumber() == num) {
					delete* t;
					pictureList.erase(t);
					found = true;
					break;
				}
			}
			cout << "删除成功！" << endl;
			break;
		}
	}

	if (!found) {
		cout << "未找到编号为 " << num << " 的员工记录。" << endl;
	}
		
}

//统计
void count() {
	cout << "请输入需要统计的类型" << endl;
	cout << "1.物品总数" << endl;
	cout << "2.图书人数" << endl;
	cout << "3.视频光盘人数" << endl;
	cout << "4.图画人数" << endl;
	

	int choice;
	cin >> choice;

	switch (choice) {
	case 1: {
		cout << "物品总数:" << resourceList.size() << endl;
		break;
	}

	case 2: {
		cout << "图书人数:" << bookList.size() << endl;
		break;
	}

	case 3: {
		cout << "视频光盘人数:" << discsList.size() << endl;
		break;
	}

	case 4: {
		cout << "图画人数:" << pictureList.size() << endl;
		break;
	}
	}
}

//保存到文件
void saveToFile() {
	ofstream outFile("D:\\code_c++\\code_vs\\course design\\3\\data.txt");
	if (!outFile) {
		cerr << "无法打开文件" << endl;
		return;
	}

	for (const auto& resource : resourceList) {
		// 动态类型识别和显示
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

	cout << "保存成功！" << endl;
	outFile.close();
}

// 从文件中读取人员信息并加载到系统中
void readFromFile(vector<Resource*>& resourceList, vector<Book*>& bookList, vector<Discs*>& discsList,
	vector<Picture*>& pictureList, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "无法打开文件 " << filename << endl;
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

		//图书
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

		//视频光盘
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

		//图书
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
		cout << "请输入需要修改的资料编号" << endl;
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