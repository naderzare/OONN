/*
 * NN.h
 *
 *  Created on: Apr 25, 2017
 *      Author: nader
 */

#include "layer_simple.h"
#include "layer.h"
#include <vector>

using namespace std;
#include <fstream>
using VLD = vector<long double>;
using LD3 = long double ***;
using LD = long double;
using VI = vector<int>;
class NN {
public:

    NN(VI c_num_noron, VI c_layer_type,VI c_function_type,
       char * c_name_of_outputfiles,
       char * c_name_of_inputfiles);
    NN(int num_data_set, VI c_num_noron, VI c_layer_type,
            VI c_function_type, double c_percent_learn,
			double c_percent_val, double c_percent_test,
            char * c_name_of_outputfiles, char * c_name_of_inputfiles,LD c_max_x=1,LD c_max_y=1);
    void FillData(LD3 & data,pair<int,int> size);
    void push_data_set_from_other(LD3 dataF,LD3 dataT,int m,int n, int z);
    void set_data_set(LD3 datax0,LD3 datay0);
	void devide_data_set();
	void dataset_upload(char * dataset_file_name);
	void dataset_upload_test(char * dataset_file_name,int num_data);
	void dataset_upload_for_autoencoder(char * dataset_file_name,int num_label);
	void normalize_dataset_one();
	void normalize_x_one();
	void normalize_y_one();
	void normalize_dataset_full();
	void normalize_x_full();
	void normalize_y_full();
	void normalize_noise_x_for_deepopp();
	void normalize_noise_y_for_deepopp();
	void data_shuffle();
	void data_learn_shuffle();

    void ForwardTest(LD3 datas, int data_number);
    void ForwardTest(LD3 datas, int data_numbers,LD3 datay);
    void Forward(LD3 datas, int data_number);
    VLD Forward(VLD & input);
    VLD Forward(VLD & input1,VLD & input2);
    void ForwardVoid(VLD & input,VLD & output);
    void ForwardVoid(VLD & input1,VLD & input2,VLD & output);



    LD calc_error_data(LD3 datas, int data_number);
    LD calc_error_data(VLD & target);

	void learn_data();

    LD LearnForReErWtErs(VLD & input,VLD & error);
    VLD LearnReErsWtTar(VLD & target);
    VLD LearnForReErsWtTar(VLD & input,VLD & target);
    pair<VLD,VLD > LearnForReErsWtTar(VLD & input1,VLD & input2,VLD & target);
    LD LearnReErWtErs(VLD & input,VLD & errors);
    LD LearnReErWtTar(VLD & target);
    LD LearnForReErWtTar(VLD & input,VLD & target);
    LD LearnForReErWtTar(VLD & input1,VLD & input2,VLD & target);

    void LearnEpoches(int max_epoch, int epoch_shuffle,bool with_val, bool autoencoder, bool & exit_print);
    void LearnDatas(ofstream * nn_error_out, bool autoencoder = false);
	void validation_datas(ofstream * nn_error_out);
	void test_datas();
	void test_datas2();

	void read_weith_from_deepl(int max_layer_from_deep);
	void read_weith();
	void write_weith(int layer = 0);
    void push_all_output(LD3 data);
public:
	int num_data;
    LD3 datax;
    LD3 datay;
    LD3 datax_temp;
    LD3 datay_temp;
	int num_learn;
	int num_validation;
	int num_test;

    LD3 data_learnx;
    LD3 data_validationx;
    LD3 data_testx;
    LD3 data_learnx_temp;
    LD3 data_learny;
    LD3 data_validationy;
    LD3 data_testy;
    LD3 data_learny_temp;
	int layer_number;
    VI num_noron;
    VI layer_type;
    VI function_type;
	char * name_of_outputfiles;
	char * name_of_inputfiles;

	bool use_normalize_with_one;
    VLD data_x_max_vec;
    VLD data_y_max_vec;
    LD data_x_max;
    LD data_y_max;

