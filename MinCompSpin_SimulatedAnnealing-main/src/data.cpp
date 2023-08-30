#include "header.h"

void get_data(string fname, Partition &p_struct) {

	// https://github.com/clelidm/MinCompSpin_Greedy

	__uint128_t state;
	string fpath = "../input/data/" + fname + ".dat";
	string line, subline;
	ifstream myfile(fpath);

	while (getline(myfile, line)) {

		subline = line.substr(0, p_struct.n);
		state = string_to_int(subline, p_struct.n);
		p_struct.data[state]++;
		p_struct.N++;

	}

	myfile.close();

	cout << "- loaded: " << fpath;
	cout << " (" << p_struct.N << " samples)\n" << endl;
}

void get_data_vect(string fname, Partition_vect &p_struct) {

	// https://github.com/clelidm/MinCompSpin_Greedy
	map<__uint128_t, unsigned int> data;

	__uint128_t state;
	string fpath = "../input/data/" + fname + ".dat";
	string line, subline;
	ifstream myfile(fpath);

	while (getline(myfile, line)) {

		subline = line.substr(0, p_struct.n);
		state = string_to_int(subline, p_struct.n);
		data[state]++;
		p_struct.N++;

	}

	myfile.close();

	cout << "- loaded: " << fpath;
	cout << " (" << p_struct.N << " samples)\n" << endl;
	cout << "test test N = " << data.size() << endl;

	(p_struct.data).resize(data.size()); // reserve(n)
  	int i=0;
  	for (auto& my_pair : data)
  	{
    	p_struct.data[i]=my_pair;
    	i++;
  	}
}