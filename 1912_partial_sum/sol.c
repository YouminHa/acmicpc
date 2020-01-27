#include <stdio.h>

#define MAX 100000

int n;
int value[MAX];
int sum[MAX];
int max = 0;
int state = 1;
int cnt = -1;

void
sol()
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		if (value[i] < 0 || i == n-1)
		{
			if (state == 1)
				sum[cnt] += value[i];
			else
			{
				if (cnt == 0)
					max = sum[cnt];
				else if (cnt > 1)
				{
					if (-(sum[cnt-1]) < sum[cnt] && -(sum[cnt-1]) < sum[cnt-2])
					{
						sum[cnt] += sum[cnt-1] + sum[cnt-2];
						cnt = cnt-2;
					}
					if (max < sum[cnt])
						max = sum[cnt];
				}
				sum[++cnt] = value[i];
			}
			state = 1;
		}
		else
		{
			if (state == 1)
				sum[++cnt] = value[i];
			else
				sum[cnt] += value[i];
			state = 0;
		}
	}
}

int
main(int argc, char *argv[])
{
	int i;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &value[i]);

	sol();

	printf("%d", max);

	return 0;
}
