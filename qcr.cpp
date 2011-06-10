#include "header.h"


//select edge with maximum Quality to Cost-Savings Ratio.
edge	max_QCR	(const edge_array<double>& util, const edge_array<LinkState>& plan)
{
	double max_qcr = 0;
	edge max_e;
	{
		edge e;
		forall_edges(e,g)
		if( compare(plan[e],max()) != 0 )
		{
			LinkState cs = plan[e];
			LinkState ns = nextup(cs);
			double e_cap = min( util[e], capacity(ns) );
			double e_gain = (e_cap-capacity(cs));
			double e_qcr = e_gain / (cost(ns)-cost(cs));
			if( e_qcr > max_qcr )
			{
				max_qcr = e_qcr;
				max_e = e;
			}
		}
	}

	assert( max_qcr > 0 );
	assert( compare(plan[max_e],max()) != 0 );

	return max_e;
}


edge_array<double> solve_qcr( const edge_array<double>& existing, const list<Demand>& K )
{
	node v; edge e;

	//calculate network utilization when all links are in maximal link-state
	edge_array<LinkState> plan(g);
	forall_edges(e,g) plan[e] = max();

	bool success;
	edge_array<double> open_util = calculate_utilization(existing,K,plan,success);
	if( !success ) fail("No feasible solution exists");


	//calculate if solution is feasible when all links are in minimal link-state
	forall_edges(e,g) plan[e] = min();


	//until solution is feasible, tune-up edge with maximal QCR
	edge_array<double> qcr_util = calculate_utilization(existing,K,plan,success);
	while( !success ) 
	{
		edge e = max_QCR(open_util,plan);
		LinkState tune_up = nextup(plan[e]);
		plan[e] = tune_up; plan[g.reversal(e)] = tune_up;
		qcr_util = calculate_utilization(existing,K,plan,success);
	}

	return qcr_util;
}