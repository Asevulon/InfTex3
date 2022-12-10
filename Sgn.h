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
	//��������� ���������
	SinParam s;
	//����� �����
	int N;
	//������� �������������
	double fd;
	//��������� ������� ����
	double start_noise_level;
	//�������� ������� ����
	double final_noise_level;
	//����� ����� �� ����
	int steps;
	//������ ����
	int wlen;
	//���������� ��������� �������
	int gennum;


	Drawer sgn_drawer;
	Drawer spd_drawer;
	Drawer disp_drawer;
protected:
	//���������� ������ �������� �����
	vector<double> GetReal(vector<cmplx>& data);


	//������� ������� ������ (���������)
	vector<cmplx>CreateSignal(double A, double f, double fi);


	//��������� ���
	vector<cmplx> addNoise(vector<cmplx>& data, double nl);
	//������� ������� ���
	vector<double> generateNoiseBasics();
	//������� ������� ����������� �������
	double CalcE(vector<cmplx>& data);
	//������� ������� ����������� �������
	double CalcE(vector<double>& data);

	//������� ���
	vector<double>CreateSPD(vector<cmplx> data);
	//������������� ����
	vector<double> RectWindow(vector<double>& data);
	//����������� ����
	vector<double> TriangleWindow(vector<double>& data);
	//������������� ���� ��� ����������
	vector<double> RoflRectWindow(vector<double>& data);


	//id ����������� �������� � �������
	int Max(vector<double>& data);
	//���������� ������� �� id
	double CalcFreqSPD(vector<double> &data);
	//���������� ������� �� id
	double CalcFreqRect(vector<double>& data);
	//���������� ������� �� id
	double CalcFreqTrian(vector<double>& data);
	//���������� ������� �� id
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
	//�������� ������������ ��������� �������� �� ����
	void GenerateStatsOnce();
	void GenerateStats();

};