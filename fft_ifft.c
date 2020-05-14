/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define pi 3.14159265358979323846


typedef struct complex
{
    long double real;
    long double imag;
}complex;

complex add(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real+n2.real;
    temp.imag = n1.imag+n2.imag;
    return temp;
}

complex mul(complex n1, complex n2)
{
    complex temp;
    temp.real = n1.real*n2.real-n1.imag*n2.imag;
    temp.imag = n1.real*n2.real+n1.imag*n2.imag ;
    return temp;
}

complex scaling(complex n, long double scale)
{
    complex temp;
    temp.real = scale*n.real;
    temp.imag = scale*n.imag;
    return temp;
}

void scan(complex *n)
{
    char ch;
    scanf("%Lf",&n->real);
    getchar();
    scanf("%c",&ch);
    getchar();
    scanf("%Lf",&n->imag);
    if(ch=='-')
    n->imag = -1.0*(n->imag) ;
    getchar(); 
    getchar();
}

void assign(complex  *n1, complex n2)
{
    n1->real = n2.real;
    n1->imag = n2.imag;
}

void ifft(complex *n1, complex *n2, long N1, long N2 )
{
    complex a,b,temp;
    long k;
    if(N1==1)
    {
        assign(n2,n1[0]);
    }
    else
    {
        ifft(n1,n2,N1/2,2*N2);
        ifft(n1+N2,n2+N1/2,N1/2,2*N2); 
        for(k=0;k<=(N1/2-1);k++)
        {
        b.real = cos(2.0*pi*k/N1);
        b.imag = sin(2.0*pi*k/N1);
        assign(&a,n2[k]);
        assign(&temp,mul(b,n2[k+N1/2]));
        assign(n2+k,add(a,temp));
        assign(n2+k+N1/2,add(a,scaling(temp,-1.0)));
        }
    }
}

void fft(complex *n1, complex *n2, long N1, long N2)
{
    complex a,b,temp;
    long k;
    if(N1==1)
    {
        assign(n2,n1[0]);
    } 
    else 
    {
     fft(n1,n2,N1/2,2*N2);
     fft(n1+N2,n2+N1/2,N1/2,2*N2);  
    for(k=0;k<=(N1/2-1);k++)
       {
        b.real = cos(2.0*pi*k/N1);
        b.imag = sin(2.0*pi*k/N1);
        assign(&a,n2[k]);
        assign(&temp,mul(b,n2[k+N1/2]));
        assign(n2+k,add(a,temp));
        assign(n2+k+N1/2,add(a,scaling(temp,-1.0)));
       }  
    }
}


int main()
{
    complex *n1, *n2;
    char ch;
    long fc,fs,f1,f2,N,L;
    int opt,type;
    
    
    
    
    printf("Size(N): ");
    scanf("%li",&N);
    int val[N];
    n1 = (complex *)malloc(N*sizeof(complex));
    n2 = (complex *)malloc(N*sizeof(complex));
    printf(" Input Type: 1) real 2) complex\n");
    scanf("%d",&type);
    
    printf("Enter values:\n");
   
    
    
    if (type==1)
    {
        n1 = (complex * )malloc(N*sizeof(complex));
        scanf("%Lf",&n1[0].real);
        n1[0].imag = 0;
        for(long i=1;i<N;i++)
        {
            getchar();
            getchar();
            scanf("%Lf",&(n1[i].real));
            n1[i].imag = 0;
        }
    }
    else 
    {
         if(N>0)
         {
            scan(n1);
            for(long i=1;i<N;i++){
                scanf("%c",&ch); // for ,
                getchar(); // For space
                scan(n1+i);
            }
    }
    }
    printf(" Choice of Filter: 1) fft 2) ifft\n");
    scanf("%d",&opt);
    if(opt == 1 )
    {
        long N2=1.00;
        fft(n1, n2, N, N2) ;
       for(long i=0;i<N;i++)
       {
           printf("%Lf + ",n2[i].real);
           printf("%Lfi\n",n2[i].imag);
       }
    }
	

    else {
        long N2=1.00;
       ifft(n1, n2, N, N2) ;
       for(long i=0;i<N;i++)
       {
           n2[i] = scaling(n2[i],1.0/(1.0*N));
           printf("%Lf + ",n2[i].real);
           printf("%Lfi\n",n2[i].imag);
       }
	}
	
 }
    
    
    

    
    







