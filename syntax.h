#ifndef SYNTAX_H_
#define SYNTAX_H_

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>

#define MAX_COUNT 1024
#define SIGN_UNDEFINED_ERR 1
#define SIGN_REDEFINED_ERR 2
#define SIGN_EXECUTE_ERR 3
#define NO_SIGN_ERR 4
#define SIGN_RESERVE_ERR 5
#define NO_PARA_ERR 6

class syntax
{
private:
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
	syntax();
	~syntax();

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

#endif