// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __ConvexHull__hxx__
#define __ConvexHull__hxx__

// -------------------------------------------------------------------------
template< class _TInIt, class _TOutIt >
void ConvexHull::
BruteForce( _TInIt in_b, _TInIt in_e, _TOutIt out )
{
  for( _TInIt p = in_b; p != in_e; ++p )
  {
    for( _TInIt q = in_b; q != in_e; ++q )
    {
      if( p != q )
      {
        bool all_right = true;
        for( _TInIt r = in_b; r != in_e; ++r )
        {
          if( p != r && q != r )
          {
            double px = (*p)[0];
            double py = (*p)[1];
            double qx = (*q)[0];
            double qy = (*q)[1];
            double rx = (*r)[0];
            double ry = (*r)[1];
            double test = ((qx - px) * (ry - py)) - ((rx - px) * (qy - py));
            all_right &= test < 0;
          } // end if
        } // end for

        if( all_right )
        {
          *out = *p;
          *out = *q;
        } // end if
      } // end if
    } // end if
  } // end if
}

// -------------------------------------------------------------------------
template< class _TInIt, class _TOutIt >
void ConvexHull::
Incremental( _TInIt in_b, _TInIt in_e, _TOutIt out )
{
}

// -------------------------------------------------------------------------
template< class _TInIt, class _TOutIt >
void ConvexHull::
DivideAndConquer( _TInIt in_b, _TInIt in_e, _TOutIt out )
{
}

#endif // __ConvexHull__hxx__

// eof - ConvexHull.hxx
