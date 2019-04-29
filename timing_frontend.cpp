#include "tDES/tDES.cpp"
#include "AES/AES.cpp"
#include "OFB/OFB.cpp"
#include "CBC/CBC.cpp"
#include "generic_utils.cpp"
#include "format/bitset_hex.cpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include <chrono>
#include <vector>
#define INFILE "test.txt"
#define OUTFILE "CBC_3DES_timerecord.txt"
#define BSIZE 64
#define KSIZE 192
#define ALGOCALL_E tDES_E
#define ALGOCALL_D tDES_D
#define MODECALL_E CBC_E<KSIZE, BSIZE, ALGOCALL_E>
#define MODECALL_D CBC_D<KSIZE, BSIZE, ALGOCALL_D>

using namespace std;

struct timing_return {
	chrono::microseconds etime;
	chrono::microseconds dtime;
};

timing_return timing_sub () {	
	ifstream readin (INFILE);
	vector<bitset<BSIZE>> ptext;
	if (!readin) {
		cout << "\nCould not open file \"" << INFILE << "\".";
	} else {
		while (!readin.eof()) {
			char buf[4];
			for (int n = 0; n < 4; n++) {
				if (!readin.eof()) {
					readin >> buf[n];
				} else {
					buf[n] = '.';//pad with periods if necessary
				}
			}
			ptext.push_back(cstring_to_bitset<BSIZE>(buf));
		}
	}
	bitset<KSIZE> key = hex_to_bitset<KSIZE>("be3849375f9e9a8ca8e8d8130098ce8a5342ef289a210be3");
	chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
	MODECALL_E (ptext, key);
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	MODECALL_D (ptext, key);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	timing_return ret;
	ret.etime = chrono::duration_cast<chrono::microseconds> (t1 - t0);
	ret.dtime = chrono::duration_cast<chrono::microseconds> (t2 - t1);
	readin.close();
	return ret;
}


int main () {
	ofstream time_record (OUTFILE);
	cout << "Iteration: xxxx";
	for (int n = 0; n < 8192; n++) {
		timing_return data = timing_sub();
		time_record << data.etime.count() << ',' << data.dtime.count() << '\n';
		if (!(n%128)) {
			cout <<  "\b\b\b\b" << setw(4) << n;
		}
	}
	time_record.close();
	cout << "\a\a\a\a";
}
	