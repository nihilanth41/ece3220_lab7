#include <iostream>
#include <cstring>
#include <stdio.h>

class Signal { 
	private:
		int len;
		int max_val;
		double avg_val;
		double *data;
		double populate(const char *);
	public:
		// Constructors
		Signal();
		Signal(int fileno);
		Signal(const char *filename);
		// Destructor
		~Signal();
};

double Signal::populate(const char *filename) {
	/* Reads data from file into data array */


}



int main(void) {
	/* Handle command line args */
	// If no switches prompt user for input
	

	return 0;
}

Signal::Signal() {
/* Takes default file and allocates memory accordingly */
	const char *filename = "Raw_data_01.txt";


}

Signal::Signal(int fileno) {
	char filename[32];
	sprintf(filename, "Raw_data_%02d.txt", fileno);
	// Open file
	// Read data
	// Close file
}

Signal::Signal(const char *filename) {

	// Open file
	// Read data
	// Close file
}

Signal::~Signal() {
	// free <=> delete
}
