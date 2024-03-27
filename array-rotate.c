#include <stdio.h> 
#include <stdlib.h> 
#include <mem.h> 
#include <string.h> 

/*
rotate a MxN matrix. the most extiorier element clockview 1 step

*/

int array[3][4] = { 
    {1,2,3,4}, 
    {5,6,7,8}, 
    {9, 10, 11, 12} 
}; 

int array2[][8] = { 
    {1,2,3,4,5,6,7,       8}, 
    {22,2,3,4,5,6,7,      9}, 
    {21,2,3,4,5,6,7,      10}, 
    {20,2,3,4,5,6,7,      11}, 
    {19,18,17,16,15,14,13,12}, 
}; 

int shift( int *p, int step, int cnt ) 
{ 
    int overflow = p[step*(cnt-1)]; 

    for( int i = 0; i<cnt-1; i++ ) 
    { 
        p[step*(cnt-i-1) ] = p[step*(cnt -i -2)]; 
    } 
    return overflow; 
} 

void prt_ar( int *p, int row, int col ) 
{ 
    for( int i = 0; i < row ; i++){ 
        for( int j = 0; j < col; j++ ) 
            printf( "%d,", p[i*col + j]); 
        printf("\n"); 
    }
    printf("\n"); 
}

void rotate_array( int *p, int row, int col )
{
    // rotate top row left
    int * start_addr = p; // the address of the first element 
    int overflow = shift( start_addr, 1, col ); // step = 1, count = col

    prt_ar( p, row, col); 
    printf("overflow=%d\n", overflow);

    //rotate most left columne down
    start_addr = p + 2*col - 1; // the address of the last element of 2nd row
    int overflow2 = shift( start_addr, col, row-1);
    *start_addr = overflow;
    overflow = overflow2;

    prt_ar( p, row, col); 
    printf("overflow=%d\n", overflow);

    //rotate the bottom to right
    start_addr = p + row*col -2; // the address of the 2nd last element 
    overflow2 = shift( start_addr, -1, col-1);
    *start_addr = overflow;
    overflow = overflow2;

    prt_ar( p, row, col); 
    printf("overflow=%d\n", overflow);

    //rotate the right colume up
    start_addr =  p + (row-2)*col; // the address of the 2nd last row
    overflow2 = shift( start_addr, -col, row-1);
    *start_addr = overflow;

    prt_ar( p, row, col); 
    printf("overflow=%d\n", overflow);

}

/*
method2 of rotate 
*/
void rotate_array2( int *p, int row, int col )
{
    int *p1 = malloc( row * col * sizeof(int));

    // make a copy of array
    memcpy(p1, p, row * col * sizeof(int));
    prt_ar( p1, row, col);

    // rotate top row left
    int i = 0;
    for( i = col - 1; i > 0; i-- ){
        p[i] = p1[i-1];
    }
    //prt_ar( p, row, col);

    // rotate right column down
    for( i = row*col -1; i > col; i = i - col ){
        p[i] = p1[i-col];
    }
    //prt_ar( p, row, col);

    // rotate bottom row left
    for( i = (row-1)*col; i < row*col-1; i++ ){
        p[i] = p1[i+1];
    }
    //prt_ar( p, row, col);

    //rotate left column up
    for( i = 0; i < row - 1; i ++ ){
        p[i*col] = p1[(i+1)*col];
    }
    prt_ar( p, row, col);

    free( p1 );

}

int main(){ 
   // rotate_array( &array[0][0], 3, 4 );

    //rotate_array( &array2[0][0], 5, 8 );

    rotate_array2( &array2[0][0], 5, 8 );

    return 0; 
}



/*
1,2,3,4,5,6,7,8,
22,2,3,4,5,6,7,9,
21,2,3,4,5,6,7,10,
20,2,3,4,5,6,7,11,
19,18,17,16,15,14,13,12,

22,1,2,3,4,5,6,7,
21,2,3,4,5,6,7,8,
20,2,3,4,5,6,7,9,
19,2,3,4,5,6,7,10,
18,17,16,15,14,13,12,11,
*/
