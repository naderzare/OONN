using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
long double abs_ld(long double num){
	if(num>0)
		return num;
	return -num;
}
void shuffle_dataset(long double *** data_x, long double *** data_y, int num_data, int num_x,
		int num_y) {
	std::vector<int> shuffle_i;
	for (int i = 0; i < num_data; i++)
		shuffle_i.push_back(i);
	std::random_shuffle(shuffle_i.begin(), shuffle_i.end());
	long double temp_x[num_x];
	long double temp_y[num_y];
	for (int d = 0; d < num_data; d++) {
		int to = shuffle_i[d];
		for (int i = 0; i < num_x; i++) {
			temp_x[i] = data_x[d][i][0];
		}
		for (int i = 0; i < num_y; i++) {
			temp_y[i] = data_y[d][i][0];
		}
		for (int i = 0; i < num_x; i++) {
			data_x[d][i][0] = data_x[to][i][0];
		}
		for (int i = 0; i < num_y; i++) {
			data_y[d][i][0] = data_y[to][i][0];
		}
		for (int i = 0; i < num_x; i++) {
			data_x[to][i][0] = temp_x[i];
		}
		for (int i = 0; i < num_y; i++) {
			data_y[to][i][0] = temp_y[i];
		}
	}
}
void zarb(long double ** a, long double ** b, long double ** c, int m, int n,
		int o) {
	for (int i = 0; i < m; i++) {

		for (int k = 0; k < o; k++) {
			long double sum = 0;
			for (int j = 0; j < n; j++) {
				sum += a[i][j] * b[j][k];

				if (isnanl(sum)) {
					//					int rr;cin>>rr;
					cout
					<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55"
					<< endl;
					cout << a[i][j] << " " << b[j][k] << " " << i << " " << j
							<< " " << k << endl;
					exit(0);
				}
			}
			c[i][k] = sum;
		}
	}
}

void zarbtak(long double ** a, long double z, long double ** b, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j] * z;
		}
	}
}
void zarbdot(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] * b[i][j];
		}
	}
}
void taghsim(long double ** a, long double ** b, long double ** c, int m, int n,
		int o) {
	for (int k = 0; k < o; k++) {
		long double sum = 0;
		for (int j = 0; j < n; j++) {
			if (b[j][k] == 0)
				return;
		}
	}
	for (int i = 0; i < m; i++) {

		for (int k = 0; k < o; k++) {
			long double sum = 0;
			for (int j = 0; j < n; j++) {
				sum += a[i][j] / b[j][k];

				if (isnanl(sum)) {
					cout
					<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"
					<< endl;
					cout << a[i][j] << " " << b[j][k] << " " << i << " " << j
							<< " " << k << endl;
				}
			}
			c[i][k] = sum;
		}
	}
}

void taghsimtak(long double ** a, long double z, long double ** b, int m,
		int n) {
	if (z == 0)
		return;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j] / z;
		}
	}
}
void taghsimdot(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (b[i][j] == 0)
				return;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] / b[i][j];
		}
	}
}

void jam_dot(long double ** a, long double b, long double ** c, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] + b;
		}
	}
}
void jam(long double ** a, long double ** b, long double ** c, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}
void menha_dot(long double ** a, long double b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] - b;
		}
	}
}
void menha(long double ** a, long double ** b, long double ** c, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}
void to_max(long double ** a, long double max, long double ** b, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] > max)
				b[i][j] = max;
			else
				b[i][j] = a[i][j];
		}
	}
}

void to_min(long double ** a, long double min, long double ** b, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] < min)
				b[i][j] = min;
			else
				b[i][j] = a[i][j];
		}
	}
}
void sigmuid(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			c[i][j] = 2.0 / (1.0 + exp(-2.0 * a[i][j])) - 1.0;
		}
}
void sigmuid_p(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			if (a[i][j] < -200)
				a[i][j] = -200;
			long double ee = exp(-2.0 * a[i][j]);

			c[i][j] = 4.0 * ee / pow(1 + ee, 2.0);
			//			cout<<"ee:"<<ee<<"c i j "<<c[i][j]<<endl;
		}
}
void sinus(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			c[i][j] = sin(a[i][j]);
		}
}
void sinus_p(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			c[i][j] = cos(a[i][j]);
		}
}
void cosinus(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			c[i][j] = cos(a[i][j]);
		}
}
void cosinus_p(long double ** a, long double **c, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			c[i][j] = -sin(a[i][j]);
		}
}
long double sum(long double ** a, int m, int n) {

	long double sum = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			sum += a[i][j];
		}
	return sum;
}

