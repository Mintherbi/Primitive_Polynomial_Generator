#include <stdio.h>
#include <stdbool.h>
//2^15 = 32768 2^14 = 16384
//sequence의 길이는 2^15-1

int LFSR(int zf);			//입력 : zformation			출력 : 다음 단계
bool* Sequence_generate(int x_t[]);			//입력 : LFSR 2^15 - 1 개 숫자			출력 : 			
//int S_t(bool a);			//Autocorrelation 함수 안에서 사용할 것 
int Autocorrelation(int tau, bool seq[]);


int main()
{
	int zf = 10000;
	int x_t[32767];		//다항식의 계수를 2진수로 저장, 길이는 2^15 -1
	x_t[0] = (zf << 1) + 1;
	bool* seq;			//도출된 sequence (길이 32767)를 bool배열로 저장
	int st[32767];


	for (int j = 0; j < 32766; j++) //첫번째는 정해져있으므로 그 다음꺼부터 해서 2^15-2
	{
		x_t[j + 1] = LFSR(x_t[j]);
		printf(x_t[j + 1]);
	}
	seq = Sequence_generate(x_t);
}



int LFSR(int zf)
{
	int binarySum = 0;
	int remainder;

	// 2진수로 변환하면서 각 자릿수의 합 계산
	while (zf > 0) {
		remainder = zf % 2;
		binarySum += remainder;
		zf /= 2;
	}

	return (zf >> 1) + (binarySum * 32768);			//2^15 = 32768
}


bool* Sequence_generate(int x_t[])
{
	bool seq[32767];			//x(t)의 길이는 2^15 -1

	for (int i = 0; i < 32767; i++)
	{
		seq[i] = x_t[i] / 32768;
	}
	return seq;
}


int Autocorrelation(int tau, bool seq[])
{
	int result = 0;

	for (int i = 0; i < 32766; i++)
	{
		if (~(seq[i] ^ seq[(i + tau) % 32768])) { result++; }
		else { result--; };
	}
	return result;
}