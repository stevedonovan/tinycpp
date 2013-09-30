// Mstring.c
// testing string class
/*
  Yes, I know it's bad to reinvent this particular wheel but
  I don't like the templatized standard string. An extra 30%
  (at least) size penalty for using the char traits templatized
  iostreams and strings, hassle debugging those long names,
  plus longer compile times. A longer version of this rave
  is available at
    home.mweb.co.za/sd/sdonovan/templates.html

  Masochists and other diehard supporters of the standard
  can switch to using <iostream> and <string> in classlib.h.

  Raves aside, this class could certainly do with improvements.
*/
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

const int MAX_LINE=512;

int nCreated = 0;

int string::npos = -1;

char * string::alloc(int size)
{
   char * ss = new char[size+1];
   return ss;
}

string::string (const char *ss /*=NULL*/)
//*acts as our default constructor
{
 if (!ss) ss = "";
 m_length = strlen((char *)ss);
 m_data = alloc (m_length);
 strcpy (m_data, (char *)ss);
 nCreated++;
}

string::string (int size)
{
  m_length = size;
  m_data = alloc (size);
  m_data[0] = 0;
  nCreated++;
}

// and (NB) a copy constructor....
string::string (const string& s)
{
  m_length = s.m_length;
  m_data = alloc(m_length);
  strcpy(m_data,s.m_data);
  nCreated++;
}

string::~string()
{
  delete m_data;
  m_data = NULL;
  nCreated--;
}

// assignment operators
string& string::operator = (const string &s)
{
  copy(s.c_str(),s.length());
  return *this;
}

string&
string::operator = (const char *str)
{
  if (!str) str = "";
  copy (str, strlen(str));
  return *this;
}


int string::compare(const string& s) const
{
    if(!m_data || !s.m_data) return -1; else
    return strcmp(m_data,s.m_data);
}

int string::compare(const char *s) const
{
    return strcmp(m_data,s);
}

string string::substr (int start, int n)
{
   int len = length();
   if (n == npos) n = len;
   if (start + n > len) n = len - start;

   string T(n);
   const char * in = m_data + start;
   char * out = T.m_data;
   for (int i = 0; i < n; i++) *out++ = *in++;
   *out = 0;

   return T;
}

string& string::insert(int pos, const char * s)
{
    int i,n  = strlen(s), on = m_length;
    // we get bigger!
    m_length += n;
    resize(m_length);
    char *p = m_data + pos; // insertion point
    for (i = on-1; i >= 0; i--) {
        p[i + n] = p[i];
    }
    for (i = 0; i < n; i++) {
        *p++ = *s++;
    }
    m_data[m_length] = '\0';
    return *this;
}

// length 10
// 01[234]56789
// pos=2 len=3; L-pos-len==5 ->
// 012345[6789]
// pos=6 len=-1->10-6 == 4; rest=(10 - 4 - 1 == 5)

string& string::erase (int pos, int len)
{
    if (len == npos)
        len = m_length - pos;
    int rest = m_length - len - pos;
    for (int i = 0; i < rest; i++) { // also '\0'
        m_data[pos+i] = m_data[pos+len+i];
    }
    m_length -= len;
    resize(m_length);
    m_data[m_length] = '\0';
    return *this;
}

string& string::replace (int pos, int len, const char* s)
{
    erase(pos,len);
    return insert(pos,s);
}

string& string::replace (int pos, int len, const string& s)
{
    return replace(pos,len,s.c_str());
}

void string::clear ()
{
    erase(0,npos);
}

string& string::insert(int pos, const string& s)
{
    return insert(pos,s.c_str());
}

typedef long long intptr;

int string::offs(const char * ss)
{
    return !ss ? string::npos :intptr(ss) - intptr(c_str());
}

int string::find(const char * ps)
{
    return offs(strstr(c_str(),ps));
}

int string::find(const string& s)
{
    return find(s.c_str());
}

int string::find(char ch)
{
    return offs(strchr(c_str(),ch));
}

int string::rfind(char ch)
{
    return offs(strrchr(c_str(),ch));
}

int string::find_first_of(const char * ps, int pos)
{
    return offs(strpbrk(c_str() + pos,ps));
}

int string::find_first_of (const string& str, int pos)
{
    return find_first_of(str.c_str(),pos);
}

int string::find_first_not_of(const char * ps, int pos)
{
    int sz = strspn(c_str() + pos, ps);
    if (sz == 0)
        return string::npos;
    else
        return sz;
}

int string::find_first_not_of (const string& str, int pos)
{
    return find_first_not_of(str.c_str(),pos);
}

string & string::operator += (const string &s)
{
    m_length += s.length();
    resize (m_length);
    strcat(m_data, s.m_data);
    return *this;
}

string& string::operator += (const char *str)
{
    if (!str) str = "";
    m_length += strlen(str);
    resize (m_length);
    strcat(m_data, str);
    return *this;
}

string& string::operator += (char ch)
{
    char tmp[] = {ch,'\0'};  // very crude!!
    return (*this) += tmp;
}

void string::copy(const char*str, int sz)
{
    if (sz > length() || sz == 0) resize(sz);
    m_length = sz;
    strcpy (m_data,str);
}

int string::resize (int size)
{
    char * new_str = alloc (size);
    if (m_data) strncpy(new_str,m_data,size+1);
    if (m_length > 0) { delete m_data; m_data = NULL; }
    m_data = new_str;
    return size;
}

string operator + (string s1, string s2)
{
    string temps(s1);
    temps += s2;
    return temps;
}

char temp_buff[MAX_LINE];

std::ostream& operator << (std::ostream& os, string s)
{
    return os << s.c_str();
}

std::istream& operator >> (std::istream& is, string& s)
{
    is >> temp_buff;
    s = temp_buff;
    return is;
}

std::istream& getline(std::istream& is, string& str)
{
    is.getline(temp_buff,sizeof(temp_buff));
    str = temp_buff;
    return is;
}
