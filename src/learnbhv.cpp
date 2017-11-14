
#include "NN.h"
#include <signal.h>

static bool exit_and_print = false;
void set_sig(int sig){
	exit_and_print = true;
}

void set_simple_w(bool read,vector<int> deepnoron){
	int num_x = deepnoron[0];
	int num_y = 11;
	int layered_learn_epoch = 75;
	int size = 1000;

	vector<int> num_layers;
	for(int i=0;i<deepnoron.size();i++){
		num_layers.push_back(deepnoron[i]);
	}

	long double *** datax;
	for(int l=1;l<num_layers.size()-1;l++){
		cout<<"learn simple w with autoencoder l="<<l<<endl;
		vector<int>deep_noron;vector<int>deep_ltype;vector<int>deep_ftype;
		deep_noron.push_back(num_layers[l-1]);deep_ltype.push_back(0);deep_ftype.push_back(0);
		deep_noron.push_back(num_layers[l]);deep_ltype.push_back(0);deep_ftype.push_back(1);
		deep_noron.push_back(num_layers[l-1]);deep_ltype.push_back(0);deep_ftype.push_back(0);
		char name[45];
		sprintf(name, "deep_l_%d",l);
		NN deep(size,deep_noron,deep_ltype,deep_ftype,100.0,0.0,0.0,name,name,1,1);
		if(l==1)
			deep.dataset_upload_for_autoencoder("train.log",num_y);
		else
			deep.set_data_set(datax,datax);
		deep.devide_data_set();
		if(read)deep.read_weith();
		deep.learn_epoches(layered_learn_epoch,2,false,true,exit_and_print);
		layered_learn_epoch = 50;
		deep.write_weith(1);


		datax = new long double **[size];
		for(int i=0;i<size;i++){
			datax[i] = new long double *[num_layers[1]];
			for(int j=0;j<num_layers[1];j++){
				datax[i][j] = new long double [1];
				datax[i][j][0]=0;
			}
		}
		deep.push_all_output(datax);
	}
}

int main(int argc, char * argv[]) {
	signal(SIGINT,set_sig);
	bool read_weight = false;
	bool read_weight_from_autoencoder = false;
	bool set_weight_from_autoencoder = false;
	bool just_test = false;
	string argv2 = argv[1];
	cout<<argv2<<endl;
	if (argv2.compare("test") == 0) {
		read_weight = true;
		just_test = true;
	}
	else if (argv2.compare("read") == 0) {
		read_weight = true;
	}else if(argv2.compare("readae") == 0){
		read_weight_from_autoencoder = true;
	}else if(argv2.compare("setsimplew") == 0){
		read_weight_from_autoencoder = true;
		set_weight_from_autoencoder = true;
	}
	int layer_number;
	cout<<"layernumber:";
	cin>>layer_number;
	vector<int>deep_noron;
	vector<int>deep_ltype;
	vector<int>deep_ftype;
	for(int i=1;i<=layer_number;i++){
		int l;
		cin>>l;
		deep_noron.push_back(l);
		int ft = 1;
		if(i==1 || i==layer_number)
			ft = 0;
		deep_ftype.push_back(ft);
		deep_ltype.push_back(0);
	}
	if(set_weight_from_autoencoder)
		set_simple_w(false,deep_noron);
	//	return 0;

	int num_x = deep_noron[0];//92//550 //605
	int num_y = deep_noron[layer_number];

	int layered_learn_epoch = 100000;

	int size_learn = 20000;
	NN deep(size_learn,deep_noron,deep_ltype,deep_ftype,90.0,10.0,0.0,"deep","deep",1,1);

	if(!just_test){
		deep.dataset_upload("train.log");
		deep.devide_data_set();
	}
	if(read_weight_from_autoencoder)deep.read_weith_from_deepl(layer_number-2);
	if(read_weight)deep.read_weith();

	if(!just_test){
		deep.learn_epoches(layered_learn_epoch,2,true,false,exit_and_print);
		deep.write_weith();
	}

	for(int i = 0;i<deep_noron.size();i++){
		cout<<"l:"<<i<<": "<<deep_noron[i]<<" "<<deep_ltype[i]<<endl;
	}

	return true;
}
