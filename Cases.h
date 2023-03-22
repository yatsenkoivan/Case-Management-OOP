#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>

namespace Cursor {
	//char symbol = char(219);
	//char symbol = '>';
	char symbol = char(254);
	void set(short x, short y) {
		const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, { x,y });
	}
	void reshow(int& pos, int dif) {
		Cursor::set(18, 10 + pos);
		std::cout << ' ';
		pos += dif;
		Cursor::set(18, 10 + pos);
		std::cout << Cursor::symbol;
		Cursor::set(0, 0);
	}
	int move(int& y, int max) {
		int x = 0;
		char choice = _getch();
		switch (choice) {
			case 'w':
			case 'W':
			case 72: //up_arrow
				if (y > 0) x = -1;
				break;
			case 's':
			case 'S':
			case 80: //down_arrow
				if (y < max - 1) x = 1;
				break;
			case ' ':
			case 13: //enter
				return y;
			case 'b':
			case 'B':
			case 27: //esc
				return -2;
		}
		Cursor::reshow(y, x);
		return -1;
	}
}

namespace Errors {
	int x = 18; //error coord_x
	int y = 20; //error coord_y
	void name_empty() {
		Cursor::set(x, y);
		std::cout << "! Name cannot be empty !";
		Cursor::set(0, 0);
	}
	void tag_empty() {
		Cursor::set(x, y);
		std::cout << "! Tag cannot be empty !";
		Cursor::set(0, 0);
	}
	void tag_not_unique() {
		Cursor::set(x, y);
		std::cout << "! Tag must be unique !";
		Cursor::set(0, 0);
	}
	void tag_not_found() {
		Cursor::set(x, y);
		std::cout << "! Tag not found !";
		Cursor::set(0, 0);
	}
	void invalid_date() {
		Cursor::set(x, y);
		std::cout << "! Invalid date !";
		Cursor::set(0, 0);
	}
}

namespace Months {
	int arr[]{ 0,31,28,31,30,31,30,30,31,30,31,30,31 };
};

class Time {
	private:
		uint16_t hours;
		uint16_t minutes;
		uint16_t seconds;
	public:
		Time() : Time(0, 0, 0) {}
		Time(uint16_t hh, uint16_t mm, uint16_t ss) :
			hours{ hh }, minutes{ mm }, seconds{ ss } {}
		friend std::ostream& operator<<(std::ostream& out, Time time) {
			out << time.hours << "\t" << time.minutes << "\t" << time.seconds;
			return out;
		}
		friend void operator>>(std::istream& in, Time& time) {
			in >> time.hours >> time.minutes >> time.seconds;
		}
		bool operator<(const Time& t) {
			if (hours > t.hours) return false;
			if (hours < t.hours) return true;
			else {
				if (minutes > t.minutes) return false;
				if (minutes < t.minutes) return true;
				else {
					if (seconds > t.seconds) return false;
					if (seconds < t.seconds) return true;
					else return false;
				}
			}
		}
		void setHours(uint16_t hh) {
			hours = hh;
		}
		void setMinutes(uint16_t mm) {
			minutes = mm;
		}
		void setSeconds(uint16_t ss) {
			seconds = ss;
		}
		uint16_t getHours() const {
			return hours;
		}
		uint16_t getMinutes() const {
			return minutes;
		}
		uint16_t getSeconds() const {
			return seconds;
		}
};

class Date {
	private:
		uint32_t yy; //year
		uint16_t mm; //month
		uint16_t dd; //day
	public:
		Date(uint16_t yy, uint16_t mm, uint16_t dd) :
			yy{ yy }, mm{ mm }, dd{ dd } {}
		Date() : Date(0, 0, 0) {}
		friend std::ostream& operator<<(std::ostream& out, Date date) {
			out << date.dd << "\t" << date.mm << "\t" << date.yy;
			return out;
		}
		friend void operator>>(std::istream& in, Date& date) {
			in >> date.dd >> date.mm >> date.yy;
		}
		bool operator==(const Date& d) {
			return (yy == d.yy
				&& mm == d.mm
				&& dd == d.dd);
		}
		bool operator<(const Date& d) {
			if (yy > d.yy) return false;
			if (yy < d.yy) return true;
			else {
				if (mm > d.mm) return false;
				if (mm < d.mm) return true;
				else {
					if (dd > d.dd) return false;
					if (dd < d.dd) return true;
					else return false;
				}
			}
		}
		void setDD(uint16_t dd) {
			this->dd = dd;
		}
		void setMM(uint16_t mm) {
			this->mm = mm;
		}
		void setYY(uint32_t yy) {
			this->yy = yy;
		}
		uint32_t getDD() const {
			return dd;
		}
		uint16_t getMM() const {
			return mm;
		}
		uint32_t getYY() const {
			return yy;
		}
};

