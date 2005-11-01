#include <vector>
#include "seispp.h"
#include "stock.h"
using namespace SEISPP;
namespace SEISPP{
/* This file contains tools that operator on ensemble objects
// to subset or sort ensembles in common ways.  May eventually
// generate a generalized sort or subset method, but for now
// it will be built up in stages with the most common uses
// built first.  All the functions in this file should return
// a pointer to a new Ensemble object (scalar or 3c time
// series) derived from a parent.  Thus, in all cases the
// result is a copy created with a new operator.  
*/

//@{
// Builds a new ensemble of members that satisfy unix regular expression
// for sta and chan attributes passed as sta_expr and chan_expr.
//
// @param parent original ensemble to be subsetted
// @param sta_expr unix regular expression to apply to sta Metadata
//    attribute
// @param chan_expr unix regular expression to apply to chan Metadata 
//    attribute
//
//@author Gary L. Pavlis
//@}
TimeSeriesEnsemble *StaChanRegExSubset(TimeSeriesEnsemble& parent,
	string sta_expr, string chan_expr)
{
	int i;
	string sta;
	string chan;
	Hook **stahook=NULL;
	Hook **chanhook=NULL;
	// This clones metadata for the ensemble, but allocs no space
	// for data members.  Since we have no way of knowing the
	// output size this is a good use of the automatic resizing
	// ability of the stl vector
	TimeSeriesEnsemble *result=new 
		TimeSeriesEnsemble(dynamic_cast<Metadata&>(parent),0);

	for(i=0;i<parent.member.size();++i)
	{
		try{
			sta=parent.member[i].get_string("sta");
			chan=parent.member[i].get_string("chan");
			if( strmatches(const_cast<char *>(sta.c_str()),
				const_cast<char *>(sta_expr.c_str()),stahook)
			 && strmatches(const_cast<char *>(chan.c_str()),
				const_cast<char *>(chan_expr.c_str()),chanhook) )
			{
				result->member.push_back(parent.member[i]);
		
			}

		} catch (MetadataGetError mde) {
			cerr << "StaChanRegExSubset (Warning):  sta/chan metadata error in building ensemble subset. "<<endl;
			mde.log_error();
		}
	}
	return(result);
}
} // End SEISPP namespace