#include "stdafx.h"
#include "Perser.h"

#include "stdafx.h"
#include "MouseAutomation.h"

BOOL GetCommand(CString sDataLine, int* iCommandType)
{
	CString sDataLocal;
	sDataLocal.Format(_T("%s"),sDataLine.Trim(_T(" ")).Trim(_T("\t")));
	if(sDataLocal.GetLength()==1){*iCommandType = COMMAND_KEY_DOWN_UP; return TRUE;}
	sDataLocal.Format(_T("%s"),sDataLocal.MakeLower());
	if(sDataLocal.Right(4).Compare(_T("down"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataLocal.Right(2).Compare(_T("up"))==0){*iCommandType=COMMAND_KEY_UP; return TRUE;}

	if(sDataLocal.Left(5).Compare(_T("break"))==0){*iCommandType=COMMAND_BREAK; return TRUE;}
	if(sDataLocal.Left(12).Compare(_T("lmouse click"))==0){		*iCommandType=COMMAND_MOUSE_L_CLICK; 		return TRUE;}
	if(sDataLocal.Left(11).Compare(_T("lmouse down"))==0){*iCommandType=COMMAND_MOUSE_L_DOWN; return TRUE;}
	if(sDataLocal.Left(9).Compare(_T("lmouse up"))==0){*iCommandType=COMMAND_MOUSE_L_UP; return TRUE;}
	if(sDataLocal.Left(8).Compare(_T("mousepos"))==0){*iCommandType=COMMAND_MOUSE_MOVE; return TRUE;}
	if(sDataLocal.Left(5).Compare(_T("wheel"))==0){*iCommandType=COMMAND_WHEEL; return TRUE;}
	if(sDataLocal.SpanIncluding(_T("0123456789")).Compare(sDataLocal)==0){*iCommandType = COMMAND_DELAY; return TRUE;}

	if((sDataLocal.Left(4).Compare(_T("dim "))==0)){*iCommandType=COMMAND_DECRARE; return TRUE;}
	if(sDataLocal.Compare(_T("_"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataLocal.Compare(_T("enter"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	if(sDataLocal.Compare(_T("return"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}

	if(sDataLocal.GetLength()==2)
	{
		if(sDataLocal.Compare(_T("f1"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f2"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f3"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f4"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f5"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f6"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f7"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f8"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f9"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	}
	
	if(sDataLocal.GetLength()==3)
	{
		if(sDataLocal.Compare(_T("f10"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f11"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f12"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f13"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f14"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f15"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f16"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f17"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f18"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f19"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		
		if(sDataLocal.Compare(_T("f20"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f21"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f22"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f23"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
		if(sDataLocal.Compare(_T("f24"))==0){*iCommandType=COMMAND_KEY_DOWN; return TRUE;}
	}

	if((sDataLocal.Left(1).Compare(_T("<"))==0)&&(sDataLocal.Left(1).Compare(_T(">"))==0))
	{
		CString sRemindRepeat;
		sRemindRepeat.Format(_T("%s"), sDataLocal.Mid(1,sDataLocal.GetLength()-2));
		sRemindRepeat.Trim(_T(" ")).Trim(_T("\t"));
		if(sRemindRepeat.Left(1).Compare(_T("r"))==0)
		{
			int iRepeat;
			iRepeat = _ttoi(sRemindRepeat.Right(sRemindRepeat.GetLength()-1));
			if(iRepeat>=1)
			{
				*iCommandType = COMMAND_REPEAT;
				return TRUE;
			}
		}
		else{return FALSE;}
	}

	if((sDataLocal.Left(1).Compare(_T("<"))==0)&&(sDataLocal.Left(1).Compare(_T(">"))==0))
	{
		CString sRemindRepeat;
		sRemindRepeat.Format(_T("%s"), sDataLocal.Mid(1,sDataLocal.GetLength()-2));
		sRemindRepeat.Trim(_T(" ")).Trim(_T("\t"));
		if(sRemindRepeat.Left(2).Compare(_T("/r"))==0)
		{
				*iCommandType = COMMAND_REPEAT_END;
				return TRUE;
		}
		else{return FALSE;}
	}

	return FALSE;
}

BOOL ExtractData(const CString sInput, const CString sDelim, CString* sOut, CString* sRemin)
{
	int iIndex;
	CString sInputLocal;
	sInputLocal.Format(_T("%s"), sInput);
	sInputLocal.MakeLower();
	iIndex=sInputLocal.Find(sDelim);
	if(iIndex<0)
	{
		sOut->Format(_T("%s"),sInputLocal.Trim(_T(" ")).Trim(_T("\t")));
		sRemin->Format(_T(""));
	}
	else
	{
		sOut->Format(_T("%s"),sInputLocal.Left(iIndex).Trim(_T(" ")).Trim(_T("\t")));
		sRemin->Format(_T("%s"),sInputLocal.Right(sInputLocal.GetLength()-iIndex-1).Trim(_T(" ")).Trim(_T("\t")));
	}
	return TRUE;
}

BOOL GetKeyType(CString sInput, CString* sOut)
{
	CString sRemind;

	CString sInputLower;
	sInputLower.Format(_T("%s"), sInput);
	sInputLower.MakeLower().Trim(_T(" ")).Trim(_T("\t"));
	if(sInputLower.Right(4).Compare(_T("down"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-5));}
	else if(sInputLower.Right(2).Compare(_T("up"))==0){sRemind.Format(_T("%s"), sInput.Left(sInput.GetLength()-2));}
	else{sRemind.Format(_T("%s"), sInput);}
	sRemind.Trim(_T(" ")).Trim(_T("\t"));
	CString sRemindLower;
	sRemindLower.Format(_T("%s"), sRemind);
	sRemindLower.MakeLower();
	
	if(sRemindLower.GetLength()==2)
	{
		if(sRemindLower.Compare(_T("f1"))==0){sOut->Format(_T("0x%02x"),VK_F1);return TRUE;}
		if(sRemindLower.Compare(_T("f2"))==0){sOut->Format(_T("0x%02x"),VK_F2);return TRUE;}
		if(sRemindLower.Compare(_T("f3"))==0){sOut->Format(_T("0x%02x"),VK_F3);return TRUE;}
		if(sRemindLower.Compare(_T("f4"))==0){sOut->Format(_T("0x%02x"),VK_F4);return TRUE;}
		if(sRemindLower.Compare(_T("f5"))==0){sOut->Format(_T("0x%02x"),VK_F5);return TRUE;}
		if(sRemindLower.Compare(_T("f6"))==0){sOut->Format(_T("0x%02x"),VK_F6);return TRUE;}
		if(sRemindLower.Compare(_T("f7"))==0){sOut->Format(_T("0x%02x"),VK_F7);return TRUE;}
		if(sRemindLower.Compare(_T("f8"))==0){sOut->Format(_T("0x%02x"),VK_F8);return TRUE;}
		if(sRemindLower.Compare(_T("f9"))==0){sOut->Format(_T("0x%02x"),VK_F9);return TRUE;}
	}
	
	if(sRemindLower.GetLength()==3)
	{
		if(sRemindLower.Compare(_T("f10"))==0){sOut->Format(_T("0x%02x"),VK_F10);return TRUE;}
		if(sRemindLower.Compare(_T("f11"))==0){sOut->Format(_T("0x%02x"),VK_F11);return TRUE;}
		if(sRemindLower.Compare(_T("f12"))==0){sOut->Format(_T("0x%02x"),VK_F12);return TRUE;}
		if(sRemindLower.Compare(_T("f13"))==0){sOut->Format(_T("0x%02x"),VK_F13);return TRUE;}
		if(sRemindLower.Compare(_T("f14"))==0){sOut->Format(_T("0x%02x"),VK_F14);return TRUE;}
		if(sRemindLower.Compare(_T("f15"))==0){sOut->Format(_T("0x%02x"),VK_F15);return TRUE;}
		if(sRemindLower.Compare(_T("f16"))==0){sOut->Format(_T("0x%02x"),VK_F16);return TRUE;}
		if(sRemindLower.Compare(_T("f17"))==0){sOut->Format(_T("0x%02x"),VK_F17);return TRUE;}
		if(sRemindLower.Compare(_T("f18"))==0){sOut->Format(_T("0x%02x"),VK_F18);return TRUE;}
		if(sRemindLower.Compare(_T("f19"))==0){sOut->Format(_T("0x%02x"),VK_F19);return TRUE;}
		
		if(sRemindLower.Compare(_T("f20"))==0){sOut->Format(_T("0x%02x"),VK_F20);return TRUE;}
		if(sRemindLower.Compare(_T("f21"))==0){sOut->Format(_T("0x%02x"),VK_F21);return TRUE;}
		if(sRemindLower.Compare(_T("f22"))==0){sOut->Format(_T("0x%02x"),VK_F22);return TRUE;}
		if(sRemindLower.Compare(_T("f23"))==0){sOut->Format(_T("0x%02x"),VK_F23);return TRUE;}
		if(sRemindLower.Compare(_T("f24"))==0){sOut->Format(_T("0x%02x"),VK_F24);return TRUE;}
	}
	
	if(sRemindLower.Compare(_T("lshift"))==0){sOut->Format(_T("0x%02x"),VK_SHIFT);return TRUE;}
	if(sRemindLower.Compare(_T("rshift"))==0){sOut->Format(_T("0x%02x"),VK_SHIFT);return TRUE;}
	if(sRemindLower.Compare(_T("lctrl"))==0){sOut->Format(_T("0x%02x"),VK_CONTROL);return TRUE;}
	if(sRemindLower.Compare(_T("rctrl"))==0){sOut->Format(_T("0x%02x"),VK_CONTROL);return TRUE;}
	if(sRemindLower.Compare(_T("lalt"))==0){sOut->Format(_T("0x%02x"),VK_MENU);return TRUE;}
	if(sRemindLower.Compare(_T("ralt"))==0){sOut->Format(_T("0x%02x"),VK_MENU);return TRUE;}

	if(sRemindLower.Compare(_T("tab"))==0){sOut->Format(_T("0x%02x"),VK_TAB);return TRUE;}
	if(sRemindLower.Compare(_T("enter"))==0){
		sOut->Format(_T("0x%02x"),VK_RETURN);return TRUE;
	}
	if(sRemindLower.Compare(_T("return"))==0){sOut->Format(_T("0x%02x"),VK_RETURN);return TRUE;}
	if(sRemindLower.Compare(_T("space"))==0){sOut->Format(_T("0x%02x"),VK_SPACE);return TRUE;}
	sOut->Format(_T("%s"), sRemind);
	return TRUE;
}

BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData)
{
	int iType;
	BOOL bRet;
	bRet = GetCommand(sDataLine, &iType);
	if(bRet == FALSE){*iCommandType = COMMAND_NOTING; return FALSE;}

	CString sDataLocal;
	sDataLocal.Format(_T("%s"), sDataLine.Trim(_T(" ")).Trim(_T("\t")));

	CString sName;
	CString sArg;
	CString sRemain;
	saData->RemoveAll();
	switch(iType)
	{
	case COMMAND_REPEAT:
		{
			CString sID;
			sID.Format(_T("%d"),(*iSceneData));
			saData->Add(sID);
			(*iSceneData)=(*iSceneData)+1;
			
			ExtractData(sDataLocal, _T("r"), &sArg, &sDataLocal);
			int iRepeat;
			CString sRepeat;
			iRepeat=_ttoi(sArg);
			sRepeat.Format(_T("%d"),iRepeat);
			saData->Add(sRepeat);
		}
	case COMMAND_MOUSE_L_DOWN:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}

	case COMMAND_MOUSE_L_UP:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}

	case COMMAND_MOUSE_MOVE:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_WHEEL:
		{
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(" "), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_MOUSE_L_CLICK:
		{
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			saData->Add(sArg);
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			saData->Add(sArg);
			*iCommandType = iType;
			break;
		}
	case COMMAND_DELAY:
		{
			saData->Add(sDataLocal);
			*iCommandType=iType;
			break;
		}
	case COMMAND_BREAK:
		{
			*iCommandType=iType;
			break;
		}
	case COMMAND_KEY_DOWN_UP:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
		}
	case COMMAND_KEY_DOWN:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
		}

	case COMMAND_KEY_UP:
		{
			CString sOut;
			GetKeyType(sDataLocal, &sOut);

			saData->Add(sOut);

			*iCommandType=iType;
		}
	}

	return TRUE;
}