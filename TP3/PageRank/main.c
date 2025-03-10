/*
* (C) Iain Fraser - GPLv3
* iainkfraser.blogspot.co.uk
* Code for #sundayfun article 2. On the original google PageRank algorithm.
*
*
* Code edited by J.Collet for ES201 lectures.
*	<julien.collet@cea.fr> 
*/


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "examples.h"


#define _VERBOSE
#define _GOOGLEMATRIX			// initilise google matrix then run normal eigenvector alogrithm
#define _LIMIT		50		// iteration limit 
#define EPSILON		0.001		// steady state precision 
#define DAMP_FACTOR	0.85

/*
* The PageRank paper uses manhattan geomtery for distance. However
* other sources use Euclidean. 
*/

#define VEC_MAG		vec_manhattan_mag


void mat_print( int n, int m, float A[n][m] ){
	int i, j;
	for( i = 0; i < n; i++ ){
		for( j = 0; j < m; j++ ){
			printf("%f ", A[i][j] );
		}
		printf("\n");
	}
}

void mat_vec_mul( int n, float d[n], float s[n], float A[n][n] ){
	int i, j;
	for( i = 0; i < n; i++ ){
		d[i] = 0.0;
		for( j = 0; j < n; j++ ){
			d[i] += s[j] * A[j][i];
		}
	}
}

void vec_scale( int n, float d[n], float s ){
	int i = 0;
	for( i = 0; i < n; i++ )
		d[i] *= s;
}

void vec_add( int n, float d[n], float s[n] ){
	int i = 0;
	for( i = 0; i < n; i++ )
		d[i] += s[i];
}

float vec_euclid_mag( int n, float a[n], float b[n] ){
	float c = 0.0;
	int i = 0;
	for( i = 0; i < n; i++ )
		c += (float)( (float)a[i] - (float)b[i] ) * (float)( (float)a[i] - (float)b[i] ); 
	return ( c );
} 

float vec_manhattan_mag( int n, float a[n], float b[n] ){
	float c = 0.0;
	int i = 0;
	for( i = 0; i < n; i++ )
		c += (float)(( (float)a[i] - (float)b[i] ) < 0.0 ?(float)-((float)a[i]-(float)b[i]):(float)((float)a[i]-(float)b[i]) );

	return c;	
} 


void do_pagerank( int n, float r[n], float A[n][n], float d, float k[n] ){
	float t[n];
	int isr = 1;	
	int iter = 0;		// purely for reporting purposes 

	do 
	{
		if( isr )
			mat_vec_mul( n, t, r, A ), vec_scale( n, t, d ), vec_add( n, t, k);			
		else
			mat_vec_mul( n, r, t, A ), vec_scale( n, r, d ), vec_add( n, r, k );			
		

#ifdef _VERBOSE
		iter++;
		if( iter > _LIMIT )
			break;

#ifdef _VVERBOSE 
		mat_print( 1, n,  ( isr ? r : t ) );
#endif
#endif
		isr = !isr;
	} while( (float)VEC_MAG( n, r, t ) > (float)EPSILON );

	if( !isr )
		memcpy( r, t, sizeof( t ) ); 

#ifdef _VERBOSE
	printf("found in %d iterations\n", iter );
#endif

} 

void PageRank( int n, float r[n], float A[n][n] ){
	float k[n];
	const float d = DAMP_FACTOR;	
	const float c = ( 1 - d ) / (float)n; 
	
	int i;

	for( i = 0; i < n; i++ )
		k[i] = c; 

	do_pagerank( n, r, A, d, k );
}

// simple dominant eigenvector algorithm i.e. PageRank without damping 
void eigenvector( int n, float r[n], float A[n][n] ){
	float k[n];
	memset( k, 0.0, sizeof( k ) );
	do_pagerank( n, r, A, 1.0, k );
}


void google_matrix( int n, float A[n][n], float d ){
	float teleport_prob = ((float)1.0 - (float)d ) / (float)n;

	int i, j;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			A[i][j] = (float)d * (float)A[i][j] + (float)teleport_prob;
	
	
}

/*
* How to handle pages with no outgoing links ( sinks ) .
*	1) Original paper suggests removing any links to those pages.
*	2) Have an outgoing link from sink to every other page in system. 
* I choose the later.  
*/
void fix_danglelink( int n, float A[n][n] ){
	float p = (float)1.0 /(float)n;
	int i,j;

	for( i = 0; i < n; i++ ){
		for( j = 0; j < n && A[i][j] == 0.0; j++ );	

		// so row i is a sink, set outlinks to all.
		if( j >= n ){
			for( j = 0; j < n; j++ ){
				A[i][j] = (float) 1.0/(float)n; 
			} 
		}
	}
}

void init_uniform( int n, int m, float A[n][m] )
{
	float count;
	int i, j;
	for( i = 0; i < n; i++ ){
		count = 0.0;	
		for( j = 0; j < m; j++ ){
			if( A[i][j] > 0.0 )
				count = (float)count + (float)1.0;
		}

		for( j = 0; j < m; j++ ){
			if( A[i][j] > 0.0 )
				A[i][j] = ((float)1.0 / (float)count);
		}
	}
}


int main( int argc, char* argv[] ){
	// I know this is horrible, but it makes it easy to switch examples so screw it! 
	#define INPUT_MATRIX( m )	\
		const int n = m ## _N;	\
		float A[ m ## _N ][ m ## _N ] = m;	\
		float r[ m ## _N ] = { [ 0 ... ( ( m ## _N ) - 1 ) ] = 1.0 }

//#undef _VERBOSE		// trust me you don't want to print that matrix out :)
//#undef _VVERBOSE

	// TODO: Changthis to one of the examples
#if defined _MAT_TWITTER
	INPUT_MATRIX( TWITTER );
#elif defined _MAT_EXAMPLE3
	INPUT_MATRIX( EXAMPLE3 );
#else
	INPUT_MATRIX( SIMPLE );
#endif

	// init rows to be uniform distribution ( even if already so this will work ).
	init_uniform( n, n, A );	
	init_uniform( 1, n, r );

#ifdef _VERBOSE
	printf("T1:\n");	
	mat_print( n, n, A );
	printf("\n");
#endif

#ifdef _GOOGLEMATRIX	 
	google_matrix( n, A, DAMP_FACTOR );
#else		// if not using google matrix we still need to fix dangling links
	fix_danglelink( n, A );	
#endif

//#undef _VERBOSE 	
#ifdef _VERBOSE
	printf("T:\n");	
	mat_print( n, n, A );
	printf("\n");
#endif

#ifdef _GOOGLEMATRIX	// incoporate teleportation into intial matrix
	eigenvector( n, r, A );
#else			// do teleportation every iteration
	PageRank( n, r, A );
#endif
	
	printf("r:\n");
	mat_print( 1, n, r );
	return 0;
}


