/***************************************************************************************/
/*****************             			LIBRARIES                      *****************/
/***************************************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <cstdlib> //contains sublib rand => srand() - changes seed
#include <cstring>

#include <limits.h>//INT_MAX/MIN, LONG_MAX/MIN...

#include <time.h>
#include <math.h>
#include <stdbool.h> //booleans

//CLASS
#include <vector> 
#include <string>


#define square(x) ((x)*(x))

using namespace std;

/***************************************************************************************/
/*****************             			GRAPHICS                       *****************/
/***************************************************************************************/

char* graph_strtochar(string A){
	char * ans = (char*)malloc((A.size()+1)*sizeof(char));
	int i;
	for (i = 0; i <= A.size(); i++){
		ans[i] = A[i];
	}
	return (ans);
}

string graph_genrandcolor(){
	string COLOR[] = {
		"#ff0000", "#ff8000", "#ffff00", "#bfff00", "#40ff00",
		"#00ffff", "#0040ff", "#bf00ff", "#ff00ff", "#ff0080"
		};
	int t = rand()%(sizeof(COLOR)/sizeof(COLOR[0]));

	return (COLOR[t]);
}

typedef struct curve{
	string title;
	string color;

	bool iseq;

	bool isdata;
	string dataname;

	vector <string> shape;

} Curve;

class Graph{
private:

	string tt;

	string xtt = "x";
	string ytt = "y";
	string ztt = "z";
	
	string xrg;
	string yrg;
	string zrg;

	bool xgd = true;
	bool ygd = true;
	bool zgd = true;

	int dim = 2;


	bool withxlabel = false;
	bool withylabel = false;
	bool withzlabel = false;

	bool withxrange = false;
	bool withyrange = false;
	bool withzrange = false;

	vector <Curve> vcurves;

	vector <string> vcommands;

	bool randomized = false;

public:

	void randomize(){
		if(!randomized){
			srand(time(NULL));
			randomized = true;
		}
	}

	bool curvexist(string t){
		for (int i = 0; i < vcurves.size(); i++){
			if(t == vcurves[i].title){
				return (true);
			}
		}
		return (false);
	}

	//prototypes for adding curve:

	//1.1 t: string for curve name; func: string whitch representes a function, e.g. "sqrt(x)+x^3" 

	void addcurve(string t, string func){ //equation
		if(curvexist(t)){
			cout << "\033[1;31mWARNING:\033[0m" << "'" << t << "'" << " ambiguous name." << endl;
		}

		Curve curve;
		(curve.title) = t;

		//setting a random color to the curve
		randomize();
		curve.color = graph_genrandcolor();
		curve.iseq = true;

		string temp;

		temp = func + " ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "with lines ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "title '" + curve.title;
		temp += "' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "linecolor rgb '" + curve.color;
		temp += "' lw 1.6 ";
		(curve.shape).push_back(temp);
		temp.clear();

		vcurves.push_back(curve);
	
	}

	//1.2 t: string for curve name; X, Y: double arrays whicth contains 'nelemes' ponts to plot" 

	void addcurve(string t, double * X, double * Y, int nelems){ //data
		if(curvexist(t)){
			cout << "\033[1;31mWARNING:\033[0m" << "'" << t << "'" << " ambiguous name." << endl;
		}

		Curve curve;
		(curve.dataname) = t;
		(curve.title) = t;

		randomize();
		curve.color = graph_genrandcolor();
		curve.isdata = true;

		string temp;

		temp = "'" + curve.dataname;
		temp += ".data' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "with linespoints ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "title '" + curve.title;
		temp += "' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "pt " + to_string(rand()%15) + " ps 1 lt 1 lw 1.6 ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "linecolor rgb '" + curve.color;
		temp += "'";
		(curve.shape).push_back(temp);
		temp.clear();

		vcurves.push_back(curve);

		char *strtemp = graph_strtochar(curve.dataname + ".data");
		FILE * data = fopen(strtemp, "w");

		for(int i = 0; i < nelems; i++){
			fprintf(data, "%lf %lf \n", X[i], Y[i]); //Write the data to a temporary file
	    }
	    free(strtemp);
	    fclose(data);
	}

	//1.3 t: string for curve name; point: a vector of double pairs for the points that will be plot" 

	void addcurve(string t, vector <pair<double, double>> point){ //data
		if(curvexist(t)){
			cout << "\033[1;31mWARNING:\033[0m" << "'" << t << "'" << " ambiguous name." << endl;
		}

		Curve curve;
		(curve.dataname) = t;
		(curve.title) = t;

		randomize();
		curve.color = graph_genrandcolor();
		curve.isdata = true;

		string temp;

		temp = "'" + curve.dataname;
		temp += ".data' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "with linespoints ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "title '" + curve.title;
		temp += "' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "pt " + to_string(rand()%15) + " ps 1 lt 1 lw 1.6 ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "linecolor rgb '" + curve.color;
		temp += "'";
		(curve.shape).push_back(temp);
		temp.clear();

		vcurves.push_back(curve);

		char *strtemp = graph_strtochar(curve.dataname + ".data");
		FILE * data = fopen(strtemp, "w");
			for(auto it = point.begin(); it != point.end(); it++){
			fprintf(data, "%lf %lf \n", (*it).first, (*it).second); //Write the data to a temporary file
	    }
	    free(strtemp);
	    fclose(data);
	}

