// PatientDetailsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedCords.h"
#include "PatientDetailsDlg.h"
#include "afxdialogex.h"

// CPatientDetailsDlg dialog

IMPLEMENT_DYNAMIC(CPatientDetailsDlg, CDialogEx)

CPatientDetailsDlg::CPatientDetailsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PATIENT_DETAILS, pParent)
	, m_firstName(_T(""))
	, m_lastName(_T(""))
	, m_dateOfBirth(_T(""))
	, m_age(_T(""))
	, m_gender(_T(""))
	, m_streetAddr(_T(""))
	, m_state(_T(""))
	, m_zipCode(_T(""))
	, m_fullName(_T(""))
	, m_personID(_T(""))
	, p_window(NULL)
{
	encounterInfoArray = new CArray<EncounterInfo, EncounterInfo>;
	pDetails = new patientDetails;
}

CPatientDetailsDlg::~CPatientDetailsDlg()
{
}

void CPatientDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4_FirstName, m_firstName);
	DDX_Text(pDX, IDC_EDIT5_LastName, m_lastName);
	DDX_Text(pDX, IDC_EDIT11_DOB, m_dateOfBirth);
	DDX_Text(pDX, IDC_EDIT9_Age, m_age);
	DDX_Text(pDX, IDC_EDIT10_Gender, m_gender);
	DDX_Text(pDX, IDC_EDIT2_StreetAddr, m_streetAddr);
	DDX_Text(pDX, IDC_EDIT8_State, m_state);
	DDX_Text(pDX, IDC_EDIT7_ZipCode, m_zipCode);
	DDX_Text(pDX, IDC_EDIT1_FullNameWelcome, m_fullName);
	DDX_Text(pDX, IDC_EDIT4_PersonID, m_personID);
	DDX_Control(pDX, IDC_LIST3, m_controlEncounterList);
	DDX_Control(pDX, IDC_TAB1, m_tabControl);
}


BEGIN_MESSAGE_MAP(CPatientDetailsDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &CPatientDetailsDlg::OnNMDblclkList3)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPatientDetailsDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CPatientDetailsDlg message handlers

BOOL CPatientDetailsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//To select the whole row 
	m_controlEncounterList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//Add columns to the list control
	CString column;
	column.LoadString(IDS_SL_NO);
	m_controlEncounterList.InsertColumn(1, column, LVCFMT_CENTER, 90);
	column.LoadString(IDS_E_ID);
	m_controlEncounterList.InsertColumn(2, column, LVCFMT_CENTER, 185);
	column.LoadString(IDS_E_TYPE);
	m_controlEncounterList.InsertColumn(3, column, LVCFMT_CENTER, 250);
	column.LoadString(IDS_E_STATUS);
	m_controlEncounterList.InsertColumn(4, column, LVCFMT_CENTER, 250);

	CString tab;
	tab.LoadString(IDS_E_DETAILS);
	m_tabControl.InsertItem(1, tab);
	tab.LoadString(IDS_T_DETAILS);
	m_tabControl.InsertItem(2, tab);
	tab.LoadString(IDS_O_DETAILS);
	m_tabControl.InsertItem(3, tab);

	DisplayList();
	
	m_tabControl.GetClientRect(rect);
	
	encounterDlg.Create(IDD_ENC_DETAILS_DLG, &m_tabControl);
	encounterDlg.SetWindowPos(NULL, 0, 40, rect.Width(), rect.Height() - 35,  SWP_NOZORDER);
	
	trackingDlg.Create(IDD_TRAC_DETAILS_DLG, &m_tabControl);
	trackingDlg.SetWindowPos(NULL, 0, 40, rect.Width(), rect.Height() - 35,  SWP_NOZORDER);

	ordersDlg.Create(IDD_ORD_DETAILS_DLG, &m_tabControl);
	ordersDlg.SetWindowPos(NULL, 0, 40, rect.Width(), rect.Height() - 35,  SWP_NOZORDER);

	encounterDlg.ShowWindow(SW_SHOW);
	ordersDlg.ShowWindow(SW_HIDE);
	trackingDlg.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


// This is the function which builds the dialog sequentially
bool CPatientDetailsDlg::MainDlgFunction(CString selectedPersonID)
{
	this->selectedPersonID = selectedPersonID;

	bool flag1, flag2;
	flag1 = RetrievePatientDetails();
	if (flag1)
	{
		PopulatePatientDetails();
		flag2 = RetrieveEncountersInfo();
		if (flag2)
		{		
			DoModal();
		}
	}
	return true;
}