	matrix2D x;
	matrix2D y;
	vector<matrix2D> o;
	vector<matrix2D> e;
	vector<layer*> layers;

};
NN::NN(VI c_num_noron, VI c_layer_type,VI c_function_type,
       char * c_name_of_outputfiles,
       char * c_name_of_inputfiles){
    layer_number = c_layer_type.size();
    for (int i = 0; i < layer_number; i++) {
        num_noron.push_back(c_num_noron[i]);
        layer_type.push_back(c_layer_type[i]);
        function_type.push_back(c_function_type[i]);
    }
    x = matrix2D(num_noron[0], 1);
    y = matrix2D(num_noron[layer_number - 1], 1);
    for (int i = 0; i < layer_number; i++) {
        o.push_back(matrix2D(num_noron[i], 1));
        e.push_back(matrix2D(num_noron[i], 1));
    }

    layers.push_back(
            new layer_simple(num_noron[0], num_noron[0],
                    layer::function_type(0)));
    for (int i = 1; i < layer_number; i++) {
        int l_type = layer_type[i];
        int f_type = function_type[i];
        layers.push_back(
                new layer_simple(num_noron[i - 1], num_noron[i],
                        layer::function_type(f_type)));
    }
    name_of_inputfiles = c_name_of_inputfiles;
    name_of_outputfiles = c_name_of_outputfiles;
}

NN::NN(int num_data_set, VI c_num_noron, VI c_layer_type,
        VI c_function_type, double c_percent_learn,
		double c_percent_val, double c_percent_test,
        char * c_name_of_outputfiles,
        char * c_name_of_inputfiles,LD c_max_x,LD c_max_y)
    :NN(c_num_noron, c_layer_type, c_function_type, c_name_of_outputfiles, c_name_of_inputfiles) {
	num_data = num_data_set;

    FillData(datax,pair<int,int>(num_data,num_noron[0]));
    FillData(datay,pair<int,int>(num_data,num_noron[layer_number-1]));
    FillData(datax_temp,pair<int,int>(num_data,num_noron[0]));
    FillData(datay_temp,pair<int,int>(num_data,num_noron[layer_number-1]));
//    datax = new LD ** [num_data];
//    datay = new LD ** [num_data];
//    datax_temp = new LD **[num_data];
//    datay_temp = new LD **[num_data];
//	for(int i=0;i<num_data;i++){
//        datax[i] = new LD *[num_noron[0]];
//        datax_temp[i] = new LD *[num_noron[0]];
//		for(int j=0;j<num_noron[0];j++){
//            datax[i][j] = new LD [1];
//			datax[i][j][0] = 0;
//            datax_temp[i][j] = new LD [1];
//			datax_temp[i][j][0] = 0;
//		}
//        datay[i] = new LD *[num_noron[layer_number-1]];
//        datay_temp[i] = new LD *[num_noron[layer_number-1]];
//		for(int j=0;j<num_noron[layer_number-1];j++){
//            datay[i][j] = new LD [1];
//			datay[i][j][0] = 0;
//            datay_temp[i][j] = new LD [1];
//			datay_temp[i][j][0] = 0;
//		}
//	}

	double percent_learn = c_percent_learn;
	double percent_val = c_percent_val;
	double percent_test = c_percent_test;
	num_learn = num_data * percent_learn / 100.0;
	num_validation = num_data * percent_val / 100.0;
	num_test = num_data * percent_test / 100.0;

    FillData(data_learnx,pair<int,int>(num_learn,num_noron[0]));
    FillData(data_learny,pair<int,int>(num_learn,num_noron[layer_number-1]));
    FillData(data_validationx,pair<int,int>(num_validation,num_noron[0]));
    FillData(data_validationy,pair<int,int>(num_validation,num_noron[layer_number-1]));
    FillData(data_testx,pair<int,int>(num_test,num_noron[0]));
    FillData(data_testy,pair<int,int>(num_test,num_noron[layer_number-1]));


//    data_learnx = new LD **[num_learn];
//    data_learny = new LD **[num_learn];
//	for(int i=0;i<num_learn;i++){
//        data_learnx[i] = new LD * [num_noron[0]];
//        data_learny[i] = new LD * [num_noron[layer_number-1]];
//		for(int j=0;j<num_noron[0];j++){
//            data_learnx[i][j] = new LD [1];
//			data_learnx[i][j][0] = 0;
//		}
//		for(int j=0;j<num_noron[layer_number-1];j++){
//            data_learny[i][j] = new LD [1];
//			data_learny[i][j][0] = 0;
//		}
//	}
//    data_validationx = new LD **[num_validation];
//    data_validationy = new LD **[num_validation];
//	for(int i=0;i<num_validation;i++){
//        data_validationx[i] = new LD * [num_noron[0]];
//        data_validationy[i] = new LD * [num_noron[layer_number-1]];
//		for(int j=0;j<num_noron[0];j++){
//            data_validationx[i][j] = new LD [1];
//			data_validationx[i][j][0] = 0;
//		}
//		for(int j=0;j<num_noron[layer_number-1];j++){
//            data_validationy[i][j] = new LD [1];
//			data_validationy[i][j][0] = 0;
//		}
//	}
//    data_testx = new LD **[num_test];
//    data_testy = new LD **[num_test];
//	for(int i=0;i<num_test;i++){
//        data_testx[i] = new LD * [num_noron[0]];
//        data_testy[i] = new LD * [num_noron[layer_number-1]];
//		for(int j=0;j<num_noron[0];j++){
//            data_testx[i][j] = new LD [1];
//			data_testx[i][j][0] = 0;
//		}
//		for(int j=0;j<num_noron[layer_number-1];j++){
//            data_testy[i][j] = new LD [1];
//			data_testy[i][j][0] = 0;
//		}
//	}

	data_x_max = c_max_x;
	data_y_max = c_max_y;

}
void NN::FillData(LD3 & data,pair<int,int> size){
    int m = size.first;
    int n = size.second;
    data = new LD **[m];
    for(int i=0;i<m;i++){
        data[i] = new LD * [n];
        for(int j=0;j<n;j++){
            data[i][j] = new LD [1];
            data[i][j][0] = 0;
        }
    }
}

