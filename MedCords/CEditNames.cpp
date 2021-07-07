#include "stdafx.h"
#include "CEditNames.h"
#include "MedCordsFunctionalities.h"
#include "MedCordsDlg.h"
BEGIN_MESSAGE_MAP(CEditNames, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()


/*-----------------------------------------------------------------------------------
	Function Name: OnChar
	Parameters: UINT nChar, UINT nRepCnt, UINT nFlags
	Return type: void
	Description: This function is invoked when a character is entered in CEditNames
				 type of Edit Control box
-----------------------------------------------------------------------------------*/
void CEditNames::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMedCordsDlg *dlgPointer = (CMedCordsDlg*)this->GetParent();
	char ch = (char)nChar;
	MedCordsFunctionalities med;
	CString firstName, lastName;
	if(!med.CheckForValidCharacter(ch))
	{
		int ID = GetDlgCtrlID();
		MessageBeep(true);
		dlgPointer->SetMessage(ID);
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	dlgPointer->m_controlFirstName.GetWindowText(firstName);
	dlgPointer->m_controlLastName.GetWindowText(lastName);
	bool validFlag = med.ValidatePersonNames(firstName, lastName);
	if (validFlag)
		dlgPointer->m_SearchControl.EnableWindow(true);
	else
		dlgPointer->m_SearchControl.EnableWindow(false);	
}