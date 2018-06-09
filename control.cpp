#include"Syntax.h"

Syntax::Syntax(){}
Syntax::~Syntax(){}

bool Syntax::init(int argc, char* argv[])
{
	if (argc != 2)
	{
		return false;
	}
	else
	{
		char* inFilename = argv[1];
		char outFilename[MAX_COUNT] = "";
		char errFilename[MAX_COUNT] = "";
		char varFilename[MAX_COUNT] = "";
		char proFilename[MAX_COUNT] = "";
		char filename[MAX_COUNT] = "";
		char path[MAX_COUNT] = "";
		//����ļ�������������չ������·��
		getFilename(inFilename, filename);
		getPath(inFilename, path);
		//��������ļ�ȫ��·��

		strcat(outFilename, path);
		//strcat(outFilename, "\\");
		strcat(outFilename, filename);
		strcat(outFilename, ".dys");
		//���ɴ����ļ�ȫ��·��

		strcat(errFilename, path);
		//strcat(errFilename, "\\");
		strcat(errFilename, filename);
		strcat(errFilename, ".err");
		//���ɱ����ļ�ȫ��·��

		strcat(varFilename, path);
		//strcat(varFilename, "\\");
		strcat(varFilename, filename);
		strcat(varFilename, ".var");
		//���ɹ����ļ�ȫ��·��

		strcat(proFilename, path);
		//strcat(proFilename, "\\");
		strcat(proFilename, filename);
		strcat(proFilename, ".pro");
		//���ļ����
		if ((inFile = fopen(inFilename, "r")) && (outFile = fopen(outFilename, "w")) && (errFile = fopen(errFilename, "w")) && (varFile = fopen(varFilename, "w")) && (procFile = fopen(proFilename, "w")))
		{
			//��ʼ������ָ�롢�ַ�ָ�롢�кš����
			inputCount = 0;
			pToken = 0;
			pChar = 0;
			lineNum = 1;//��ǰ�к�
						//level = 0;//��ǰ���
						//varCountInPro = 0;
			strcpy(currentProc.pname, "");
			currentProc.plev = 0;
			currentProc.varNum = 0;
			currentProc.parameter = -1;

			varCount = 0;
			procCount = 0;
			//��ȡ�����ļ����ݣ���ʼ��input����
			while (!feof(inFile))
			{
				char stringOfLine[MAX_COUNT];
				if (fgets(stringOfLine, MAX_COUNT, inFile))
				{
					char lineString[20] = "";
					strncpy(lineString, stringOfLine, 19);
					char* kindString = strrchr(lineString, ' ');
					kind[inputCount] = atoi(kindString + 1);

					char string[17] = "";
					strncpy(string, stringOfLine, 16);
					char* lastString = strrchr(string, ' ');
					strcpy(input[inputCount], lastString + 1);

					inputCount++;
				}
			}
			return true;
		}
		else
		{
			fclose(inFile);
			fclose(outFile);
			fclose(errFile);
			fclose(varFile);
			fclose(procFile);
			return false;
		}
	}
}

bool Syntax::final()
{
	for (int i = 0; i < varCount; i++)
	{
		int vkind = var[i].vkind ? 1 : 0;
		std::string temp = (var[i].vtype == integer) ? "integer" : "";
		char *vtype = new char[temp.length() + 1];
		strcpy(vtype, temp.c_str());
		//char* vtype = (var[i].vtype == integer) ? "integer" : "";
		fprintf(varFile, "%16s %16s %d %s %d %d\n", var[i].vname, var[i].vproc, vkind, vtype, var[i].vlev, var[i].vadr);
	}
	for (int i = 0; i < procCount; i++)
	{
		std::string temp = (proc[i].ptype == integer) ? "integer" : "";
		char* ptype = new char[temp.length() + 1];
		strcpy(ptype, temp.c_str());
		fprintf(procFile, "%16s %s %d %d %d\n", proc[i].pname, ptype, proc[i].plev, proc[i].fadr, proc[i].ladr);
	}
	if (fseek(inFile, 0, 0) == 0)
	{
		while (!feof(inFile))
			fputc(fgetc(inFile), outFile);

	}

	bool val;
	val = fclose(inFile);
	val = fclose(outFile);
	val = fclose(errFile);
	val = fclose(varFile);
	val = fclose(procFile);
	return val;
}

