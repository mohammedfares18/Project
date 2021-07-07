#pragma once
#include "afxwin.h"
#include "DataStorage.h"
#include "DatabaseFunctionalities.h"

// CEncounterDialog dialog

class CEncounterDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEncounterDialog)

public:
	CEncounterDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEncounterDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENC_DETAILS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CEdit m_encounterID;
	CEdit m_encounterType;
	CEdit m_encounterStatus;
	CEdit m_encounterReason;
	CEdit m_encounterRegDate;
	CEdit m_encounterDischDate;
	CEdit m_encounterFacility;
	CEdit m_encounterBuilding;
	CEdit m_encounterNurseUnit;
	CEdit m_encounterRoom;
	CEdit m_encounterBed;

	//Structure to store selected encounter details
	encounterDetails *eDetails;

	//Selected Encounter ID
	CString selectedEncounterID;

	//Object to invoke functions of DatabaseFunctionalities class
	CDatabaseFunctionalities databaseObject;

public:
	/*-----------------------------------------------------------------------------------
		Function Name: MainDlgFunction
		Parameters: CString selectedEncounterID
		Return type: bool
		Description: This function is the entry point for the implemntation of encounter
					 dialog box
	-----------------------------------------------------------------------------------*/
	bool MainDlgFunction(CString selectedEncounterID);


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveEncounterDetails
		Parameters: Zero parameters
		Return type: bool
		Description: This function retrieves the encounter details from the DatabaseFunctionalities Class
	-----------------------------------------------------------------------------------*/
	bool RetrieveEncounterDetails();
	
	
	/*-----------------------------------------------------------------------------------
		Function Name: PopulateEncounterDetails
		Parameters: Zero parameters
		Return type: void
		Description: This function is used to Display the encounter details in the encounter
					 dialog box
	-----------------------------------------------------------------------------------*/
	void PopulateEncounterDetails();
};