void tar(long double ** a, int m, int n, long double **b) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			b[j][i] = a[i][j];
		}
	}
}

long double sumABS(long double ** a, int m, int n) {

	long double sum = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			long double tmp = a[i][j];
			if (tmp < 0)
				tmp *= (-1.0);
			sum += tmp;
		}
	return sum;
}
void set_max(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = max(a[i][j], b[i][j]);
		}
	}
}
void set_min(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = min(a[i][j], b[i][j]);
		}
	}
}
void are_max(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = (a[i][j] > b[i][j] ? 1.0 : 0.0);
		}
	}
}
void are_min(long double ** a, long double ** b, long double ** c, int m,
		int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = (a[i][j] < b[i][j] ? 1.0 : 0.0);
		}
	}
}
void set_matrix_zeros(long double ** a, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = 0;
		}
	}
}
void copy_matrix(long double ** a, int m, int n, long double ** b) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void print(long double ** a, int m, int n) {
	cout << "---------------------" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << ",\t";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
}

class matrix2D {
public:
	int m;
	int n;
	long double ** matrix;
	matrix2D() {
		m = 1;
		n = 1;
		matrix = new long double *[m];
		for (int i = 0; i < m; i++) {
			matrix[i] = new long double[n];
			for (int j = 0; j < n; j++) {
				matrix[i][j] = 0;
			}
		}
	}
	matrix2D(int num_of_row, int num_of_col, long double default_val = 0) {
		m = num_of_row;
		n = num_of_col;
		matrix = new long double *[m];
		for (int i = 0; i < m; i++) {
			matrix[i] = new long double[n];
			for (int j = 0; j < n; j++) {
				matrix[i][j] = default_val;
			}
		}
	}
	matrix2D(int num_of_row, int num_of_col, long double ** first_array) {
		m = num_of_row;
		n = num_of_col;
		matrix = new long double *[m];
		for (int i = 0; i < m; i++) {
			matrix[i] = new long double[n];
			for (int j = 0; j < n; j++) {
				matrix[i][j] = first_array[i][j];
			}
		}
	}
	matrix2D(int num_of_row, int num_of_col, matrix2D *first_matrix2D) {
		m = num_of_row;
		n = num_of_col;
		matrix = new long double *[m];
		for (int i = 0; i < m; i++) {
			matrix[i] = new long double[n];
			for (int j = 0; j < n; j++) {
				matrix[i][j] = first_matrix2D->get_value(i, j);
			}
		}
	}
	void set_value(long double val) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = val;
			}
		}
	}
	void set_value(long double ** array) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = array[i][j];
			}
		}
	}
	void set_value(matrix2D array) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = array.get_value(i, j);
			}
		}
	}
	void set_value(matrix2D * array) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = array->get_value(i, j);
			}
		}
	}
	void set_value(int i,int j,long double value){
		matrix[i][j] = value;
	}
	void set_value_random() {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = ((long double) rand() / (long double) RAND_MAX
						- 0.5);
			}
		}

	}
	void operator=(matrix2D *new_matrix) {
		this->set_value(new_matrix);
	}
	long double ** get_array() {
		return matrix;
	}
	matrix2D * get_matrix() {
		matrix2D* temp = new matrix2D(m, n, matrix);
		return temp;
	}
	int get_num_of_row() {
		return m;
	}
	int get_num_of_col() {
		return n;
	}
	long double get_value(int i, int j) {
		return matrix[i][j];
	}
	long double get_sum() {
		return sum(matrix, m, n);
	}
	long double get_sum_abs() {
		return sumABS(matrix, m, n);
	}
	void print_matrix() {
		cout << "row:" << m << " col:" << n << endl;
		print_array();
	}
	void print_array() {
		print(matrix, m, n);
	}
	void multiply_to_num_onthis(long double num) {
		zarbtak(matrix, num, matrix, m, n);
	}
	//	matrix2D multiply_to_num_matrix2D(long double num) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		zarbtak(temp.get_array(), num, temp.get_array(), m, n);
	//		return temp;
	//	}
	void multiply_to_dot_onthis(long double ** array) {
		zarbdot(matrix, array, matrix, m, n);
	}
	//	matrix2D multiply_to_dot_matrix2D(long double ** array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		zarbdot(temp.get_array(), array, temp.get_array(), m, n);
	//		return temp;
	//	}
	void multiply_to_dot_onthis(matrix2D* array) {
		zarbdot(matrix, array->get_array(), matrix, m, n);
	}
	//	matrix2D multiply_to_dot_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		zarbdot(temp.get_array(), array->get_array(), temp.get_array(), m, n);
	//		return temp;
	//	}
	//	matrix2D multiply_to_matrix_matrix2D(long double ** array, int r, int c) {
	//		matrix2D temp = matrix2D(m, c);
	//		zarb(matrix, array, temp.get_array(), m, n, c);
	//		return temp;
	//	}
	//	matrix2D multiply_to_matrix_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(m, array->get_num_of_col());
	//		zarb(matrix, array->get_array(), temp.get_array(), m, n,
	//				array->get_num_of_col());
	//		return temp;
	//	}
	//
	//	matrix2D multiply_matrix_to_this_matrix2D(long double ** array, int r,
	//			int c) {
	//		matrix2D temp = matrix2D(r, n);
	//		zarb(array, matrix, temp.get_array(), r, m, n);
	//		return temp;
	//	}
	//	matrix2D multiply_matrix_to_this_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(array->get_num_of_row(), n);
	//		zarb(array->get_array(), matrix, temp.get_array(),
	//				array->get_num_of_col(), m, n);
	//		return temp;
	//	}
	void multiply_dot_matrix_to_matrix_onthis(long double ** array1,
			long double ** array2, int a1_r, int a1_c) {
		zarbdot(array1, array2, matrix, a1_r, a1_c);
	}
	void multiply_dot_matrix_to_matrix_onthis(matrix2D *matrix1,
			matrix2D* matrix2) {
		zarbdot(matrix1->get_array(), matrix1->get_array(), matrix,
				matrix1->get_num_of_row(), matrix1->get_num_of_col());
	}
	void multiply_matrix_to_matrix_onthis(long double ** array1,
			long double ** array2, int a1_r, int a1_c, int a2_c) {
		zarb(array1, array2, matrix, a1_r, a1_c, a2_c);
	}
	void multiply_matrix_to_matrix_onthis(matrix2D *matrix1,
			matrix2D* matrix2) {
		zarb(matrix1->get_array(), matrix1->get_array(), matrix,
				matrix1->get_num_of_row(), matrix1->get_num_of_col(),
				matrix2->get_num_of_col());
	}
	void divide_to_num_onthis(long double num) {
		taghsimtak(matrix, num, matrix, m, n);
	}
	//	matrix2D divide_to_num_matrix2D(long double num) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		taghsimtak(temp.get_array(), num, temp.get_array(), m, n);
	//		return temp;
	//	}
	void divide_to_dot_onthis(long double ** array) {
		taghsimdot(matrix, array, matrix, m, n);
	}
	//	matrix2D divide_to_dot_matrix2D(long double ** array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		taghsimdot(temp.get_array(), array, temp.get_array(), m, n);
	//		return temp;
	//	}
	void divide_to_dot_onthis(matrix2D *array) {
		taghsimdot(matrix, array->get_array(), matrix, m, n);
	}
	//	matrix2D divide_to_dot_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		taghsimdot(temp.get_array(), array->get_array(), temp.get_array(), m,
	//				n);
	//		return temp;
	//	}
	//	matrix2D divide_to_matrix_matrix2D(long double ** array, int r, int c) {
	//		matrix2D temp = matrix2D(m, c);
	//		taghsim(matrix, array, temp.get_array(), m, n, c);
	//		return temp;
	//	}
	//	matrix2D divide_to_matrix_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(m, array->get_num_of_col());
	//		taghsim(matrix, array->get_array(), temp.get_array(), m, n,
	//				array->get_num_of_col());
	//		return temp;
	//	}
	//
	//	matrix2D divide_matrix_to_this_matrix2D(long double ** array, int r,
	//			int c) {
	//		matrix2D temp = matrix2D(r, n);
	//		taghsim(array, matrix, temp.get_array(), r, m, n);
	//		return temp;
	//	}
	//	matrix2D divide_matrix_to_this_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(array->get_num_of_row(), n);
	//		taghsim(array->get_array(), matrix, temp.get_array(),
	//				array->get_num_of_col(), m, n);
	//		return temp;
	//	}

	void sum_whit_num_onthis(long double num) {
		jam_dot(matrix, num, matrix, m, n);
	}
	//	matrix2D sum_whit_num_matrix2D(long double num) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		jam_dot(temp.get_array(), num, temp.get_array(), m, n);
	//		return temp;
	//	}
	void sum_whit_onthis(long double ** array) {
		jam(matrix, array, matrix, m, n);
	}
	//	matrix2D sum_whit_matrix2D(long double ** array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		jam(temp.get_array(), array, temp.get_array(), m, n);
	//		return temp;
	//	}
	void sum_whit_onthis(matrix2D* array) {
		jam(matrix, array->get_array(), matrix, m, n);
	}
	//	matrix2D sum_whit_matrix2D(matrix2D* array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		jam(temp.get_array(), array->get_array(), temp.get_array(), m, n);
	//		return temp;
	//	}
	void sum_matrix_whit_matrix_onthis(long double ** array1,
			long double ** array2) {
		jam(array1, array2, matrix, m, n);
	}
	void sum_matrix_whit_matrix_onthis(matrix2D *matrix1, matrix2D *matrix2) {
		jam(matrix1->get_array(), matrix2->get_array(), matrix, m, n);
	}

	void mines_whit_num_onthis(long double num) {
		menha_dot(matrix, num, matrix, m, n);
	}
	//	matrix2D mines_whit_num_matrix2D(long double num) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		menha_dot(temp.get_array(), num, temp.get_array(), m, n);
	//		return temp;
	//	}
	void mines_whit_onthis(long double ** array) {
		menha(matrix, array, matrix, m, n);
	}
	//	matrix2D mines_whit_matrix2D(long double ** array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		menha(temp.get_array(), array, temp.get_array(), m, n);
	//		return temp;
	//	}
	void mines_whit_onthis(matrix2D *array) {
		menha(matrix, array->get_array(), matrix, m, n);
	}
	//	matrix2D mines_whit_matrix2D(matrix2D *array) {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		menha(temp.get_array(), array->get_array(), temp.get_array(), m, n);
	//		return temp;
	//	}
	void mines_matrix_whit_matrix_onthis(long double ** array1,
			long double ** array2) {
		menha(array1, array2, matrix, m, n);
	}
	void mines_matrix_whit_matrix_onthis(matrix2D *matrix1, matrix2D *matrix2) {
		menha(matrix1->get_array(), matrix2->get_array(), matrix, m, n);
	}

	void max_matrix_and_matrix_onthis(long double ** matrix1,
			long double ** matrix2) {
		set_max(matrix1, matrix2, matrix, m, n);
	}
	void min_matrix_and_matrix_onthis(long double ** matrix1,
			long double ** matrix2) {
		set_min(matrix1, matrix2, matrix, m, n);
	}
	void are_max_first_matrix_onthis(long double ** matrix1,
			long double ** matrix2) {
		are_max(matrix1, matrix2, matrix, m, n);
	}
	void are_min_first_matrix_onthis(long double ** matrix1,
			long double ** matrix2) {
		are_min(matrix1, matrix2, matrix, m, n);
	}
	void sigmuid_onthis() {
		sigmuid(matrix, matrix, m, n);
	}
	void sigmuid_matrix_onthis(long double ** array) {
		sigmuid(array, matrix, m, n);
	}
	void sigmuid_matrix_onthis(matrix2D* array) {
		sigmuid(array->get_array(), matrix, m, n);
	}
	//	matrix2D sigmuid_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		sigmuid(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}
	void sigmuidp_onthis() {
		sigmuid_p(matrix, matrix, m, n);
	}
	void sigmuidp_matrix_onthis(long double ** array) {
		sigmuid_p(array, matrix, m, n);
	}
	void sigmuidp_matrix_onthis(matrix2D *array) {
		sigmuid_p(array->get_array(), matrix, m, n);
	}
	//	matrix2D sigmuidp_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		sigmuid_p(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}

	void sin_onthis() {
		sinus(matrix, matrix, m, n);
	}
	void sin_matrix_onthis(long double ** array) {
		sinus(array, matrix, m, n);
	}
	void sin_matrix_onthis(matrix2D* array) {
		sinus(array->get_array(), matrix, m, n);
	}
	//	matrix2D sin_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		sinus(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}
	void sinp_onthis() {
		sinus_p(matrix, matrix, m, n);
	}
	void sinp_matrix_onthis(long double ** array) {
		sinus_p(array, matrix, m, n);
	}
	void sinp_matrix_onthis(matrix2D *array) {
		sinus_p(array->get_array(), matrix, m, n);
	}
	//	matrix2D sinp_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		sinus_p(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}

	void cos_onthis() {
		cosinus(matrix, matrix, m, n);
	}
	void cos_matrix_onthis(long double ** array) {
		cosinus(array, matrix, m, n);
	}
	void cos_matrix_onthis(matrix2D* array) {
		cosinus(array->get_array(), matrix, m, n);
	}
	//	matrix2D cos_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		cosinus(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}
	void cosp_onthis() {
		cosinus_p(matrix, matrix, m, n);
	}
	void cosp_matrix_onthis(long double ** array) {
		cosinus_p(array, matrix, m, n);
	}
	void cosp_matrix_onthis(matrix2D *array) {
		cosinus_p(array->get_array(), matrix, m, n);
	}
	//	matrix2D cosp_matrix2D() {
	//		matrix2D temp = matrix2D(m, n, this->get_matrix());
	//		cosinus_p(matrix, temp.get_array(), m, n);
	//		return temp;
	//	}
	//
	void function_onthis(int type) {
		switch (type) {
		case 0:
			return;
			break;
		case 1:
			sigmuid_onthis();
			break;
		case 2:
			sin_onthis();
			break;
		case 3:
			cos_onthis();
			break;
		default:
			break;
		}
	}
	void function_matrix_onthis(long double ** array, int type) {
		switch (type) {
		case 0:
			set_value(array);
			break;
		case 1:
			sigmuid_matrix_onthis(array);
			break;
		case 2:
			sin_matrix_onthis(array);
			break;
		case 3:
			cos_matrix_onthis(array);
			break;
		default:
			break;
		}
	}
	void function_matrix_onthis(matrix2D *array, int type) {
		switch (type) {
		case 0:
			set_value(array);
			break;
		case 1:
			sigmuid_matrix_onthis(array);
			break;
		case 2:
			sin_matrix_onthis(array);
			break;
		case 3:
			cos_matrix_onthis(array);
			break;
		default:
			break;
		}
	}

	void functionp_onthis(int type) {
		switch (type) {
		case 0:
			set_value(1.0);
			break;
		case 1:
			sigmuidp_onthis();
			break;
		case 2:
			sinp_onthis();
			break;
		case 3:
			cosp_onthis();
			break;
		default:
			break;
		}
	}
	void functionp_matrix_onthis(long double ** array, int type) {
		switch (type) {
		case 0:
			set_value(1.0);
			break;
		case 1:
			sigmuidp_matrix_onthis(array);
			break;
		case 2:
			sinp_matrix_onthis(array);
			break;
		case 3:
			cosp_matrix_onthis(array);
			break;
		default:
			break;
		}
	}
	void functionp_matrix_onthis(matrix2D *array, int type) {
		switch (type) {
		case 0:
			set_value(1.0);
			break;
		case 1:
			sigmuidp_matrix_onthis(array);
			break;
		case 2:
			sinp_matrix_onthis(array);
			break;
		case 3:
			cosp_matrix_onthis(array);
			break;
		default:
			break;
		}
	}

	void transpose_matrix_onthis(long double ** array) {
		tar(array, n, m, matrix);
	}
	void transpose_matrix_onthis(matrix2D *array) {
		tar(array->get_array(), n, m, matrix);
	}
	void low_from_max(long double max) {
		to_max(matrix, max, matrix, m, n);
	}
	void up_from_min(long double min) {
		to_min(matrix, min, matrix, m, n);
	}
	void decussate_from_matrix_and_matrix_onthis(long double ** matrix1,
			long double ** matrix2) {
		for (int i = 0; i < m; i++) {
			if (i % 2 == 0)
				matrix[i][0] = matrix1[i / 2][0];
			else
				matrix[i][0] = matrix2[i / 2][0];
		}
	}
	void decussate_this_to_matrix_and_matrix(long double ** matrix1,
			long double ** matrix2) {
		for (int i = 0; i < m; i++) {
			if (i % 2 == 0)
				matrix1[i / 2][0] = matrix[i][0];
			else
				matrix2[i / 2][0] = matrix[i][0];
		}
	}
};
