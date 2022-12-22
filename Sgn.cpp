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
vector<cmplx> Sgn::RealToCmplx(vector<double>& data)
{
	vector<cmplx>res;
	for (auto& item : data)res.push_back(cmplx(item, 0));
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
vector<double> Sgn::CreateRealSignal(double A, double f, double y)
{
	vector<double> res;
	for (int i = 0; i < N; i++)
	{
		res.push_back(A * sin(2 * pi * f * i / fd + y));
	}
	return res;
}

vector<cmplx> Sgn::AddNoise(vector<cmplx>& data, double nl)
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
vector<double> Sgn::AddNoise(vector<double>& data, double nl)
{
	vector<double>res;


	vector<double>noise = generateNoiseBasics();


	double Es = CalcE(data);
	double En = CalcE(noise);
	double betta = sqrt(nl * Es / En);


	for (int i = 0; i < N; i++)
	{
		double temp;
		temp = noise[i] * betta + data[i];
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
	fourea(data.size(), data, -1);


	vector<double> res;
	for (auto& item : data)
		res.push_back(sqrt(item.re * item.re + item.im * item.im));
	return res;
}


vector<double>Sgn::GetSubVector(vector<double>& data, int pos, int len)
{
	vector<double> res;
	for (int i = pos; i < pos + len; i++)res.push_back(data[i]);
	return res;
}
vector<vector<double>> Sgn::RectWindow(vector<double>& data)
{
	vector<vector<double>> res;


	int num = data.size() / wlen;
	for (int i = 0; i < num; i++)
	{
		res.push_back(GetSubVector(data, i * wlen, wlen));
	}
	if (data.size() % wlen != 0)
	{
		vector<double> temp(wlen, 0);
		for (int i = num * wlen; i < data.size(); i++)
		{
			temp[i - num * wlen] = data[i];
		}
		res.push_back(temp);
	}

	return res;
}
vector<vector<double>> Sgn::TriangleWindow(vector<double>& data)
{
	vector<vector<double>> res;


	int num = data.size() / wlen;
	for (int i = 0; i < num; i++)
	{
		vector<double> temp = GetSubVector(data, i * wlen, wlen);
		for (int g = 0; g < temp.size(); g++)
		{
			temp[g] *= (wlen - 2 * abs(g - wlen / 2)) / float(wlen);
		}
		res.push_back(temp);
	}
	if (data.size() % wlen != 0)
	{
		vector<double> temp(wlen, 0);
		for (int i = num * wlen; i < data.size(); i++)
		{
			temp[i - num * wlen] = data[i]* (wlen - 2 * abs(i-num*wlen - wlen / 2)) / float(wlen);
		}
		res.push_back(temp);
	}

	return res;
}
vector<vector<double>> Sgn::OverlappingRectWindow(vector<double>& data)
{
	vector<vector<double>> res;


	for (int i = 0; i < data.size()-wlen+1; i+=wlen/4)
	{
		res.push_back(GetSubVector(data, i, wlen));
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


double Sgn::CalcF(vector<double>& data)
{
	double res = Max(data) * fd / (data.size() - 1);
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


double Sgn::CalcStats(vector < vector<double>>& data)
{
	double res = 0;
	for (auto& item : data)
	{
		vector<double> spd = CreateSPD(RealToCmplx(item));
		double f = CalcF(spd);
		res += (s.f - f) * (s.f - f);
	}
	res = res / data.size();
	return res;
}


void Sgn::GenerateStatsOnce()
{
	srand(time(NULL));


	vector<double> signal = CreateRealSignal(s.A, s.f, s.y);
	vector<double> nsignal = AddNoise(signal, start_noise_level);


	auto rect = RectWindow(nsignal);
	auto trian = TriangleWindow(nsignal);
	auto ovrect = OverlappingRectWindow(nsignal);
	sgn_drawer.DrawThreeSignals(nsignal, ToOne(rect), ToOne(trian), fd);


	vector<double>spd = CreateSPD(RealToCmplx(nsignal));
	auto rectspd = CreateSPD(RealToCmplx(rect[0]));
	auto trianspd = CreateSPD(RealToCmplx(trian[0]));
	auto ovrectspd = CreateSPD(RealToCmplx(ovrect[0]));
	spd_drawer.DrawFourSpecters(spd, rectspd, trianspd, ovrectspd, fd);


	double rst = CalcStats(rect);
	double trst = CalcStats(trian);
	double ovrst = CalcStats(ovrect);


	disp_drawer.DrawDispersionOnce(rst, trst, ovrst, start_noise_level);
}
void Sgn::GenerateStats()
{
	srand(time(NULL));


	vector<double> signal = CreateRealSignal(s.A, s.f, s.y);
	vector<double> nsignal;

	vector<vector<double>>rect;
	vector<vector<double>>trian;
	vector<vector<double>>ovrect;


	vector<double>rectspd;
	vector<double>trianspd;
	vector<double>ovrectspd;
	vector<double>spd;


	vector<double> rectstats;
	vector<double> trianstats;
	vector<double> ovrectstats;


	double steplen = (final_noise_level - start_noise_level) / (steps - 1);
	for (double nl = start_noise_level; nl <= final_noise_level; nl += steplen)
	{
		double rst = 0;
		double trst = 0;
		double ovrst = 0;
		for (int i = 0; i < gennum; i++)
		{
			nsignal = AddNoise(signal, nl);


			rect = RectWindow(nsignal);
			trian = TriangleWindow(nsignal);
			ovrect = OverlappingRectWindow(nsignal);


			rst += CalcStats(rect);
			trst += CalcStats(trian);
			ovrst += CalcStats(ovrect);
		}
		rectstats.push_back(rst / gennum);
		trianstats.push_back(trst / gennum);
		ovrectstats.push_back(ovrst / gennum);


		spd = CreateSPD(RealToCmplx(nsignal));
		rectspd = CreateSPD(RealToCmplx(rect[0]));
		trianspd = CreateSPD(RealToCmplx(trian[0]));
		ovrectspd = CreateSPD(RealToCmplx(ovrect[0]));
		sgn_drawer.DrawThreeSignals(nsignal, ToOne(rect), ToOne(trian), fd);
		spd_drawer.DrawFourSpecters(spd, rectspd, trianspd, ovrectspd, fd);
		disp_drawer.DrawDispersion(rectstats, trianstats, ovrectstats, start_noise_level, nl);
	}


	disp_drawer.DrawDispersion(rectstats, trianstats, ovrectstats, start_noise_level, final_noise_level);
}


void Sgn::test()
{
	auto signal = CreateRealSignal(s.A,s.f,s.y);
	auto rect = RectWindow(signal);
	auto trian = TriangleWindow(signal);
	auto ovrect = OverlappingRectWindow(signal);
	sgn_drawer.DrawThreeSignals(signal, ToOne(rect), ToOne(trian), fd);
}


vector<double> Sgn::ToOne(vector < vector<double>>& data)
{
	vector<double> res;
	for (auto& obj : data)
	{
		for (auto& item : obj)res.push_back(item);
	}
	return res;
}
