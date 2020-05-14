#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void print(int n, long double a[])
{
    int i;
    for (i=0;i<n;i++)
    printf("%Lf",a[i]);
}


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
		   i++;
           B[i]=0;
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

long double* reduce(long double* p, int n, int h)
{
	long double *p_red = (long double*)malloc(n*sizeof(long double));
	int rem_value;
	rem_value= (h-1)/2 ;
	for(int i=0;i<n;i++)
	p_red[i] = p[i+rem_value];
	return p_red ;
}

long double *decimation(int n,long double *x,int m,long double *h,int samplingrate)
{
	long double *p,*p_reduced,*y;
	p = convolution(n,m,x,h);
	p_reduced = reduce(p,n,m);
	y = downsampling(p_reduced,samplingrate,n);
	return y;
}

long double *interpolation(int n,long double *y,int m, long double* h,int samplingrate)
{
	long double *ups,*z,*z_reduced;
	ups = upsampling(y,samplingrate,n);
	z = convolution(samplingrate*n,m,ups,h);
	z_reduced = reduce(z,samplingrate*n,m);
	return z_reduced;
}

long double *hbf_decimation(int n,long double *x,int m,long double *h,int samplingrate)
{
	long double *p,*p_reduced,*y;
	p = (long double *)malloc(sizeof(long double)*(m+n-1)) ;
    int a,b;
    for(int i=0;i<m+n-1;i++){
        p[i]=0;
        for(b=0;b<m/2;b=b+2)
        {
			a = i-b;
            if(a>=0 && n>a){
                p[i] += ((h[b])*(x[a]));
            }
           a = i - (m-1-b) ;
            
            if(a>=0 && n>a)
            {
                p[i] += ((h[b])*(x[a]));
            }
        }
        b = m/2;
        a = i-b;
        if(a>=0 && n>a){
                p[i] += ((h[b])*(x[a]));
        }   
    }
    
	p_reduced = reduce(p,n,m);
	y = downsampling(p_reduced,samplingrate,n);
	return y;
}

long double *hbf_interpolation(int n,long double *y,int m,long double *h,int samplingrate){
	long double *ups,*z,*z_reduced;
	int factor = 2;
	ups= upsampling(y,factor,n);
	int sizeofy = n*samplingrate;
	z = (long double *)malloc(sizeof(long double)*(m+sizeofy-1)) ;
    int b,c;
    for(int i=0;i<m+sizeofy-1;i++){
        z[i]=0;
        
        for(b = 0;b<m/2;b=b+2){
			
            c = i-b;
            
            if(c>=0 && sizeofy>c)
            {
                z[i] += ((h[b])*(ups[c]));
            }
        
            c = i - (m-1-b) ;
            if(c>=0 && sizeofy>c)
            {
                z[i] = z[i]+ ((h[b])*(ups[c]));
            }
        }
        b = m/2;
       c = i-b;
        if(c>=0 && sizeofy>c)
         {
                z[i] = z[i]+ ((h[b])*(ups[c]));
            }  
    }
    	
	z_reduced = reduce(z,samplingrate*n,m);
	return z_reduced;
}

int main()
{
long double *x;
int n, samplingrate=2;
printf("Enter size of input x: ");
scanf("%d",&n);

int g = samplingrate*n;

int f = (n-1)/samplingrate+1;
x = (long double *)malloc(n*sizeof(long double));
printf("Enter Array values: ");
for(int i=0;i<n;i++)
scanf("%Lf",&x[i]);

long double *h;
int m;
printf("Enter size of input h:");
scanf("%d",&m);
h = (long double *)malloc(m*sizeof(long double));
printf("Enter Array values: ");
for(int i=0;i<m;i++)
scanf("%Lf",&h[i]);

int opt;
printf("Enter 0 to perform decimation and 1 to perform interpolation:\n");
scanf("%d",&opt);

if(opt == 0)
{
		printf("Output:\n");
		print(f,decimation(n,x,m,h,samplingrate));
		printf("\n Output with Modified HBF Equations:\n");
		print(f,hbf_decimation(n,x,m,h,samplingrate));
    }
    
if(opt == 1)
    {
    
		printf("Output:\n");
		print(g,interpolation(n,x,m,h,samplingrate));
		printf("\nOutput with Modified HBF Equations:\n");
		print(g,hbf_interpolation(n,x,m,h,samplingrate));
    }
    

 return 0;
}


