#include <stdio.h>

void solution(int n)
{
	int cnt = 0;
	int room[100] = {0,};
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j = j+(i+1))
			if (room[j] == 0)
				room[j] = 1;
			else
				room[j] = 0;
	}
	
	for (int i = 0; i < n; i++)
	{
		if (room[i] == 1)
			cnt++;
	}
	
	printf("%d\n", cnt);
}

int main(void)
{
	int t, n;
	
	scanf("%d", &t);
	
	for (int i = 0; i < t; i++)
	{
		scanf("%d", &n);
		
		solution(n);
	}
	
	return 0;
}