void NN::push_data_set_from_other(LD3 dataF, LD3 dataT, int m, int n, int z){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<z;k++){
				dataT[i][j][k] = dataF[i][j][k];
			}
		}
	}
}
void NN::set_data_set(LD3 datax0,LD3 datay0){
	push_data_set_from_other(datax0,datax,num_data,num_noron[0],1);
	push_data_set_from_other(datay0,datay,num_data,num_noron[layer_number-1],1);
	shuffle_dataset(datax,datay,num_data,num_noron[0],num_noron[layer_number-1]);
}
void NN::devide_data_set(){
	cutting_dataset(datax, num_data, num_noron[0], data_learnx,
			data_validationx, data_testx, num_learn, num_validation,
			num_test);
	cutting_dataset(datay, num_data, num_noron[layer_number - 1],
			data_learny, data_validationy, data_testy, num_learn,
			num_validation, num_test);
}
void NN::dataset_upload(char * dataset_file_name) {
	dataset_read(num_data, datax, num_noron[0], datay,
			num_noron[layer_number - 1], dataset_file_name);
	shuffle_dataset(datax,datay,num_data,num_noron[0],num_noron[layer_number-1]);
}
void NN::dataset_upload_test(char * dataset_file_name,int num_data) {
    num_test = num_data;
    FillData(data_testx,pair<int,int>(num_test,num_noron[0]));
    FillData(data_testy,pair<int,int>(num_test,num_noron[layer_number-1]));

//    data_testx = new LD **[num_test];
//    data_testy = new LD **[num_test];
//	for(int i=0;i<num_test;i++){
//        data_testx[i] = new LD * [num_noron[0]];
//        data_testy[i] = new LD * [num_noron[layer_number-1]];
//		for(int j=0;j<num_noron[0];j++){
//            data_testx[i][j] = new LD [1];
//			data_testx[i][j][0] = 0;
//		}
//		for(int j=0;j<num_noron[layer_number-1];j++){
//            data_testy[i][j] = new LD [1];
//			data_testy[i][j][0] = 0;
//		}
//	}
	dataset_read(num_test, data_testx, num_noron[0], data_testy,
			num_noron[layer_number - 1], dataset_file_name);
}
void NN::dataset_upload_for_autoencoder(char * dataset_file_name,int num_label) {
	dataset_read_for_autoencoder(num_data, datax, num_noron[0], datay,
			num_noron[layer_number - 1], dataset_file_name,num_label);
	shuffle_dataset(datax,datay,num_data,num_noron[0],num_noron[layer_number-1]);
}

