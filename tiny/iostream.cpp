// IOSTREAM
// 'fake' or 'pocket' iostreams...
// UnderC Development Project, 2001.
#include <string.h>
#define _IOSTREAM_CODE
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_LINE = 512;

bool base_stream::open_file(const char *file, int access)
{
if (file) {
  char mode[5],ch;
  int i = 0;
  if (access & ios::in) ch = 'r';
  if (access & ios::out) ch = 'w';
  if (access & ios::app)  ch = 'a';
  mode[i++] = ch;
  if (ch == 'r' && access & ios::out) {
       mode[i++] = 'w';
       mode[i++] = '+';
  }
  if (access & ios::binary) mode[i++] = 'b';
  mode[i] = '\0';
  hand = fopen(file,mode);
} else hand = 0;
return hand ? true : false;
}

void base_stream::close()
{
   if (hand) {
       fclose(hand);
       hand = 0;
   }
}

 void base_stream::flush()
{ fflush(hand); }

  ostream::ostream(FHandle h)
  {
      hand = h;
      //~ fprintf(stderr,"++hand = %x  (%x)\n",h,this);
   }

  ostream& ostream::write(char *buff, int sz) {
    fwrite(buff,1,sz,hand);
    return *this;
  }

  bool ostream::good()
  { return hand ? true : false;  }

  bool ostream::bad()
  { return ! good(); }

  ostream& ostream::seekp(streampos pos, int which)
  { fseek(hand,pos,which); return *this; }

  streampos ostream::tellp()
  { return ftell(hand); }

 bool ofstream::open(const char *file, int access) {
   return open_file(file,access | ios::out);
 }

 ofstream::ofstream(const char *file, int access)
 { open(file,access); }

 ofstream::~ofstream()
 { close(); }

 //// istream
istream::istream(FHandle h)
{
    hand = h;
}

istream& istream::getline(char *buff,int sz)
{
    char *s = fgets(buff,sz,hand);
    if (s != NULL) s[strlen(s)-1] = '\0'; // remove \n!
    return *this;
}

istream& istream::read(char *buff, int sz) {
    m_no_read = fread(buff,1,sz,hand);
    return *this;
}

istream& istream::putback(char ch) {
    ungetc(ch, hand);
    return *this;
}

int istream::gcount() { return m_no_read; }

istream& istream::write(char *buff, int sz) { // have to say ios::out as well!
    fwrite(buff,1,sz,hand);
    return *this;
}

istream& istream::seekg(streampos pos, int which)
{ fseek(hand,pos,which); return *this; }

streampos istream::tellg()
{ return ftell(hand); }

bool istream::eof()
{ return feof(hand); }

bool istream::good()
{ return hand ? (! eof()) : false;  }

bool istream::bad()
{ return ! good(); }

bool istream::operator! ()
{ return ! good(); }

istream::operator int () { return good(); }


bool ifstream::open(const char *str, int access) {
    return open_file(str,access | ios::in);
}

ifstream::ifstream(const char *file, int access)
{
    open(file,access);
}

ifstream::~ifstream()
{
    close();
}

ostream std::cout(stdout);
ostream std::cerr(stderr);
istream cin(stdin);

_Endl_ std::endl;

std::ostream& operator<< (ostream& os, int val)
{ fprintf(os.hand,"%d",val); return os; }

ostream& operator<< (ostream& os, long val)
{ fprintf(os.hand,"%ld",val); return os; }

ostream& operator<< (ostream& os, unsigned int val)
{ fprintf(os.hand,"%u",val); return os; }

std::ostream& operator<< (std::ostream& os, unsigned long val)
{ fprintf(os.hand,"%lu",val); return os; }

std::ostream& operator<< (std::ostream& os, bool val)
{ fprintf(os.hand,"%s",val ? "true" : "false"); return os; }

std::ostream& operator<< (std::ostream& os, double val)
{ fprintf(os.hand,"%lf",val); return os; }

std::ostream& operator<< (std::ostream& os, float val)
{ fprintf(os.hand,"%lf",(double)val); return os; }

std::ostream& operator<< (std::ostream& os, const char *val)
{
//~ fprintf(stderr,"++hand = %x  (%x)\n",os.hand,&os);
    fprintf(os.hand,"%s",val);
    return os;
}

std::ostream& operator << (std::ostream& os, std::_Endl_& e)
{
 fprintf(os.hand,"\n");
 os.flush();
 return os;
}

std::ostream& operator<< (std::ostream& os, void *val)
{ fprintf(os.hand,"%p",val); return os; }

std::ostream& operator<< (std::ostream& os, char ch)
{ fprintf(os.hand,"%c",ch);  return os; }

std::istream& operator>> (std::istream& is, int& val)
{
 fscanf(is.hand,"%d",&val);
 return is;
}

std::istream& operator>> (std::istream& is, double& val)
{
 fscanf(is.hand,"%lf",&val);
 return is;
}

std::istream& operator>> (std::istream& is, float& val)
{
 fscanf(is.hand,"%f",&val);
 return is;
}

std::istream& operator>> (std::istream& is, char *val)
{
 fscanf(is.hand,"%s",val);
 return is;
}

std::istream& operator>> (std::istream& is, char& ch)
{
 fscanf(is.hand,"%c",&ch);
 return is;
}

