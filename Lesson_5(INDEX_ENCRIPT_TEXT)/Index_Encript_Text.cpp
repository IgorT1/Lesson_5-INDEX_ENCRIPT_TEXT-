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
string ABC = "абвгдежзийклмнопрстуфхцчшщъыьэюя";//для удобного использования алфавита ставим его выше по иерархии инкапсуляции 

string Text() {//функция для работы с файлом 
	//string str1 = " Карл у Клары Украл корали ,Карла у Карлы украла кларнет  ";//проверочный текст 
	string path = "..\\file2.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "Ошибка вывода файла " << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		//char ch;
		//fin.get(ch) выводит данные по символьно 

		string str;
		while (!fin.eof()) // отлвливает конец вайла 
		{
			str = ""; //для корректного счетия	
			getline(fin, str);
			res += str;
		}
	}



	fin.close();

	return res;
}


string filterWithoutSpace(string& text, string& ABC) { //метод фильтрации текста без пробелов 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);//переводит в нижний регистр 

		if (v == 'ё')v = 'е';//замена букв

		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filterText += v;//добавляет символ к тексту 
		}
		else if (isspace(v)) {
			continue; //пропускаем пробелы 
		}
	}

	return filterText;
}

// функция получения кода символа
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
		keyChar = keycode(key[i % key.length()]); //для цикличного перебора ключа по длине текста 
		code += ABC[(keycode(text[i]) + keyChar) % ABC.length()];
	}
	return code;
}
double indexOfCoincidence(string& text) {
	unordered_map<char, int> freqs; // unordered_map для хранения частот каждой буквы
	long long int total = 0; // общее количество букв в тексте
	long double ic = 0.0; // индекс совпадений

	// подсчет частот каждой буквы
	for (char c : text) {
		if (c >= 'а' && c <= 'я') {
			freqs[c]++; // увеличиваем частоту символа на 1
			total++; // увеличиваем счетчик символов на 1
		}
	}

	// расчет индекса совпадений
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
	vector<string> key = { "яд","кот","ключ","лимон" ,"абсент" ,"сладкийсок" ,"абстрагирование" ,"антикоммунистический" };;//ключи разной длины 
	/*cout << "Введите ключ для шифрования :\t" ;
	cin >> key;*/

	string withoutSpace = filterWithoutSpace(text, ABC); //без них
	//string withSpace = filterSpace(text, ABC);//  с пробелами
	double decText = indexOfCoincidence(withoutSpace);
	cout << "Индекс совпадений для текста\t" << decText << endl;
	//cout << withoutSpace << endl;
	int size = key.size();
	for (int i = 0; i < size; i++)//цикл для перебора текстов с разной длиной ключа шифроания 
	{
		enText = Encode(withoutSpace, key[i]);//передает в метод отфильтрованый текст и элеменит с масива ключей 
		//cout << enText << endl;
		double ic = indexOfCoincidence(enText);//вычисляет индекс соответсвия 
		cout << "Индекс совпадений для ключа :\t" + key[i] + "\nравен :\t" << ic << endl;
	}

}



int main() {
	setlocale(LC_ALL, "RU");
	Log();
	return 0;
}