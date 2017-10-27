#include "layer.h"
class layer_simple : public layer{

public:
	layer_simple(int nnx, int nnh, function_type function_t);
    virtual void forward(matrix2D & output, bool debug = false);
    virtual long double learn(matrix2D & er, matrix2D & prev_e,
			bool debug = false,bool learning = true);
	virtual void read_layer(ifstream * input);
	virtual void print_layer(ofstream * output);
private:
    matrix2D b;
    matrix2D a;
    matrix2D w;
    matrix2D w_tar;
    matrix2D x_tar;
    matrix2D net;
    matrix2D anet;
    matrix2D o;
    matrix2D e;
    matrix2D g_w;
    matrix2D g_a;
    matrix2D g_b;
    matrix2D fp;
    matrix2D g_x;

};






















layer_simple::layer_simple(int nnx, int nnh, function_type function_t)
:layer(nnx,nnh,function_t){
    x = matrix2D(nx, 1);
    x_tar = matrix2D(1, nx);
    a = matrix2D(nh, 1);
    a.set_value_random();
    b = matrix2D(nh, 1);
    b.set_value_random();
    w = matrix2D(nh, nx);
    w.set_value_random();
    w.divide_to_num_onthis((long double) nx);
    w_tar = matrix2D(nx, nh);
    net = matrix2D(nh, 1);
    anet = matrix2D(nh, 1);
    o = matrix2D(nh, 1);
    e = matrix2D(nh, 1);
    fp = matrix2D(nh, 1);
    g_a = matrix2D(nh, 1);
    g_b = matrix2D(nh, 1);
    g_w = matrix2D(nh, nx);
    g_x = matrix2D(nx, 1);
}
void layer_simple::forward(matrix2D & output, bool debug) {
    net.multiply_matrix_to_matrix_onthis(w.get_array(), x.get_array(),
			nh, nx, 1);
    net+=(b.get_array());
    anet.multiply_dot_matrix_to_matrix_onthis(net.get_array(),
            a.get_array(), net.get_num_of_row(), net.get_num_of_col());
    o.function_matrix_onthis(anet, (int) f_type);
    output.set_value(o.get_array());
}

long double layer_simple::learn(matrix2D & er, matrix2D & prev_e,
		bool debug,bool learning) {
//    cout<<"a"<<endl;
    e.set_value(er.get_array());
//    cout<<"b"<<endl;
    long double em = e.get_sum_abs();
//    cout<<"c"<<endl;
    fp.functionp_matrix_onthis(anet.get_array(), (int) f_type);
    g_a.multiply_dot_matrix_to_matrix_onthis(e.get_array(),
            fp.get_array(), nh, 1);
//    cout<<"d"<<endl;
    g_a*=net;
//	g_a->multiply_to_dot_onthis(net->get_array());
    g_b.set_value(e.get_array());
    g_b*=fp;
    g_b*=a;
//    cout<<"e"<<endl;
//	g_b->multiply_to_dot_onthis(fp->get_array());
//	g_b->multiply_to_dot_onthis(a->get_array());
    x_tar.transpose_matrix_onthis(x.get_array());
    g_w.multiply_matrix_to_matrix_onthis(g_b.get_array(),
            x_tar.get_array(), nh, 1, nx);
//    cout<<"f"<<endl;
    w_tar.transpose_matrix_onthis(w.get_array());
//    cout<<"ff"<<endl;
//    cout<<"g_x"<<g_x<<endl;
//    cout<<w_tar<<endl;
//    cout<<"g_b"<<g_b<<endl;
    g_x.multiply_matrix_to_matrix_onthis(w_tar.get_array(),
            g_b.get_array(), nx, nh, 1);
//    cout<<"fff"<<endl;
    prev_e.set_value(g_x.get_array());
	long double teta = 0.01;
//    cout<<"g"<<endl;
	if(learning){
        g_a*=(teta);
        g_b*=(teta);
        g_w*=(teta);
        g_a.low_from_max(1.0);
        g_b.low_from_max(1.0);
        g_w.low_from_max(1.0);
        g_a.up_from_min(-1.0);
        g_b.up_from_min(-1.0);
        g_w.up_from_min(-1.0);


        a+=(g_a.get_array());
        b+=(g_b.get_array());
        w+=(g_w.get_array());
	}
	return em;
}
void layer_simple::read_layer(ifstream * input){
	read_abw(input,a);
	read_abw(input,b);
	read_abw(input,w);
}
void layer_simple::print_layer(ofstream * output){
	print_abw(output,a);
	print_abw(output,b);
	print_abw(output,w);
}
