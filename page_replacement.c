#include<stdio.h>
#include<stdlib.h>
int n,f,i,j,k,p,fault=0,flag;
void fifo(int[],int,int[],int);
void lru(int[],int,int[],int);
void lfu(int[],int,int[],int);
void printframe(int[],int);
void main()
{
    printf("Enter the number of pages: ");
    scanf("%d",&n);
    printf("Enter the number of frames: ");
    scanf("%d",&f);
    int pages[n],realframes[f];
    printf("Enter the page sequence\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    for(j=0;j<f;j++)
    {
        realframes[j]=-1;
    }
    fifo(pages,n,realframes,f);
    lru(pages,n,realframes,f);
    lfu(pages,n,realframes,f);
}
void fifo(int pages[],int n,int realframes[],int f)
{
    int frames[f];
    for(j=0;j<f;j++)
    {
        frames[j]=realframes[j];
    }
    printf("FIRST IN FIRST OUT REPLACEMENT\n-----------------\n");
    fault=0;
    k=0;
    for(i=0;i<n;i++)
    {
        p=pages[i];
        flag=1;
        for(j=0;j<f;j++)
        {
            if(p==frames[j])
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            fault++;
            frames[k]=p;
            k=(k+1)%f;
            printframe(frames,f);
        }
        else
        {
            printframe(frames,f);
        }
    }
    printf("Page Fault in FIFO page replacement is %d\n",fault);
}
void printframe(int frames[],int f)
{
    int i;
    for(i=0;i<f;i++)
    {
        printf("%d\t",frames[i]);
    }
    printf("\n");
}
void lru(int pages[],int n,int realframes[],int f)
{
    int min;
    int frames[f],recent[f];
    for(j=0;j<f;j++)
    {
        frames[j]=realframes[j];
        recent[j]=0;
    }
    printf("LEAST RECENTLY USED REPLACEMENT\n-----------------\n");
    fault=0;
    k=1;
    for(i=0;i<n;i++)
    {
        p=pages[i];
        flag=1;
        for(j=0;j<f;j++)
        {
            if(p==frames[j])
            {
                flag=0;
                recent[j]=k;
                k++;
                break;
            }
        }
        if(flag==1)
        {
            fault++;
            min=0;
            for(j=1;j<f;j++)
            {
                if(recent[j]<recent[min])
                {
                    min=j;
                }
            }
            frames[min]=p;
            recent[min]=k;
            k++;
            printframe(frames,f);
        }
        else
        {
            printframe(frames,f);
        }
    }
    printf("Page Fault in LRU Page Replacement is %d\n",fault);
}
void lfu(int pages[],int n,int realframes[],int f)
{
    int min;
    int frames[f],freq[f];
    for(j=0;j<f;j++)
    {
        frames[j]=realframes[j];
        freq[j]=0;
    }
    printf("LEAST FREQUENTLY USED PAGE REPLACEMENT\n------------------\n");
    fault=0;
    for(i=0;i<n;i++)
    {
        p=pages[i];
        flag=1;
        for(j=0;j<f;j++)
        {
            if(p==frames[j])
            {
                flag=0;
                freq[j]++;
                break;
            }
        }
        if(flag==1)
        {
            fault++;
            min=0;
            for(j=1;j<f;j++)
            {
                if(freq[j]<freq[min])
                {
                    min=j;
                }
            }
            frames[min]=p;
            freq[min]=1;
            printframe(frames,f);
        }
        else
        {
            printframe(frames,f);
        }
    }
    printf("Page Fault in lfu page replacement is %d\n",fault);
}
