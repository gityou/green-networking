#include "header.h"


edge_array<double> solve_optimal( const edge_array<double>& existing, const list<Demand>& K )
{
	lp_Program lp; Demand k; edge e, e_;

	dictionary<Demand,list<list<edge> > > Pk;
	forall(k,K) Pk.insert( k, edge_disjoint_paths(source(k),target(k)) );

	//objective constraint 7
	forall_edges(e,g)
	if( e < g.reversal(e) )
	for( LinkState ls = min(); compare(ls,max())<=0; ls = nextup(ls) )
	{
		lp.objective += lp_Atom( cost(ls), choice_repr(e,ls) );
		lp.binary_vars += choice_repr(e,ls);
	}

	//constraint 8
	forall(k,K)
	{
		lp_Constraint c; c.op = Eq; c.rhs = traffic(k);
		list<list<edge> > pk = Pk.access(k);
		list<edge> p;
		forall(p,pk)
		{
			c.lhs += lp_Atom( 1.0, flow_repr(p,k) ); 
		}
		lp.constraints += c;
	}

	//constraint 9
	forall_edges(e,g)
	{
		lp_Constraint c; c.op = Eq; c.rhs = 0.0;

		c.lhs += lp_Atom( 1.0, flow_repr(e) );

		e_ = g.reversal(e); 
		forall(k,K)
		{
			list<list<edge> > pk = Pk.access(k); 
			list<edge> p;
			forall(p,pk)
			if( contains(p,e) || contains(p,e_) )
			{
				c.lhs += lp_Atom( -1.0, flow_repr(p,k) );
			}
		}
		lp.constraints += c;
	}

	//constraint 10
	forall_edges(e,g)
	{
		lp_Constraint c; c.op = Le; c.rhs = capacity( max() ) - existing[e];
		c.lhs += lp_Atom( 1.0, flow_repr(e) );
		lp.constraints += c;
	}

	//if capacity of this link > flow demand, this sequence must be 1
	forall_edges(e,g)
	if( e < g.reversal(e) )
	for( LinkState j = min(); compare(j,max())<=0; j = nextup(j) )
	{
		lp_Constraint c; c.op = Le; c.rhs = -capacity(j)/capacity(max());
		c.lhs += lp_Atom( -1/capacity(max()), flow_repr(e) );

		for(LinkState i = min(); compare(i,j)<=0; i = nextup(i))
			c.lhs += lp_Atom( -1.0, choice_repr(e,i) );

		lp.constraints += c;
	}

	//if capacity of this link < flow demand, this sequence must be 0
	forall_edges(e,g)
	if( e < g.reversal(e) )
	for( LinkState j = min(); compare(j,max())<=0; j = nextup(j) )
	{
		lp_Constraint c; c.op = Le; c.rhs = 1 + capacity(j)/capacity(max());
		c.lhs += lp_Atom( +1/capacity(max()), flow_repr(e) );

		//upto and including j
		for(LinkState i = min(); compare(i,j)<=0; i=nextup(i))
			c.lhs += lp_Atom( 1.0, choice_repr(e,i) );

		lp.constraints += c;
	}


	dictionary<std::string,double> solution;
	solve(lp,solution);
	if( solution.size()==0 ) { fail("no feasible solution"); }

	edge_array<double> util(g);
	forall_edges(e,g) { util[e] = solution.access(flow_repr(e)); }
	return util;
}