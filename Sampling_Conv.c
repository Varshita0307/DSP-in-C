#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double *convolution(int Alen, int Blen, long double *A, long double *B )
{   int conlen;
    int i,j,k;
    conlen = Alen+Blen-1;
    long double *C = (long double*)malloc(conlen*sizeof(long double));
    for (i=0;i<conlen;i++)
    {
        C[i]=0;
        for(j=0;j<Alen;j++)
        {
            k = i-j;
        if (k>=0&&k<Blen) 
        {
         C[i]=C[i]+(A[j]*B[k]);  
        }
        }
    }
    return C;
    
}

long double *correlation(int Alen, int Blen, long double *A, long double *B )
{   int conlen;
    int i,j,k;
    conlen = Alen+Blen-1;
    long double *C = (long double*)malloc(conlen*sizeof(long double));
    for (i=0;i<conlen;i++)
    {
        C[i]=0;
        for(j=0;j<Alen;j++)
        {
            k = i+j;
        if (k>=0&&k<Blen) 
        {
         C[i]=C[i]+(A[j]*B[k]);  
        }
        }
    }
    return C;
    
}

long double *upsampling(long double A[], int samplingrate, int n )
{   int oplen = n*samplingrate; 
    long double *B = (long double*)malloc(oplen*sizeof(long double)); 
    for(int i=0; i<oplen;i++)
    {
        B[i] = A[i/samplingrate];
        int zeroes = samplingrate-1;
       while (zeroes--) //inserting zeroes between values
       {
           B[i]=0;
           i++;
        }
    }
   return B;
        
}

long double *downsampling(long double A[], int samplingrate, int n )
{   int oplen = (n-1)/samplingrate+1;
    long double *B = (long double*)malloc(oplen*sizeof(long double));
    int opin = 0;
    for(int i=0; i<n;i=i+samplingrate)
    {
        B[opin]=A[i];
        opin++;
    }
   return B;
}

void print(int n, long double a[])
{
    int i;
    for (i=0;i<n;i++)
    printf("%Lf",a[i]);
}

int main()
{       
       int m,n,i,j,No;
       int samplingrate;
       long double *A, *B;
       
       printf("No. of samples in Vector A:\n");
       scanf("%d",&n);
       A = (long double*)malloc(n*sizeof(long double)); 
       printf("Enter values of Vector A\n ");
       for (i=0;i<n;i++)
       {
        scanf("%Lf",&A[i]);
       }
       
       
       
       
       printf("No. of samples in Vector B:\n");
       scanf("%d",&m);
       B = (long double*)malloc(m*sizeof(long double)); 
       printf("Enter values of Vector B\n ");
       for (j=0;j<m;j++)
       {
        scanf("%Lf",&B[j]);
       }
       printf("Enter sampling rate\n");
       scanf("%d",&samplingrate);
       
       printf("Upsampling\n");
       print(n*samplingrate,upsampling(A,samplingrate,n));
       printf("Downsampling\n");
       print((n-1)/samplingrate+1,downsampling(A,samplingrate,n));
       
       int conlen = n+m-1;
       printf("Convolution\n");
       print(conlen,convolution(n,m,A,B));
       printf("Correlation\n");
       print(conlen,correlation(n,m,A,B));
       
      
}
