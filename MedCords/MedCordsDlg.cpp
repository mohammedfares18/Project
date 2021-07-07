
// MedCordsDlg.cpp : implementation file

#include "stdafx.h"
#include "MedCords.h"
#include "MedCordsDlg.h"
#include "MedCordsFunctionalities.h"
#include "PatientDetailsDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMedCordsDlg dialog



CMedCordsDlg::CMedCordsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PERSON_SEARCH, pParent)
	, m_FirstName(_T(""))
	, m_LastName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	personInfoArray = new CArray<PersonInfo, PersonInfo>;
}

void CMedCordsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_FirstName, m_FirstName);
	DDX_Text(pDX, IDC_EDIT2_LastName, m_LastName);
	DDX_Control(pDX, IDC_EDIT1_FirstName, m_controlFirstName);
	DDX_Control(pDX, IDC_EDIT2_LastName, m_controlLastName);
	DDX_Control(pDX, IDC_LIST_SelectPersonList, m_personListControl);
	DDX_Control(pDX, IDC_STATIC_FN_MESSAGE, m_FN_Message);
	DDX_Control(pDX, IDC_STATIC_LN_MESSAGE, m_LN_Message);
	DDX_Control(pDX, IDC_BUTTON_Search, m_SearchControl);
}

BEGIN_MESSAGE_MAP(CMedCordsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMedCordsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_Search, &CMedCordsDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_Reset, &CMedCordsDlg::OnBnClickedButtonReset)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SelectPersonList, &CMedCordsDlg::OnNMClickListSelectpersonlist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SelectPersonList, &CMedCordsDlg::OnNMDblclkListSelectpersonlist)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMedCordsDlg message handlers

BOOL CMedCordsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//To select the whole row 
	m_personListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	//Add columns to the person list control
	CString column;
	column.LoadString(IDS_SL_NO);
	m_personListControl.InsertColumn(1, column, LVCFMT_CENTER, 80);
	column.LoadString(IDS_P_ID);
	m_personListControl.InsertColumn(2, column, LVCFMT_CENTER, 100);
	column.LoadString(IDS_P_FULLNAME);
	m_personListControl.InsertColumn(3, column, LVCFMT_CENTER, 250);
	column.LoadString(IDS_P_DOB);
	m_personListControl.InsertColumn(4, column, LVCFMT_CENTER, 140);
	column.LoadString(IDS_P_AGE);
	m_personListControl.InsertColumn(5, column, LVCFMT_CENTER, 102);
	column.LoadString(IDS_P_GENDER);
	m_personListControl.InsertColumn(6, column, LVCFMT_CENTER, 102);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMedCordsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam); 
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMedCordsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMedCordsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*-----------------------------------------------------------------------------------
	Function Name: OnBnClickedSearch
	Parameters: Zero parameters
	Return type: void
	Description: This is event handler function when Search button is clicked
