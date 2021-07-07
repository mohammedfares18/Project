// EncounterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MedCords.h"
#include "EncounterDialog.h"
#include "afxdialogex.h"


// CEncounterDialog dialog

IMPLEMENT_DYNAMIC(CEncounterDialog, CDialogEx)

CEncounterDialog::CEncounterDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENC_DETAILS_DLG, pParent)
{
	eDetails = new encounterDetails;
}

CEncounterDialog::~CEncounterDialog()
{
}

void CEncounterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_encounterID);
	DDX_Control(pDX, IDC_EDIT2_E_TYPE, m_encounterType);
	DDX_Control(pDX, IDC_EDIT3_E_STATUS, m_encounterStatus);
	DDX_Control(pDX, IDC_EDIT4_E_REASON, m_encounterReason);
	DDX_Control(pDX, IDC_EDIT5_E_REG_DATE, m_encounterRegDate);
	DDX_Control(pDX, IDC_EDIT6_E_DISCH__DATE, m_encounterDischDate);
	DDX_Control(pDX, IDC_EDIT7_E_FACILITY, m_encounterFacility);
	DDX_Control(pDX, IDC_EDIT8_E_BUILDING, m_encounterBuilding);
	DDX_Control(pDX, IDC_EDIT9_E_NURSE_UNIT, m_encounterNurseUnit);
	DDX_Control(pDX, IDC_EDIT11_E_ROOM, m_encounterRoom);
	DDX_Control(pDX, IDC_EDIT12_E_BED, m_encounterBed);
}


BEGIN_MESSAGE_MAP(CEncounterDialog, CDialogEx)
END_MESSAGE_MAP()


// CEncounterDialog message handlers


/*-----------------------------------------------------------------------------------
	Function Name: MainDlgFunction
	Parameters: CString selectedEncounterID
	Return type: bool
	Description: This function is the entry point for the implemntation of encounter
				 dialog box
-----------------------------------------------------------------------------------*/
bool CEncounterDialog::MainDlgFunction(CString selectedEncounterID)
{
	this->selectedEncounterID = selectedEncounterID;
	bool flag;
	flag = RetrieveEncounterDetails();
	if (flag)
	{
		PopulateEncounterDetails();
	}
	return true;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveEncounterDetails
	Parameters: Zero parameters
	Return type: bool
	Description: This function retrieves the encounter details from the DatabaseFunctionalities Class
-----------------------------------------------------------------------------------*/
bool CEncounterDialog::RetrieveEncounterDetails()
{
	bool flag = false;
	flag = databaseObject.RetrieveEncounterDetails(selectedEncounterID, eDetails);
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: PopulateEncounterDetails
	Parameters: Zero parameters
	Return type: void
	Description: This function is used to Display the encounter details in the encounter
				 dialog box
-----------------------------------------------------------------------------------*/
void CEncounterDialog::PopulateEncounterDetails()
{
	m_encounterID.SetWindowText(eDetails->m_encounterID);
	m_encounterType.SetWindowText(eDetails->m_encounterType);
	m_encounterStatus.SetWindowText(eDetails->m_encounterStatus);
	m_encounterReason.SetWindowText(eDetails->m_encounterReason);
	m_encounterRegDate.SetWindowText(eDetails->m_encounterRegDate);
	m_encounterDischDate.SetWindowText(eDetails->m_encounterDischDate);
	m_encounterFacility.SetWindowText(eDetails->m_encounterFacility);
	m_encounterBuilding.SetWindowText(eDetails->m_encounterBuilding);
	m_encounterNurseUnit.SetWindowText(eDetails->m_encounterNurseUnit);
	m_encounterRoom.SetWindowText(eDetails->m_encounterRoom);
	m_encounterBed.SetWindowText(eDetails->m_encounterBed);
}
