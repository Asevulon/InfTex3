#pragma once
#include"Drawer.h"
#include"cmplx.h"
#include<thread>
const double pi = 4 * atan(1);


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
	//переводит реальный сигнал в комплексный
	vector<cmplx> RealToCmplx(vector<double>& data);

	//создает базовый сигнал (синусоида)
	vector<cmplx>CreateSignal(double A, double f, double fi);
	//создает базовый сигнал (синусоида)
	vector<double> Sgn::CreateRealSignal(double A, double f, double y);


	//добавл€ет шум
	vector<cmplx> AddNoise(vector<cmplx>& data, double nl);
	//добавл€ет шум
	vector<double> Sgn::AddNoise(vector<double>& data, double nl);
	//создает базовый шум
	vector<double> generateNoiseBasics();
	//считает энергию переданного сигнала
	double CalcE(vector<cmplx>& data);
	//считает энергию переданного сигнала
	double CalcE(vector<double>& data);


	//считает —ѕћ
	vector<double>CreateSPD(vector<cmplx> data);


	//возвращает субвектор заданной длины начина€ с заданной позиции
	vector<double>GetSubVector(vector<double>& data, int pos, int len);
	//–азрезает сигнал на пр€моугольные окна
	vector<vector<double>> RectWindow(vector<double>& data);
	//треугольное окно
	vector<vector<double>> Sgn::TriangleWindow(vector<double>& data);
	//пр€моугольное окно без перекрыти€
	vector<vector<double>> Sgn::OverlappingRectWindow(vector<double>& data);



	//id наибольшего значени€ в векторе
	int Max(vector<double>& data);
	//¬озвращает частоту по id
	double CalcF(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqSPD(vector<double> &data);
	//¬озвращает частоту по id
	double CalcFreqRect(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqTrian(vector<double>& data);
	//¬озвращает частоту по id
	double CalcFreqRofl(vector<double>& data);


	double CalcStats(vector < vector<double>>& data);

	//переводит вектор векторов в один вектор
	vector<double> ToOne(vector < vector<double>>& data);
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