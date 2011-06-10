#include "header.h"


void	simple4()
{
	node v0 = g.new_node(0);
	node v1 = g.new_node(1);
	node v2 = g.new_node(2);
	node v3 = g.new_node(3);

	g.new_edge(v0,v1,1.0);
	g.new_edge(v1,v0,1.0);

	g.new_edge(v1,v2,1.0);
	g.new_edge(v2,v1,1.0);

	g.new_edge(v2,v3,1.0);
	g.new_edge(v3,v2,1.0);
}

void	abilene_research()
{
	node v0 = g.new_node(0);
	node v1 = g.new_node(1);
	node v2 = g.new_node(2);
	node v3 = g.new_node(3);
	node v4 = g.new_node(4);
	node v5 = g.new_node(5);
	node v6 = g.new_node(6);
	node v7 = g.new_node(7);
	node v8 = g.new_node(8);
	node v9 = g.new_node(9);

	// <out of 0>
	g.new_edge(v0,v1,1.0);
	g.new_edge(v1,v0,1.0);

	g.new_edge(v0,v2,1.0);
	g.new_edge(v2,v0,1.0);

	g.new_edge(v0,v3,1.0);
	g.new_edge(v3,v0,1.0);
	// </out of 0>

	// </out of 1>
	g.new_edge(v1,v3,1.0);
	g.new_edge(v3,v1,1.0);
	// </out of 1>

	// <out of 2>
	g.new_edge(v2,v5,1.0);
	g.new_edge(v5,v2,1.0);
	// </out of 2>

	// <out of 3>
	g.new_edge(v3,v4,1.0);
	g.new_edge(v4,v3,1.0);
	// </out of 3>

	// <out of 4>
	g.new_edge(v4,v5,1.0);
	g.new_edge(v5,v4,1.0);

	g.new_edge(v4,v6,1.0);
	g.new_edge(v6,v4,1.0);
	// </out of 4>

	// <out of 5>
	g.new_edge(v5,v7,1.0);
	g.new_edge(v7,v5,1.0);
	// </out of 5>

	// <out of 6>
	g.new_edge(v6,v7,1.0);
	g.new_edge(v7,v6,1.0);

	g.new_edge(v6,v8,1.0);
	g.new_edge(v8,v6,1.0);
	// </out of 6>

	// <out of 7>
	g.new_edge(v7,v9,1.0);
	g.new_edge(v9,v7,1.0);
	// </out of 7>

	// <out of 8>
	g.new_edge(v8,v9,1.0);
	g.new_edge(v9,v8,1.0);
	// </out of 8>
}

void	random20()
{
	GRAPH<point,double> graph_from_file;
	graph_from_file.read("C:\\random20.graph");

	g.clear();

	node_array<node> r2g(graph_from_file); node v; int vi = 0;
	forall_nodes(v,graph_from_file) r2g[v] = g.new_node(vi++);

	edge e;
	forall_edges(e,graph_from_file) 
		g.new_edge(
			r2g[source(e)],
			r2g[target(e)],
			1 );
}

void	nsf()
{
	node v0 = g.new_node(0);
	node v1 = g.new_node(1);
	node v2 = g.new_node(2);
	node v3 = g.new_node(3);
	node v4 = g.new_node(4);
	node v5 = g.new_node(5);
	node v6 = g.new_node(6);
	node v7 = g.new_node(7);
	node v8 = g.new_node(8);
	node v9 = g.new_node(9);
	node v10 = g.new_node(10);
	node v11 = g.new_node(11);
	node v12 = g.new_node(12);
	node v13 = g.new_node(13);

	// <out of 0>
	g.new_edge(v0,v1,1.0);
	g.new_edge(v1,v0,1.0);

	g.new_edge(v0,v2,1.0);
	g.new_edge(v2,v0,1.0);

	g.new_edge(v0,v8,1.0);
	g.new_edge(v8,v0,1.0);
	// </out of 0>

	// <out of 2>
	g.new_edge(v2,v1,1.0);
	g.new_edge(v1,v2,1.0);

	g.new_edge(v2,v5,1.0);
	g.new_edge(v5,v2,1.0);
	// </out of 2>

	// <out of 3>
	g.new_edge(v3,v1,1.0);
	g.new_edge(v1,v3,1.0);

	g.new_edge(v3,v4,1.0);
	g.new_edge(v4,v3,1.0);

	g.new_edge(v3,v10,1.0);
	g.new_edge(v10,v3,1.0);
	// </out of 3>

	// <out of 5>
	g.new_edge(v5,v4,1.0);
	g.new_edge(v4,v5,1.0);

	g.new_edge(v5,v7,1.0);
	g.new_edge(v7,v5,1.0);

	g.new_edge(v5,v12,1.0);
	g.new_edge(v12,v5,1.0);
	// </out of 5>

	// <out of 6>
	g.new_edge(v6,v4,1.0);
	g.new_edge(v4,v6,1.0);

	g.new_edge(v6,v8,1.0);
	g.new_edge(v8,v6,1.0);
	// </out of 6>

	// <out of 9>
	g.new_edge(v9,v7,1.0);
	g.new_edge(v7,v9,1.0);

	g.new_edge(v9,v8,1.0);
	g.new_edge(v8,v9,1.0);

	g.new_edge(v9,v11,1.0);
	g.new_edge(v11,v9,1.0);

	g.new_edge(v9,v13,1.0);
	g.new_edge(v13,v9,1.0);
	// </out of 9>

	// <out of 11>
	g.new_edge(v11,v12,1.0);
	g.new_edge(v12,v11,1.0);
	// </out of 11>

	// <out of 13>
	g.new_edge(v13,v10,1.0);
	g.new_edge(v10,v13,1.0);

	g.new_edge(v13,v12,1.0);
	g.new_edge(v12,v13,1.0);
	// </out of 13>
}

