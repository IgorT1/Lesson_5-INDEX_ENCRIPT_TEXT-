#include <iostream>
#include <string>
#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <regex>

using namespace std;
string ABC = "��������������������������������";//��� �������� ������������� �������� ������ ��� ���� �� �������� ������������ 

string Text() {//������� ��� ������ � ������ 
	//string str1 = " ���� � ����� ����� ������ ,����� � ����� ������ �������  ";//����������� ����� 
	string path = "..\\file2.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "������ ������ ����� " << endl;
	}
	else
	{
		cout << "���� ������" << endl;
		//char ch;
		//fin.get(ch) ������� ������ �� ��������� 

		string str;
		while (!fin.eof()) // ���������� ����� ����� 
		{
			str = ""; //��� ����������� ������	
			getline(fin, str);
			res += str;
		}
	}



	fin.close();

	return res;
}


string filterWithoutSpace(string& text, string& ABC) { //����� ���������� ������ ��� �������� 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);//��������� � ������ ������� 

		if (v == '�')v = '�';//������ ����

		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filterText += v;//��������� ������ � ������ 
		}
		else if (isspace(v)) {
			continue; //���������� ������� 
		}
	}

	return filterText;
}

// ������� ��������� ���� �������
int keycode(char s) {
	for (int i = 0; i < ABC.length(); i++) {
		if (s == ABC[i]) return i;
	}
	return 0;
}

string Encode(string text, string key) {
	string code;
	char keyChar;
	for (int i = 0; i < text.length(); i++) {
		keyChar = keycode(key[i % key.length()]); //��� ���������� �������� ����� �� ����� ������ 
		code += ABC[(keycode(text[i]) + keyChar) % ABC.length()];
	}
	return code;
}
double indexOfCoincidence(string& text) {
	unordered_map<char, int> freqs; // unordered_map ��� �������� ������ ������ �����
	long long int total = 0; // ����� ���������� ���� � ������
	long double ic = 0.0; // ������ ����������

	// ������� ������ ������ �����
	for (char c : text) {
		if (c >= '�' && c <= '�') {
			freqs[c]++; // ����������� ������� ������� �� 1
			total++; // ����������� ������� �������� �� 1
		}
	}

	// ������ ������� ����������
	for (auto& pair : freqs) {
		ic += pair.second * (pair.second - 1);
	}
	long long int f = (total * (total - 1));
	ic /= f;

	return ic;
}

void Log() {
	string text = Text();
	string enText;
	vector<string> key = { "��","���","����","�����" ,"������" ,"����������" ,"���������������" ,"��������������������" };;//����� ������ ����� 
	/*cout << "������� ���� ��� ���������� :\t" ;
	cin >> key;*/

	string withoutSpace = filterWithoutSpace(text, ABC); //��� ���
	//string withSpace = filterSpace(text, ABC);//  � ���������
	double decText = indexOfCoincidence(withoutSpace);
	cout << "������ ���������� ��� ������\t" << decText << endl;
	//cout << withoutSpace << endl;
	int size = key.size();
	for (int i = 0; i < size; i++)//���� ��� �������� ������� � ������ ������ ����� ��������� 
	{
		enText = Encode(withoutSpace, key[i]);//�������� � ����� �������������� ����� � �������� � ������ ������ 
		//cout << enText << endl;
		double ic = indexOfCoincidence(enText);//��������� ������ ����������� 
		cout << "������ ���������� ��� ����� :\t" + key[i] + "\n����� :\t" << ic << endl;
	}

}



int main() {
	setlocale(LC_ALL, "RU");
	Log();
	return 0;
}