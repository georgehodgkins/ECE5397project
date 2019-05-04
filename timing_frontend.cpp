//#include "tDES/tDES.cpp"
#include "AES/AES.cpp"
//#include "OFB/OFB.cpp"
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
#define INFILE_1 "test1.txt"
#define INFILE_2 "test2.txt"
#define OUTFILE "CBC_AES192_timerecord.txt"
#define BSIZE 128
#define KSIZE 256
#define ALGOCALL_E AES_E<KSIZE>
#define ALGOCALL_D AES_D<KSIZE>
#define MODECALL_E CBC_E<KSIZE, BSIZE, ALGOCALL_E>
#define MODECALL_D CBC_D<KSIZE, BSIZE, ALGOCALL_D>

using namespace std;

struct timing_return {
	chrono::microseconds etime;
	chrono::microseconds dtime;
};

timing_return timing_sub (string rdf) {	
	ifstream readin (rdf);
	vector<bitset<BSIZE>> ptext;
	if (!readin) {
		cout << "\nCould not open file \"" << rdf << "\".";
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
	timing_return ret;
	bitset<KSIZE> key = hex_to_bitset<KSIZE>("3be3849375f1e9a2ca8ed813b098ce8a3e4910d20c18b1a67481930294859362");
	chrono::high_resolution_clock::time_point t0 = chrono::high_resolution_clock::now();
	MODECALL_E (ptext, key);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	MODECALL_D (ptext, key);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	ret.etime = chrono::duration_cast<chrono::microseconds> (t1 - t0);
	ret.dtime = chrono::duration_cast<chrono::microseconds> (t2 - t1);
	readin.close();
	return ret;
}


int main () {
	ofstream time_record (OUTFILE);
	cout << "Iteration: xxxx";
	timing_return data;
	int poops = 0;
	for (int n = 0; n < 8192; n++) {
		if (n % 2) {
			data = timing_sub(INFILE_1);
		} else {
			data = timing_sub(INFILE_2);
		}
		if (data.etime.count() == 0 || data.dtime.count() == 0) {
			n--;//discard bad runs
			poops++;
		} else {
			time_record << data.etime.count() << ',' << data.dtime.count() << '\n';
		}
		if (!(n%128)) {
			cout <<  "\b\b\b\b" << setw(4) << n;
		}
	}
	time_record.close();
	cout << "\a\n" << "Done. " << poops << " runs discarded.";
}
	