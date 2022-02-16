#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct cardtype{
	char ogstr[3];
	int suit;
	int num;
}card[99];
void SF(int ifF)
{
	for(int i=12;i>=0;i--)
	{
		int flag=0;
		if(card[i].num==-99)
			continue;
		if(card[i].num==2)
		{
			char output[5][3];
			int count=3;
			strcpy(output[0],card[i].ogstr);
			for(int j=0 ; j<i && count<7 ; j++)
				if(card[j].num==count && (card[j].suit==card[i].suit || ifF))
				{
					strcpy(output[count-2],card[j].ogstr);
					count++;
					if(count==7)
					{
						flag++;
						printf("%s %s %s %s %s\n",output[0],output[1],output[2],output[3],output[4]);
					}
				}
			if(flag)
				for(int k=0;k<5;k++)
					card[(i+k)%13].num=-99;
		}
		else if(card[i].num==1 || card[i].num>4)
		{
			char output[5][4];
			int count=0;
			strcpy(output[4],card[i].ogstr);
			for(int j=0 ; j<13 && count<4 ; j++)
				if(card[j%13].num==(card[i].num+8+count)%13+1 && (card[j%13].suit==card[i].suit || ifF))
				{
					strcpy(output[count],card[j%13].ogstr);
					count++;
					if(count==4)
					{
						flag++;
						printf("%s %s %s %s %s\n",output[0],output[1],output[2],output[3],output[4]);
						break;
					}
				}
			if(flag)
				for(int k=0;k<5;k++)
					card[(i-k+13)%13].num=-99;
		}
	}
}
void FK()
{
	for(int i=12;i>=0;i--)
		if(card[i].num>0)if(card[(i+12)%13].num==card[i].num)if(card[(i+10)%13].num==card[i].num)if(card[(i+11)%13].num==card[i].num)
		{
			for(int k=0;k<4;k++)
			{
				card[i-k].num=-99;
				printf("%s ",card[i-k].ogstr);
			}
			for(int j=0;j<13;j++)
				if(-99!=card[j].num/* && card[(j+2)%13].num!=card[j].num && card[(j+3)%13].num!=card[j].num*/)
				{
					card[j].num=-99;		
					printf("%s\n",card[j].ogstr);
					break;
				}
		}
}
void FH()
{
	for(int i=12;i>=0;i--)
	{
		int flag=0;
		if(card[i].num>0 && (card[(i+12)%13].num==card[i].num) + (card[(i+11)%13].num==card[i].num) + (card[(i+10)%13].num==card[i].num)==2)
			for(int j=0;j<13;j++)
			{
				if(card[j].num!=-99 && card[j].num!=card[i].num)
					for(int k=1;k<4;k++)
						if(card[(j+k)%13].num==card[j].num)// + (card[(j+2)%13].num==card[j].num && card[(j+1+(k+2)%3)%13].num!=card[j].num)
						{
							int temp=card[i].num;
							for(int l=12;l>=0;l--)
								if(card[l].num==temp)
								{
									card[l].num=-99;	
									printf("%s ",card[l].ogstr);
								}
							card[j].num=-99;		
							card[j+k].num=-99;
							printf("%s %s\n",card[j+k].ogstr,card[j].ogstr);
							flag++;
							break;
						}
				if(flag)
					break;
			}
	}
}
void pair()
{
	for(int j=12;j>=0;j--)
		if(card[j].num!=-99)
			for(int k=0;k<j;k++)
			{
				if(card[k].num==card[j].num)
				{
					card[j].num=-99;		
					card[k].num=-99;
					printf("%s %s\n",card[j].ogstr,card[k].ogstr);
					break;
				}
			}

}
void swap(struct cardtype *a,struct cardtype *b)
{
	struct cardtype temp=*a;
	*a=*b;
	*b=temp;
}
int main()
{
	int i=0;
	while(scanf("%s",card[i].ogstr)>0)					//input data
	{
		switch(card[i].ogstr[0])
		{
			case 'S':card[i].suit=4;break;
			case 'H':card[i].suit=3;break;
			case 'D':card[i].suit=2;break;
			case 'C':card[i].suit=1;break;
		}
		switch(card[i].ogstr[1])
		{
			case 'J':card[i].num=11;break;
			case 'Q':card[i].num=12;break;
			case 'K':card[i].num=13;break;
			case 'A':card[i].num=1;break;
			default:card[i].num=(int)(card[i].ogstr[1]-48);		
		}
		if(card[i].ogstr[2]=='0')
			card[i].num=10;
		i++;
	}
	for(int i=0;i<12;i++)//sorting
		for(int j=0;j<12-i;j++)
			if((card[j].num+10)%13>(card[j+1].num+10)%13 || ((card[j].num+10)%13==(card[j+1].num+10)%13 && card[j].suit>card[j+1].suit))
				swap(&card[j],&card[j+1]);
	SF(0);
	FK();
	FH();
	SF(1);
	pair();
	for(int i=12;i>=0;i--)
		if(card[i].num!=-99)
			printf("%s\n",card[i].ogstr);
	return 0;
}

