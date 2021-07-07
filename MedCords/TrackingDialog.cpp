// TrackingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MedCords.h"
#include "TrackingDialog.h"
#include "afxdialogex.h"

// CTrackingDialog dialog

IMPLEMENT_DYNAMIC(CTrackingDialog, CDialogEx)

CTrackingDialog::CTrackingDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAC_DETAILS_DLG, pParent)
{
	trackingInfoArray = new CArray<TrackingInfo, TrackingInfo>;
}

CTrackingDialog::~CTrackingDialog()
{
}

void CTrackingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRACKING_LIST, m_trackingListControl);
}


BEGIN_MESSAGE_MAP(CTrackingDialog, CDialogEx)
END_MESSAGE_MAP()


// CTrackingDialog message handlers


BOOL CTrackingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//To select the whole row 
	m_trackingListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//Add columns to the person list control
	CString column;
	column.LoadString(IDS_SL_NO);
	m_trackingListControl.InsertColumn(1, column, LVCFMT_CENTER, 80);
	column.LoadString(IDS_T_ID);
	m_trackingListControl.InsertColumn(2, column, LVCFMT_CENTER, 100);
	column.LoadString(IDS_T_BASE_LOC);
	m_trackingListControl.InsertColumn(3, column, LVCFMT_CENTER, 130);
	column.LoadString(IDS_TC_ID);
	m_trackingListControl.InsertColumn(4, column, LVCFMT_CENTER, 100);
	column.LoadString(IDS_TC_GROUP);
	m_trackingListControl.InsertColumn(5, column, LVCFMT_CENTER, 130);
	column.LoadString(IDS_TC_DATE);
	m_trackingListControl.InsertColumn(6, column, LVCFMT_CENTER, 130);
	column.LoadString(IDS_TCO_DATE);
	m_trackingListControl.InsertColumn(7, column, LVCFMT_CENTER, 130);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


/*-----------------------------------------------------------------------------------
	Function Name: MainDlgFunction
	Parameters: CString selectedEncounterID
	Return type: bool
	Description: This function is the entry point for the implementation of tracking
				 dialog box
-----------------------------------------------------------------------------------*/
bool CTrackingDialog::MainDlgFunction(CString selectedEncounterID)
{
	this->selectedEncounterID = selectedEncounterID;
	trackingInfoArray->RemoveAll();
	m_trackingListControl.DeleteAllItems();
	bool flag = RetrieveTrackingInfo();
	if (flag)
		DisplayList();
	return false;
}


/*-----------------------------------------------------------------------------------
	Function Name : RetrieveTrackingInfo
	Parameters : Zero parameters
	Return type : bool
	Description : This function retrieves the tracking info from the DatabaseFunctionalities Class
----------------------------------------------------------------------------------- */
bool CTrackingDialog::RetrieveTrackingInfo()
{
	bool flag = false;
	flag = databaseObject.RetrieveTrackingInfo(selectedEncounterID, trackingInfoArray);
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: DisplayList (Virtual function from DialogFunctionalities class)
	Parameters: Zero parameters
	Return type: bool
	Description: This function is used to Display the tracking list in the tracking list control
-----------------------------------------------------------------------------------*/
bool CTrackingDialog::DisplayList()
{
	numberOftrackingInfo = trackingInfoArray->GetCount();

	//Loop through the list and add tracking info to the list
	CString slNo;
	int iTracking = 0;
	for (iTracking = 0; iTracking < numberOftrackingInfo; iTracking++)
	{
		slNo.Format(_T("%d"), iTracking + 1);
		m_trackingListControl.InsertItem(iTracking, slNo);
		m_trackingListControl.SetItemText(iTracking, 1, trackingInfoArray->GetAt(iTracking).getTrackingID());
		m_trackingListControl.SetItemText(iTracking, 2, trackingInfoArray->GetAt(iTracking).getBaseLoc());
		m_trackingListControl.SetItemText(iTracking, 3, trackingInfoArray->GetAt(iTracking).getTrackingCheckinID());
		m_trackingListControl.SetItemText(iTracking, 4, trackingInfoArray->GetAt(iTracking).getTrackingGroup());
		m_trackingListControl.SetItemText(iTracking, 5, trackingInfoArray->GetAt(iTracking).getCheckinDate());
		m_trackingListControl.SetItemText(iTracking, 6, trackingInfoArray->GetAt(iTracking).getCheckoutDate());
	}
	if (iTracking == numberOftrackingInfo)
		return true;
	return false;
}