class Case {
	private:
		std::string tag;
		std::string name;
		std::string description;
		int priority;
		Date date;
		Time time;
	public:
		Case(std::string tag, std::string name, std::string description, int priority, Date date, Time time) :
			tag{ tag }, name{ name }, description{ description }, priority{ priority }, date{ date }, time{ time } {}
		Case() : Case("", "", "", 0, Date(), Time()) {}
		friend void operator>>(std::istream& in, Case& c) {
			in >> c.tag;
			in >> c.name;
			in.ignore();
			getline(in, c.description);

			in >> c.priority;
			in >> c.date;
			in >> c.time;
		}
		void show() {
			std::cout << "Name:\t\t\t" << name << std::endl;
			std::cout << "Description:\t\t" << description << std::endl;
			std::cout << "Priority:\t\t" << priority << std::endl;
			std::cout << "Date:\t\t\t" << date << std::endl;
			std::cout << "Time:\t\t\t" << time << std::endl;
			std::cout << "~Tag\t\t\t" << tag << std::endl;
			std::cout << "--------------------------------------------------\n";
		}
		std::string getTag() const {
			return tag;
		}
		std::string getName() const {
			return name;
		}
		std::string getDesc() const {
			return description;
		}
		int getPrior() const {
			return priority;
		}
		Date getDate() const {
			return date;
		}
		Time getTime() const {
			return time;
		}
		void setTag(std::string tag) {
			this->tag = tag;
		}
		void setName(std::string name) {
			this->name = name;
		}
		void setDesc(std::string desc) {
			this->description = desc;
		}
		void setPrior(int prior) {
			this->priority = prior;
		}
		void setDate(Date date) {
			this->date = date;
		}
		void setTime(Time time) {
			this->time = time;
		}
};


