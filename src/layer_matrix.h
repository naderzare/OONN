/*
 * layer.h
 *
 *  Created on: Dec 19, 2016
 *      Author: nader
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include "matrix.h"
using namespace std;


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
class oldlayer {
public:
	int nx;
	int nh;
	matrix2D *b;
	matrix2D *a;
	matrix2D *w;
	matrix2D *w_tar;
	matrix2D *x;
	matrix2D *x_tar;
	matrix2D *net;
	matrix2D *anet;
	matrix2D *o;
	matrix2D *e;
	matrix2D *g_w;
	matrix2D *g_a;
	matrix2D *g_b;
	matrix2D *fp;
	matrix2D *g_x;

	matrix2D *wl;
	matrix2D *wl_tar;
	matrix2D *wu;
	matrix2D *wu_tar;
	matrix2D *al;
	matrix2D *au;
	matrix2D *bl;
	matrix2D *bu;
	matrix2D *netl;
	matrix2D *netu;
	matrix2D *anetl;
	matrix2D *anetu;
	matrix2D *fl;
	matrix2D *fu;
	matrix2D *fl_ismax;
	matrix2D *fl_ismin;
	matrix2D *fu_ismax;
	matrix2D *fu_ismin;
	matrix2D *fpl;
	matrix2D *fpu;
	matrix2D *ol;
	matrix2D *ou;
	matrix2D *g_wl;
	matrix2D *g_al;
	matrix2D *g_al_l;
	matrix2D *g_al_u;
	matrix2D *g_bl;
	matrix2D *g_bl_l;
	matrix2D *g_bl_u;
	matrix2D *g_wu;
	matrix2D *g_au;
	matrix2D *g_au_l;
	matrix2D *g_au_u;
	matrix2D *g_bu;
	matrix2D *g_bu_l;
	matrix2D *g_bu_u;
	matrix2D *g_xl;
	matrix2D *g_xu;
	matrix2D *el;
	matrix2D *eu;
public:
	enum function_type {
		line, sig2, sin, cos
	};
	enum layer_type {
		mlp, rough1, rough2
	};
	layer_type l_type;
	function_type f_type;
	oldlayer(int nnx, int nnh, layer_type layer_t, function_type function_t) {
		l_type = layer_t;
		f_type = function_t;
		nx = nnx;
		nh = nnh;

		x = new matrix2D(nx, 1);
		x_tar = new matrix2D(1, nx);
		a = new matrix2D(nh, 1);
		a->set_value_random();
		b = new matrix2D(nh, 1);
		b->set_value_random();
		w = new matrix2D(nh, nx);
		w->set_value_random();
		w->divide_to_num_onthis((long double) nx);
		w_tar = new matrix2D(nx, nh);
		net = new matrix2D(nh, 1);
		anet = new matrix2D(nh, 1);
		o = new matrix2D(nh, 1);
		e = new matrix2D(nh, 1);
		fp = new matrix2D(nh, 1);
		g_a = new matrix2D(nh, 1);
		g_b = new matrix2D(nh, 1);
		g_w = new matrix2D(nh, nx);
		g_x = new matrix2D(nx, 1);

		wl = (l_type == 2 ? new matrix2D(nh / 2, nx) : new matrix2D(nh, nx));
		wl->set_value_random();
		wl->divide_to_num_onthis((long double) nx);
		wu = (l_type == 2 ? new matrix2D(nh / 2, nx) : new matrix2D(nh, nx));
		wu->set_value_random();
		wu->divide_to_num_onthis((long double) nx);
		wl_tar =
				(l_type == 2 ? new matrix2D(nx, nh / 2) : new matrix2D(nx, nh));
		wu_tar =
				(l_type == 2 ? new matrix2D(nx, nh / 2) : new matrix2D(nx, nh));
		al = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		al->set_value_random();
		au = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		au->set_value_random();
		bl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		bl->set_value_random();
		bu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		bu->set_value_random();
		netl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		netu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		anetl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		anetu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fl_ismax =
				(l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fu_ismax =
				(l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fl_ismin =
				(l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fu_ismin =
				(l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fpl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		fpu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		ol = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		ou = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_al = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_al_l = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_al_u = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bl = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bl_l = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bl_u = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_wl = (l_type == 2 ? new matrix2D(nh / 2, nx) : new matrix2D(nh, nx));
		g_au = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_au_l = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_au_u = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bu = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bu_l = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_bu_u = (l_type == 2 ? new matrix2D(nh / 2, 1) : new matrix2D(nh, 1));
		g_wu = (l_type == 2 ? new matrix2D(nh / 2, nx) : new matrix2D(nh, nx));
		g_xl = new matrix2D(nx, 1);
		g_xu = new matrix2D(nx, 1);
		el = new matrix2D(nh / 2, 1);
		eu = new matrix2D(nh / 2, 1);
	}
	void set_x(long double **new_data) {
		x->set_value(new_data);
	}
	void set_x(matrix2D *new_data) {
		x->set_value(new_data);
	}

	void forward(matrix2D * output, bool debug = false) {
		switch (l_type) {
		case 0:
			forward_mlpd(output, debug);
			break;
		case 1:
			forward_rough1d(output, debug);
			break;
		case 2:
			forward_rough2d(output, debug);
			break;
		default:
			break;
		}
	}

	void forward_mlpd(matrix2D * output, bool debug = false) {
		net->multiply_matrix_to_matrix_onthis(w->get_array(), x->get_array(),
				nh, nx, 1);
		net->sum_whit_onthis(b->get_array());
		anet->multiply_dot_matrix_to_matrix_onthis(net->get_array(),
				a->get_array(), net->get_num_of_row(), net->get_num_of_col());
		o->function_matrix_onthis(anet->get_array(), (int) f_type);
		output->set_value(o->get_array());
	}
	void forward_rough1d(matrix2D * output, bool debug = false) {

		netl->multiply_matrix_to_matrix_onthis(wl->get_array(), x->get_array(),
				nh, nx, 1);
		netl->sum_whit_onthis(bl->get_array());
		netu->multiply_matrix_to_matrix_onthis(wu->get_array(), x->get_array(),
				nh, nx, 1);
		netu->sum_whit_onthis(bu->get_array());

		anetl->multiply_dot_matrix_to_matrix_onthis(netl->get_array(),
				al->get_array(), netl->get_num_of_row(),
				netl->get_num_of_col());
		anetu->multiply_dot_matrix_to_matrix_onthis(netu->get_array(),
				au->get_array(), netu->get_num_of_row(),
				netu->get_num_of_col());

		fl->function_matrix_onthis(anetl->get_array(), (int) f_type);
		fu->function_matrix_onthis(anetu->get_array(), (int) f_type);
		ol->min_matrix_and_matrix_onthis(fl->get_array(), fu->get_array());
		ou->max_matrix_and_matrix_onthis(fl->get_array(), fu->get_array());

		o->sum_matrix_whit_matrix_onthis(ol->get_array(), ou->get_array());
		o->divide_to_num_onthis(2.0);

		output->set_value(o->get_array());
	}
	void forward_rough2d(matrix2D * output, bool debug = false) {


		netl->multiply_matrix_to_matrix_onthis(wl->get_array(), x->get_array(),
				nh/2, nx, 1);
		netl->sum_whit_onthis(bl->get_array());
		netu->multiply_matrix_to_matrix_onthis(wu->get_array(), x->get_array(),
				nh/2, nx, 1);
		netu->sum_whit_onthis(bu->get_array());

		anetl->multiply_dot_matrix_to_matrix_onthis(netl->get_array(),
				al->get_array(), netl->get_num_of_row(),
				netl->get_num_of_col());
		anetu->multiply_dot_matrix_to_matrix_onthis(netu->get_array(),
				au->get_array(), netu->get_num_of_row(),
				netu->get_num_of_col());

		fl->function_matrix_onthis(anetl->get_array(), (int) f_type);
		fu->function_matrix_onthis(anetu->get_array(), (int) f_type);
		fl_ismax->are_max_first_matrix_onthis(fl->get_array(), fu->get_array());
		fu_ismax->are_max_first_matrix_onthis(fu->get_array(), fl->get_array());
		fl_ismin->are_max_first_matrix_onthis(fl->get_array(), fu->get_array());
		fl_ismin->are_max_first_matrix_onthis(fu->get_array(), fl->get_array());

		ol->min_matrix_and_matrix_onthis(fl->get_array(), fu->get_array());
		ou->max_matrix_and_matrix_onthis(fl->get_array(), fu->get_array());

		o->decussate_from_matrix_and_matrix_onthis(ol->get_array(),
				ou->get_array());

		output->set_value(o->get_array());
	}
	long double learn(matrix2D * e, matrix2D * prev_e, bool debug = false, bool learning = true) {

		switch (l_type) {
		case 0:
			return learn_mlpd(e, prev_e, debug,learning);
		case 1:
			return learn_rough1d(e, prev_e, debug,learning);
		case 2:
			return learn_rough2d(e, prev_e, debug,learning);
		default:
			break;
		}
		return 0;

	}

	long double learn_mlpd(matrix2D * er, matrix2D * prev_e,
			bool debug = false,bool learning = true) {

		e->set_value(er->get_array());
		long double em = e->get_sum_abs();
		fp->functionp_matrix_onthis(anet->get_array(), (int) f_type);
		g_a->multiply_dot_matrix_to_matrix_onthis(e->get_array(),
				fp->get_array(), nh, 1);
		g_a->multiply_to_dot_onthis(net->get_array());
		g_b->set_value(e->get_array());
		g_b->multiply_to_dot_onthis(fp->get_array());
		g_b->multiply_to_dot_onthis(a->get_array());
		x_tar->transpose_matrix_onthis(x->get_array());
		g_w->multiply_matrix_to_matrix_onthis(g_b->get_array(),
				x_tar->get_array(), nh, 1, nx);
		w_tar->transpose_matrix_onthis(w->get_array());
		g_x->multiply_matrix_to_matrix_onthis(w_tar->get_array(),
				g_b->get_array(), nx, nh, 1);
		prev_e->set_value(g_x->get_array());
		long double teta = 0.01;
		if(learning){
			g_a->multiply_to_num_onthis(teta);
			g_b->multiply_to_num_onthis(teta);
			g_w->multiply_to_num_onthis(teta);
			g_a->low_from_max(1.0);
			g_b->low_from_max(1.0);
			g_w->low_from_max(1.0);
			g_a->up_from_min(-1.0);
			g_b->up_from_min(-1.0);
			g_w->up_from_min(-1.0);


			a->sum_whit_onthis(g_a->get_array());
			b->sum_whit_onthis(g_b->get_array());
			w->sum_whit_onthis(g_w->get_array());
		}
		return em;
	}
	long double learn_rough1d(matrix2D * er, matrix2D * prev_e, bool debug =
			false,bool learning = true) {

		e->set_value(er->get_array());
		long double em = e->get_sum_abs();

		fpl->functionp_matrix_onthis(anetl->get_array(), (int) f_type);
		fpu->functionp_matrix_onthis(anetu->get_array(), (int) f_type);

		g_al->multiply_dot_matrix_to_matrix_onthis(e->get_array(),
				fpl->get_array(), nh, 1);
		g_al->multiply_to_dot_onthis(netl->get_array());

		g_au->multiply_dot_matrix_to_matrix_onthis(e->get_array(),
				fpu->get_array(), nh, 1);
		g_au->multiply_to_dot_onthis(netu->get_array());

		g_bl->set_value(e->get_array());
		g_bl->multiply_to_dot_onthis(fpl->get_array());
		g_bl->multiply_to_dot_onthis(al->get_array());
		g_bu->set_value(e->get_array());
		g_bu->multiply_to_dot_onthis(fpu->get_array());
		g_bu->multiply_to_dot_onthis(au->get_array());

		x_tar->transpose_matrix_onthis(x->get_array());
		g_wl->multiply_matrix_to_matrix_onthis(g_bl->get_array(),
				x_tar->get_array(), nh, 1, nx);
		g_wu->multiply_matrix_to_matrix_onthis(g_bu->get_array(),
				x_tar->get_array(), nh, 1, nx);

		wl_tar->transpose_matrix_onthis(wl->get_array());
		wu_tar->transpose_matrix_onthis(wu->get_array());

		g_xl->multiply_matrix_to_matrix_onthis(wl_tar->get_array(),
				g_bl->get_array(), nx, nh, 1);
		g_xu->multiply_matrix_to_matrix_onthis(wu_tar->get_array(),
				g_bu->get_array(), nx, nh, 1);

		g_x->sum_matrix_whit_matrix_onthis(g_xl->get_array(),
				g_xu->get_array());
		prev_e->set_value(g_x->get_array());

		long double teta = 0.01;
		if(learning){
			g_al->multiply_to_num_onthis(teta);
			g_au->multiply_to_num_onthis(teta);
			g_bl->multiply_to_num_onthis(teta);
			g_bu->multiply_to_num_onthis(teta);
			g_wl->multiply_to_num_onthis(teta);
			g_wu->multiply_to_num_onthis(teta);
			g_al->low_from_max(1.0);
			g_au->low_from_max(1.0);
			g_bl->low_from_max(1.0);
			g_bu->low_from_max(1.0);
			g_wl->low_from_max(1.0);
			g_wu->low_from_max(1.0);
			g_al->up_from_min(-1.0);
			g_au->up_from_min(-1.0);
			g_bl->up_from_min(-1.0);
			g_bu->up_from_min(-1.0);
			g_wl->up_from_min(-1.0);
			g_wu->up_from_min(-1.0);

			al->sum_whit_onthis(g_al->get_array());
			au->sum_whit_onthis(g_au->get_array());
			bl->sum_whit_onthis(g_bl->get_array());
			bu->sum_whit_onthis(g_bu->get_array());
			wl->sum_whit_onthis(g_wl->get_array());
			wu->sum_whit_onthis(g_wu->get_array());
		}
		return em;
	}
	long double learn_rough2d(matrix2D * er, matrix2D * prev_e, bool debug =
			false,bool learning = true) {

		e->set_value(er->get_array());
		long double em = e->get_sum_abs();

		e->decussate_this_to_matrix_and_matrix(el->get_array(),
				eu->get_array());
		fpl->functionp_matrix_onthis(anetl->get_array(), (int) f_type);
		fpu->functionp_matrix_onthis(anetu->get_array(), (int) f_type);

		g_al_l->multiply_dot_matrix_to_matrix_onthis(el->get_array(),
				fpl->get_array(), nh/2, 1);
		g_al_l->multiply_to_dot_onthis(netl->get_array());
		g_al_l->multiply_to_dot_onthis(fl_ismin->get_array());
		g_al_u->multiply_dot_matrix_to_matrix_onthis(eu->get_array(),
				fpl->get_array(), nh/2, 1);
		g_al_u->multiply_to_dot_onthis(netl->get_array());
		g_al_u->multiply_to_dot_onthis(fl_ismax->get_array());
		g_al->sum_matrix_whit_matrix_onthis(g_al_l->get_array(),
				g_al_u->get_array());

		g_au_l->multiply_dot_matrix_to_matrix_onthis(el->get_array(),
				fpu->get_array(), nh/2, 1);
		g_au_l->multiply_to_dot_onthis(netu->get_array());
		g_au_l->multiply_to_dot_onthis(fu_ismin->get_array());
		g_au_u->multiply_dot_matrix_to_matrix_onthis(eu->get_array(),
				fpu->get_array(), nh/2, 1);
		g_au_u->multiply_to_dot_onthis(netu->get_array());
		g_au_u->multiply_to_dot_onthis(fu_ismax->get_array());

		g_au->sum_matrix_whit_matrix_onthis(g_au_l->get_array(),
				g_au_u->get_array());

		g_bl_l->set_value(el->get_array());
		g_bl_l->multiply_to_dot_onthis(fpl->get_array());
		g_bl_l->multiply_to_dot_onthis(al->get_array());
		g_bl_l->multiply_to_dot_onthis(fl_ismin);
		g_bl_u->set_value(eu->get_array());
		g_bl_u->multiply_to_dot_onthis(fpl->get_array());
		g_bl_u->multiply_to_dot_onthis(al->get_array());
		g_bl_u->multiply_to_dot_onthis(fl_ismax);
		g_bu_l->set_value(el->get_array());
		g_bu_l->multiply_to_dot_onthis(fpu->get_array());
		g_bu_l->multiply_to_dot_onthis(au->get_array());
		g_bu_l->multiply_to_dot_onthis(fu_ismin);
		g_bu_u->set_value(eu->get_array());
		g_bu_u->multiply_to_dot_onthis(fpu->get_array());
		g_bu_u->multiply_to_dot_onthis(au->get_array());
		g_bu_u->multiply_to_dot_onthis(fu_ismax);

		g_bl->sum_matrix_whit_matrix_onthis(g_bl_l->get_array(),g_bl_u->get_array());
		g_bu->sum_matrix_whit_matrix_onthis(g_bu_l->get_array(),g_bu_u->get_array());

		x_tar->transpose_matrix_onthis(x->get_array());
		g_wl->multiply_matrix_to_matrix_onthis(g_bl->get_array(),
				x_tar->get_array(), nh/2, 1, nx);
		g_wu->multiply_matrix_to_matrix_onthis(g_bu->get_array(),
				x_tar->get_array(), nh/2, 1, nx);

		wl_tar->transpose_matrix_onthis(wl->get_array());
		wu_tar->transpose_matrix_onthis(wu->get_array());

		g_xl->multiply_matrix_to_matrix_onthis(wl_tar->get_array(),
				g_bl->get_array(), nx, nh/2, 1);
		g_xu->multiply_matrix_to_matrix_onthis(wu_tar->get_array(),
				g_bu->get_array(), nx, nh/2, 1);

		g_x->sum_matrix_whit_matrix_onthis(g_xl->get_array(),
				g_xu->get_array());
		prev_e->set_value(g_x->get_array());

		long double teta = 0.01;

		if(learning){
			g_al->multiply_to_num_onthis(teta);
			g_au->multiply_to_num_onthis(teta);
			g_bl->multiply_to_num_onthis(teta);
			g_bu->multiply_to_num_onthis(teta);
			g_wl->multiply_to_num_onthis(teta);
			g_wu->multiply_to_num_onthis(teta);
			g_al->low_from_max(1.0);
			g_au->low_from_max(1.0);
			g_bl->low_from_max(1.0);
			g_bu->low_from_max(1.0);
			g_wl->low_from_max(1.0);
			g_wu->low_from_max(1.0);
			g_al->up_from_min(-1.0);
			g_au->up_from_min(-1.0);
			g_bl->up_from_min(-1.0);
			g_bu->up_from_min(-1.0);
			g_wl->up_from_min(-1.0);
			g_wu->up_from_min(-1.0);


			al->sum_whit_onthis(g_al->get_array());
			au->sum_whit_onthis(g_au->get_array());
			bl->sum_whit_onthis(g_bl->get_array());
			bu->sum_whit_onthis(g_bu->get_array());
			wl->sum_whit_onthis(g_wl->get_array());
			wu->sum_whit_onthis(g_wu->get_array());
		}
		return em;
	}
	void print_layer(ofstream * output){
		switch (l_type) {
		case 0:
			print_layer_mlpd(output);
			break;
		case 1:
			print_layer_roughd(output);
			break;
		case 2:
			print_layer_roughd(output);
			break;
		default:
			break;
		}
	}
	void print_layer_mlpd(ofstream * output){
		print_abw(output,a);
		print_abw(output,b);
		print_abw(output,w);
	}
	void print_layer_roughd(ofstream * output){
		print_abw(output,al);
		print_abw(output,au);
		print_abw(output,bl);
		print_abw(output,bu);
		print_abw(output,wl);
		print_abw(output,wu);
	}
	void print_abw(ofstream * output,matrix2D * abw){
		for(int i=0;i<abw->get_num_of_row();i++){
			for(int j=0;j<abw->get_num_of_col();j++){
				(*output)<<(abw->get_value(i,j));
				(*output)<<endl;
			}
		}
	}

	void read_layer(ifstream * input){
		switch (l_type) {
		case 0:
			read_layer_mlpd(input);
			break;
		case 1:
			read_layer_roughd(input);
			break;
		case 2:
			read_layer_roughd(input);
			break;
		default:
			break;
		}
	}
	void read_layer_mlpd(ifstream * input){
		read_abw(input,a);
		read_abw(input,b);
		read_abw(input,w);
	}
	void read_layer_roughd(ifstream * input){
		read_abw(input,al);
		read_abw(input,au);
		read_abw(input,bl);
		read_abw(input,bu);
		read_abw(input,wl);
		read_abw(input,wu);
	}
	void read_abw(ifstream * input,matrix2D * abw){
		for(int i=0;i<abw->get_num_of_row();i++){
			for(int j=0;j<abw->get_num_of_col();j++){
				long double value;
				(*input)>>value;
				abw->set_value(i,j,value);
			}
		}
	}
};

#endif /* LAYER_H_ */
