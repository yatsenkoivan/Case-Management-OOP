#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>

namespace Cursor {
	//char symbol = char(219);
	char symbol = '>';
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
}

class Time {
	private:
		int hours;
		int minutes;
		int seconds;
	public:
		Time() : Time(0, 0, 0) {}
		Time(int hh, int mm, int ss) :
			hours{ hh }, minutes{ mm }, seconds{ ss } {}
		friend std::ostream& operator<<(std::ostream& out, Time time) {
			out << time.hours << "\t" << time.minutes << "\t" << time.seconds;
			return out;
		}
		friend void operator>>(std::istream& in, Time& time) {
			in >> time.hours >> time.minutes >> time.seconds;
		}
		void setHours(int hh) {
			hours = hh;
		}
		void setMinutes(int mm) {
			minutes = mm;
		}
		void setSeconds(int ss) {
			seconds = ss;
		}
};

class Date {
	private:
		int yy; //year
		int mm; //month
		int dd; //day
	public:
		Date(int yy, int mm, int dd) :
			yy{ yy }, mm{ mm }, dd{ dd } {}
		Date() : Date(0, 0, 0) {}
		friend std::ostream& operator<<(std::ostream& out, Date date) {
			out << date.dd << "\t" << date.mm << "\t" << date.yy;
			return out;
		}
		friend void operator>>(std::istream& in, Date& date) {
			in >> date.dd >> date.mm >> date.yy;
		}
		void setDD(int dd) {
			this->dd = dd;
		}
		void setMM(int mm) {
			this->mm = mm;
		}
		void setYY(int yy) {
			this->yy = yy;
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
			tag{tag}, name {name}, description{ description }, priority{ priority }, date{ date }, time{ time } {}
		Case() : Case("", "", "", 0, Date(), Time() ) {}
		friend void operator>>(std::istream& in, Case& c) {
			in >> c.tag;
			in >> c.name;
			in.ignore();
			getline(in, c.description);
			
			in >> c.priority;
			in >> c.date;
			in >> c.time;
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
		void show_menu(int cursor_pos) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << "Menu";
			Cursor::set(18, 10 + cursor_pos);
			std::cout << Cursor::symbol << ' ';
			Cursor::set(20, 10);
			std::cout << "Show cases";
			Cursor::set(20, 11);
			std::cout << "Add case";
			Cursor::set(20, 12);
			std::cout << "Delete case";
			Cursor::set(20, 13);
			std::cout << "Search case";
			Cursor::set(20, 14);
			std::cout << "Edit case";
			Cursor::set(20, 15);
			std::cout << "Change color";
			Cursor::set(20, 16);
			std::cout << "Exit";
			Cursor::set(0, 0);
		}
		void show_addCase_menu(int cursor_pos, Case& c) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << "Add Case";
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
			Cursor::set(20, 18);
			std::cout << "B - to return";
			Cursor::set(0, 0);
		}
		void addCase() {
			system("cls");

			Case c;
			Time t;
			Date d;

			int y = 0;
			int x = 0;
			show_addCase_menu(0, c);

			char choice;
			std::string temp;
			int temp_int;
			while (true) {
				x = 0;
				choice = _getch();
				switch (choice) {
					case 'w':
					case 'W':
						if (y > 0) x = -1;
						break;
					case 's':
					case 'S':
						if (y < 6) x = 1;
						break;
					case ' ':
						switch (y) {
							case 0:
								Cursor::set(40, 10 + y);
								std::cin >> temp;
								c.setName(temp);
								break;
							case 1:
								if (std::cin) std::cin.ignore(100,'\n');
								Cursor::set(40, 10 + y);
								getline(std::cin, temp);
								c.setDesc(temp);
								//std::cin.ignore();
								break;
							case 2:
								Cursor::set(40, 10 + y);
								std::cin >> temp_int;
								c.setPrior(temp_int);
								std::cin.clear(); 
								break;
							case 3:
								Cursor::set(40, 10 + y);
								std::cin >> temp_int;
								d.setDD(temp_int);
								Cursor::set(48, 10 + y);
								std::cin >> temp_int;
								d.setMM(temp_int);
								Cursor::set(56, 10 + y);
								std::cin >> temp_int;
								d.setYY(temp_int);
								c.setDate(d);
								break;
							case 4:
								Cursor::set(40, 10 + y);
								std::cin >> temp_int;
								t.setHours(temp_int);
								std::cin.clear();
								Cursor::set(48, 10 + y);
								std::cin >> temp_int;
								t.setMinutes(temp_int);
								std::cin.clear();
								Cursor::set(56, 10 + y);
								std::cin >> temp_int;
								t.setSeconds(temp_int);
								c.setTime(t);
								break;
							case 5:
								Cursor::set(40, 10 + y);
								std::cin >> temp;
								c.setTag(temp);
								break;
							case 6:
								cases.push_back(c);
								return;
						}
						std::cin.clear();
						show_addCase_menu(y, c);
						Cursor::set(0, 0);
						break;
					case 'b':
					case 'B':
						return;
				}
				Cursor::reshow(y, x);
			}
		}
		void show_changeColor_menu(int cursor_pos) {
			system("cls");
			Cursor::set(16, 8);
			std::cout << "Change Color";
			Cursor::set(18, 10 + cursor_pos);
			std::cout << Cursor::symbol << ' ';
			Cursor::set(20, 10);
			std::cout << "Backgrond";
			Cursor::set(20, 11);
			std::cout << "Foreground";
			Cursor::set(20, 13);
			std::cout << "AD - to change";
			Cursor::set(20, 14);
			std::cout << "B - to return";
			Cursor::set(0, 0);
		}
		void setColor() {
			char cmd[]{ 'c','o','l','o','r',' ',bg_color,fg_color,'\0' };
			system(cmd);
		}
		void saveColor() {
			std::ofstream data;
			data.open("color.txt", std::ios::out);
			data << bg_color << "\t" << fg_color << std::endl;
		}
		void changeColor() {
			char choice;
			
			int y = 0;
			int x = 0;
			show_changeColor_menu(y);

			do {
				x = 0;
				choice = _getch();
				switch (choice) {
					case 'w':
					case 'W':
						if (y > 0) x = -1;
						break;
					case 's':
					case 'S':
						if (y < 1) x = 1;
						break;
					case 'a':
					case 'A':
						if (y == 0) bg_color--;
						if (y == 1) fg_color--;
						break;
					case 'd':
					case 'D':
						if (y == 0) bg_color++;
						if (y == 1) fg_color++;
						break;
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

				Cursor::reshow(y, x);
			} while (choice != 'b' && choice != 'B');
		}
		void menu() {

			setColor();

			int y = 0; //current pos
			int x = 0; //change

			show_menu(0);

			char choice;
			while (true) {
				x = 0;
				choice = _getch();
				switch (choice) {
					case 'w':
					case 'W':
						if (y > 0) x = -1;
						break;
					case 's':
					case 'S':
						if (y < 6) x = 1;
						break;
					case ' ':
						switch (y) {
							case 0:
								show();
								break;
							case 1:
								addCase();
								save();
								break;
							case 2:

								break;
							case 3:

								break;
							case 4:

								break;
							case 5:
								changeColor();
								break;
							case 6:
								return;
						}
						show_menu(y);
						break;
				}
				Cursor::reshow(y, x);
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
				std::cout << "Name:\t\t\t" << c.getName() << std::endl;
				std::cout << "Description:\t\t" << c.getDesc() << std::endl;
				std::cout << "Priority:\t\t" << c.getPrior() << std::endl;
				std::cout << "Date:\t\t\t" << c.getDate() << std::endl;
				std::cout << "Time:\t\t\t" << c.getTime() << std::endl;
				std::cout << "~Tag\t\t\t" << c.getTag() << std::endl;
				std::cout << "--------------------------------------------------\n";
			}
			system("pause");
		}
};
