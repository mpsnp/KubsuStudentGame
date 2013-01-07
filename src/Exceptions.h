#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <string>
#include <sstream>
using namespace std;

class CException
{
protected:
    string _Message;
    int _ID;
public:
	CException(int, string);
	virtual string GetMessage() const;
	int ID()const;
};

class CModelLoadingException:public CException
{
protected:
	string _FileName;
public:
	CModelLoadingException(int, string, string);
	virtual string GetMessage() const;
};

class CFileNotFoundException:public CModelLoadingException
{
public:
	CFileNotFoundException(int, string);
	string GetMessage() const;
};

class CChunkNotFoundException:public CModelLoadingException
{
public:
	CChunkNotFoundException(int, string);
	string GetMessage() const;
};

#endif //_EXCEPTIONS_H
