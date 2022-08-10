#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<vector<string>> *t1 = new vector<vector<string>>();
vector<string> *l1 = new vector<string>();

void transposition(vector<vector<string>> &t)
{
}
string *file = new string();

int main(int argc, char *argv[])
{
    
    ofstream readfile;
    readfile.open(argv[0], ios::in);
    char *file0 = new char[1024];
    readfile >> *file0;
    readfile.close();


    return 0;
}
