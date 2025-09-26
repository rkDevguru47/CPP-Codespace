#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cout << "Hello world" << endl;
  fstream in_file("../responses.txt");
  if (!in_file) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  string res, name;
  int tot_stu{0};
  int score{0};
  int name_len{0};
  int res_len{0};
  vector<pair<string, string>> students;

  // Read file in pairs: response then name
  while (getline(in_file, res) && getline(in_file, name)) {
    // Trim whitespace from both strings
    res.erase(res.find_last_not_of(" \n\r\t") + 1);
    name.erase(name.find_last_not_of(" \n\r\t") + 1);
    students.emplace_back(name, res);
    if (name.length() > name_len) name_len = name.length();
    if (res.length() > res_len) res_len = res.length();
  }

  // Print header
  cout << setw(name_len + 2) << left << "Name" << setw(res_len + 2) << "Score" << endl;
  cout << setfill('-') << setw(name_len + res_len + 4) << "" << endl;
  cout << setfill(' ');  // Reset fill

  // Process and print scores
  double total_score = 0.0;
  for (const auto& [name, res] : students) {
    ++tot_stu;
    try {
      char m = 'A';
      score = 0;
      for (char c : res) {
        if (c == m) {
          score++;
        }
        m++;
      }
      cout << setw(name_len + 2) << name;
      cout << setw(res_len + 2) << score << endl;
    } catch (exception& e) {
      cerr << "error" << endl;
    }
    total_score += score;
  }
  cout << setfill('-') << setw(name_len + res_len + 4) << "" << endl;
  cout << setfill(' ');  // Reset fill
  cout << setw(name_len + 2) << "Average : " << setw(res_len + 2) << (total_score / tot_stu) << endl;
  in_file.close();
  return 0;
}