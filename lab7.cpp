#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

class Signal { 
	private:
		int len;
		int max_val;
		double avg_val;
		double *data;
		void populate(const char *);
	public:
		// Constructors
		Signal();
		Signal(int fileno);
		Signal(const char *filename);
		// Destructor
		~Signal();
};

void Signal::populate(const char *filename) {
	/* Reads data from file into data array */
	/* Populates len, max, and avg fields */
	FILE *fp_r = fopen(filename, "r");
	if(fp_r != NULL)
	{
		fscanf(fp_r, "%d %d", &len, &max_val);
		// allocate memory for signal
		data = new double[len];
		int i=0;
		avg_val = 0;
		for(i=0; i<len; i++)
		{
			// Load data into array 
			fscanf(fp_r, "%lf", data+i);
			// Find average at the same time
			avg_val += *(data+i);
		}
		avg_val /= len;
		fclose(fp_r);
	}
	else
	{
		// Failed to open file
		cout << "Failed to open file " 
		<< filename << endl;
	}
}


int main(void) {
	/* Handle command line args */
	// If no switches prompt user for input
	Signal sig1 = Signal();
	

	return 0;
}

Signal::Signal() {
/* Takes default file and allocates memory accordingly */
	const char *filename = "Raw_data_01.txt";
	populate(filename);
}

Signal::Signal(int fileno) {
	char filename[32];
	sprintf(filename, "Raw_data_%02d.txt", fileno);
	populate(filename);
}

Signal::Signal(const char *filename) {
	populate(filename);
}

Signal::~Signal() {
	// Free memory allocated at runtime
	delete[] data;
}
