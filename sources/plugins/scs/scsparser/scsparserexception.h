/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCSPARSEREXCEPTION_H
#define SCSPARSEREXCEPTION_H


#include <QString>
#include <QVector>
#include <QSet>

class SCsParserException
{
public:

	enum ExceptionPlace{
		PARSER,
		LEXER, 
		UNDEFINED
	};

	typedef int ExceptionType;
	SCsParserException();
    SCsParserException(SCsParserException::ExceptionPlace place);
	SCsParserException(ExceptionPlace place, int line, int positionInLine, ExceptionType exType);
	SCsParserException(const SCsParserException& copy);
	SCsParserException &operator=(const SCsParserException &copy);

	virtual ~SCsParserException();

	ExceptionPlace type() const { return mExceptionPlace; }
	int line() const { return mLine; }
	int positionInLine() const { return  mPositionInLine; }
	ExceptionType getExceptionType() const { return mExceptionType; }

private:
	ExceptionPlace mExceptionPlace;
	ExceptionType mExceptionType;
	int mLine;
	int mPositionInLine;

};

class SCsParserToken
{
public:
	
	enum Tokens 
	{
		UNKNOWN	
	};
	SCsParserToken();
	SCsParserToken(int tokenType);
    SCsParserToken(int tokenType, const QString &tokenText, int line, int positionInLine);
	SCsParserToken(const SCsParserToken& copy);
	SCsParserToken& operator=(const SCsParserToken& copy);
	virtual ~SCsParserToken();

	inline int tokenType(){ return mTokenType; }
	inline QString tokenText(){ return mTokenText; }
	inline int line(){ return mLine; }
	inline int positionInLine(){ return mPositionInLine; }

private:
	QString mTokenText;
	int mLine;
	int mPositionInLine;
	int mTokenType;
};

typedef QVector<SCsParserException> SCsParserExceptionArray;
typedef QVector<SCsParserToken> SCsParserTokenArray;
typedef QSet<int> SCsParserErrorLinesArray;
typedef QSet<QString> SCsParserIdtfArray;

#endif // SCSPARSEREXCEPTION_H
