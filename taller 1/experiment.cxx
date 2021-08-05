#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>

#include "ConvexHull.h"

// -------------------------------------------------------------------------
template< class _TIt >
void SaveAsOBJ(
  const std::string& fname, _TIt b, _TIt e, bool save_line = false
  )
{
  std::stringstream o;
  o << "# Vertices" << std::endl;
  for( _TIt i = b; i != e; ++i )
    o << "v " << ( *i )[ 0 ] << " " << ( *i )[ 1 ] << " 0" << std::endl;

  if( save_line )
  {
    o << "# Line" << std::endl;
    o << "l";
    unsigned int c = 1;
    for( _TIt i = b; i != e; ++i )
      o << " " << c++;
    o << std::endl;
  } // end if

  std::ofstream os( fname.c_str( ) );
  os.write( o.str( ).c_str( ), o.str( ).size( ) );
  os.close( );
}

// -------------------------------------------------------------------------
double getPointClockwiseAngle(const std::vector<double> point){
  return -atan2(point[0], -point[1]);
}

// -------------------------------------------------------------------------
template< class _TIt >
void sortVectorClockwise(_TIt start, _TIt end){
  std::sort(
    start,
    end,
    [] (const std::vector<double>& a, const std::vector<double>& b){
      return getPointClockwiseAngle(a) < getPointClockwiseAngle(b);
    });
}


// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 6 )
  {
    std::cerr
      << "Usage: " << argv[ 0 ]
      << " number_of_points out_points out_bf out_incremental"
      << " out_divide_and_conquer" << std::endl;
    return( EXIT_FAILURE );
  } // end if
  unsigned long n = std::atoi( argv[ 1 ] );
  std::string out_points = argv[ 2 ];
  std::string out_bf = argv[ 3 ];
  std::string out_inc = argv[ 4 ];
  std::string out_dc = argv[ 5 ];
  
  // Prepare a random device
  std::random_device rd;
  std::mt19937 mt( rd( ) );
  std::uniform_real_distribution< double > dist( -100, 100 );

  // Cloud of random points
  std::vector< std::vector< double > > points;
  for( unsigned long i = 0; i < n; ++i )
    points.push_back( { dist( mt ), dist( mt ) } );

  // Compute hulls
  std::vector< std::vector< double > > ch_bf, ch_inc, ch_dc;
  ConvexHull::BruteForce(
    points.begin( ), points.end( ),
    std::back_inserter( ch_bf )
    );

  //Sort compute hull clockwise
  sortVectorClockwise(ch_bf.begin(), ch_bf.end());
  ch_bf.push_back(ch_bf[0]);

  // Save outputs
  SaveAsOBJ( out_points, points.begin( ), points.end( ) );
  SaveAsOBJ( out_bf, ch_bf.begin( ), ch_bf.end( ), true );
  SaveAsOBJ( out_inc, ch_inc.begin( ), ch_inc.end( ), true );
  SaveAsOBJ( out_dc, ch_dc.begin( ), ch_dc.end( ), true );

  /* TODO
     std::vector< TPoint > ch_naive;
     auto start = std::chrono::steady_clock::now( );
     ConvexHull_Naive( P.begin( ), P.end( ), ch_naive );
     auto end = std::chrono::steady_clock::now( );
     auto t_naive = std::chrono::duration_cast< std::chrono::nanoseconds >( end - start ).count( );
     std::cout << ch_naive.size( ) << " (" << ( double( t_naive ) / 1e9 ) << " s)" << std::endl;
  */

  return( EXIT_SUCCESS );
}

// eof - experiment.cxx
