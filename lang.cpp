
#include "header.h"

void			fail		(const std::string& msg)		{ println(msg); assert(false); }
void			breakpoint	(const std::string& prompt)	{ println(prompt); std::string pause; std::cin >> pause; }
void			print		(const std::string& s )		{ std::cout << s; std::cout.flush(); }
void			println		(const std::string& s )		{ print(s); print("\n"); }
bool debug_flag = false;
void			debug		(const std::string& msg)	{ if(debug_flag) println(msg); } 

std::string		repr		(const bool& b)				{ return b?"true":"false"; }
std::string		repr		(const int& i)				{ std::ostringstream buffer; buffer << i; return buffer.str(); }
std::string		repr		(const double& f)			{ std::ostringstream buffer; buffer << f; return buffer.str(); }
std::string		repr		(const edge& e)				{ return repr(source(e)) + "->" + repr(target(e)); }
std::string		repr		(const node& v)				{ return "v"+repr(g[v]); }

namespace leda
{
	int compare(const std::string& s1, const std::string& s2)
	{
		return s1.compare(s2);
	}
}