double  random(const double start, const double end)
{
	return start + (end-start) * rand() / (RAND_MAX + 1.0);
}

list<Demand> krandom(const int k)
{
	list<Demand> K;
	while(K.size() < k)
	{
		array<node> nodes(g.number_of_nodes());
		node v; int i = 0;
		forall_nodes(v,g) nodes[i++] = v;
		node src = nodes[rand()%nodes.size()];
		node tgt = nodes[rand()%nodes.size()];
		if(src != tgt)
			K += Demand( src,tgt,random(50,100));
	}
	return K;
}

GRAPH<int,double> g;

double calc_cost( const edge_array<double>& util )
{
	edge e; double total_cost = 0;

	forall_edges(e,g)
	if( e < g.reversal(e) )
	{
		LinkState ls = min();
		while(capacity(ls) < util[e]-FERR) ls = nextup(ls);
		assert( compare(ls,super_max) != 0 );
		total_cost += cost(ls);
	}
	return total_cost;
}

void dyn_info(const std::string& s, const list<edge_array<double> >& util, const int peak_K)
{
	list<edge_array<double>> c = util;

	double total_cost = 0;
	double incremental_cost = 0;

	while( c.size() > 0 )
	{
		double current_cost = calc_cost(sum_flows(c,peak_K));
		c.pop_back();
		double prev_cost = calc_cost(sum_flows(c,peak_K-1));

		assert(prev_cost <= current_cost);

		total_cost += current_cost;
		incremental_cost += current_cost - prev_cost;
	}

	println("mode: " + s);
	println("average total cost = " +repr(total_cost/util.size()) );
	println("average incremental cost = " +repr(incremental_cost/util.size()) );
	println("");
	//average total cost
	//average incremental cost
}