// This function retrieves selected patient details 
bool CPatientDetailsDlg::RetrievePatientDetails()
{
	bool flag = false;
	flag = databaseObject.RetrievePatientDetails(selectedPersonID, pDetails);
	return flag;
}

void CPatientDetailsDlg::PopulatePatientDetails()
{
	CString welcome, space;
	welcome.LoadString(IDS_STRING_WELCOME);
	space.LoadString(IDS_STRING_SPACE);
	m_fullName = welcome + space + pDetails->m_fullName;
	m_firstName = pDetails->m_firstName;
	m_lastName = pDetails->m_lastName;
	m_dateOfBirth = pDetails->m_dateOfBirth;
	m_age = pDetails->m_age;
	m_gender = pDetails->m_gender;
	m_personID = pDetails->m_personID;
	if(pDetails->m_streetAddr.GetLength() == 0 || pDetails->m_city.GetLength() == 0)
		m_streetAddr = pDetails->m_streetAddr + pDetails->m_city;
	else
		m_streetAddr = pDetails->m_streetAddr + _T(", ") + pDetails->m_city;
	if(pDetails->m_state.GetLength() == 0 || pDetails->m_country.GetLength() == 0)
		m_state = pDetails->m_state + pDetails->m_country;
	else
		m_state = pDetails->m_state + _T(", ") + pDetails->m_country;
	m_zipCode = pDetails->m_zipCode;
}

// This function retrieves encounters
bool CPatientDetailsDlg::RetrieveEncountersInfo()
{
	bool flag = false;
	flag = databaseObject.RetrieveEncountersInfo(selectedPersonID, encounterInfoArray);
	return flag;
}

// This function displays all the encounters of the selected patient on the encounters list
bool CPatientDetailsDlg::DisplayList()
{
	//To set the number of encounters
	numberOfEncounters = encounterInfoArray->GetCount();

	//Loop through the list and add encounters info for that person
	CString slNo;
	int iEncounter = 0;
	for (iEncounter = 0; iEncounter < numberOfEncounters; iEncounter++)
	{
		slNo.Format(_T("%d"), iEncounter + 1);
		this->m_controlEncounterList.InsertItem(iEncounter, slNo);
		m_controlEncounterList.SetItemText(iEncounter, 1, encounterInfoArray->GetAt(iEncounter).getEncounterID());
		m_controlEncounterList.SetItemText(iEncounter, 2, encounterInfoArray->GetAt(iEncounter).getEncounterType());
		m_controlEncounterList.SetItemText(iEncounter, 3, encounterInfoArray->GetAt(iEncounter).getEncounterStatus());
	}
	if (iEncounter == numberOfEncounters)
		return true;
	return false;
}

void CPatientDetailsDlg::OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int selectedItemIndex;
	selectedItemIndex = m_controlEncounterList.GetSelectionMark();
	if (selectedItemIndex != -1)
		selectedEncounterID = encounterInfoArray->GetAt(selectedItemIndex).getEncounterID();

	bool encFlag, tracFlag, ordFlag;
	encFlag = encounterDlg.MainDlgFunction(selectedEncounterID);
	tracFlag = trackingDlg.MainDlgFunction(selectedEncounterID);
	ordFlag = ordersDlg.MainDlgFunction(selectedEncounterID);
	if (encFlag)
	{
		if (p_window != NULL)
		{
			p_window->ShowWindow(SW_HIDE);
			p_window = NULL;
		}
		m_tabControl.SetCurSel(0);
		encounterDlg.ShowWindow(SW_SHOW);
		p_window = &encounterDlg;
	}
	*pResult = 0;
}


void CPatientDetailsDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if (p_window != NULL)
	{
		p_window->ShowWindow(SW_HIDE);
		p_window = NULL;
	}
	int tabIndex;
	tabIndex = m_tabControl.GetCurSel();
	switch (tabIndex)
	{
	case 0 : encounterDlg.ShowWindow(SW_SHOW);
			 p_window = &encounterDlg;
			 break;
	case 1 : trackingDlg.ShowWindow(SW_SHOW);
			 p_window = &trackingDlg;
			 break;
	case 2 : ordersDlg.ShowWindow(SW_SHOW);
			 p_window = &ordersDlg;
			 break;
	}
	*pResult = 0;
}
