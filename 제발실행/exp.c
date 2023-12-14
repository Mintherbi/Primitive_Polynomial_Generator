#include <stdio.h>
#include <stdbool.h>
//2^15 = 32768 2^14 = 16384
//sequence�� ���̴� 2^15-1

int LFSR(int zf);			//�Է� : zformation			��� : ���� �ܰ�
bool* Sequence_generate(int x_t[]);			//�Է� : LFSR 2^15 - 1 �� ����			��� : 			
//int S_t(bool a);			//Autocorrelation �Լ� �ȿ��� ����� �� 
int Autocorrelation(int tau, bool seq[]);


int main()
{
	int zf = 10000;
	int x_t[32767];		//���׽��� ����� 2������ ����, ���̴� 2^15 -1
	x_t[0] = (zf << 1) + 1;
	bool* seq;			//����� sequence (���� 32767)�� bool�迭�� ����
	int st[32767];


	for (int j = 0; j < 32766; j++) //ù��°�� �����������Ƿ� �� ���������� �ؼ� 2^15-2
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

	// 2������ ��ȯ�ϸ鼭 �� �ڸ����� �� ���
	while (zf > 0) {
		remainder = zf % 2;
		binarySum += remainder;
		zf /= 2;
	}

	return (zf >> 1) + (binarySum * 32768);			//2^15 = 32768
}


bool* Sequence_generate(int x_t[])
{
	bool seq[32767];			//x(t)�� ���̴� 2^15 -1

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