	//1.4 t: string for curve name; point: a vector whitch has a pair for a pair and a double; the inner vector stands for X and Y, and the outter double, Z axis.  

	void addcurve(string t, vector <pair<pair<double, double>, double>> point){ //data
		if(curvexist(t)){
			cout << "\033[1;31mWARNING:\033[0m" << "'" << t << "'" << " ambiguous name." << endl;
		}

		Curve curve;
		(curve.dataname) = t;
		(curve.title) = t;

		randomize();
		curve.color = graph_genrandcolor();
		curve.isdata = true;

		string temp;

		temp = "'" + curve.dataname;
		temp += ".data' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "with linespoints ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "ti '" + curve.title;
		temp += "' ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "pt " + to_string(rand()%15) + " ps 1 lt 1 lw 1.6 ";
		(curve.shape).push_back(temp);
		temp.clear();

		temp = "linecolor rgb '" + curve.color;
		temp += "'";
		(curve.shape).push_back(temp);
		temp.clear();

		vcurves.push_back(curve);

		char *strtemp = graph_strtochar(curve.dataname + ".data");
		FILE * data = fopen(strtemp, "w");
			for(auto it = point.begin(); it != point.end(); it++){
			fprintf(data, "%lf %lf %lf\n", ((*it).first).first, ((*it).first).second, (*it).second); //Write the data to a temporary file
	    }
	    free(strtemp);
	    fclose(data);
	}

	void title(string t){
		tt = t;
	}

	void dimension(int d){
		dim = d;
	}

	void xlabel(string t){
		withxlabel = true;
		xtt = t;
	}

	void ylabel(string t){
		withylabel = true;
		ytt = t;
	}

	void zlabel(string t){
		withzlabel = true;
		ztt = t;
	}

	void xrange(pair <double, double> r){
		withxrange = true;
		xrg = "[" + to_string(r.first);
		xrg += ":";
		xrg += to_string(r.second);
		xrg += "]";
	}

	void yrange(pair <double, double> r){
		withyrange = true;
		yrg = "[" + to_string(r.first);
		yrg += ":";
		yrg += to_string(r.second);
		yrg += "]";
	}

	void zrange(pair <double, double> r){
		withzrange = true;
		zrg = "[" + to_string(r.first);
		zrg += ":";
		zrg += to_string(r.second);
		zrg += "]";
	}

	void commands(){
		vcommands.clear();
		vcommands.push_back("set title '" + tt + "'; ");
		if(xgd){
			vcommands.push_back("set grid xtics; ");
		}
		if(withxlabel){
			vcommands.push_back("set xlabel '" + xtt + "'; show xlabel; ");
		}
		else{
			vcommands.push_back("set xlabel 'x'; ");
		}
		if(ygd){
			vcommands.push_back("set grid ytics; ");
		}
		if(withylabel){
			vcommands.push_back("set ylabel '" + ytt + "'; show ylabel; ");
		}
		else{
			vcommands.push_back("set ylabel 'y'; ");
		}
		if(zgd){
			vcommands.push_back("set grid ztics; ");
		}
		if(withzlabel){
			vcommands.push_back("set zlabel '" + ztt + "'; show zlabel; ");
		}
		else{
			vcommands.push_back("set zlabel 'z'; ");
		}

		if(withxrange){
			vcommands.push_back("set xrange " + xrg + "; ");
		}
		if(withyrange){
			vcommands.push_back("set yrange " + yrg + "; ");
		}
		if(withzrange){
			vcommands.push_back("set zrange " + zrg + "; ");
		}
		vcommands.push_back("set style line 11 lc rgb '#505050' lt 1; ");
		vcommands.push_back("set border 3 back ls 11; ");
		vcommands.push_back("set tics nomirror; ");

		for (int i = 0; i < vcurves.size(); i++){
			string temp;
			for (int j = 0; j < (vcurves[i].shape).size(); j++){
				temp += vcurves[i].shape[j];
			}
			if(i == 0){ //first function
				string sd;
				if(dim == 3){
					sd = "splot ";
				}
				else{
					sd = "plot ";
				}
				if(vcurves.size() > 1){
					vcommands.push_back(sd + temp + ", ");
				}
				else{
					vcommands.push_back(sd + temp + "\n");
				}
			}
			else if(i == vcurves.size()-1){ //last function
				vcommands.push_back(temp + "\n");
			}
			else{ //other function
				vcommands.push_back(temp + ", ");
			}
		}
	}

	void xgrid(bool withgrid){
		if(withgrid){
			xgd = true;
		}
		else{
			xgd = false;
		}
	}

	void ygrid(bool withgrid){
		if(withgrid){
			ygd = true;
		}
		else{
			ygd = false;
		}
	}

	void zgrid(bool withgrid){
		if(withgrid){
			zgd = true;
		}
		else{
			zgd = false;
		}
	}

	void plot(){
		commands();
		FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
		for (int i = 0; i < vcommands.size(); i++){
			char* strtemp = graph_strtochar(vcommands[i]);
	    	fprintf(gnuplotPipe, "%s", strtemp); //Send commands to gnuplot one by one.
	    	free(strtemp);
	    }
	    pclose(gnuplotPipe);
	}

};