class Manager {
	private:
		std::vector<Case> cases;
		char bg_color;
		char fg_color;
	public:
		Manager() : Manager('7', '0') {}
		Manager(char bg, char fg) : bg_color{ bg }, fg_color{ fg } {}
		std::vector<Case>::iterator findByTag(std::string tag) {
			auto res = find_if(cases.begin(), cases.end(), [tag](const Case& c) { return c.getTag() == tag; });
			return res;
		}
		void addCase() {

			Case c;
			editCase(c);

			cases.push_back(c);
			return;
		}
		void showSortedMenu() {
			system("cls");

			int cursor_y = 0;
			std::string title = "Show sorted";
			std::vector<std::string> choices
			{ "By name", "By priority", "By date and time" };
			menu_show(title, choices, cursor_y);

			std::vector<Case> res = cases;

			int move = 0;
			do {
				move = Cursor::move(cursor_y, choices.size());
				switch (move) {
				case 0:
					std::sort(res.begin(), res.end(), [](const Case& a, const Case& b) { return a.getName() < b.getName(); });
					break;
				case 1:
					sort(res.begin(), res.end(), [](const Case& a, const Case& b) { return a.getPrior() > b.getPrior(); });
					break;
				case 2:
					sort(res.begin(), res.end(), [](const Case& a, const Case& b) {
						if (a.getDate() == b.getDate()) return a.getTime() < b.getTime();
						else return a.getDate() < b.getDate();
						});
					break;
				}
				if (move >= 0) {
					system("cls");
					for (Case& c : res) c.show();
					system("pause");
					menu_show(title, choices, cursor_y);
				}
			} while (move != -2);
		}
		void showMenu() {
			int move = 0;

			int cursor_y = 0;
			std::string title = "Show";
			std::vector<std::string> choices
			{ "Default", "Sorted" };
			menu_show(title, choices, cursor_y);

			do {
				move = Cursor::move(cursor_y, choices.size());
				switch (move) {
				case 0:
					show();
					break;
				case 1:
					showSortedMenu();
					break;
				}
				if (move >= 0) menu_show(title, choices, cursor_y);
			} while (move != -2);
		}
		void editCase_menu(int cursor_pos, const Case& c) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << "Edit case";
			Cursor::set(18, 10 + cursor_pos);
			std::cout << Cursor::symbol << ' ';
			Cursor::set(20, 10);
			std::cout << "Name:\t\t" << c.getName();
			Cursor::set(20, 11);
			std::cout << "Description:\t" << c.getDesc();
			Cursor::set(20, 12);
			std::cout << "Priority:\t\t" << c.getPrior();
			Cursor::set(20, 13);
			std::cout << "Date:\t\t" << c.getDate();
			Cursor::set(20, 14);
			std::cout << "Time:\t\t" << c.getTime();
			Cursor::set(20, 15);
			std::cout << "Tag:\t\t" << c.getTag();
			Cursor::set(20, 16);
			std::cout << "Submit";
			Cursor::set(0, 0);
		}
		bool editCase(Case& c) {
			system("cls");

			Case new_case(c);

			int cursor_y = 0;
			editCase_menu(cursor_y, new_case);

			Date d = c.getDate();
			Time t = c.getTime();

			int move = 0;
			std::string temp;
			int temp_int;
			do {
				move = Cursor::move(cursor_y, 7);
				switch (move) {
				case 0:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp;
					new_case.setName(temp);
					break;
				case 1:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					getline(std::cin, temp);
					new_case.setDesc(temp);
					break;
				case 2:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					new_case.setPrior(temp_int);
					break;
				case 3:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					d.setDD(temp_int);
					Cursor::set(46, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					d.setMM(temp_int);
					Cursor::set(54, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					d.setYY(temp_int);
					new_case.setDate(d);
					break;
				case 4:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					t.setHours(temp_int);
					Cursor::set(46, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					t.setMinutes(temp_int);
					Cursor::set(54, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp_int;
					t.setSeconds(temp_int);

					t.setMinutes(t.getMinutes() + t.getSeconds() / 60);
					t.setSeconds(t.getSeconds() % 60);
					t.setHours(t.getHours() + t.getMinutes() / 60);
					t.setMinutes(t.getMinutes() % 60);
					t.setHours(t.getHours() % 24);

					new_case.setTime(t);
					break;
				case 5:
					Cursor::set(38, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> temp;
					new_case.setTag(temp);
					break;
				case 6:
					if (new_case.getName() == "") Errors::name_empty();
					else if (new_case.getTag() == "") Errors::tag_empty();
					else if (findByTag(new_case.getTag()) != cases.end()) Errors::tag_not_unique();
					else if
						((d.getYY() == 0 || d.getMM() == 0 || d.getDD() == 0)
							||
							(d.getMM() > 12 || d.getDD() > 31)) Errors::invalid_date();
					else if
						(d.getDD() > Months::arr[d.getMM()]) Errors::invalid_date(); //incorrect days
					else if
						(d.getMM() != 2 && d.getDD() == 29) Errors::invalid_date(); //feb_29
					else {
						c = new_case;
						return true;
					}
					break;
				}
				if (move >= 0 && move != 6) {
					editCase_menu(cursor_y, new_case);
					Cursor::set(0, 0);
				}
			} while (move != -2);
			return false;
		}
		void searchTag_menu(int cursor_y, std::string tag) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << "Search case\n";
			Cursor::set(18, 10 + cursor_y);
			std::cout << Cursor::symbol;
			Cursor::set(20, 10);
			std::cout << "Tag:\t" << tag;
			Cursor::set(20, 11);
			std::cout << "Submit";
			Cursor::set(0, 0);
		}
		std::vector<Case>::iterator searchTag() {
			system("cls");
			int move = 0;
			int cursor_y = 0;

			std::string tag = "";
			searchTag_menu(cursor_y, tag);

			std::vector<Case>::iterator c;
			do {
				move = Cursor::move(cursor_y, 2);
				switch (move) {
				case 0:
					Cursor::set(32, 10 + cursor_y);
					std::cout << "> ";
					std::cin >> tag;
					Cursor::set(0, 0);
					break;
				case 1:
					if (tag == "") Errors::tag_empty();
					else {
						c = findByTag(tag);
						if (c == cases.end()) Errors::tag_not_found();
						else {
							return c;
						}
					}
				}
				if (move >= 0 && move != 1) {
					searchTag_menu(cursor_y, tag);
				}

			} while (move != -2);
			return cases.end();
		}
		void editCaseSearch() {
			std::vector<Case>::iterator c = searchTag();
			if (c != cases.end()) {
				Case new_case(*c);
				std::string tag = c->getTag();
				c->setTag(""); //tag_unique bug
				if (editCase(new_case)) {
					*c = new_case;
					save();
				}
				else
					c->setTag(tag);
			}
		}
		void delCaseSearch() {
			std::vector<Case>::iterator c = searchTag();
			if (c != cases.end()) {
				cases.erase(c);
			}
		}
		void setColor() {
			char cmd[] = { 'c','o','l','o','r',' ',bg_color,fg_color,'\0' };
			system(cmd);
		}
		void saveColor() {
			std::ofstream data;
			data.open("color.txt", std::ios::out);
			data << bg_color << "\t" << fg_color << std::endl;
		}
		void changeColor() {
			int move = 0;

			int cursor_y = 0;
			std::string title = "Change color";
			std::vector<std::string> choices
			{ "Background", "Foreground", "Back" };

			menu_show(title, choices, cursor_y);

			do {
				move = Cursor::move(cursor_y, choices.size());

				switch (move) {
				case 0:
					bg_color++;
					break;
				case 1:
					fg_color++;
					break;
				case 2:
					return;
				}

				if (bg_color == '9' + 1) bg_color = 'a';
				if (fg_color == '9' + 1) fg_color = 'a';
				if (bg_color == 'f' + 1) bg_color = '0';
				if (fg_color == 'f' + 1) fg_color = '0';

				if (bg_color == '0' - 1) bg_color = 'f';
				if (fg_color == '0' - 1) fg_color = 'f';
				if (bg_color == 'a' - 1) bg_color = '9';
				if (fg_color == 'a' - 1) fg_color = '9';

				setColor();
				saveColor();

			} while (move != -2);
		}
		void menu_show(std::string title, std::vector<std::string> choices, int cursor_pos) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << title;
			Cursor::set(18, 10 + cursor_pos);
			std::cout << Cursor::symbol << ' ';
			int y = 10;
			for (std::string choice : choices) {
				Cursor::set(20, y);
				std::cout << choice;
				y++;
			}
			Cursor::set(0, 0);
		}
		void menu() {

			setColor();

			int cursor_y = 0; //current pos

			std::string title = "Menu";
			std::vector<std::string> choices
			{ "Show", "Add case", "Delete case", "Search case", "Edit case", "Change color", "Exit" };


			menu_show(title, choices, cursor_y);

			int move;
			while (true) {
				move = Cursor::move(cursor_y, choices.size());
				switch (move) {
				case 0:
					showMenu();
					break;
				case 1:
					addCase();
					save();
					break;
				case 2:
					delCaseSearch();
					break;
				case 3:
					//search
					break;
				case 4:
					editCaseSearch();
					break;
				case 5:
					changeColor();
					break;
				case 6:
					return;
				}
				if (move >= 0) menu_show(title, choices, cursor_y);
			}
		}
		void load() {
			std::ifstream data;
			data.open("color.txt", std::ios::in);

			data >> bg_color >> fg_color;

			data.close();

			data.open("cases.txt", std::ios::in);

			int amount;
			data >> amount;

			Case c;

			for (int i = 0; i < amount; i++) {
				if (data.eof()) break;
				data >> c;
				cases.push_back(c);
			}
		}
		void save() {
			std::ofstream data;
			data.open("cases.txt", std::ios::out);
			data << cases.size() << std::endl;
			for (auto& i : cases) {
				data << i.getTag() << std::endl;
				data << i.getName() << std::endl;
				data << i.getDesc() << std::endl;
				data << i.getPrior() << std::endl;
				data << i.getDate() << std::endl;
				data << i.getTime() << std::endl;
			}
		}
		void show() {
			system("cls");
			for (Case& c : cases) {
				c.show();
			}
			system("pause");
		}
};
