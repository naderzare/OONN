
void dataset_create(int num_data, long double *** dataX, int num_x,
		long double *** dataY, int num_y) {
	dataX = new long double **[num_data];
	dataY = new long double **[num_data];
	for (int i = 0; i < 500; i++) {
		dataX[i] = new long double *[num_x];
		for (int j = 0; j < num_x; j++) {
			dataX[i][j] = new long double[1];
			dataX[i][j][0] = (long double) (rand()) / (long double) RAND_MAX;
		}
		dataY[i] = new long double *[num_y];
		for (int j = 0; j < num_y; j++) {
			dataY[i][j] = new long double[1];
			if (j == 0) {
				dataY[i][j][0] = sin(dataX[i][0][0]);
				dataY[i][j][0] /= 1.0;
			} else {
				dataY[i][j][0] = dataX[i][0][0] * dataX[i][1][0]
															  + cos(dataX[i][0][0]) * cos(dataX[i][0][0]);
				dataY[i][j][0] /= 1.0;
			}
		}
	}
}
void dataset_read(int &num_data, long double *** dataX, int num_x,
		long double *** dataY, int num_y, char * dataset_file_name) {
	ifstream input;
	cout << dataset_file_name << endl;
	input.open(dataset_file_name);
	if (num_data == 0)
		input >> num_data;
	for (int i = 0; i < num_data; i++) {
		for (int j = 0; j < num_x; j++) {
			input >> dataX[i][j][0];
		}
		for (int j = 0; j < num_y; j++) {
			input >> dataY[i][j][0];
		}
	}
	input.close();
}

void dataset_read_for_autoencoder(int &num_data, long double *** dataX, int num_x,
		long double *** dataY, int num_y, char * dataset_file_name, int num_label) {
	ifstream input;
	cout << dataset_file_name << endl;
	input.open(dataset_file_name);
	if (num_data == 0)
		input >> num_data;
	for (int i = 0; i < num_data; i++) {
		for (int j = 0; j < num_x; j++) {
			long double val = 0;
			input >> val;
			dataX[i][j][0] = val;
			dataY[i][j][0] = val;
		}
		for (int j = 0; j < num_label; j++) {
			long double val = 0;
			input >> val;
		}
	}
	input.close();
}
void dataset_read_x(int num_data, long double *** dataX, int num_x,
		char * dataset_file) {
	ifstream input;
	input.open(dataset_file);

	dataX = new long double **[num_data];
	for (int i = 0; i < num_data; i++) {
		dataX[i] = new long double *[num_x];
		for (int j = 0; j < num_x; j++) {
			dataX[i][j] = new long double[1];
			input >> dataX[i][j][0];
		}
	}
}
void dataset_read_y(int num_data, long double *** dataY, int num_y,
		char * dataset_file) {
	ifstream input;
	input.open(dataset_file);

	dataY = new long double **[num_data];
	for (int i = 0; i < num_data; i++) {
		dataY[i] = new long double *[num_y];
		for (int j = 0; j < num_y; j++) {
			dataY[i][j] = new long double[1];
			input >> dataY[i][j][0];
		}
	}
}
void normalize_dataset(long double *** data, int num_data, int num_x,
		vector<long double> & max_vec,bool push_max_vec = true) {

	if(push_max_vec)
		for (int i = 0; i < num_x; i++) {
			max_vec.push_back(abs_ld(data[0][i][0]));
			for (int d = 0; d < num_data; d++) {
				if (max_vec[i] < abs_ld(data[d][i][0])) {
					max_vec[i] = abs_ld(data[d][i][0]);
				}
			}
		}
	for (int d = 0; d < num_data; d++) {
		for (int i = 0; i < num_x; i++) {
			data[d][i][0] /= max_vec[i];
		}
	}
}
void normalize_dataset(long double *** data, int num_data, int num_x,
		long double & max) {
	for (int d = 0; d < num_data; d++) {
		for (int i = 0; i < num_x; i++) {
			data[d][i][0] /= max;
		}
	}
}

void cutting_dataset(long double *** data, int num_data, int num_x,
		long double *** learn, long double *** valid, long double *** test,
		int num_l, int num_v, int num_t) {
	int d = 0;
	for (int dd = 0; dd < num_l; dd++) {
		learn[dd] = new long double *[num_x];
		for (int i = 0; i < num_x; i++) {
			learn[dd][i] = new long double[1];
			learn[dd][i][0] = data[d][i][0];
		}
		d++;
	}
	for (int dd = 0; dd < num_v; dd++) {
		valid[dd] = new long double *[num_x];
		for (int i = 0; i < num_x; i++) {
			valid[dd][i] = new long double[1];
			valid[dd][i][0] = data[d][i][0];
		}
		d++;
	}
	for (int dd = 0; dd < num_t; dd++) {
		test[dd] = new long double *[num_x];
		for (int i = 0; i < num_x; i++) {
			test[dd][i] = new long double[1];
			test[dd][i][0] = data[d][i][0];
		}
		d++;
	}
}
void push_zeros_to_array3D(long double *** data, int m, int n, int z) {
	for (int i = 0; i < m; i++) {
		data[i] = new long double *[n];
		for (int j = 0; j < n; j++) {
			data[i][j] = new long double[z];
			for (int k = 0; k < z; k++) {
				data[i][j][k] = 0;
			}
		}
	}
}
