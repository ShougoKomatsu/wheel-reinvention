#include "stdafx.h"



BOOL ReadUTFFile(CString sFilePath, CString* sData)
{
	CFileFind cFind;
	if(cFind.FindFile(sFilePath)==FALSE){return FALSE;}

	FILE* f;
	CString sBuf;
	CString sDocBuf;

	_tfopen_s(&f, sFilePath,_T("r, ccs=UTF-8"));
	CStdioFile cstdioF(f);
	while(cstdioF.ReadString(sBuf)!= NULL){sDocBuf = sDocBuf + sBuf+_T("\x0d\x0a");}
	cstdioF.Close();
	fclose(f);

	sData->Format(_T("%s"), sDocBuf);
	return TRUE;
}


BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands)
{

	saCommands->RemoveAll();
	BOOL bRet;
	CString sFileDataRaw;
	bRet = ReadUTFFile(sFilePath, &sFileDataRaw);
	if(bRet != TRUE){return FALSE;}

	unsigned long ulFileDataLength;
	long lCR1;
	long lCR2;

	lCR1 = 0;
	ulFileDataLength = sFileDataRaw.GetLength();
	for(unsigned long ulPointer = 0; ulPointer<=ulFileDataLength; ulPointer++)
	{
		lCR2 = sFileDataRaw.Find(_T("\r"),lCR1);
		if(lCR2<=0)
		{
			lCR2 = sFileDataRaw.Find(_T("\n"),lCR1);
			if(lCR2<=0)
			{
				CString sBufTemp;
				sBufTemp.Trim(_T("\r"));
				sBufTemp.Trim(_T("\n"));
				sBufTemp.Format(_T("%s"), sFileDataRaw.Mid(lCR1, sFileDataRaw.GetLength()-lCR1));
				if(sBufTemp.GetLength()>0)
				{
					if(sBufTemp.GetLength()>0){saCommands->Add(sBufTemp);}
				}
				return TRUE;
			}
		}

		CString sLineData;
		sLineData.Format(_T("%s"), sFileDataRaw.Mid(lCR1, lCR2-lCR1));
		sLineData.Trim(_T("\r"));
		sLineData.Trim(_T("\n"));
		if(sLineData.GetLength()>0)
		{
			if(sLineData.GetLength()>0){saCommands->Add(sLineData);}
		}
		lCR1=lCR2+1;
	}

	//�����ɂ͗��Ȃ�
	return FALSE;
}
