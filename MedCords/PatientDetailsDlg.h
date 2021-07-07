#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataStorage.h"
#include "DatabaseFunctionalities.h"
#include "EncounterDialog.h"
#include "TrackingDialog.h"
#include "OrdersDialog.h"
#include "DialogFunctionalities.h"

// CPatientDetailsDlg dialog

class CPatientDetailsDlg : public CDialogEx, public DialogFunctionalities
{
	DECLARE_DYNAMIC(CPatientDetailsDlg)

public:
	CPatientDetailsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientDetailsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATIENT_DETAILS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_firstName;
	CString m_lastName;
	CString m_dateOfBirth;
	CString m_age;
	CString m_gender;
	CString m_streetAddr;
	CString m_city;
	CString m_state;
	CString m_country;
	CString m_zipCode;
	CString m_fullName;
	CString m_personID;
	
	//To store selected patient details
	patientDetails *pDetails;

	// Control variable for encounters list control
	CListCtrl m_controlEncounterList;

	//number of encounters
	int numberOfEncounters;

	//Selected Person ID
	CString selectedPersonID;

	//Object to invoke functions of DatabaseFunctionalities class
	CDatabaseFunctionalities databaseObject;

	// This variable is used for tab control
	CTabCtrl m_tabControl;

	// This is the object for encounter details dialog in tab control
	CEncounterDialog encounterDlg;

	// This is the object for tracking details dialog in tab control
	CTrackingDialog trackingDlg;

	// This is the object for orders details dialog in tab control
	COrdersDialog ordersDlg;

	//Selected Encounter ID
	CString selectedEncounterID;

public:
	//Array to store encounter info objects
	CArray<EncounterInfo, EncounterInfo>* encounterInfoArray;
	
	void PopulatePatientDetails();
	virtual BOOL OnInitDialog();
	
	// This function retrieves selected patient details 
	bool RetrievePatientDetails();
	
	// This is the function which builds the dialog sequentially
	bool MainDlgFunction(CString selectedID);
	
	// This function retrieves encounters
	bool RetrieveEncountersInfo();

	// This function displays all the encounters of the selected patient on the encounters list
	virtual bool DialogFunctionalities::DisplayList() override;

	
private:
	CWnd* p_window;
	CRect rect;

public:
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
