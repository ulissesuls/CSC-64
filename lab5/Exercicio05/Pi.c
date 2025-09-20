#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double wall_time(void);

// inCircle: generate "points" random points at domain
//           (xStart, yStart) : (xStart+xRange, yStart+yRange), 
//           that is a part of the square (-1.,-1):(1,1) and
//           count how many of these points lye inside the
//           unit circle

long inCircle(long points,   // # random pairs to generate
	      float xStart,  // start point at x domain
	      float xRange,  // range of x domain
	      float yStart,  // start point at y domain
	      float yRange)  // range of y domain
{
  long count;
  long inside;
  int randVal;
  float xRand;
  float yRand;

  // random point is (xStart,yStart) + random fraction
  // of (xRange,yRange);
  // inside unit circle iff distance to origin <= 1.0

  inside=0;
  for (count=0; count<points; count++) {
    randVal=rand();
    xRand = xStart + xRange*(float)randVal/(float)RAND_MAX;
    randVal=rand();
    yRand = yStart + yRange*(float)randVal/(float)RAND_MAX;
    if (xRand*xRand + yRand*yRand <= 1.0) inside++;
  }
  return inside;
}
      
int main(int argc, char *argv[]) {
  int nProc;
  float xStart, xRange;
  float yStart, yRange;
  const long points = 1L<<31;
  long inside;
  double tend, tstart;
  double computedPi, referencePi, relError;

  int myId;
  
  // enroll MPI, range and id

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &myId);

  // square that circumscribes unit circle

  xStart=-1.0; xRange=2.0;
  yStart=-1.0; yRange=2.0;

  // compute pi and measure execution time

  tstart = wall_time();
  inside = inCircle(points, 
		    xStart, xRange,
		    yStart, yRange);
  computedPi = 4.0* ((double)inside/(double)points);
  tend = wall_time() - tstart;

  // relative error and final dump

  referencePi = 2.0*asin(1.0);
  relError = 100.0*fabs(computedPi-referencePi)/referencePi;
  printf("pi=%9.7f, rel error %9.5f%%, %ld points, %d procs, %lf(s) exec time\n", 
	 computedPi, relError, points, nProc, tend);
  
  MPI_Finalize();
  return 0;
}
