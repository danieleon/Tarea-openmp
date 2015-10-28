#include <stdio.h>
#include <omp.h> 
#include <sys/time.h>

#define NUMITER	1000000    

static long MULTIPLIER  = 1366;
static long ADDEND      = 150889;
static long PMOD        = 714025;
long random_last = 0.0;
double random_low, random_hi;

/*
Functions used to generate random numbers
*/

double random()
{   
  long random_next;
  double ret_val;

  random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
  random_last = random_next;

  ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;
  return ret_val;
}

void seed(double low_in, double hi_in)
{
  if(low_in < hi_in)
  {
    random_low = low_in;
    random_hi  = hi_in;
  }
  else
  {
    random_low = hi_in;
    random_hi  = low_in;
  }
  random_last = PMOD/ADDEND;

}   
   
//    
// The monte carlo pi program   
// Include the OpenMP directives to transform this sequential program in  a
// parallel one
//   
   
static long num_trials = NUMITER;
   
int main ()   
{   
  long i;
  long chunk=num_trials/2;
  long Ncirc = 0;
  int tid;
  double pi, x, y, x1, y1, test;
  double r = 1.0;// radius of circle. Side of squrare is 2*r    
  struct timeval tv1,tv2;

  gettimeofday(&tv1,NULL);
  seed(-r, r);// The circle and square are centered at the origin

  //PARALELO
  #pragma omp parallel for private(i, test, x, y) \
    default(shared) schedule(dynamic)
  for(i=0;i<num_trials; i++)
  {
    x = drandom();
    y = drandom();

    if (test <= r*r){
    #pragma omp atomic
      Ncirc++;
    }
  }

  pi = 4.0 * ((double)Ncirc/(double)num_trials);
  gettimeofday(&tv2,NULL);
  printf("\nPARALELO   %ld trials, pi is %lf - time %lf\n",num_trials, pi,
    (double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

  //SECUENCIAL
  gettimeofday(&tv1,NULL);
  seed(-r, r);// The circle and square are centered at the origin
  
  Ncirc=0;

  for(i=0;i<num_trials; i++)
  {
    x = drandom();
    y = drandom();

    test = x*x + y*y;
    
    if (test <= r*r) Ncirc++;
  }

  pi = 4.0 * ((double)Ncirc/(double)num_trials);
  gettimeofday(&tv2,NULL);
  printf("\nSECUENCIAL %ld trials, pi is %lf - time %lf\n",num_trials, pi,
    (double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

  return 0;
}
