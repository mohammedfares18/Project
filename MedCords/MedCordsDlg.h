
// MedCordsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataStorage.h"
#include "DatabaseFunctionalities.h"
#include "DialogFunctionalities.h"
#include "CEditNames.h"

// CMedCordsDlg dialog
class CMedCordsDlg : public CDialogEx, public DialogFunctionalities
{
// Construction
public:
	CMedCordsDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_SEARCH};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// Person's first name
	CString m_FirstName;
	
	//Person's last name
	CString m_LastName;
	
	//Flag to populate similar persons details
	bool flag = false;
	
	//number of people
	int numberOfPeople;
	
	//Selected ID of the patient
	CString selectedID;
	
	//Object to invoke functions of DatabaseFunctionalities class
	CDatabaseFunctionalities databaseObject;

	// To control the Person list
	CListCtrl m_personListControl;
	
public:
	//Control variable for Search button
	CButton m_SearchControl;

	// This is the variable to control the message for wrong character input
	CStatic m_FN_Message;

	// This is the variable to control the message for wrong character input
	CStatic m_LN_Message;

	//Array to store person info objects
	CArray<PersonInfo, PersonInfo>* personInfoArray;

	//Control variable for first name
	CEditNames m_controlFirstName;

	//Control variable for last name
	CEditNames m_controlLastName;

	
	/*-----------------------------------------------------------------------------------
		Function Name: DisplayList (Virtual function from DialofFunctionalities class)
		Parameters: Zero parameters
		Return type: bool
		Description: This function is used to Display the patients list in the Select Patient
					 list control
	-----------------------------------------------------------------------------------*/
	virtual bool DialogFunctionalities::DisplayList() override;


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveSimilarPersonsInfo
		Parameters: Zero parameters
		Return type: bool
		Description: This function retrieves the patient info from the DatabaseFunctionalities Class  
	-----------------------------------------------------------------------------------*/ 
	bool RetrieveSimilarPersonsInfo();


	/*-----------------------------------------------------------------------------------
		Function Name: SetMessage
		Parameters: int ID
		Return type: bool
		Description: This function retrieves sets the message for wrong character input
	-----------------------------------------------------------------------------------*/
	bool SetMessage(int ID);


	/*-----------------------------------------------------------------------------------
		Function Name: OnBnClickedOk
		Parameters: Zero parameters
		Return type: void
		Description: This is event handler function when OK button is clicked
	-----------------------------------------------------------------------------------*/
	afx_msg void OnBnClickedOk();


	/*-----------------------------------------------------------------------------------
		Function Name: OnBnClickedSearch
		Parameters: Zero parameters
		Return type: void
		Description: This is event handler function when Search button is clicked
	-----------------------------------------------------------------------------------*/
	afx_msg void OnBnClickedButtonSearch();

	
	/*-----------------------------------------------------------------------------------
		Function Name: OnBnClickedReset
		Parameters: Zero parameters
		Return type: void
		Description: This is event handler function when Reset button is clicked
	-----------------------------------------------------------------------------------*/
	afx_msg void OnBnClickedButtonReset();


	/*-----------------------------------------------------------------------------------
		Function Name: OnNMClickListSelectpersonlist
		Parameters: NMHDR *pNMHDR, LRESULT *pResult
		Return type: void
		Description: This is event handler function when a row in Select Person list is clicked
	-----------------------------------------------------------------------------------*/
	afx_msg void OnNMClickListSelectpersonlist(NMHDR *pNMHDR, LRESULT *pResult);


	/*-----------------------------------------------------------------------------------
		Function Name: OnNMDblclkListSelectpersonlist
		Parameters: NMHDR *pNMHDR, LRESULT *pResult
		Return type: void
		Description: This is event handler function when a row in Select Person list is double clicked
	-----------------------------------------------------------------------------------*/
	afx_msg void OnNMDblclkListSelectpersonlist(NMHDR *pNMHDR, LRESULT *pResult);


	/*-----------------------------------------------------------------------------------
		Function Name: OnCtlColor
		Parameters: CDC* pDC, CWnd* pWnd, UINT nCtlColor
		Return type: HBRUSH
		Description: This function is invoked when a child control is about to be drawn
	-----------------------------------------------------------------------------------*/
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
