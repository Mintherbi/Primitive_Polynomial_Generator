#include <stdio.h>
#include <stdbool.h>

int LFSR(int zf);			//입력 : zformation			출력 : 다음 단계
bool* Sequence_generate(int* x_t);			//입력 : LFSR 2^15 - 1 개 숫자			출력 : sequence
int Autocorrelation(int tau, bool seq[]);		//autocorrealtion 계산 값 출력


int main()
{
	for (int zf = 0; zf < 16384; zf++)
	{
		int x_t[32767];		//다항식의 계수를 2진수로 저장, 길이는 2^15 -1
		x_t[0] = (zf<<1) +1;
		bool *seq;			//도출된 sequence (길이 32767)를 bool배열로 저장


		for (int j = 0; j < 32766; j++) //첫번째는 정해져있으므로 그 다음꺼부터 해서 2^15-2
		{
			x_t[j + 1] = LFSR(x_t[j]);
		}
		seq = Sequence_generate(x_t);

		for (int tau=0; tau < 32767; tau++)		//tau는 2^15-2까지 계산
		{
			int result;

			result = Autocorrelation(tau, seq);

			if (!(result == -1 || result == 1 || result == 32767))			//조건을 만족하지 못하면 중도 하차
			{
				//printf("pass %d, result %d, tau %d\n", zf,result,tau);			디버깅용...
				break;
			}
			if (tau == 32766) { printf("%d \n", (zf<<1)+65537); }			//출력할때 15차항(2^16=65536)과 상수항 (1) 출력
		}
	}

	return 0;
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

	return (zf >> 1) + ((binarySum%2) * 32768);			//shift 와 모든 자리수의 합을 2로 나눈 나머지를 앞으로 보냄
}


bool* Sequence_generate(int x_t[])
{
	bool seq[32767];			//x(t)의 길이는 2^15 -1

	for (int i = 0; i < 32767; i++) { 
		seq[i] = x_t[i] / 32768;
	}
	
	return seq;
}


int Autocorrelation(int tau, bool seq[])
{
	int result=0;

	for (int i=0; i < 32767; i++)
	{
		if (seq[i] == seq[(i + tau) % 32767]) { result++; }			//s(t) 만들기를 생락하기 위해 논리 연산으로 계산
		else { result--; }
	}
	return result;
}

