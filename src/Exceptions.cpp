#include "Exceptions.h"

CException::CException(int ID, string Message)
{
	_ID = ID;
	_Message = Message;
}

string CException::GetMessage() const
{
	return _Message;
}

int CException::ID()const
{
	return _ID;
}

CModelLoadingException::CModelLoadingException(int ID, string Message, string FileName)
	: CException(ID,Message)
{
	_FileName = FileName;
}

string CModelLoadingException::GetMessage() const
{
	return (string)"Model loading exception. File " + _FileName + ": " + _Message;
}

CFileNotFoundException::CFileNotFoundException(int ID, string FileName)
	: CModelLoadingException(ID,"",FileName)
{
}

string CFileNotFoundException::GetMessage() const
{
	return (string)"File not found: " + _FileName;
}

CChunkNotFoundException::CChunkNotFoundException(int ID, string FileName)
	: CModelLoadingException(ID,"",FileName)
{
}

string CChunkNotFoundException::GetMessage() const
{
	stringstream stri;
	stri << _ID;
	return (string)"Chunk "+ stri.str() +" not found in file: " + _FileName;
}

