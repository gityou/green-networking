

//defines basic operations that really should be part of the language standard...


template<typename T> bool	contains(list<T>& a, T& b)
{
	T i;
	forall(i,a) if(compare(i,b)==0) return true;
	return false;
}


namespace leda
{
	template<typename T>
	set<T>& operator +=(set<T>& a, const T& b) { a.insert(b); return a; }

	int compare(const std::string& s1, const std::string& s2);
}

__declspec (noreturn)	
void				fail				(const std::string& msg);
void				breakpoint			(const std::string& msg);
void				print				(const std::string& msg);
void				println				(const std::string& msg);
extern bool debug_flag;
void				debug				(const std::string& msg);

std::string		repr		(const bool& b);
std::string		repr		(const double& f);
std::string		repr		(const int& i);
std::string		repr		(const edge& e);
std::string		repr		(const node& v);

template<typename K, typename V>
std::string		repr		(const dictionary<K,V>& d)
{
	std::string r = "{\n";
	K k;
	forall_defined(k,d)
		r += "\t" + repr(k) + " : " + repr(d.access(k)) + ",\n";
	return r + "}";
}

template<typename T>
std::string			repr				(const list<T>& l)
{
	std::string out = "[";
	T t;
	forall(t,l) out += repr(t) + ",";
	return out + "]";
}
