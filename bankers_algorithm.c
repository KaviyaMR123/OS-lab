#include<stdio.h>
#include<stdlib.h>
int n,m,max[10][10],need[10][10],alloc[10][10];
void read(int b[10][10])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
}
void display(int a[10][10])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}
void calculate()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
}
int banker(int avail[10])
{
    int finish[10],safesequence[10],i,j,k,ind=0,flag,s;
    for(i=0;i<n;i++)
    {
        finish[i]=0;
    }
    for(s=0;s<n;s++)
    {
        for(i=0;i<n;i++)
        {
            flag=0;
            if(finish[i]==0)
            {
                for(j=0;j<m;j++)
                {
                    if(need[i][j]>avail[j])
                    {
                        flag=1;
                        break;
                    }
                }
              if(flag==0)
              {
                  finish[i]==1;
                  safesequence[ind]=i;
                  ind++;
                  for(k=0;k<m;k++)
                  {
                      avail[k]+=alloc[i][k];
                  }
              }
            }
        }
    }
    flag=0;
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            printf("The following sequence is unsafe\n");
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("The safe sequence is:\n");
        for(i=0;i<n-1;i++)
        {
            printf("p%d->",safesequence[i]);
        }
        printf("p%d\n",safesequence[5]);
    }
}
int req(int avil[10])
{
    int p,req[10][10],i,j,flag1=0,flag2=0;
    printf("Enter the process number:\n");
    scanf("%d",&p);
    for(i=0;i<n;i++)
    {
        if(i==p)
        {
            printf("Enter the resources: \n");
            for(j=0;j<m;j++)
            {
                scanf("%d",&req[p][j]);
            }
            for(j=0;j<m;j++)
            {
                if(req[p][j]<=need[p][j])
                {
                    flag1=1;
                }
                else
                {
                    printf("Error occured");
                    exit(0);
                }
            }
            for(j=0;j<m;j++)
            {
                if(req[p][j]<=avil[j])
                {
                    flag2=1;
                }
                else
                {
                    printf("Error occured");
                    exit(0);
                }
            }
            if(flag1==1 && flag2==1)
            {
                for(j=0;j<m;j++)
                {
                    avil[j]=avil[j]-req[p][j];
                    alloc[p][j]=alloc[p][j]+req[p][j];
                    need[p][j]=need[p][j]-req[p][j];
                }
            }
        }
    }
printf("Allocation:\n");
display(alloc);
printf("Need matrix:\n");
display(need);
printf("Available:\n");
for(i=0;i<m;i++)
{
    printf("%d\t",avil[i]);
}
printf("\n");
banker(avil);
}
int main()
{
    int avail[10],avil[10],ch,j;
    printf("Enter the number of process:\n");
    scanf("%d",&n);
    printf("Enter the number of resources:\n");
    scanf("%d",&m);
    printf("Enter the alloction matrix:\n");
    read(alloc);
    display(alloc);
    printf("Enter the maximum matrix:");
    read(max);
    display(max);
    calculate(need);
    printf("\n");
    printf("Need matrix is: \n");
    display(need);
    printf("Enter the available resources:\n");
    for(j=0;j<m;j++)
    {
        scanf("%d",&avail[j]);
        avil[j]=avail[j];
    }
    banker(avail);
    printf("Do you want to comtinue press '1'\n");
    scanf("%d",&ch);
    if(ch==1)
    {
        req(avil);
    }
    return 0;
}