void NN::normalize_dataset_one() {
	normalize_x_one();
	normalize_y_one();
	data_shuffle();
	cutting_dataset(datax, num_data, num_noron[0], data_learnx,
			data_validationx, data_testx, num_learn, num_validation,
			num_test);
	cutting_dataset(datay, num_data, num_noron[layer_number - 1],
			data_learny, data_validationy, data_testy, num_learn,
			num_validation, num_test);

}
void NN::normalize_x_one() {
	if(data_x_max==0){
		data_x_max = 0;
		for(int i=0;i<num_data;i++){
			for(int j=0;j<num_noron[0];j++){
				if(abs_ld(datax[i][j][0]) >data_x_max){
					data_x_max = abs_ld(datax[i][j][0]);
				}
			}
		}
	}
	normalize_dataset(datax, num_data, num_noron[0], data_x_max);
}
void NN::normalize_y_one() {
	if(data_y_max==0){
		data_y_max = 0;
		for(int i=0;i<num_data;i++){
			for(int j=0;j<num_noron[layer_number-1];j++){
				if(abs_ld(datay[i][j][0]) >data_y_max){
					data_y_max = abs_ld(datay[i][j][0]);
				}
			}
		}
	}
	normalize_dataset(datay, num_data, num_noron[layer_number - 1],
			data_y_max);
}
void NN::normalize_dataset_full() {
	normalize_x_full();
	normalize_y_full();
}
void NN::normalize_x_full() {
    //		LD max_x[num_noron[0]] = {1};
	//		for(int i=0;i<num_noron[0];i++)
		//			data_x_max_vec.push_back(max_x[i]);
	normalize_dataset(datax, num_data, num_noron[0], data_x_max_vec);
}
void NN::normalize_y_full() {
    //		LD max_y[num_noron[layer_number-1]] = {1};
	//		for(int i=0;i<num_noron[layer_number-1];i++)
	//			data_y_max_vec.push_back(max_y[i]);
	normalize_dataset(datay, num_data, num_noron[layer_number - 1],
			data_y_max_vec);
}
void NN::normalize_noise_x_for_deepopp(){
	for(int i=0;i<num_data;i++){
		for(int j=0;j<num_noron[0];j++){
			datax[i][j][0] /= 10.0;
		}
	}
}
void NN::normalize_noise_y_for_deepopp(){

	for(int i=0;i<num_data;i++){
		for(int j=0;j<num_noron[layer_number-1];j++){
			datay[i][j][0]/=10.0;
		}
	}
}

void NN::data_shuffle() {
	shuffle_dataset(datax, datay, num_data,
			num_noron[0], num_noron[layer_number - 1]);
}
void NN::data_learn_shuffle() {
	shuffle_dataset(data_learnx, data_learny, num_learn, num_noron[0],
			num_noron[layer_number - 1]);
}

