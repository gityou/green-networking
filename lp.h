

typedef two_tuple<double,std::string> lp_Atom;
double				multiplier		(const lp_Atom&);
std::string			variable_name	(const lp_Atom&);

enum	lp_Comparison			{ Eq, Le, Ge };
struct	lp_Constraint			{ set<lp_Atom> lhs; lp_Comparison op; double rhs; };

struct	lp_Program				{ set<lp_Atom> objective; list<lp_Constraint> constraints; set<std::string> binary_vars; };

std::ostream&		operator<<	(std::ostream& out, const lp_Comparison& a);
std::ostream&		operator<<	(std::ostream& out, const lp_Atom& a);
std::ostream&		operator<<	(std::ostream& out, const lp_Constraint& a); 
std::ostream&		operator<<	(std::ostream& out, const lp_Program& a); // lots of output; avoid handling strings in memory.

void				solve	(const lp_Program& lp, dictionary<std::string,double>& variables);