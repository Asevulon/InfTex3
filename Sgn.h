#pragma once
#include"Drawer.h"
#include"cmplx.h"
#include<thread>
const double pi = 4 * atan(1);


struct package2
{
	vector<double>data1;
	vector<double>data2;
	package2() {}
	package2(vector<double>d1, vector<double>d2):data1(d1),data2(d2) {}
};
struct package4
{
	vector<double>data1;
	vector<double>data2;
	vector<double>data3;
	vector<double>data4;
	package4() {}
	package4(vector<double>d1, vector<double>d2, vector<double>d3, vector<double>d4) :data1(d1), data2(d2), data3(d3), data4(d4) {}
};


struct SinParam
{
	double A = 0;
	double f = 0;
	double y = 0;
};


class Sgn
{
private:
	//параметры синусоиды
	SinParam s;
	//число точек
	int N;
	//частота дискретизации
	double fd;
	//начальный уровень шума
	double start_noise_level;
	//конечный уровень шума
	double final_noise_level;
	//число шагов по шуму
	int steps;
	//ширина окна
	int wlen;
	//количество элементов выборок
	int gennum;


	Drawer sgn_drawer;
	Drawer spd_drawer;
	Drawer disp_drawer;
protected:
	//возвращает вектор реальной части
	vector<double> GetReal(vector<cmplx>& data);


	//создает базовый сигнал (синусоида)
	vector<cmplx>CreateSignal(double A, double f, double fi);


	//добавл€ет шум
	vector<cmplx> addNoise(vector<cmplx>& data, double nl);
	//создает базовый шум
	vector<double> generateNoiseBasics();
	//считает энергию переданного сигнала
	double CalcE(vector<cmplx>& data);
	//считает энергию переданного сигнала
	double CalcE(vector<double>& data);

	//считает —ѕћ
	vector<double>CreateSPD(vector<cmplx> data);
	//пр€моугольное окно
	vector<double> RectWindow(vector<double>& data);
	//треугольное окно
	vector<double> TriangleWindow(vector<double>& data);
	//пр€моугольное окно без перекрыти€
	vector<double> RoflRectWindow(vector<double>& data);


	//id наибольшего значени€ в векторе
	int Max(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqSPD(vector<double> &data);
	//¬озвращает частоту по id
	double CalcFreqRect(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqTrian(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqRofl(vector<double>& data);


	
public:
	void SetN(int n);
	void SetFD(double FD);
	void SetStartNoiseLevel(double nl);
	void SetFinalNoiseLevel(double nl);
	void SetNoiseSteps(int st);
	void SetWlen(int WLEN);
	void SetGenNum(int GN);
	void SetSinParam(double a, double ff, double yy);


	void SetSngDrwHWND(HWND hWnd);
	void SetSpdDrwHWND(HWND hWnd);
	void SetDispDrwHWND(HWND hWnd);
	void Redraw();


	void test();
	//проводит исследование дисперсии смещени€ от шума
	void GenerateStatsOnce();
	void GenerateStats();

};