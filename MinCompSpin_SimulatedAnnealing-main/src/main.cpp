#include "header.h"


#include <ctime> // for chrono
#include <ratio> // for chrono
#include <chrono> // for chrono]

using namespace std::chrono;

int main(int argc, char **argv) {


	cout << "SIMULATED ANNEALING [STAND-ALONE VERSION - v20230623]\n" << endl;


	// ==== initialize RNG ====
 	random_device randDevice;
    srand(randDevice());
    // ========================


    // ==== declarations ======
    bool pload = false; // load partition
    bool rload = false;
    bool greedy = false;
    bool anneal = true;
    string fname, pname;
    // ========================


    // ==== default values ====
    unsigned int max_iterations = 500; //50000;
    unsigned int max_no_improve = 10;  //10000;
    // ========================


    // ==== parse runtime arguments ====
    unsigned int n;
    sscanf(argv[1], "%d", &n);

    for (int i = 2; i < argc; i++) {

    	string arg = argv[i];

    	// input data
    	if (arg == "-i") {
    		fname = argv[i+1];
    		i++;
    		cout << "- input file: " << fname << endl;
    	}

    	// input partition
    	if (arg == "-p") {
    		pname = argv[i+1];
    		pload = true;
    		i++;
    		cout << "- input partition: " << pname << endl;
    	}

        // start from random partition
    	if (arg == "-r") {
    		rload = true;
    	}

        // perform greedy merhing
    	if (arg == "-g") {
    		greedy = true;
    	}

        // turn annealing off (greedy only)
        if (arg == "-s") {
            anneal = false;
        }

    	// maximum iterations
    	if (arg == "--max") {
    		max_iterations = stoi(argv[i+1]);
    		i++;
    	}

    	// stopping iterations
    	if (arg == "--stop") {
    		max_no_improve = stoi(argv[i+1]);
    		i++;
    	}
    }

    // have to do something 
    if (!greedy) {anneal = true;}

    cout << "- max iterations (stop): ";
    cout << max_iterations;
    cout << " (" << max_no_improve << ")\n" << endl;
    // =================================

    // initialize partition and load data
/*   Partition p_struct(n);
    get_data(fname, p_struct);
    cout << "Number of datapoints: N = " << p_struct.N << endl;
    cout << "Nset.size = " << (p_struct.data).size() << endl << endl;
*/

    Partition_vect p_struct_vect(n);
    get_data_vect(fname, p_struct_vect);
    cout << "Number of datapoints: N = " << p_struct_vect.N << endl;
    cout << "Nset.size = " << (p_struct_vect.data).size() << endl << endl;

    if (pload) {
//    	load_partition(p_struct, pname);
    } else if (rload) {
//    	random_partition(p_struct);
    } else {
//    	independent_partition(p_struct);    
        independent_partition_vect(p_struct_vect);
    }

    if (greedy) {

        auto start = chrono::system_clock::now(); 
        auto end = chrono::system_clock::now(); 
        chrono::duration<double> elapsed = end - start; 

        start = chrono::system_clock::now();
        greedy_merging_vect(p_struct_vect);
        cout << "- current log-evidence (after GMA): " << p_struct_vect.current_log_evidence << endl;
        cout << "- best log-evidence (after GMA):    " << p_struct_vect.best_log_evidence << endl;
        end = chrono::system_clock::now();
        elapsed = end - start;
        cout << "- elapsed time      : " << elapsed.count() << "s" << endl ;
/*
        start = chrono::system_clock::now();
        greedy_merging(p_struct);
        cout << "- current log-evidence (after GMA): " << p_struct.current_log_evidence << endl;
        cout << "- best log-evidence (after GMA):    " << p_struct.best_log_evidence << endl;
        end = chrono::system_clock::now();
        elapsed = end - start;
        cout << "- elapsed time      : " << elapsed.count() << "s" << endl;
*/
    }
    cout << endl;

    // main algorithm 
    if (anneal) {
/*        simulated_annealing(p_struct, max_iterations, max_no_improve);

        cout << "- current log-evidence (after SAA): " << p_struct.current_log_evidence << endl;
        cout << "- best log-evidence (after SAA):    " << p_struct.best_log_evidence << endl;
*/    }
    


	// print and save best partition
	string cpath = "../output/comms/" + fname + "_comms.dat";
	string spath = "../output/stats/" + fname + "_stats.dat";
	ofstream comm_file(cpath);
	ofstream stat_file(spath);
	stat_file << "best log-evidence: " << p_struct_vect.best_log_evidence << endl;
    cout << "final log-evidence: " << p_struct_vect.best_log_evidence << endl;
    cout << "final community: " << endl;
	for(unsigned int i = 0; i < n; i++){
		__uint128_t community = p_struct_vect.best_partition[i];
		if (bit_count(community) > 0){
			cout << i << "\t" << int_to_bitstring(community, n) << " | size: " << bit_count(community) << endl;
			comm_file << int_to_bitstring(community, n) << endl;
		}
	}   
	comm_file.close(); 
	stat_file.close(); 

    return 0;

}