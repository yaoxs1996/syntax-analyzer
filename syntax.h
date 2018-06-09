#pragma once

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>

class Syntax
{
private:
	//各错误信号的常量定义
	static const int MAX_COUNT = 1024;
	static const int SIGN_UNDEFINED_ERR = 1;
	static const int SIGN_REDEFINED_ERR = 2;
	static const int SIGN_EXECUTE_ERR = 3;
	static const int NO_SIGN_ERR = 4;
	static const int SIGN_RESERVE_ERR = 5;
	static const int NO_PARA_ERR = 6;

	typedef enum{integer} types;

	typedef struct
	{
		char vname[17];
		char vproc[17];
		bool vkind;
		types vtype;
		int vlev;
		int vadr;
	}varRecord;

	typedef struct
	{
		char pname[17];
		types ptype;
		int plev;
		int varNum;
		int fadr;
		int ladr;
		int parameter;
		bool parameterIsDefined;
	}procRecord;

	char input[MAX_COUNT][17];
	int kind[MAX_COUNT];
	int inputCount;
	int pToken;
	int pChar;

	varRecord currentVar;
	procRecord currentProc;

	int lineNum;

	varRecord var[MAX_COUNT];
	procRecord proc[MAX_COUNT];
	int varCount;
	int procCount;

	FILE* inFile;
	FILE* outFile;
	FILE* errFile;
	FILE* varFile;
	FILE* procFile;

public:
	//构造函数与析构函数
	Syntax();
	~Syntax();

	//相关的处理函数
	bool init(int argc, char* argv[]);
	bool final();
	bool error(int errNum, const char* sign);
	void getPath(char* in, char* out);
	void getFilename(char* in, char* out);
	bool nextToken();
	bool nextChar();
	bool isVarExisted(char* vname, char* vproc, bool vkind);
	bool isProcExisted(char* vname);
	int getNextToken();

	//语法分析函数
	void A();
	void B();
	void C();
	void C_();
	void D();
	void E();
	void F();
	void G();
	void J();
	void K();
	void L();
	void M();
	void M_();
	void N();
	void O();
	void P();
	void Q();
	void R();
	void R_();
	void S();
	void S_();
	void T();
	void U();
	void W();
	void X();
	void Y();
	void Z();
};