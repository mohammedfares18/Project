#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DatabaseFunctionalities.h"
#include "DataStorage.h"
#include "DialogFunctionalities.h"

// CTrackingDialog dialog

class CTrackingDialog : public CDialogEx, public DialogFunctionalities
{
	DECLARE_DYNAMIC(CTrackingDialog)

public:
	CTrackingDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrackingDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAC_DETAILS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	// Control variable for tracking list control
	CListCtrl m_trackingListControl;

	//Selected Encounter ID
	CString selectedEncounterID;

	//Object to invoke functions of DatabaseFunctionalities class
	CDatabaseFunctionalities databaseObject;

	//number of tracking info
	int numberOftrackingInfo;

public:
	//Array to store tracking info objects
	CArray<TrackingInfo, TrackingInfo>* trackingInfoArray;

	
	/*-----------------------------------------------------------------------------------
		Function Name: MainDlgFunction
		Parameters: CString selectedEncounterID
		Return type: bool
		Description: This function is the entry point for the implementation of tracking
					 dialog box
	-----------------------------------------------------------------------------------*/
	bool MainDlgFunction(CString selectedEncounterID);

	
	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveTrackingInfo
		Parameters: Zero parameters
		Return type: bool
		Description: This function retrieves the tracking info from the DatabaseFunctionalities Class
	-----------------------------------------------------------------------------------*/
	bool RetrieveTrackingInfo();

	
	/*-----------------------------------------------------------------------------------
		Function Name: DisplayList (Virtual function from DialogFunctionalities class)
		Parameters: Zero parameters
		Return type: bool
		Description: This function is used to Display the tracking list in the tracking list control
	-----------------------------------------------------------------------------------*/
	virtual bool DialogFunctionalities::DisplayList() override;
};
