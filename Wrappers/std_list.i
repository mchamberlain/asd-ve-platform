/* -----------------------------------------------------------------------------
 * See the LICENSE file for information on copyright, usage and redistribution
 * of SWIG, and the README file for authors - http://www.swig.org/release.html.
 *
 * std_list.i
 *
 * std::list typemaps for LUA
 * ----------------------------------------------------------------------------- */

%{
#include <list>
%}
%include <std_except.i> // the general exepctions
/*
A really cut down version of the list class.

Note: this does not match the true std::list class
but instead is an approximate, so that SWIG knows how to wrapper it.
(Eg, all access is by value, not ref, as SWIG turns refs to pointers)

And no support for iterators & insert/erase

It would be useful to have a list<->Lua table conversion routine

*/
namespace std {

	template<class T>
    class list {
      public:
        list();
        list(const list&);
        unsigned int size() const;
        bool empty() const;
        void clear();
        void push_back(T val);
        void pop_back();
        T front()const; // only read front & back
        T back()const;  // not write to them
    };

}

/*
Vector<->LuaTable fns
These look a bit like the array<->LuaTable fns
but are templated, not %defined
(you must have template support for STL)

*/
/*
%{
// reads a table into a list of numbers
// lua numbers will be cast into the type required (rounding may occur)
// return 0 if non numbers found in the table
// returns new'ed ptr if ok
template<class T>
std::list<T>* SWIG_read_number_list(lua_State* L,int index)
{
	int i=0;
	std::list<T>* vec=new std::list<T>();
	while(1)
	{
		lua_rawgeti(L,index,i+1);
		if (!lua_isnil(L,-1))
		{
			lua_pop(L,1);
			break;	// finished
		}
		if (!lua_isnumber(L,-1))
		{
			lua_pop(L,1);
			delete vec;
			return 0;	// error
		}
		vec->push_back((T)lua_tonumber(L,-1));
		lua_pop(L,1);
		++i;
	}
	return vec;	// ok
}
// writes a list of numbers out as a lua table
template<class T>
int SWIG_write_number_list(lua_State* L,std::list<T> *vec)
{
	lua_newtable(L);
	for(int i=0;i<vec->size();++i)
	{
		lua_pushnumber(L,(double)((*vec)[i]));
		lua_rawseti(L,-2,i+1);// -1 is the number, -2 is the table
	}
}
%}

// then the typemaps

%define SWIG_TYPEMAP_NUM_VECTOR(T)

// in
%typemap(in) std::list<T> *INPUT
%{	$1 = SWIG_read_number_list<T>(L,$input);
	if (!$1) SWIG_fail;%}

%typemap(freearg) std::list<T> *INPUT
%{	delete $1;%}

// out
%typemap(argout) std::list<T> *OUTPUT
%{	SWIG_write_number_list(L,$1); SWIG_arg++; %}

%enddef
*/
