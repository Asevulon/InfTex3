#include"pch.h"
#include"Sgn.h"


void Sgn::SetN(int n)
{
	N = n;
}
void Sgn::SetFD(double FD)
{
	fd = FD;
}
void Sgn::SetStartNoiseLevel(double nl)
{
	start_noise_level = nl;
}
void Sgn::SetFinalNoiseLevel(double nl)
{
	final_noise_level = nl;
}
void Sgn::SetNoiseSteps(int st)
{
	steps = st;
}
void Sgn::SetWlen(int WLEN)
{
	if (WLEN % 2 != 0)WLEN++;
	wlen = WLEN;
}
void Sgn::SetGenNum(int GN)
{
	gennum = GN;
}
void Sgn::SetSinParam(double a, double ff, double yy)
{
	s.A = a;
	s.f = ff;
	s.y = yy;
}


void Sgn::SetSngDrwHWND(HWND hWnd)
{
	sgn_drawer.Create(hWnd);
}
void Sgn::SetSpdDrwHWND(HWND hWnd)
{
	spd_drawer.Create(hWnd);
}
void Sgn::SetDispDrwHWND(HWND hWnd)
{
	disp_drawer.Create(hWnd);
}
void Sgn::Redraw()
{
	sgn_drawer.Redraw();
	spd_drawer.Redraw();
	disp_drawer.Redraw();
}


vector<double> Sgn::GetReal(vector<cmplx>& data)
{
	vector<double> res;
	for (auto& item : data)
		res.push_back(item.re);
	return res;
}


vector<cmplx> Sgn::CreateSignal(double A, double f, double y)
{
	vector<cmplx> res;
	for (int i = 0; i < N; i++)
	{
		res.push_back(cmplx(A * sin(2 * pi * f * i / fd + y), 0));
	}
	return res;
}


vector<cmplx> Sgn::addNoise(vector<cmplx>& data, double nl)
{
	vector<cmplx>res;


	vector<double>noise = generateNoiseBasics();


	double Es = CalcE(data);
	double En = CalcE(noise);
	double betta = sqrt(nl * Es / En);


	for (int i = 0; i < N; i++)
	{
		cmplx temp;
		temp.re = noise[i] * betta + data[i].re;
		res.push_back(temp);
	}


	return res;
}
vector<double> Sgn::generateNoiseBasics()
{


	vector<double> res;


	for (int i = 0; i < N; i++)
	{
		res.push_back(0);


		for (int g = 0; g < 12; g++)
		{
			res[i] += -1 + 2. * double(rand()) / RAND_MAX;
		}
	}


	return res;
}
double Sgn::CalcE(vector<cmplx>& data)
{
	double res = 0;
	for (auto& item : data)
		res += item.re * item.re;
	return res;
}
double Sgn::CalcE(vector<double>& data)
{
	double res = 0;
	for (auto& item : data)
		res += item * item;
	return res;
}


vector<double>Sgn::CreateSPD(vector<cmplx> data)
{
	fourea(N, data, -1);


	vector<double> res;
	for (auto& item : data)
		res.push_back(sqrt(item.re * item.re + item.im * item.im));
	return res;
}
vector<double> Sgn::RectWindow(vector<double>& data)
{
	vector<double> res;


	for (int i = wlen / 2; i < N - wlen/2; i++)
	{
		double temp = 0;
		for (int g = i - (wlen / 2); g < i + (wlen / 2); g++)
		{
			temp += data[g];
		}
		res.push_back(temp / wlen);
	}


	return res;
}
vector<double> Sgn::TriangleWindow(vector<double>& data)
{
	vector<double> res;


	for (int i = wlen / 2; i < N - wlen/2; i++)
	{
		double temp = 0;
		for (int g = i - wlen / 2; g < i + wlen / 2; g++)
		{
			temp += data[g] * (wlen - 2 * abs(i - g)) / float(N);
		}
		res.push_back(temp);
	}


	return res;
}
vector<double> Sgn::RoflRectWindow(vector<double>& data)
{
	vector<double> res;


	for (int i = wlen / 2; i < N - wlen; i+=wlen)
	{
		double temp = 0;
		for (int g = i - (wlen / 2); g < i + (wlen / 2); g++)
		{
			temp += data[g];
		}
		res.push_back(temp / wlen);
	}


	return res;
}


int Sgn::Max(vector<double>& data)
{
	int res = 0;
	int size = data.size() / 2;

	for (int i = 0; i < size; i++)
		if (data[res] < data[i])res = i;


	return res;
}