int main(int argc, char* argv[])
{
	all_states.append( LinkState( 0.84, 10 ) );
	all_states.append( LinkState( 0.96, 100 ) );
	all_states.append( LinkState( 1.8, 1000 ) );
	all_states.append( LinkState( 10, 10000 ) );

	if( argc==5 )
	{
		if(	strcmp(argv[1],"abilene")==0 ) abilene_research();
		else if( strcmp(argv[1],"nsf")==0 ) nsf();
		else if( strcmp(argv[1],"simple4")==0 ) simple4();
		else if( strcmp(argv[1],"random20")==0 ) random20();
		else fail("nw ::= abilene | nsf | simple4");
		{
			edge e, e_;
			forall_edges(e,g)
			forall_edges(e_,g)
			if( source(e)==target(e_) && target(e)==source(e_) )
			{
				g.set_reversal(e,e_);
				g.set_reversal(e_,e);
			}
			forall_edges(e,g)
			{
				assert( g.reversal(e)!=nil );
				assert( target(g.reversal(e)) == source(e) );
				assert( source(g.reversal(e)) == target(e) );
			}
		}

		int peak_K = atoi(argv[3]);
		srand(atoi(argv[4]));

		if( strcmp(argv[2],"multi")==0 )
		{
			list<Demand> K = krandom(peak_K);
			edge_array<double> zero(g); edge e; forall_edges(e,g) zero[e] = 0;
			double baseline_cost = calc_cost(solve_baseline(zero,K));
			double rcr_cost = calc_cost(solve_rcr(zero,K));
			//

			printf( "baseline cost = %f\n",baseline_cost );
			printf( "rcr cost = %f\n",rcr_cost );
			printf( "\n" );

			printf( "rcr improvement = %2.2f\n",(baseline_cost - rcr_cost) / baseline_cost );
			printf( "\n" );

			double optimal_cost = calc_cost(solve_optimal(zero,K));
			printf( "optimal cost = %f\n",optimal_cost );
			printf( "optimal improvement = %2.2f\n" ,(baseline_cost - optimal_cost) / baseline_cost );
			printf( "baseline slack = %2.2f\n",(baseline_cost - optimal_cost) / optimal_cost );
			printf( "rcr slack = %2.2f\n" ,(rcr_cost - optimal_cost) / optimal_cost );
		} else if( strcmp(argv[2],"single")==0 )
		{
			list<edge_array<double> > bu;
			list<edge_array<double> > ou;

			for(int i=0; i<100; i++)
			{
				list<Demand> K = krandom(1);

				//each produces as result the incremental flow allocation
				bu.append( solve_baseline(sum_flows(bu,peak_K-1),K) );
				ou.append( solve_optimal(sum_flows(ou,peak_K-1),K) );
			}
			dyn_info("baseline",bu,peak_K);
			dyn_info("optimal",ou,peak_K);
		} else fail("mode ::= single | multi");

	} else {
		println ("no valid command specified, doing nothing.");
		println ("commands:");
		println	("	(nw:nw, mode:mode, peak-K:int, srand:int)");
		println	("	nw ::= abilene | nsf | simple4 | random20");
		println ("	mode ::= single | multi");
	}

	return 0;
}


/*
int main(int argc, char* argv[])
{
	all_states.append( LinkState( 0.84, 10 ) );
	all_states.append( LinkState( 0.96, 100 ) );
	all_states.append( LinkState( 1.8, 1000 ) );
	all_states.append( LinkState( 10, 10000 ) );

	if( argc==4 )
	{
		if(	strcmp(argv[1],"abilene")==0 ) abilene_research();
		else if( strcmp(argv[1],"nsf")==0 ) nsf();
		else if( strcmp(argv[1],"simple4")==0 ) simple4();
		else fail("nw ::= abilene | nsf | simple4");
		{
			edge e, e_;
			forall_edges(e,g)
			forall_edges(e_,g)
			if( source(e)==target(e_) && target(e)==source(e_) )
			{
				g.set_reversal(e,e_);
				g.set_reversal(e_,e);
			}
		}

		int peak_K = atoi(argv[2]);
		srand(atoi(argv[3]));


		double baseline_total_cost = 0;
		double qcr_total_cost = 0;
		double rcr_total_cost = 0;
		double optimal_total_cost = 0;

		double baseline_incremental_cost = 0;
		double qcr_incremental_cost = 0;
		double rcr_incremental_cost = 0;
		double optimal_incremental_cost = 0;

		edge e;
		edge_array<double> optimal_util(g);
		forall(e,g) optimal_util[e] = 0;

		list<Demand> K;
		for(int i=0; i<100; i++)
		{
			if( K.size() > peak_K ) K.pop();

			//double baseline_pre_cost = TODO;
			//double qcr_pre_cost = TODO;
			//double rcr_pre_cost = TODO;
			double optimal_pre_cost = run_simulation_optimal(K,);
			K.append( krandom(1).pop() );
			//double baseline_post_cost = TODO;
			//double qcr_post_cost = TODO;
			//double rcr_post_cost = TODO;
			two_tuple<double optimal_post_cost = run_simulation_single_optimal(K);

			baseline_total_cost += run_simulation_baseline(K);
			qcr_total_cost += run_simulation_qcr(K);
			rcr_total_cost += run_simulation_rcr(K);
		}
		println( "baseline average cost = " + repr(baseline_total_cost/100) );
		println( "qcr average cost = " + repr(qcr_total_cost/100) );
		println( "rcr average cost = " + repr(rcr_total_cost/100) );

	} else {
		println ("no valid command specified, doing nothing.");
		println ("commands:");
		println	("	(nw:nw, peak-K:int, srand:int)");
		println	("	nw ::= abilene | nsf | simple4");
	}

	return 0;
}
*/
