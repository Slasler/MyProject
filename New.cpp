#include <iostream>
#include <fstream>
using namespace std;

long long input[1'000'000];
int pos = 0;

void read_file() {
	cout << "Введите путь файла: ";
	string path; cin >> path;
	ifstream in(path);
	int number;
	while (in >> number) {
		input[pos++] = number;
	}
	in.close();
}

void solve() {
	int triangle_numbers[1001];
	triangle_numbers[0] = 0;
	for (int i = 1; i <= 1000; i++) {
		triangle_numbers[i] = i * (i + 1) / 2;
	}

	int l = -1;
	int r = 1001;
	while (l < r - 1) {
		int m = (l + r) / 2;
		if (triangle_numbers[m] < pos) {
			l = m;
		}
		else {
			r = m;
		}
	}
	int triangle_size = r;
	long long** pascal_triangle = new long long* [triangle_size];
	long long** triangle = new long long* [triangle_size];
	for (int i = 0; i < triangle_size; i++) {
		pascal_triangle[i] = new long long[triangle_size];
		triangle[i] = new long long[triangle_size];
	}
	for (int i = 0; i < triangle_size; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i) {
				pascal_triangle[i][j] = 1;
			}
			else {
				pascal_triangle[i][j] = pascal_triangle[i - 1][j - 1] + pascal_triangle[i - 1][j];
			}
			cout << pascal_triangle[i][j] << ' ';
		}
		cout << '\n';
	}
	int c = 0;
	if (triangle_numbers[triangle_size] == pos) {
		cout << "Считанный из файла треугольник Паскаля: \n";
		for (int i = 0; i < triangle_size; i++) {
			for (int j = 0; j <= i; j++) {
				triangle[i][j] = input[c++];
				cout << triangle[i][j] << ' ';
			}
			cout << '\n';
		}
		bool ok = false;
		for (int i = 0; i < triangle_size; i++) {
			for (int j = 0; j <= i; j++) {
				if (triangle[i][j] != pascal_triangle[i][j]) {
					if (!ok) {
						cout << "Ошибка в " << i + 1 << "-й строке: ";
						for (int g = 0; g <= i; g++) {
							cout << triangle[i][g] << ' ';
						}
						cout << '\n';
						ok = true;
					}
					triangle[i][j] = pascal_triangle[i][j];
				}
			}
		}
		ofstream out("output.txt");
		cout << "Полученный треугольник Паскаля: \n";
		for (int i = 0; i < triangle_size; i++) {
			for (int j = 0; j <= i; j++) {
				cout << triangle[i][j] << ' ';
				out << triangle[i][j] << ' ';
			}
			cout << '\n';
			out << '\n';
		}
		out.close();
	}
	else cout << "Размер последовательности не является треугольным числом\n";
}

int main() {
	setlocale(LC_ALL, "RUS");
	read_file();
	solve();
}
