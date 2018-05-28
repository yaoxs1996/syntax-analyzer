#include"syntax.h"

void syntax::A()
{
	B();
}
void syntax::B()
{
	if (strcmp(input[pToken], "begin") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "begin");
		if (strcmp(input[pToken], "integer") != 0)
		{
			nextToken();
		}
	}
	C();
	if (strcmp(input[pToken], ";") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ";");
		if ((strcmp(input[pToken], "integer") != 0) && (strcmp(input[pToken], "read") != 0) && (strcmp(input[pToken], "write") != 0) && (kind[pToken] != 10))
		{
			nextToken();
		}
	}
	M();
	if (strcmp(input[pToken], "end") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "end");
	}
}
void syntax::C()
{
	D();
	C_();
}
void syntax::C_()
{

	if (strcmp(input[pToken], ";") == 0 && strcmp(input[getNextToken()], "integer") == 0)
	{
		nextToken();
		D();
		C_();
	}
	else
	{
		if (strcmp(input[pToken], "integer") == 0)
		{
			error(NO_SIGN_ERR, ";");
			D();
			C_();
		}
	}

}
void syntax::D()
{
	if (strcmp(input[pToken + 1], "function") == 0)
	{
		J();
	}
	else
	{
		E();
	}
}
void syntax::E()
{
	if (strcmp(input[pToken], "integer") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "integer");
		nextToken();
	}
	strcpy(currentVar.vname, input[pToken]);
	strcpy(currentVar.vproc, currentProc.pname);
	if (pToken == currentProc.parameter)
	{
		currentVar.vkind = true;
		currentProc.parameterIsDefined = true;
	}
	else
	{
		currentVar.vkind = false;
	}
	currentVar.vtype = integer;
	currentVar.vlev = currentProc.plev;
	currentVar.vadr = varCount;
	if (isVarExisted(input[pToken], currentProc.pname, currentVar.vkind))//如果存在变量
	{
		error(SIGN_REDEFINED_ERR, NULL);
	}
	else
	{
		if (currentProc.varNum == 0)//如果当前过程中变量数为0，则当前变量是当前过程的第一个变量
		{
			currentProc.fadr = currentVar.vadr;
		}
		currentProc.ladr = currentVar.vadr;//过程中最后一个变量在变量表中的位置
		currentProc.varNum++;//过程中变量数++
		var[varCount] = currentVar;//当前变量存入var数组
		varCount++;//变量数++
	}
	F();
}
void syntax::F()
{
	G();
}
void syntax::G()
{
	if (kind[pToken] == 10)
	{
		nextToken();
	}
}
void syntax::J()
{
	procRecord proBackup = currentProc;//备份当前过程，在匹配完G过程后恢复
	if (strcmp(input[pToken], "integer") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "integer");
		if (strcmp(input[pToken], "function") != 0)
		{
			nextToken();
		}
	}
	if (strcmp(input[pToken], "function") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "function");
		if (kind[pToken] != 10)
		{
			nextToken();
		}
	}
	strcpy(currentProc.pname, input[pToken]);
	currentProc.ptype = integer;
	currentProc.plev++;
	currentProc.varNum = 0;
	currentProc.parameterIsDefined = false;
	if (isProcExisted(input[pToken]))
	{
		error(SIGN_REDEFINED_ERR, NULL);
	}
	G();
	if (strcmp(input[pToken], "(") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "(");
		if (kind[pToken] != 10)
		{
			nextToken();
		}
	}
	currentProc.parameter = pToken;
	K();

	if (strcmp(input[pToken], ")") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ")");
		if (strcmp(input[pToken], ";") != 0)
		{
			nextToken();
		}
	}
	if (strcmp(input[pToken], ";") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ";");
		if (strcmp(input[pToken], "begin") != 0)
		{
			nextToken();
		}
	}
	L();
	currentProc = proBackup;//匹配完G过程后恢复原过程
}
void syntax::K()
{
	F();
}
void syntax::L()
{
	if (strcmp(input[pToken], "begin") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "begin");
		if (strcmp(input[pToken], "integer") != 0)
		{
			nextToken();
		}
	}
	C();
	if (!currentProc.parameterIsDefined)
	{
		error(NO_PARA_ERR, input[currentProc.parameter]);
	}
	proc[procCount] = currentProc;//在这里而不是在J()函数最后把currentProc加入pro数组是因为M中可能会使用当前过程(递归)
	procCount++;
	if (strcmp(input[pToken], ";") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ";");
		if ((strcmp(input[pToken], "integer") != 0) && (strcmp(input[pToken], "read") != 0) && (strcmp(input[pToken], "write") != 0) && (kind[pToken] != 10))
		{
			nextToken();
		}
	}
	M();
	if (strcmp(input[pToken], "end") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "end");
		if ((strcmp(input[pToken], ";") != 0) && (strcmp(input[pToken], "end") != 0))
		{
			nextToken();
		}
	}
}
void syntax::M()
{
	N();
	M_();
}
void syntax::M_()
{
	if (strcmp(input[pToken], ";") == 0)
	{
		nextToken();
		N();
		M_();
	}
	else
	{
		if ((strcmp(input[pToken], "end") != 0) && (strcmp(input[pToken], "EOF") != 0))
		{
			error(NO_SIGN_ERR, ";");
			N();
			M_();
		}
	}
}
void syntax::N()
{
	if (strcmp(input[pToken], "read") == 0)
	{
		O();
	}
	else if (strcmp(input[pToken], "write") == 0)
	{
		P();
	}
	else if (strcmp(input[pToken], "if") == 0)
	{
		W();
	}
	else if (kind[pToken] == 10)
	{
		Q();
	}
	else
	{
		error(SIGN_EXECUTE_ERR, NULL);
		nextToken();
	}
}
void syntax::O()
{
	if (strcmp(input[pToken], "read") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "read");
		if (strcmp(input[pToken], "(") != 0)
		{
			nextToken();
		}
	}
	if (strcmp(input[pToken], "(") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "(");
		if (kind[pToken] != 10)
		{
			nextToken();
		}
	}
	if (!isVarExisted(input[pToken], currentProc.pname, false) && !isVarExisted(input[pToken], currentProc.pname, true))
	{
		error(SIGN_UNDEFINED_ERR, NULL);
	}
	F();
	if (strcmp(input[pToken], ")") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ")");
		if ((strcmp(input[pToken], ";") != 0) && (strcmp(input[pToken], "end") != 0))
		{
			nextToken();
		}
	}
}
void syntax::P()
{
	if (strcmp(input[pToken], "write") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "write");
		if (strcmp(input[pToken], "(") != 0)
		{
			nextToken();
		}
	}
	if (strcmp(input[pToken], "(") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "(");
		if (kind[pToken] != 10)
		{
			nextToken();
		}
	}
	if (!isVarExisted(input[pToken], currentProc.pname, false) && !isVarExisted(input[pToken], currentProc.pname, true))
	{
		error(SIGN_UNDEFINED_ERR, NULL);
	}
	F();
	if (strcmp(input[pToken], ")") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ")");
		if ((strcmp(input[pToken], ";") != 0) && (strcmp(input[pToken], "end") != 0))
		{
			nextToken();
		}
	}
}
void syntax::Q()
{
	if (!isVarExisted(input[pToken], currentProc.pname, false) && !isVarExisted(input[pToken], currentProc.pname, true) && !isProcExisted(input[pToken]))
	{
		error(SIGN_UNDEFINED_ERR, NULL);
	}
	F();
	if (strcmp(input[pToken], ":=") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ":=");
		if ((kind[pToken] != 10) && (kind[pToken] != 11))
		{
			nextToken();
		}
	}
	R();
}
void syntax::R()
{
	S();
	R_();
}
void syntax::R_()
{
	if (strcmp(input[pToken], "-") == 0)
	{
		nextToken();
		S();
		R_();
	}
	else
	{
		if ((kind[pToken] == 10) || (kind[pToken] == 11))
		{
			S();
			R_();
		}
	}
}
void syntax::S()
{
	T();
	S_();
}
void syntax::S_()
{
	if (strcmp(input[pToken], "*") == 0)
	{
		nextToken();
		T();
		S_();
	}
	else
	{
		if ((kind[pToken] == 10) || (kind[pToken] == 11))
		{
			T();
			S_();
		}
	}
}
void syntax::T()
{
	if (input[pToken][pChar] >= '0' && input[pToken][pChar] <= '9')
	{
		U();
	}
	else if (strcmp(input[getNextToken()], "(") == 0)///////////////////////pToken+1
	{
		Z();
	}
	else
	{
		if (!isVarExisted(input[pToken], currentProc.pname, false) && !isVarExisted(input[pToken], currentProc.pname, true))
		{
			error(SIGN_UNDEFINED_ERR, NULL);
		}
		F();
	}
}
void syntax::U()
{
	if (kind[pToken] == 11)
	{
		nextToken();
	}
}
void syntax::W()
{
	if (strcmp(input[pToken], "if") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "if");
		if ((kind[pToken] != 10) && (kind[pToken] != 11))
		{
			nextToken();
		}
	}
	X();
	if (strcmp(input[pToken], "then") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "then");
		if ((strcmp(input[pToken], "integer") != 0) && (strcmp(input[pToken], "read") != 0) && (strcmp(input[pToken], "write") != 0) && (kind[pToken] != 10))
		{
			nextToken();
		}
	}
	N();
	if (strcmp(input[pToken], "else") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "else");
		if ((strcmp(input[pToken], "integer") != 0) && (strcmp(input[pToken], "read") != 0) && (strcmp(input[pToken], "write") != 0) && (kind[pToken] != 10))
		{
			nextToken();
		}
	}
	N();
}
void syntax::X()
{
	R();
	Y();
	R();
}
void syntax::Y()
{
	if (strcmp(input[pToken], "<") == 0 || strcmp(input[pToken], "<=") == 0 || strcmp(input[pToken], ">") == 0 || strcmp(input[pToken], ">=") == 0 || strcmp(input[pToken], "=") == 0 || strcmp(input[pToken], "<>") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "关系运算符");
		if ((kind[pToken] != 10) && (kind[pToken] != 11))
		{
			nextToken();
		}
	}
}
void syntax::Z()
{
	if (!isProcExisted(input[pToken]))
	{
		error(SIGN_UNDEFINED_ERR, NULL);
	}
	G();
	if (strcmp(input[pToken], "(") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, "(");
		if ((kind[pToken] != 10) && (kind[pToken] != 11))
		{
			nextToken();
		}
	}
	R();
	if (strcmp(input[pToken], ")") == 0)
	{
		nextToken();
	}
	else
	{
		error(NO_SIGN_ERR, ")");
		if ((strcmp(input[pToken], "-") != 0) && (strcmp(input[pToken], "*") != 0) && (strcmp(input[pToken], ";") != 0) && (strcmp(input[pToken], "end")))
		{
			nextToken();
		}
	}
}