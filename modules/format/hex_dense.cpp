#include <string>
#include <ios>
#include <sstream>
using namespace std;

string pack_string (string X) {
	stringstream Y;
	stringstream Xs (X);
	Xs.setf(ios::hex);
	Xs.setw(2);