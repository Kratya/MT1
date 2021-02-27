#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct VarTableElem //������� � �������
{
	VarTableElem(string name, int type, bool value) :name(name), type(type), value(value) {}
	VarTableElem() : name(""), type(0), value(0) {}
	string name;
	int type;
	bool value;
};

struct IntTableElem //������� � �������
{
	IntTableElem(string name, int type, int value) :name(name), type(type), value(value) {}
	IntTableElem() : name(""), type(0), value(0) {}
	string name;
	int type;
	int value;
};

struct FloatTableElem //������� � �������
{
	FloatTableElem(string name, int type, float value) :name(name), type(type), value(value) {}
	FloatTableElem() : name(""), type(0), value(0) {}
	string name;
	int type;
	float value;
};


struct place //���������� � �������
{
	int i;
	int j;
	place(int i, int j) :i(i), j(j) {}
	place() :i(), j() {}
};
struct token //���������� � ������� ���� �������
{
	int table;
	int i;
	int j;
	token(int table, int i, int j) :table(table), i(i), j(j) {}
};

class ConstTable
{
public:
	vector<string> array;
	ConstTable(string fileName)
	{
		readTable(fileName);
	};
	~ConstTable()
	{
		array.~vector();
	}

	int findElem(string Name) //����� ��������
	{
		auto res = find(array.begin(), array.end(), Name);
		if (res == array.end())
			return -1;
		else
			return res - array.begin();//������� ������� ��������
	}
	string getElem(int index)//������ ������� �� �������
	{
		return array[index];
	}


private:
	void readTable(string fileName)
	{
		string tmp;
		fstream in(fileName);
		while (!(in.eof()))
		{
			in >> tmp;
			array.push_back(tmp);
		}
		in.close();
	}
};

class TableVar 
{
public:
	vector<vector<VarTableElem>> array;

	TableVar()
	{
		array.resize(52);
	};
	~TableVar()
	{
		array.~vector();
	}

	place findElem(string name)
	{
		place pl;
		auto hash = getHash(name);
		pl.i = hash;
		if (array[hash].size())
		{
			auto res = find_if(array[hash].begin(), array[hash].end(), [&](const VarTableElem& s)-> bool {return s.name == name; });
			if (res == array[hash].end())
			{
				array[hash].push_back(VarTableElem(name, 0, 0));//���� �� ����� �������, �� ��������� ��� � �������
				pl.j = array[hash].size() - 1;
			}

			else pl.j = res - array[hash].begin(); //���� ����� �������, �� ���������� ������ j
		}

		else 
		{
			array[hash].push_back(VarTableElem(name, 0, 0)); //���� ������� ������ � ������, �� ����� �� ���� � ������ �������� �������
			pl.j = 0;
		}
		return pl; //���������� ���������� ��������
	}
	void changeElem(place pl, bool value) 
	{
		array[pl.i][pl.j].value = value;
	}
	VarTableElem getElem(place pl) //�� ����������� ������� �������
	{
		return array[pl.i][pl.j];
	}

private:
	int getHash(string h) 
	{
		char len = 0;
		if (h[0] >= 'A' && h[0] <= 'Z')
			len = h[0] - 'A';
		if (h[0] >= 'a' && h[0] <= 'z')
			len = h[0] - 'a' + 26;
		return (int)len;
	}
};

class TableInt //������� ����� ��������
{
public:
	vector<vector<IntTableElem>> array;

	TableInt()
	{
		array.resize(19);
	};
	~TableInt() 
	{
		array.~vector();
	}

	place findElem(string value)
	{
		int tmp = stoi(value);//����������� ������� - ��������� �������� � int
		place pl;
		auto hash = getHash(value);
		pl.i = hash;
		if (array[hash].size())//���� �� �������� i ������ �� ������ � �������, �� ��������� �����
		{
			auto res = find(array[hash].begin(), array[hash].end(), [&](const IntTableElem& s)-> bool {return s.value == tmp; });
			if (res == array[hash].end())
			{
				array[hash].push_back(IntTableElem("INT", 1,tmp));
				pl.j = array[hash].size() - 1;
			}

			else pl.j = res - array[hash].begin();
		}

		else 
		{
			array[hash].push_back(IntTableElem("INT", 1, tmp));
			pl.j = 0;
		}
		return pl;
	}
	void changeElem(place pl, int value) 
	{
		array[pl.i][pl.j].value = value;
	}
	IntTableElem getElem(place pl)
	{
		return array[pl.i][pl.j];
	}

private:
	int getHash(string h) 
	{
		int len = 0;
		if (h[0] == '-')
			len = (int)h[1] - '0' + 9;
		else len = (int)h[0] - '0';
		return len;
	}
};

class TableFloat //������� ����� ��������
{
public:
	vector<vector<FloatTableElem>> array;

	TableFloat()
	{
		array.resize(19);
	};
	~TableFloat()
	{
		array.~vector();
	}

