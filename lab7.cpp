#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Signal { 
	private:
		int len;
		int max_val;
		double avg_val;
		double *data;
		int isAlloc;
		
		void populate(const char *);
		void average(void);

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
	FILE *fp_r = fopen(filename, "r");
	if(fp_r == NULL)
	{
		cout << "Error opening file" << endl;
		isAlloc = 0;
	}
	else
	{
		fscanf(fp_r, "%d %d", &len, &max_val);
		// allocate memory for signal
		data = new double[len];
		isAlloc = 1;
		int i=0;
		for(i=0; i<len; i++)
		{
			// Load data into array 
			fscanf(fp_r, "%lf", data+i);
		}
		fclose(fp_r);
	}
}

void Signal::average(void) {
	int i=0;
	avg_val = 0;
	for(i=0; i<len; i++)
	{
		avg_val += *(data+i);
	}
	avg_val /= len;
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
	average();
}

Signal::Signal(int fileno) {
	char filename[32];
	sprintf(filename, "Raw_data_%02d.txt", fileno);
	populate(filename);
	average();
}

Signal::Signal(const char *filename) {
	populate(filename);
	average();
}

Signal::~Signal() {
	// Free memory allocated at runtime
	if(isAlloc)
	{
		delete[] data;
	}
}
