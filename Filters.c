#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define pi 3.14159265358979323846

void print(int n, long double arr[])
{
    for (int i=0;i<n;i++)
    printf("%Lf\n",arr[i]);
}

long double *Mul(long len, long double *a,long double *b)
{
    long double *res = (long double *)malloc(len*sizeof(long double));
    for(long i=0;i<len;i++)
    res[i] = a[i]*b[i] ;
    return res;
}


long double *RectWin(long len)
{
    long double *res = (long double *)malloc(len*sizeof(long double));
    for(long i=0;i<len;i++)
    res[i] = 1.0;
    return res;
}

long double *HamWin(long len)
{ 
    long double *res = (long double *)malloc(len*sizeof(long double));
    for(long i=0;i<len;i++)
    res[i] = 0.54 - 0.46*cos(2.0*pi*i/(len-1.0));
    return res;
}

void LowPass(long double len, long double hd[], long double wc)
{
    long k = (len-1)/2.0 ;
   
    long n=-k;
    for(long i=0;i<k;i++,n++)
    hd[i] = sin(wc*n)/(pi*n) ;
    hd[k] = wc/pi ;
    
}
void LowPassOp(long len,long double hd[], long double wc){
    long k = (len-1)/2.0 ;
    long n = 1;
    for(int i=k+1;i<len;i++,n++)
    hd[i] = sin(wc*n)/(pi*n) ;
    long double *RectWin_output = Mul(len, hd, RectWin(len));
    long double *HamWin_output = Mul(len, hd, HamWin(len));
    printf("Using Rectangular Window\n");
    print(len, RectWin_output);
    printf("Using Hamming Window\n");
    print(len, HamWin_output);
}

void HighPass(long len, long double hd[], long double wc)
{
   
    long k = (len-1)/2.0 ;
    long n=-k;
    for(long i=0;i<k;i++,n++)
    hd[i] = (sin(pi*n)-sin(wc*n))/(pi*n) ;
    hd[k] = 1.0 - wc/pi ;
}

void HighPassOp(long len, long double hd[], long double wc)
{   long k = (len-1)/2.0 ;
    long n = 1 ;
    for(int i=k+1;i<len;i++,n++)
    hd[i] = (sin(pi*n)-sin(wc*n))/(pi*n) ;
    long double *RectWin_output = Mul(len, hd, RectWin(len));
    long double *HamWin_output = Mul(len, hd, RectWin(len));
    printf("Using Rectangular Window\n");
    print(len, RectWin_output);
    printf("Using Hamming Window\n");
    print(len, HamWin_output);
}

void BandPass(long len, long double hd[], long double wc2, long double wc1)
{
    long k = (len-1)/2.0 ;
    long n=-k;
    for(long i=0;i<k;i++,n++)
    hd[i] = (sin(wc2*n)-sin(wc1*n))/(pi*n) ;
    hd[k] = wc2/pi- wc1/pi ;
}


void BandPassOp(long len, long double hd[], long double wc2, long double wc1)
{
    long k = (len-1)/2.0;
    long n = 1 ;
    for(int i=k+1;i<len;i++,n++)
    hd[i] = (sin(wc2*n)-sin(wc1*n))/(pi*n) ;
    long double *RectWin_output = Mul(len, hd, RectWin(len));
    long double *HamWin_output = Mul(len, hd, RectWin(len));
    printf("Using Rectangular Window\n");
    print(len, RectWin_output);
    printf("Using Hamming Window\n");
    print(len, HamWin_output);
}

long double* MAF(long double* x, long len, long L)
{
    long double* res = (long double*)malloc(len * sizeof(long double));
    for(long i = 0; i < len; i++)

    {
        res[i] = 0;
    for(long k = 0; k < L; k++){
    res[i] += x[i - k];
}
     res[i] /= L;
}
return res;

}



int main()
{
    int operation;
    long double *x ;
    long fc,fs,fc1,fc2,len,L;
    
        
    printf(" Choose Operation to be performed : 1)LPF\n 2)HPF\n 3)BPF\n 4)Moving Average Filter\n");
    scanf("%d",&operation);
    
    if(operation == 1 || operation == 2)
    {
        printf("fc : ");
        scanf("%li",&fc);
        printf("fs : ");
        scanf("%li",&fs);
        printf("len : ");
        scanf("%li",&len);
        if(operation==1){
        long double wc = (2.0*pi*fc)/fs ;
        long double *hd = (long double *)malloc(len*sizeof(long double));
        LowPass(len, hd , wc);
        LowPassOp(len ,hd , wc);
        }
        else
        {
         long double wc = (2.0*pi*fc)/fs ;
         long double *hd = (long double *)malloc(len*sizeof(long double));
         HighPass(len, hd, wc);
         HighPassOp(len, hd, wc);
        }
	
    }
    
    else if(operation == 3)
    {
        printf("fc1 : ");
        scanf("%li",&fc1);
        printf("fc2 : ");
        scanf("%li",&fc2);
        printf("fs : ");
        scanf("%li",&fs);
        printf("Len : ");
        scanf("%li",&len);
         long double wc1 = (2.0*pi*fc1)/fs ;
         long double wc2 = (2.0*pi*fc2)/fs ;
         long double *hd = (long double *)malloc(len*sizeof(long double));
         BandPass(len,hd,wc2,wc1);
         BandPassOp(len,hd,wc2,wc1);
    }
    
    else if(operation == 4)
    {
        printf("Size of x: ");
        scanf("%li",&len);
        x = (long double *)malloc(len*sizeof(long double));
        printf("Input Array Values: \n");
        for(long i=0;i<len;i++)
        scanf("%Lf",&x[i]);
        printf("L: ");
        scanf("%li",&L);
        long double *res = MAF(x,len,L);
        printf("Output:\n");
		print(len-L+1,res);

		}

    else{
        printf("\nYour Choice of Operation cannot be performed\n");
    }


    return 0;
}