	place findElem(string value)
	{
		float tmp = stof(value);//����������� ������� - ��������� �������� � float
		place pl;
		auto hash = getHash(value);
		pl.i = hash;
		if (array[hash].size())//���� �� �������� i ������ �� ������ � �������, �� ��������� �����
		{
			auto res = find(array[hash].begin(), array[hash].end(), [&](const FloatTableElem& s)-> bool {return s.value == tmp; });
			if (res == array[hash].end())
			{
				array[hash].push_back(FloatTableElem("FLOAT", 2, tmp));
				pl.j = array[hash].size() - 1;
			}

			else pl.j = res - array[hash].begin();
		}

		else
		{
			array[hash].push_back(FloatTableElem("FLOAT", 2, tmp));
			pl.j = 0;
		}
		return pl;
	}
	void changeElem(place pl, float value)
	{
		array[pl.i][pl.j].value = value;
	}
	FloatTableElem getElem(place pl)
	{
		return array[pl.i][pl.j];
	}

private:
	int getHash(string h)
	{
		int len = 0;
		if (h[0] == '-')
			len = (int)h[1] - '0' + 9;
		else len = (int)h[0] - '0';
		return len;
	}
};

class Lexeme
{
public:
	ConstTable* keyWords = new ConstTable("KeyWords.txt");
	ConstTable* operations = new ConstTable("Operation.txt");
	ConstTable* delimiters = new ConstTable("Delimiter.txt");
	TableInt* tableInt = new TableInt(); //������� ��������
	TableVar* tableVar = new TableVar(); //������� ����������
	TableFloat* tableFloat = new TableFloat();
	Lexeme()
	{}


	string str;
	int valueInt;
	float valueFloat;
	VarTableElem var;

	void getElemByToken(token tmp) 
	{
		switch (tmp.table)
		{
		case 0: str = keyWords->getElem(tmp.i); break;
		case 1: str = operations->getElem(tmp.i); break;
		case 2: str = delimiters->getElem(tmp.i); break;
		case 3: valueInt = tableInt->getElem(place(tmp.i, tmp.j)).value; break;
		case 4: var = tableVar->getElem(place(tmp.i, tmp.j)); break;
		case 5: valueFloat = tableFloat->getElem(place(tmp.i, tmp.j)).value; break;
		}
	}

};

int main()
{
	auto lexeme = new Lexeme();
	int index;


	
	for (unsigned int i = 0; i < lexeme->keyWords->array.size(); i++)
		cout << lexeme->keyWords->array[i]<<endl;
	index = lexeme->keyWords->findElem("break");
	cout << "place=" << index<<endl<<endl;

	for (unsigned int i = 0; i < lexeme->delimiters->array.size(); i++)
		cout << lexeme->delimiters->array[i] << endl;
	index = lexeme->delimiters->findElem(";");
	cout << "place=" << index << endl << endl;

	for (unsigned int i = 0; i < lexeme->operations->array.size(); i++)
		cout << lexeme->operations->array[i] << endl;
	index = lexeme->operations->findElem("*=");
	cout << "place=" << index << endl << endl;
	
	

	/*
	cout << "-----------------------------------------" << endl;
	place pl;
	pl = lexeme->tableInt->findElem("5");
	pl =lexeme->tableInt->findElem("54");
	pl =lexeme->tableInt->findElem("10");
	pl =lexeme->tableInt->findElem("19");
	
	cout << "place=" << pl.i<<" "<<pl.j << endl << endl;
	for (int i = 0; i < lexeme->tableInt->array.size(); i++) 
	{
		cout << i << ": ";
		for (int j = 0; j < lexeme->tableInt->array[i].size(); j++)
			cout << j << ":" << "(" << lexeme->tableInt->array[i][j].value << ") ";
		cout << endl;
	}	
	*/
	//cout << "-----------------------------------------" << endl;

	/*
	place pl;
	pl = lexeme->tableVar->findElem("a");
	pl = lexeme->tableVar->findElem("b");
	pl = lexeme->tableVar->findElem("zsh");
	pl = lexeme->tableVar->findElem("zs");
	pl = lexeme->tableVar->findElem("zsoooo");
	pl = lexeme->tableVar->findElem("cs_go");
	pl = lexeme->tableVar->findElem("sdssdsds");
	pl = lexeme->tableVar->findElem("zs");
	

	cout << "place=" << pl.i << " " << pl.j << endl << endl;

	for (int i = 0; i < lexeme->tableVar->array.size(); i++) 
	{
		cout << i << ": ";
		for (int j = 0; j < lexeme->tableVar->array[i].size(); j++) 
	{
			cout << j << ":" << "(" << lexeme->tableVar->array[i][j].name << " " << lexeme->tableVar->array[i][j].value << ") ";
		}
		cout << endl;
	}

*/
	//cout << "-----------------------------------------" << endl;
	/*
	token a = token(0, 1, 1);
	lexeme->getElemByToken(a);
	cout << "name=" << lexeme->str << "  is_value=" << lexeme->var.value << endl;
	*/
	system("pause");
	return 0;
}