void NN::ForwardTest(LD3 datas, int data_number) {
	normalize_dataset(datas, data_number, num_noron[0], data_x_max);
	for(int d=0;d<data_number;d++){
		o[0].set_value(datas[d]);
		for (int l = 1; l < layer_number; l++) {
            layers[l]->set_x(o[l - 1]);
            layers[l]->forward(o[l], false);
		}
		cout<<"input:"<<endl;
		for(int in=0;in<num_noron[0];in++){
			cout<<datas[d][in][0]*data_x_max<<endl;
		}
		cout<<"output:"<<endl;
		for(int on=0;on<num_noron[layer_number-1];on++){
			cout<<o[layer_number-1].matrix[on][0]*data_y_max<<endl;
		}
		cout<<endl;
	}
}
void NN::ForwardTest(LD3 datas, int data_numbers,LD3 datay) {
	normalize_dataset(datas, data_numbers, num_noron[0], data_x_max);
	for(int d=0;d<data_numbers;d++){
		o[0].set_value(datas[d]);
		for (int l = 1; l < layer_number; l++) {
            layers[l]->set_x(o[l - 1]);
            layers[l]->forward(o[l], false);
		}
		cout<<"input:"<<endl;
		for(int in=0;in<num_noron[0];in++){
			cout<<datas[d][in][0]*data_x_max<<endl;
		}
		cout<<"output:"<<endl;
		for(int on=0;on<num_noron[layer_number-1];on++){
			cout<<o[layer_number-1].matrix[on][0]*data_y_max<<endl;
			datay[d][on][0] = o[layer_number-1].matrix[on][0]*data_y_max;
		}
		cout<<endl;
	}
}

void NN::ForwardVoid(VLD & input,VLD & output){
    o[0].set_value(input);
    for (int l = 1; l < layer_number; l++) {
        layers[l]->set_x(o[l - 1]);
        layers[l]->forward(o[l], false);
    }
    for(int i=0;i<output.size();i++)
        output[i] = o[layer_number-1].get_value(i,0);
//    o[layer_number-1].get_vector_1D(output);
}

void NN::ForwardVoid(VLD & input1,VLD & input2,VLD & output){
    o[0].set_value(input1,input2);
    for (int l = 1; l < layer_number; l++) {
        layers[l]->set_x(o[l - 1]);
        layers[l]->forward(o[l], false);
    }
    for(int i=0;i<output.size();i++)
        output[i] = o[layer_number-1].get_value(i,0);
//    o[layer_number-1].get_vector_1D(output);
}

VLD NN::Forward(VLD & input){
    o[0].set_value(input);
    for (int l = 1; l < layer_number; l++) {
        layers[l]->set_x(o[l - 1]);
        layers[l]->forward(o[l], false);
    }
    return o[layer_number-1].get_vector_1D();
}

VLD NN::Forward(VLD & input1,VLD & input2){
    o[0].set_value(input1,input2);
    for (int l = 1; l < layer_number; l++) {
        layers[l]->set_x(o[l - 1]);
        layers[l]->forward(o[l], false);
    }
    auto p =  o[layer_number-1].get_vector_1D();
    return p;
}

void NN::Forward(LD3 inputs, int data_number) {
    o[0].set_value(inputs[data_number]);
//    o[0].print_matrix();
	for (int l = 1; l < layer_number; l++) {
        layers[l]->set_x(o[l - 1]);
        layers[l]->forward(o[l], false);
	}
//    o[layer_number-1].print_matrix();
}
LD NN::calc_error_data(VLD & target) {
    y.set_value(target);
    e[layer_number - 1].set_value(y.get_array());
    e[layer_number - 1].mines_whit_onthis(o[layer_number - 1].get_array());
    LD error = 0;
    for (int i = 0; i < e[layer_number - 1].get_num_of_row(); i++) {
        error += abs_ld(e[layer_number - 1].get_value(i, 0));
    }
    return error;
}