double Sgn::CalcFreqSPD(vector<double>& data)
{
	double res = Max(data) * fd / (N - 1);
	return res;
}
double Sgn::CalcFreqRect(vector<double>& data)
{
	double noiseconst = 0.8 * data[Max(data)];
	int left = 0;

	while (data[left] < noiseconst)
	{
		left++;
		if (left == data.size())
			return -1;
	}


	int right = left;

	while (data[right] > noiseconst)
	{
		right++;
		if (right == data.size())
			return -1;
	}


	int id = (left + right) / 2 + wlen / 2;
	return id * fd / (N - 1);
}
double Sgn::CalcFreqTrian(vector<double>& data)
{
	int id = ((wlen / 2) + Max(data));
	return id * fd / (N - 1);
}
double Sgn::CalcFreqRofl(vector<double>& data)
{
	int id = (wlen / 2 + Max(data) * wlen);
	return  id * fd / (N - 1);
}

void Sgn::GenerateStatsOnce()
{
	srand(time(NULL));


	vector<cmplx>signal = CreateSignal(s.A, s.f, s.y);
	vector <cmplx>nsignal = addNoise(signal, start_noise_level);
	sgn_drawer.DrawTwoSignals(GetReal(signal), GetReal(nsignal), fd);

	vector<double> spd = CreateSPD(nsignal);
	vector<double> rectspd = RectWindow(spd);
	vector<double>trianspd = TriangleWindow(spd);
	vector<double>roflspd = RoflRectWindow(spd);
	spd_drawer.DrawFourSpecters(spd, rectspd, trianspd, roflspd, fd, wlen);


	double rectstat = 0;
	double trianstat = 0;
	double roflstat = 0;
	for (int i = 0; i < gennum; i++)
	{
		nsignal = addNoise(signal, start_noise_level);
		
		spd = CreateSPD(nsignal);
		rectspd = RectWindow(spd);
		trianspd = TriangleWindow(spd);
		roflspd = RoflRectWindow(spd);

		double rectf = CalcFreqRect(rectspd);
		double trianf = CalcFreqTrian(trianspd);
		double roflf = CalcFreqRofl(roflspd);

		rectstat += (s.f - rectf) * (s.f - rectf);
		trianstat += (s.f - trianf) * (s.f - trianf);
		roflstat += (s.f - roflf) * (s.f - roflf);
	}


	rectstat = sqrt(rectstat / gennum);
	trianstat = sqrt(trianstat / gennum);
	roflstat = sqrt(roflstat / gennum);


	disp_drawer.DrawDispersionOnce(rectstat, trianstat, roflstat, start_noise_level);
}
void Sgn::GenerateStats()
{
	srand(time(NULL));


	vector<cmplx>signal = CreateSignal(s.A, s.f, s.y);
	vector <cmplx>nsignal = addNoise(signal, start_noise_level);
	sgn_drawer.DrawTwoSignals(GetReal(signal), GetReal(nsignal), fd);

	vector<double> spd = CreateSPD(nsignal);
	vector<double> rectspd = RectWindow(spd);
	vector<double>trianspd = TriangleWindow(spd);
	vector<double>roflspd = RoflRectWindow(spd);
	spd_drawer.DrawFourSpecters(spd, rectspd, trianspd, roflspd, fd, wlen);

	vector<double>rest;
	vector<double>trst;
	vector<double>rost;
	

	double steplen = (final_noise_level - start_noise_level) / (steps - 1);
	for (double nl = start_noise_level; nl <= final_noise_level; nl += steplen)
	{
		double rectstat = 0;
		double trianstat = 0;
		double roflstat = 0;


		for (int i = 0; i < gennum; i++)
		{

			nsignal = addNoise(signal, nl);
			

			spd = CreateSPD(nsignal);
			rectspd = RectWindow(spd);
			trianspd = TriangleWindow(spd);
			roflspd = RoflRectWindow(spd);


			double rectf = CalcFreqRect(rectspd);
			double trianf = CalcFreqTrian(trianspd);
			double roflf = CalcFreqRofl(roflspd);

			rectstat += (s.f - rectf) * (s.f - rectf);
			trianstat += (s.f - trianf) * (s.f - trianf);
			roflstat += (s.f - roflf) * (s.f - roflf);
		}


		rectstat = sqrt(rectstat / gennum);
		trianstat = sqrt(trianstat / gennum);
		roflstat = sqrt(roflstat / gennum);

		rest.push_back(rectstat);
		trst.push_back(trianstat);
		rost.push_back(roflstat);
		
		
		sgn_drawer.DrawTwoSignals(GetReal(signal), GetReal(nsignal), fd);
		spd_drawer.DrawFourSpecters(spd, rectspd, trianspd, roflspd, fd, wlen);
		disp_drawer.DrawDispersion(rest, trst, rost, start_noise_level, nl);
	}

	

	disp_drawer.DrawDispersion(rest, trst, rost, start_noise_level, final_noise_level);
}