bool Syntax::error(int errNum, const char* symbol)
{
	char* errInfo;
	std::string temp1 = "�Ա����ֿ�ͷ";
	std::string temp2 = "δ֪����";

	switch (errNum)
	{
	case SIGN_UNDEFINED_ERR:
		fprintf(errFile, "***LINE:%d  %s�����޶���\n", lineNum, input[pToken]);
		break;
	case SIGN_REDEFINED_ERR:
		fprintf(errFile, "***LINE:%d  %s�����ض���\n", lineNum, input[pToken]);
		break;
	case SIGN_EXECUTE_ERR:
		fprintf(errFile, "***LINE:%d  %s������ƥ��ִ�����\n", lineNum, input[pToken]);
		break;
	case NO_SIGN_ERR:
		fprintf(errFile, "***LINE:%d  %s��ȱ��%s\n", lineNum, input[pToken], symbol);
		break;
	case SIGN_RESERVE_ERR:
		errInfo = NULL;
		strcpy(errInfo, temp1.c_str());
		//errInfo = "�Ա����ֿ�ͷ";
		break;
	case NO_PARA_ERR:
		fprintf(errFile, "***LINE:%d  ȱ���β�%s������\n", lineNum, symbol);
		break;
	default:
		errInfo = NULL;
		strcpy(errInfo, temp2.c_str());
		//errInfo = "δ֪����";
	}
	return true;
}

void Syntax::getPath(char* in, char* out)
{
	char* name;
	name = strrchr(in, '\\');
	if (name != NULL)
		strncpy(out, in, strlen(in) - strlen(name) + 1);
	else
		strcpy(out, "");
}

void Syntax::getFilename(char* in, char* out)
{
	char* fullName;
	char* extension;
	fullName = strrchr(in, '\\');
	extension = strrchr(in, '.');
	if (fullName != NULL)
		strncpy(out, fullName + 1, strlen(fullName) - 1 - strlen(extension));
	else
		strncpy(out, in, strlen(in) - strlen(extension));
}

bool Syntax::nextToken()
{
	pToken++;
	pChar = 0;
	if (strcmp(input[pToken], "EOF") == 0)
	{
		return true;
	}
	while (strcmp(input[pToken], "EOLN") == 0)
	{
		pToken++;
		lineNum++;
	}
	return false;
}

bool Syntax::nextChar()
{
	if (input[pToken][pChar] == '\0')
	{
		//nextToken();
		return true;
	}
	pChar++;
	return false;

}

bool Syntax::isVarExisted(char* vname, char* vproc, bool vkind)
{
	for (int i = 0; i < varCount; i++)
	{
		if ((strcmp(vname, var[i].vname) == 0) && (strcmp(vproc, var[i].vproc) == 0) && (var[i].vkind == vkind))
			return true;
	}
	for (int i = 0; i < procCount; i++)
	{
		if (strcmp(vname, proc[i].pname) == 0)
			return true;
	}
	return false;
}

bool Syntax::isProcExisted(char* vname)
{
	for (int i = 0; i < varCount; i++)
	{
		if (strcmp(vname, var[i].vname) == 0)
			return true;
	}
	for (int i = 0; i < procCount; i++)
	{
		if (strcmp(vname, proc[i].pname) == 0)
			return true;
	}
	return false;
}

int Syntax::getNextToken()
{
	int pNextToken = pToken + 1;
	while (strcmp(input[pNextToken], "EOLN") == 0)
	{
		pNextToken++;
	}
	return pNextToken;
}