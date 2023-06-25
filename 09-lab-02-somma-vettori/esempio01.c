#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void printVector( float*, int, char[] );
int main() {

    int i, N, t, nloc, indice;
    float *a, *b, *c;

    srand( time( NULL ) );

    printf( "\nInserire N:" );
    scanf( "%d", &N );

    // allocazione
    a = ( float * ) calloc( N, sizeof( float ) );
    b = ( float * ) calloc( N, sizeof( float ) );
    c = ( float * ) calloc( N, sizeof( float ) );

    // lettura
    for ( i = 0; i < N; i++ )
        a[i] = rand() % 100 + 1;

    for ( i = 0; i < N; i++ )
        b[i] = rand() % 100 + 1;

    // Stampa 
    printVector( a, N, "Vector A:" );
    printVector( b, N, "Vector B:" );

    /**
     * Nucleo computazionale full parallel
     * tecnica semplificata per la ri-distribuzione delle locazione
     * pensata solo per size divisibili per il numero di thread
    */
    #pragma omp parallel private(nloc, i, indice) shared(a, b, c)
    { // se piu di un’istruzione
        
        t = omp_get_num_threads();
        nloc = N / t;

        printf( "sono %d, di %d: numeri %d\n", omp_get_thread_num(), t, nloc );
        for ( i = 0; i < nloc; i++ )
        {
            indice = i + nloc * omp_get_thread_num();
            c[ indice ] = a[ indice ] + b[ indice ];
        }

    } // fine direttiva

    // stampa finale
    printVector( c, N, "Vector C:" );
    
    printf( "\n" );
    return 0;
}

void printVector( float* a, int N, char name[] ) {
    printf( "\n%s:\n", name );
    for ( int i = 0; i < N; i++ )
        printf( "%f ", a[i] );
    printf( "\n" );
}