LD NN::calc_error_data(LD3 datas, int data_number) {
	y.set_value(datas[data_number]);
	e[layer_number - 1].set_value(y.get_array());
	e[layer_number - 1].mines_whit_onthis(o[layer_number - 1].get_array());
    LD error = 0;
	for (int i = 0; i < e[layer_number - 1].get_num_of_row(); i++) {
		error += abs_ld(e[layer_number - 1].get_value(i, 0));
	}
	return error;
}


VLD NN::LearnReErsWtTar(VLD & target){
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[0].get_vector_1D();
}
LD NN::LearnReErWtErs(VLD & input,VLD & error){
    e[layer_number - 1].set_value(error);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[layer_number-1].get_sum();
}

LD NN::LearnForReErWtErs(VLD & input,VLD & error){
    Forward(input);
    e[layer_number - 1].set_value(error);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[layer_number-1].get_sum();
}


VLD NN::LearnForReErsWtTar(VLD & input, VLD & target){
    Forward(input);
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[0].get_vector_1D();
}

pair<VLD,VLD > NN::LearnForReErsWtTar(VLD & input1,VLD & input2, VLD & target){
    Forward(input1,input2);
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    VLD ers = e[0].get_vector_1D();
    VLD ers1(input1.size());
    for(int i=0;i<input1.size();i++){
        ers1[i] = ers[i];
    }
    int j=0;
    VLD ers2(input2.size());
    for(int i=input1.size();i<input1.size() + input2.size();i++){
        ers2[j]= ers[i-input1.size()];
        j++;
    }
    pair<VLD,VLD >(ers1,ers2);
}

LD NN::LearnReErWtTar(VLD & target){
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[layer_number-1].get_sum();
}

LD NN::LearnForReErWtTar(VLD & input, VLD & target){
    Forward(input);
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[layer_number-1].get_sum();
}

LD NN::LearnForReErWtTar(VLD & input1,VLD & input2, VLD & target){
    Forward(input1,input2);
    calc_error_data(target);
    for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
    }
    return e[layer_number-1].get_sum();
}

