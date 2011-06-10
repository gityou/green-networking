#include "header.h"


//select edge with minimum Reroute to Cost-Savings Ratio.
edge	min_RCR	(const edge_array<double>& util, const edge_array<LinkState>& plan)
{
	double min_rcr = 9999999999;
	edge min_e;
	{
		edge e;
		forall_edges(e,g)
		if( compare(plan[e],min()) != 0 )
		{
			LinkState cs = plan[e];
			LinkState ns = nextdown(cs);

			//double reroute = max( 0, (util.access(e)-capacity(ns));
			double reroute = 0>(util[e]-capacity(ns)) ?0:(util[e]-capacity(ns));
			double e_rcr = reroute / (cost(cs)-cost(ns));
			if( e_rcr < min_rcr )
			{
				min_rcr = e_rcr;
				min_e = e;
			}
		}
	}

	assert( min_rcr < 9999999999 );
	assert( compare(plan[min_e],min()) != 0 );

	return min_e;
}


edge_array<double> solve_rcr( const edge_array<double>& existing, const list<Demand>& K )
{
	//calculate network utilization when all links are in maximal link-state
	edge_array<LinkState> plan(g); edge e;
	forall_edges(e,g) plan[e] = max();

	bool success;
	edge_array<double> open_util = calculate_utilization(existing,K,plan,success);
	if( !success ) fail("No feasible solution exists");

	//until solution is feasible, tune-down edge with minimal RCR
	edge_array<double> cur_util = open_util, tmp_util = open_util;
	while( success ) 
	{
		e = min_RCR(open_util,plan);
		LinkState tune_down = nextdown(plan[e]);
		plan[e] = tune_down;
		plan[g.reversal(e)] = tune_down;

		cur_util = tmp_util;
		tmp_util = calculate_utilization(existing,K,plan,success);
	}
	return cur_util;
}