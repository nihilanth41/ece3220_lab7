#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <limits.h>

using namespace std;

class Signal { 
	private:
		int len;
		double max_val;
		double avg_val;
		double *data;
		int isAlloc;
		void populate(const char *);
		void getAverage(void);
		void getMax(void);
	public:
		// Class methods
		void offset(double);
		void scale(double);
		void center(void);
		void normalize(void);
		void statistics(void);
		// Additional
		void Sig_info(void);
		void Save_file(const char *filename);
		// Constructors
		Signal();
		Signal(int fileno);
		Signal(const char *filename);
		// Destructor
		~Signal();
};

void Signal::Save_file(const char *filename) {
	FILE *fp_w = fopen(filename, "w");
	if(fp_w != NULL)
	{	
		fprintf(fp_w, "%d %0.4lf\n", len, max_val);
		for(int i=0; i<len; i++)
		{
			fprintf(fp_w, "%0.4lf\n", *(data+i));
		}
		fclose(fp_w);
	}
}
	
void Signal::offset(double offset_val) {
	int i=0;
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) += offset_val;
	}
	// Update data members
	getAverage();
	getMax();

}

void Signal::scale(double scale_val) {
	int i=0;
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) *= scale_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::center(void) {
	int i=0;
	// Ensure average is accurate
	getAverage();
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) -= avg_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::normalize(void) {
	int i=0;
	// Ensure max_val is accurate
	getMax();
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) /= max_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::statistics(void) {
	//getAverage();
	//getMax();
}

int main(void) {
	/* Handle command line args */
	// If no switches prompt user for input
	Signal sig1 = Signal();
	sig1.Sig_info();

//	menu (offset, scale, center, normalize, statistic)
//		(print signal, save signal, exit)

	return 0;
}

void Signal::Sig_info(void) {
/* Display length, current maximum, current average */
	cout << "Signal length: " << len << endl;
	cout << "Maximum val:" << max_val << endl;
	cout << "Average val:" << avg_val << endl;
}

/* Private */

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
		fscanf(fp_r, "%d %lf", &len, &max_val);
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

void Signal::getAverage(void) {
	int i=0;
	avg_val = 0;
	for(i=0; i<len; i++)
	{
		avg_val += *(data+i);
	}
	avg_val /= len;
}

void Signal::getMax(void) {
	max_val = (double)INT_MIN;
	int i=0;
	for(i=0; i<len; i++)
	{
		if( *(data+i) > max_val )
		{
			max_val = *(data+i);
		}
	}
}	

Signal::Signal() {
/* Takes default file and allocates memory accordingly */
	const char *filename = "Raw_data_01.txt";
	populate(filename);
	getAverage();
	getMax();
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
	if(isAlloc)
	{
		delete[] data;
	}
}
