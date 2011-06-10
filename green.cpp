#include "header.h"



double	cost			(const LinkState& s) { return s.first(); } 
double	capacity		(const LinkState& s) { return s.second(); }

node	source			(const Demand& k) { return k.first(); }
node	target			(const Demand& k) { return k.second(); } 
double	traffic			(const Demand& k) { return k.third(); }

std::string	repr		(const LinkState& l) { std::ostringstream buffer; buffer << l; return buffer.str(); }

std::string		repr(const Demand& k)
{
	return "k["+ repr(source(k))+"->" + repr(target(k))+":" +repr(traffic(k))+"]";
}

std::string		flow_repr(const list<edge>& p, const Demand& k)
{
	return "fpk_" + repr(p) + "_" + repr(k);
}

std::string		flow_repr(const edge e)
{
	edge e_ = g.reversal(e); 
	assert(e_ != nil);
	edge l = min(e,e_);
	return "fl_" + repr(l);
}

std::string		choice_repr(const edge e, const LinkState& ls)
{
	assert( compare(ls,super_min)!=0 );
	assert( compare(ls,super_max)!=0 );
	edge e_ = g.reversal(e); 
	assert(e_ != nil);
	edge l = min(e,e_);
	return "x_" + repr(l) + "_" + repr(ls);
}

edge_array<double> calculate_utilization
( const edge_array<double>& existing, const list<Demand>& K,
  const edge_array<LinkState>& plan, bool& success)
{
	//create lp and solve
	lp_Program lp; Demand k; edge e, e_;

	//objective
	lp.objective += lp_Atom(1.0,"B");

	dictionary<Demand,list<list<edge> > > Pk;
	forall(k,K) Pk.insert( k, edge_disjoint_paths(source(k),target(k)) );
	
	//constraint 8
	forall(k,K)
	{
		lp_Constraint c; c.op = Eq; c.rhs = traffic(k);
		list<list<edge> > pk = Pk.access(k); list<edge> p;
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
			list<list<edge> > pk = Pk.access(k); list<edge> p;
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
		lp_Constraint c; c.op = Le; c.rhs = capacity(plan[e]);
		c.lhs += lp_Atom( 1.0, flow_repr(e) );
		lp.constraints += c;
	}

	//constraint Beta
	forall_edges(e,g)
	{
		lp_Constraint c; c.op = Le; c.rhs = 0;
		c.lhs += lp_Atom( 1.0, flow_repr(e) );
		c.lhs += lp_Atom( -1.0, "B" ); 
		lp.constraints += c;
	}


	dictionary<std::string,double> solution;
	solve(lp,solution);
	if( solution.size()==0 ) { success = false; edge_array<double> _(g); return _; }

	edge_array<double> util(g);
	forall_edges(e,g) { util[e] = solution.access(flow_repr(e)); }
	success = true;
	return util - existing;
}

list<LinkState> all_states;
LinkState   super_min = LinkState(-999999,-999999);
LinkState	super_max = LinkState(9999999,9999999);
LinkState	min(){ all_states.sort(); return all_states.head(); }
LinkState	max(){ all_states.sort(); return all_states.tail(); }
LinkState	nextup(const LinkState& l)
{
	all_states.sort();
	LinkState s;
	forall(s,all_states)
	if( compare(capacity(l),capacity(s)) < 0)
		return s;
	return super_max;
}


LinkState	nextdown(const LinkState& l)
{
	all_states.sort();
	all_states.reverse();
	LinkState s;
	forall(s,all_states)
	if( compare(capacity(l),capacity(s)) > 0)
		return s;
	return super_min;
}




list<list<edge> >		edge_disjoint_paths		(const node src, const node tgt)
{
	edge_array<double> cost(g); edge e;
	forall_edges(e,g) cost[e] = 1.0;

	list<list<edge>> allPaths;
	node_array<double> dist(g);
	node_array<edge>  pred(g);	

	DIJKSTRA_T(g, src, cost, dist, pred);
	while( pred[tgt] != nil )
	{		
		list<edge> path = COMPUTE_SHORTEST_PATH(g,src,tgt,pred);
		allPaths.push( path );

		forall(e,path)
		{
			g.hide_edge(e);
			g.hide_edge( g.reversal(e) );
		}

		DIJKSTRA_T(g, src, cost, dist, pred);
	}
	g.restore_all_edges();

	return allPaths;
}

list<edge>				shortest_path			(const node src, const node tgt)
{
	edge_array<double> cost(g); edge e;
	forall_edges(e,g) cost[e] = 1.0;

	node_array<double> dist(g);
	node_array<edge>  pred(g);	

	DIJKSTRA_T(g, src, cost, dist, pred);
	assert( pred[tgt] != nil );
		
	return COMPUTE_SHORTEST_PATH(g,src,tgt,pred);
}


edge_array<double> sum_flows (const list<edge_array<double>>& grp, const int slice)
{
	edge_array<double> _sum(g); edge e;
	forall_edges(e,g) _sum[e] = 0;

	for(int i=max(0,grp.size()-slice);i<grp.size(); i++)
	{
		edge_array<double> item = grp.inf(grp.get_item(i));
		forall_edges(e,g) _sum[e] += item[e];
	}

	return _sum;
}

edge_array<double> operator- (const edge_array<double>& u1, const edge_array<double>& u2)
{
	edge_array<double> ur(g); edge e;
	forall_edges(e,g) ur[e] = u1[e] - u2[e];
	return ur;
}
