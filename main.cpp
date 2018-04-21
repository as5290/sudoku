#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

int Initial_Num[10][10];
int v[10][10] = { 0 };

int Get_Num(int hang, int lie)
{
	if (hang > 9 || lie > 9) return 1;
	if (v[hang][lie])
	{
		if (lie < 9)
		{
			if (Get_Num(hang, lie + 1))
				return 1;
		}
		else
		{
			if (hang < 9)
			{
				if (Get_Num(hang + 1, 1))
					return 1;
			}
			else return 1;
		}
	}
	else
	{
		for (int num = 1; num <= 9; num++)
		{
			int can = 1;
			for (int i = 1; i <= 9; i++)
			{
				if (Initial_Num[i][lie] == num)
				{
					can = 0;
					break;
				}
			}//列是否有该数
			if (can)
			{
				for (int j = 1; j <= 9; j++)
				{
					if (Initial_Num[hang][j] == num)
					{
						can = 0;
						break;
					}
				}
			}//行是否有该数
			if (can)
			{
				int max_hang, max_lie;
				if (hang % 3 == 0)
					max_hang = hang;
				else
					max_hang = (hang / 3) * 3 + 3;

				if (lie % 3 == 0)
					max_lie = lie;
				else
					max_lie = (lie / 3) * 3 + 3;

				for (int i = max_hang - 2; i <= max_hang; i++)
				{
					for (int j = max_lie - 2; j <= max_lie; j++)
					{
						if (Initial_Num[i][j] == num)
						{
							can = 0;
							break;
						}
					}
					if (!can) break;
				}
			}//3x3格子里是否有该数
			if (can)
			{
				Initial_Num[hang][lie] = num;
				if (lie < 9)
				{
					if (Get_Num(hang, lie + 1))
						return 1;
				}
				else
				{
					if (hang < 9)
					{
						if (Get_Num(hang + 1, 1))
							return 1;
					}
					else return 1;
				}
				Initial_Num[hang][lie] = 0;
			}


		}//1--9是否可以放置
	}
	return 0;
}


void create(int n)
{
	int times = 0;
	int move[10] = { 0, 0, 3, 6, 1, 4, 7, 2, 5, 8 },
			lie;
	char N[10]={'9','1','2','3','4','5','6','7','8','9'};
		if ( times < n )
		{
			for (int a = 0; a < 6; a++)
			{
				if (times == n)break;
				if (a)
					next_permutation(move + 4, move + 6);
				for (int b = 0; b < 6; b++)
				{
					if (b)
						next_permutation(move + 7, move + 9);
					int t = 0; char kong = ' ';
					do
					{
						if (t)
							next_permutation(N + 2, N + 9);
						for (int i = 1; i <= 9; i++)
						{
							for (int j = 1; j <= 9; j++)
							{
								if (j - move[i] < 0)lie = j - move[i] + 9;
								else lie = j - move[i];
								putchar(N[lie % 9]);
								if (j < 9) putchar(kong);
							}putchar('\n');
						}
						times++; t++;
						if (times == n)break;
						else putchar('\n');
					}while (t<40320);
					if (times == n)break;
				}

				
			}

		}
	
}


void jie()
{
		Get_Num(1, 1);
		int flag = 0;
		int time_lie[10] = { 0 };
		for (int i = 1; i <= 9; i++)
		{
			int time[10] = { 0 };
			for (int j = 1; j <= 9; j++)
			{
				if (!Initial_Num[i][j])
				{
					flag = 1;
					break;
				}
				else
				{
					if (j == 1) time_lie[Initial_Num[i][j]]++;
					time[Initial_Num[i][j]]++;
					if (time[Initial_Num[i][j]] > 1 || time_lie[Initial_Num[i][j]] > 1)
					{
						flag = 1;
						break;
					}
				}
			}
			if (flag)
			{
				cout << "No solution!" << endl ;
				putchar('\n');
				break;
			}
		}

		if (!flag)
		{
			for (int i = 1; i <= 9; i++)
			{
				for (int j = 1; j <= 9; j++)
				{
					printf("%d", Initial_Num[i][j]);
					if (j < 9) printf(" ");
				}cout << endl;
			}cout << endl;
		}

}




int main(int argc,char* argv[] )
{
	if (strcmp(argv[1],"-c")==0 )//生成数独
	{
		freopen("sudoku.txt", "w", stdout);
		int num = 0,
			f = 0;
		for (int i = 0; i < strlen(argv[2]); i++)
		{
			if (argv[2][i]<'0' || argv[2][i]>'9')
			{
				printf("Wrong Input\n");
				f = 1;
				break;
			}
			num = num * 10 + (argv[2][i] - '0');
		}
		if (f);
		else
			create(num);
	}
	else if (strcmp(argv[1],"-s")==0)//解数独
	{
			freopen( argv[2], "r", stdin);
			freopen("demo_jie.txt", "w", stdout);
			while (scanf("%d", &Initial_Num[1][1]) != EOF)
			{
				memset(v, 0, sizeof(v));
				if (Initial_Num[1][1] > 0) v[1][1] = 1;
				for (int i = 1; i <= 9; i++)
				{
					for (int j = 1; j <= 9; j++)
					{
						if (i == 1 && j == 1)continue;
						scanf("%d", &Initial_Num[i][j]);
						if (Initial_Num[i][j] > 0)
							v[i][j] = 1;
					}
				}
				jie();
			}
			
	}
	else printf("Wrong Input\n");
	return 0;
}
