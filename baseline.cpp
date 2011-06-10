#include "header.h"


edge_array<double> solve_baseline( const edge_array<double>& existing, const list<Demand>& K )
{
	edge_array<double> util(g); Demand k; edge e;
	forall_edges(e,g) util[e] = 0.0;
	forall(k,K)
	{
		list<edge> Pk = shortest_path(source(k),target(k));
		forall(e,Pk)
		{
			util[e] += traffic(k);
			util[g.reversal(e)] += traffic(k);
		}
	}
	return util;
}