void NN::learn_data() {
	for (int l = layer_number - 1; l > 0; l--) {
        layers[l]->learn(e[l], e[l - 1], true);
	}
}
void NN::LearnDatas(ofstream * nn_error_out, bool autoencoder) {
	{
        LD eee = 0;
		double currect_bhv = 0;
		for (int d = 0; d < num_learn; d++) {
//            cout<<"-------------------------------------------------------------------"<<endl;
            Forward(data_learnx, d);
			if(!autoencoder){
				int bhv_y = 0;
				for(int i=0;i<num_noron[layer_number-1];i++){
					if(data_learny[d][i][0] == 1){
						bhv_y = i;
						break;
					}
				}
				double max_in_o = -1000;
				int bhv_o = 0;
				for(int i=0;i<num_noron[layer_number-1];i++){
					double oi = o[layer_number-1].get_value(i,0);
					if(oi > max_in_o){
						max_in_o = oi;
						bhv_o = i;
					}
				}
				if(bhv_o == bhv_y){
					currect_bhv ++;
				}
			}
			eee += calc_error_data(data_learny, d);
//            cout<<"target:"<<endl;
//            for(int i=0;i<11;i++){
//                cout<<data_learny[d][i][0]<<endl;
//            }
			learn_data();
            Forward(data_learnx, d);
		}
		if(autoencoder){
            cout<<0<< "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<endl;
            (*nn_error_out)<<0<< "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<endl;
		}else{
            cout<<0<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_learn<<"\t"<<endl;
            (*nn_error_out)<<0<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_learn<<"\t"<<endl;
		}
	}
    return ;
	{
        LD eee = 0;
		double currect_bhv = 0;
		for (int d = 0; d < num_learn; d++) {
            Forward(data_learnx, d);
			if(!autoencoder){
				int bhv_y = 0;
				for(int i=0;i<num_noron[layer_number-1];i++){
					if(data_learny[d][i][0] == 1){
						bhv_y = i;
						break;
					}
				}
				double max_in_o = -1000;
				int bhv_o = 0;
				for(int i=0;i<num_noron[layer_number-1];i++){
					double oi = o[layer_number-1].get_value(i,0);
					if(oi > max_in_o){
						max_in_o = oi;
						bhv_o = i;
					}
				}
				if(bhv_o == bhv_y){
					currect_bhv ++;
				}
			}
			eee += calc_error_data(data_learny, d);
		}
		if(autoencoder){
            cout<<1<< "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<endl;
            (*nn_error_out)<<1<< "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<endl;
		}else{
            cout<<1<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_learn<<"\t"<<endl;
            (*nn_error_out)<<1<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_learn/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_learn<<"\t"<<endl;
		}

	}
}
void NN::validation_datas(ofstream * nn_error_out) {
    LD eee = 0;
	double currect_bhv = 0;
	for (int d = 0; d < num_validation; d++) {
        Forward(data_validationx, d);
		int bhv_y = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			if(data_validationy[d][i][0] == 1){
				bhv_y = i;
				break;
			}
		}
		double max_in_o = -1000;
		int bhv_o = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			double oi = o[layer_number-1].get_value(i,0);
			if(oi > max_in_o){
				max_in_o = oi;
				bhv_o = i;
			}
		}
		if(bhv_o == bhv_y){
			currect_bhv ++;
		}
		eee += calc_error_data(data_validationy, d);
	}
    cout<<2<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_validation/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_validation<<"\t"<<endl;
    (*nn_error_out)<<2<< "\t"<<eee/(LD)num_learn << "\t"<<eee/(LD)num_validation/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv/(LD)num_validation<<"\t"<<endl;
}
void NN::test_datas() {
	static int test_number = 0;
	test_number++;
	char error_out[30];
	sprintf(error_out, "nn_%s_lns%d_error_learn",
			name_of_outputfiles, layer_number);
	ofstream nn_error_out(error_out,ios::app);
    LD eee = 0;
	double currect_bhv = 0;
	for (int d = 0; d < num_test; d++) {
        Forward(data_testx, d);
		int bhv_y = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			if(data_testy[d][i][0] == 1){
				bhv_y = i;
				break;
			}
		}
		double max_in_o = -1000;
		int bhv_o = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			double oi = o[layer_number-1].get_value(i,0);
			if(oi > max_in_o){
				max_in_o = oi;
				bhv_o = i;
			}
		}

		if(bhv_o == bhv_y){
			currect_bhv ++;
		}
		eee += calc_error_data(data_testy, d);
	}
    cout<<3<<"\t"<<test_number<< "\t"<<eee/(LD)num_test << "\t"<<eee/(LD)num_test/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv<<"\t"<<currect_bhv/(LD)num_test<<"\t"<<endl;
}
void NN::test_datas2() {//agar nn dovomi ro ham pish bini kone ok hast
	static int test_number = 0;
	test_number++;
	char error_out[30];
	sprintf(error_out, "nn_%s_lns%d_error_learn",
			name_of_outputfiles, layer_number);
	ofstream nn_error_out(error_out,ios::app);
    LD eee = 0;
	double currect_bhv = 0;
	for (int d = 0; d < num_test; d++) {
        Forward(data_testx, d);
		int bhv_y = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			if(data_testy[d][i][0] == 1){
				bhv_y = i;
				break;
			}
		}
		double max_in_o = -1000;
		int bhv_o = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			double oi = o[layer_number-1].get_value(i,0);
			if(oi > max_in_o){
				max_in_o = oi;
				bhv_o = i;
			}
		}
		max_in_o = -1000;
		int bhv_o2 = 0;
		for(int i=0;i<num_noron[layer_number-1];i++){
			double oi = o[layer_number-1].get_value(i,0);
			if(i == bhv_o)
				continue;
			if(oi > max_in_o){
				max_in_o = oi;
				bhv_o2 = i;
			}
		}
		if(bhv_o == bhv_y || bhv_o2 == bhv_y){
			currect_bhv ++;
		}
		eee += calc_error_data(data_testy, d);
	}
    cout<<3<<"\t"<<test_number<< "\t"<<eee/(LD)num_test << "\t"<<eee/(LD)num_test/(LD)num_noron[layer_number-1]<<"\t"<<currect_bhv<<"\t"<<currect_bhv/(LD)num_test<<"\t"<<endl;
}
void NN::LearnEpoches(int max_epoch, int epoch_shuffle,bool with_val, bool autoencoder, bool & exit_print) {
    cout<<"in learn_epoches"<<endl;
    char error_out[30];
	sprintf(error_out, "nn_%s_lns%d_error_learn",
			name_of_outputfiles, layer_number);
	ofstream nn_error_out(error_out,ios::app);
	for (int epoch = 1; epoch < max_epoch; epoch++) {
		if (epoch % epoch_shuffle == 0){
			data_learn_shuffle();
			if(!autoencoder)write_weith();
		}
		if(exit_print){
			break;
		}
		cout<<"epoch : "<<epoch<<endl;
        LearnDatas(&nn_error_out,autoencoder);
		if(with_val)validation_datas(&nn_error_out);
	}
	nn_error_out.close();
}
void NN::read_weith_from_deepl(int max_layer_from_deep) {
	for (int i = 1; i <= max_layer_from_deep; i++) {
		cout<<num_noron[i]<<endl;
		char layer_file_name_in[45];
		sprintf(layer_file_name_in, "nn_deep_l_%d_lns3_ln1_lt%d_ft%d_n%d", i, layer_type[i],function_type[i],num_noron[i]);
		cout<<layer_file_name_in<<endl;
		ifstream layer_input;
		layer_input.open(layer_file_name_in);
		layers[i]->read_layer(&layer_input);
		layer_input.close();
	}
}
void NN::read_weith() {
	for (int i = 1; i < layer_number; i++) {
		char layer_file_name_in[45];
		sprintf(layer_file_name_in, "nn_%s_lns%d_ln%d_lt%d_ft%d_n%d",
				name_of_inputfiles, layer_number, i, layer_type[i],
				function_type[i], num_noron[i]);
		cout<<"layer "<<i<<" read from:"<<layer_file_name_in<<endl;
		ifstream layer_input;
		layer_input.open(layer_file_name_in);
		layers[i]->read_layer(&layer_input);
		layer_input.close();
	}
}
void NN::write_weith(int layer ) {
	if(layer == 0){
		for (int i = 1; i < layer_number; i++) {
			char layer_file_name_out[45];
			sprintf(layer_file_name_out, "nn_%s_lns%d_ln%d_lt%d_ft%d_n%d",
					name_of_outputfiles, layer_number, i, layer_type[i],
					function_type[i], num_noron[i]);
			ofstream layer_output;
			layer_output.open(layer_file_name_out);
			layers[i]->print_layer(&layer_output);
			layer_output.close();
		}
	}else{
		char layer_file_name_out[45];
		sprintf(layer_file_name_out, "nn_%s_lns%d_ln%d_lt%d_ft%d_n%d",
				name_of_outputfiles, layer_number, layer, layer_type[layer],
				function_type[layer], num_noron[layer]);
		ofstream layer_output;
		layer_output.open(layer_file_name_out);
		layers[layer]->print_layer(&layer_output);
		layer_output.close();
	}
}
void NN::push_all_output(LD3 data){
	for(int d=0;d<num_data;d++){
		o[0].set_value(data_learnx[d]);
		for (int l = 1; l < layer_number; l++) {
            layers[l]->set_x(o[l - 1]);
            layers[l]->forward(o[l], false);
		}
		for(int n=0;n<num_noron[1];n++){
			data[d][n][0] = o[1].get_value(n,0);
		}
	}
}