-----------------------------------------------------------------------------------*/
void CMedCordsDlg::OnBnClickedButtonSearch()
{
	m_personListControl.DeleteAllItems();
	personInfoArray->RemoveAll();

	m_controlFirstName.GetWindowText(m_FirstName);
	m_controlLastName.GetWindowText(m_LastName);
	m_FirstName.Trim();
	m_LastName.Trim();

	bool flagConnect = CDatabaseFunctionalities::connectToDatabase();
	if (flagConnect)
	{
		bool flagSearch = CDatabaseFunctionalities::searchPatientsFromDatabase(m_FirstName, m_LastName);
		if (flagSearch)
		{
			bool flagRetrieve = RetrieveSimilarPersonsInfo();
			if (flagRetrieve)
				DisplayList();
			else
			{
				CString message;
				message.LoadString(IDS_STRING_NOPEOPLE);
				AfxMessageBox(message);
			}
		}
	}
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveSimilarPersonsInfo
	Parameters: Zero parameters
	Return type: bool
	Description: This function retrieves the patient info from the DatabaseFunctionalities Class
-----------------------------------------------------------------------------------*/
bool CMedCordsDlg::RetrieveSimilarPersonsInfo()
{
	bool flag = false;
	flag = databaseObject.RetrieveSimilarPersonsInfo(personInfoArray);
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: DisplayList (Virtual function from DialofFunctionalities class)
	Parameters: Zero parameters
	Return type: bool
	Description: This function is used to Display the patients list in the Select Patient
				 list control
-----------------------------------------------------------------------------------*/
bool CMedCordsDlg::DisplayList()
{
	numberOfPeople = personInfoArray->GetCount();

	//Loop through the list and add patients info with similar names
	CString slNo;
	int iPerson = 0;
	for (iPerson = 0; iPerson < numberOfPeople; iPerson++)
	{
		slNo.Format(_T("%d"), iPerson + 1);
		m_personListControl.InsertItem(iPerson, slNo);
		m_personListControl.SetItemText(iPerson, 1, personInfoArray->GetAt(iPerson).getPersonID());
		m_personListControl.SetItemText(iPerson, 2, personInfoArray->GetAt(iPerson).getFullName());
		m_personListControl.SetItemText(iPerson, 3, personInfoArray->GetAt(iPerson).getPersonDOB());
		m_personListControl.SetItemText(iPerson, 4, personInfoArray->GetAt(iPerson).getPersonAge());
		m_personListControl.SetItemText(iPerson, 5, personInfoArray->GetAt(iPerson).getPersonGender());
	}
	if (iPerson == numberOfPeople)
		return true;
	return false;
}


/*-----------------------------------------------------------------------------------
	Function Name: OnBnClickedReset
	Parameters: Zero parameters
	Return type: void
	Description: This is event handler function when Reset button is clicked
-----------------------------------------------------------------------------------*/
void CMedCordsDlg::OnBnClickedButtonReset()
{
	m_controlFirstName.SetWindowText(_T(""));
	m_controlLastName.SetWindowText(_T(""));
	m_personListControl.DeleteAllItems();

	m_FirstName.SetString(_T(""));
	m_LastName.SetString(_T(""));

	m_SearchControl.EnableWindow(false);
}


/*-----------------------------------------------------------------------------------
	Function Name: OnBnClickedOk
	Parameters: Zero parameters
	Return type: void
	Description: This is event handler function when OK button is clicked
-----------------------------------------------------------------------------------*/
void CMedCordsDlg::OnBnClickedOk()
{
	if (selectedID.GetLength() > 0)
	{
		CPatientDetailsDlg obj;
		bool b = obj.MainDlgFunction(selectedID);
		selectedID.SetString(_T(""));
	}
	else
	{
		CString message;
		message.LoadString(IDS_STRING_SELECT_PAT);
		AfxMessageBox(message);
	}
}


/*-----------------------------------------------------------------------------------
	Function Name: OnNMClickListSelectpersonlist
	Parameters: NMHDR *pNMHDR, LRESULT *pResult
	Return type: void
	Description: This is event handler function when a row in Select Person list is clicked
-----------------------------------------------------------------------------------*/
void CMedCordsDlg::OnNMClickListSelectpersonlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int selectedItemIndex;
	selectedItemIndex = m_personListControl.GetSelectionMark();
	if (selectedItemIndex != -1)
		selectedID = personInfoArray->GetAt(selectedItemIndex).getPersonID();
	*pResult = 0;
}


/*-----------------------------------------------------------------------------------
	Function Name: OnNMDblclkListSelectpersonlist
	Parameters: NMHDR *pNMHDR, LRESULT *pResult
	Return type: void
	Description: This is event handler function when a row in Select Person list is double clicked
-----------------------------------------------------------------------------------*/
void CMedCordsDlg::OnNMDblclkListSelectpersonlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedOk();
	*pResult = 0;
}


/*-----------------------------------------------------------------------------------
	Function Name: OnCtlColor
	Parameters: CDC* pDC, CWnd* pWnd, UINT nCtlColor
	Return type: HBRUSH
	Description: This function is invoked when a child control is about to be drawn
-----------------------------------------------------------------------------------*/
HBRUSH CMedCordsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_FN_MESSAGE || pWnd->GetDlgCtrlID() == IDC_STATIC_LN_MESSAGE)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	return hbr;
}


/*-----------------------------------------------------------------------------------
	Function Name: SetMessage
	Parameters: int ID
	Return type: bool
	Description: This function retrieves sets the message for wrong character input
-----------------------------------------------------------------------------------*/
bool CMedCordsDlg::SetMessage(int ID)
{
	CString wrongChar;
	wrongChar.LoadString(IDS_STRING_WRONG_CHAR);
	if (ID == IDC_EDIT1_FirstName)
	{
		m_FN_Message.SetWindowTextA(wrongChar);
		Sleep(1200);
		m_FN_Message.SetWindowTextA(_T(""));
		return true;
	}
	else
	{
		m_LN_Message.SetWindowText(wrongChar);
		Sleep(1200);
		m_LN_Message.SetWindowText(_T(""));
		return true;
	}
	return false;
}