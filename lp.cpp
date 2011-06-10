
#include "header.h"
#include "lp_lib.h"

double				multiplier		(const lp_Atom& a) { return a.first(); }
std::string			variable_name	(const lp_Atom& a) { return a.second(); }

void				clear_row		(REAL* row, const dictionary<std::string,double>& vars)
{
	row[0] = 0.0;
	for(int i=0; i < vars.size(); i++)
		row[1+i] = 0.0;
}


void				solve	(const lp_Program& lp, dictionary<std::string,double>& vars)
{
	//if(lp.binary_vars.size()>0) std::cout << lp;
	println("enter solver");

	vars.clear();

	lp_Constraint c; lp_Atom a;
	forall(a,lp.objective) 
		vars.insert( variable_name(a), 0.0 );

	forall(c,lp.constraints)
	forall(a,c.lhs) 
		vars.insert( variable_name(a), 0.0 );

	lprec* lpr = make_lp(lp.constraints.size()+1, vars.size()); assert(lpr!=NULL); set_verbose(lpr,0); //set_add_rowmode(lpr, TRUE);
	REAL* row = new REAL[1+vars.size()]; // must be 1 more then number of columns !

	//enumerate variables <-> columns, a 1:1 mapping
	dictionary<std::string,int> var_column; std::string s; int vi = 1;
	forall_defined(s,vars) var_column.insert( s, vi++ );


	clear_row(row,vars);
	forall(a,lp.objective)
		row[ var_column.access(variable_name(a)) ] = multiplier(a);
	set_obj_fn(lpr, row);


	forall(c,lp.constraints)
	{
		int constr_type;
		if(c.op==Le) constr_type = LE; //1;
		else if(c.op==Ge) constr_type = GE; // 2;
		else if(c.op==Eq) constr_type = EQ; // 3;
		else fail("no match");


		clear_row(row,vars);
		forall(a,c.lhs)
			row[ var_column.access(variable_name(a)) ] = multiplier(a);
		add_constraint(lpr, row, constr_type, c.rhs);
	}

	forall(s,lp.binary_vars)
		set_binary(lpr, var_column.access(s), TRUE);

	int result = solve(lpr);

	if (result == 2) { vars.clear(); println("exit solver"); return; }
	if (result != 0) fail("result is not 0 (optimal) or 2 (infeasible): "+repr(result));

	get_variables(lpr,row);	

	/*
	if( lp.binary_vars.size() > 0 )
	{
		println("SOLUTION:");
		forall_defined(s,vars)
		{
			println( "var "+s+" = " + repr(row[var_column.access(s)-1]) );
		}
		println("");
	}
	*/
	

	forall_defined(s,vars)
	{
		vars.insert( s, row[var_column.access(s)-1] );
	}	

	delete_lp(lpr); delete [] row;
	println("exit solver");
}


std::ostream&	operator<<		(std::ostream& out, const lp_Comparison& a)
{
	switch(a)
	{
		case Eq: out << "="; return out;
		case Le: out << "<=";return out;
		case Ge: out << ">=";return out;
	}
	fail("inexhaustive pattern match");
}

std::ostream&	operator<<	(std::ostream& out, const lp_Atom& a)
{
		out << ( multiplier(a)>0 ? "+" : "" );
		out << multiplier(a);
		out << " " << variable_name(a);
		return out;
}

std::ostream&	operator<<	(std::ostream& out, const lp_Constraint& a)
{
	if( a.lhs.size() >  0 )
	{
		lp_Atom x;
		forall(x,a.lhs) { out << x << " "; }
		out << a.op << " " << a.rhs << ";\n";
	}
	return out;
}


std::ostream&	operator<<	(std::ostream& out, const lp_Program& a)
{
	out << "min: ";

	lp_Atom x;
	forall(x,a.objective) { out << x << " " ; }
	out << ";\n";

	lp_Constraint y;
	forall(y,a.constraints) { out << y; }
	return out;
}