#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
#include <sys/stat.h>
// 名前空間
using namespace std;

bool GetContents(const string& filename, vector<vector<string> >& table, const char delimiter = ',');
int check_file_status(string last_time_stamp);
