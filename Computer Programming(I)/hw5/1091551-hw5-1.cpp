#include <iostream>
using namespace std;

// returns the maximum element in the array relevance
int recursiveMax( int last );

// prints all the URLs of the web pages with the highest relevance
void recursiveOutput( int max, int first );

char webPages[ 10 ][ 101 ];
int relevance[ 10 ];
int main()
{
   int n;
   cin >> n;
   for( int i = 1; i <= n; i++ )
   {
      for( int j = 0; j < 10; j++ )
         cin >> webPages[ j ] >> relevance[ j ];

      int max = recursiveMax( 9 );

      cout << "Case #" << i << ":\n";
      recursiveOutput( max, 0 );
   }

   system( "pause" );
}

int recursiveMax( int last )
{
    if (last == 0)
        return relevance[0];
    else {
        int max = recursiveMax(last - 1);
        if (max > relevance[last])
            return max;
        else if (max < relevance[last])
            return relevance[last];
        else if (max == relevance[last])
            return max, relevance[last];
    }
}

void recursiveOutput(int max, int first)
{
    max = recursiveMax(9);
    if ( relevance[first]==max&&first<10) {
        cout << webPages[first] << endl;
        recursiveOutput(relevance[first + 1], first+1);
    }
    else if(relevance[first] != max && first < 10){
        recursiveOutput(relevance[first + 1], first+1);
    }
    
        
     
}