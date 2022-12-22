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
	//��������� �������� ������ � �����������
	vector<cmplx> RealToCmplx(vector<double>& data);

	//������� ������� ������ (���������)
	vector<cmplx>CreateSignal(double A, double f, double fi);
	//������� ������� ������ (���������)
	vector<double> Sgn::CreateRealSignal(double A, double f, double y);


	//��������� ���
	vector<cmplx> AddNoise(vector<cmplx>& data, double nl);
	//��������� ���
	vector<double> Sgn::AddNoise(vector<double>& data, double nl);
	//������� ������� ���
	vector<double> generateNoiseBasics();
	//������� ������� ����������� �������
	double CalcE(vector<cmplx>& data);
	//������� ������� ����������� �������
	double CalcE(vector<double>& data);


	//������� ���
	vector<double>CreateSPD(vector<cmplx> data);


	//���������� ��������� �������� ����� ������� � �������� �������
	vector<double>GetSubVector(vector<double>& data, int pos, int len);
	//��������� ������ �� ������������� ����
	vector<vector<double>> RectWindow(vector<double>& data);
	//����������� ����
	vector<vector<double>> Sgn::TriangleWindow(vector<double>& data);
	//������������� ���� ��� ����������
	vector<vector<double>> Sgn::OverlappingRectWindow(vector<double>& data);



	//id ����������� �������� � �������
	int Max(vector<double>& data);
	//���������� ������� �� id
	double CalcF(vector<double>& data);
	//���������� ������� �� id
	double CalcFreqSPD(vector<double> &data);
	//���������� ������� �� id
	double CalcFreqRect(vector<double>& data);
	//���������� ������� �� id
	double CalcFreqTrian(vector<double>& data);
	//���������� ������� �� id
	double CalcFreqRofl(vector<double>& data);


	double CalcStats(vector < vector<double>>& data);

	//��������� ������ �������� � ���� ������
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
	//�������� ������������ ��������� �������� �� ����
	void GenerateStatsOnce();
	void GenerateStats();
};