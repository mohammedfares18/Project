#pragma once
#include <afxwin.h>
class CEditNames : public CEdit
{
public:
	DECLARE_MESSAGE_MAP()

	/*-----------------------------------------------------------------------------------
		Function Name: OnChar
		Parameters: UINT nChar, UINT nRepCnt, UINT nFlags
		Return type: void
		Description: This function is invoked when a character is entered in CEditNames
					 type of Edit Control box
	-----------------------------------------------------------------------------------*/
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

