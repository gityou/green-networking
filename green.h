

typedef two_tuple<double,double> LinkState;
double	cost			(const LinkState&);
double	capacity		(const LinkState&);
std::string	repr		(const LinkState&);


typedef three_tuple<node,node,double> Demand;
node	source			(const Demand&);
node	target			(const Demand&);
double	traffic			(const Demand&);

std::string		flow_repr(const list<edge>& p, const Demand& k);
std::string		flow_repr(const edge e);
std::string		choice_repr(const edge e, const LinkState& ls);

edge_array<double> calculate_utilization
( const edge_array<double>& existing, const list<Demand>& K,
  const edge_array<LinkState>& plan, bool& success);

edge_array<double> sum_flows (const list<edge_array<double>>&, const int);
edge_array<double> operator- (const edge_array<double>&, const edge_array<double>&);

edge_array<double> solve_baseline( const edge_array<double>& existing, const list<Demand>& K );
edge_array<double> solve_qcr( const edge_array<double>& existing, const list<Demand>& K );
edge_array<double> solve_rcr( const edge_array<double>& existing, const list<Demand>& K );
edge_array<double> solve_optimal( const edge_array<double>& existing, const list<Demand>& K );

extern list<LinkState> all_states;
extern LinkState super_min;
extern LinkState super_max;
LinkState	max();
LinkState	min();
LinkState	nextup(const LinkState& l);
LinkState	nextdown(const LinkState& l);

list<list<edge> >		edge_disjoint_paths		(const node src, const node tgt);
list<edge>				shortest_path			(const node src, const node tgt);

extern GRAPH<int,double> g;