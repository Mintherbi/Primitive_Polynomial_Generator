#include <stdio.h>
#include <stdbool.h>

int LFSR(int zf);			//�Է� : zformation			��� : ���� �ܰ�
bool* Sequence_generate(int* x_t);			//�Է� : LFSR 2^15 - 1 �� ����			��� : sequence
int Autocorrelation(int tau, bool seq[]);		//autocorrealtion ��� �� ���


int main()
{
	for (int zf = 0; zf < 16384; zf++)
	{
		int x_t[32767];		//���׽��� ����� 2������ ����, ���̴� 2^15 -1
		x_t[0] = (zf<<1) +1;
		bool *seq;			//����� sequence (���� 32767)�� bool�迭�� ����


		for (int j = 0; j < 32766; j++) //ù��°�� �����������Ƿ� �� ���������� �ؼ� 2^15-2
		{
			x_t[j + 1] = LFSR(x_t[j]);
		}
		seq = Sequence_generate(x_t);

		for (int tau=0; tau < 32767; tau++)		//tau�� 2^15-2���� ���
		{
			int result;

			result = Autocorrelation(tau, seq);

			if (!(result == -1 || result == 1 || result == 32767))			//������ �������� ���ϸ� �ߵ� ����
			{
				//printf("pass %d, result %d, tau %d\n", zf,result,tau);			������...
				break;
			}
			if (tau == 32766) { printf("%d \n", (zf<<1)+65537); }			//����Ҷ� 15����(2^16=65536)�� ����� (1) ���
		}
	}

	return 0;
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

	return (zf >> 1) + ((binarySum%2) * 32768);			//shift �� ��� �ڸ����� ���� 2�� ���� �������� ������ ����
}


bool* Sequence_generate(int x_t[])
{
	bool seq[32767];			//x(t)�� ���̴� 2^15 -1

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
		if (seq[i] == seq[(i + tau) % 32767]) { result++; }			//s(t) ����⸦ �����ϱ� ���� �� �������� ���
		else { result--; }
	}
	return result;
}

