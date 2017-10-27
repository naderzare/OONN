
#ifndef LAYER_H_
#define LAYER_H_

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "file.h"
using namespace std;


class layer {
public:
	int nx;
	int nh;
    matrix2D x;
	enum function_type {
		line, sig2, sin, cos
	};
	function_type f_type;
	layer(int nnx, int nnh, function_type function_t) {
//		x = NULL;
		nx = nnx;
		nh = nnh;
		f_type = function_t;
	}
	void set_x(long double **new_data) {
        x.set_value(new_data);
	}
    void set_x(matrix2D &new_data) {
        x.set_value(new_data);
	}

    virtual void forward(matrix2D & output, bool debug = false) = 0;

    virtual long double learn(matrix2D & e, matrix2D & prev_e, bool debug = false, bool learning = true) = 0;

	virtual void print_layer(ofstream * output) = 0;

	virtual void read_layer(ifstream * input) = 0;

    void read_abw(ifstream * input,matrix2D & abw){
        for(int i=0;i<abw.get_num_of_row();i++){
            for(int j=0;j<abw.get_num_of_col();j++){
				long double value;
				(*input)>>value;
                abw.set_value(i,j,value);
			}
		}
	}
    void print_abw(ofstream * output,matrix2D & abw){
        for(int i=0;i<abw.get_num_of_row();i++){
            for(int j=0;j<abw.get_num_of_col();j++){
                (*output)<<(abw.get_value(i,j));
				(*output)<<endl;
			}
		}
	}
	virtual ~layer(){

	}
};

#endif /* LAYER_H_ */
