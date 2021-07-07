// OrdersDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MedCords.h"
#include "OrdersDialog.h"
#include "afxdialogex.h"


// COrdersDialog dialog
IMPLEMENT_DYNAMIC(COrdersDialog, CDialogEx)

COrdersDialog::COrdersDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ORD_DETAILS_DLG, pParent)
{
	ordersInfoArray = new CArray<OrdersInfo, OrdersInfo>;
}

COrdersDialog::~COrdersDialog()
{
}

void COrdersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ordersListControl);
}


BEGIN_MESSAGE_MAP(COrdersDialog, CDialogEx)
END_MESSAGE_MAP()


// COrdersDialog message handlers


BOOL COrdersDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//To select the whole row 
	m_ordersListControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//Add columns to the person list control
	CString column;
	column.LoadString(IDS_SL_NO);
	m_ordersListControl.InsertColumn(1, column, LVCFMT_CENTER, 80);
	column.LoadString(IDS_O_ID);
	m_ordersListControl.InsertColumn(2, column, LVCFMT_CENTER, 100);
	column.LoadString(IDS_O_NAME);
	m_ordersListControl.InsertColumn(3, column, LVCFMT_CENTER, 250);
	column.LoadString(IDS_O_STATUS);
	m_ordersListControl.InsertColumn(4, column, LVCFMT_CENTER, 130);
	column.LoadString(IDS_O_CATALOG);
	m_ordersListControl.InsertColumn(5, column, LVCFMT_CENTER, 150);
	column.LoadString(IDS_O_CATALOG_TYPE);
	m_ordersListControl.InsertColumn(6, column, LVCFMT_CENTER, 130);
	column.LoadString(IDS_O_DATE);
	m_ordersListControl.InsertColumn(7, column, LVCFMT_CENTER, 130);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


/*-----------------------------------------------------------------------------------
	Function Name: MainDlgFunction
	Parameters: CString selectedEncounterID
	Return type: bool
	Description: This function is the entry point for the implementation of orders
				 dialog box
-----------------------------------------------------------------------------------*/
bool COrdersDialog::MainDlgFunction(CString selectedEncounterID)
{
	this->selectedEncounterID = selectedEncounterID;
	ordersInfoArray->RemoveAll();
	m_ordersListControl.DeleteAllItems();
	bool flag = RetrieveOrdersInfo();
	if (flag)
		DisplayList();
	return false;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveOrdersInfo
	Parameters: Zero parameters
	Return type: bool
	Description: This function retrieves the orders info from the DatabaseFunctionalities Class
-----------------------------------------------------------------------------------*/
bool COrdersDialog::RetrieveOrdersInfo()
{
	bool flag = false;
	flag = databaseObject.RetrieveOrdersInfo(selectedEncounterID, ordersInfoArray);
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: DisplayList (Virtual function from DialogFunctionalities class)
	Parameters: Zero parameters
	Return type: bool
	Description: This function is used to Display the orders list in the orders list control
-----------------------------------------------------------------------------------*/
bool COrdersDialog::DisplayList()
{
	numberOfOrders = ordersInfoArray->GetCount();

	//Loop through the list and add tracking info to the list
	CString slNo;
	int iOrders = 0;
	for (iOrders = 0; iOrders < numberOfOrders; iOrders++)
	{
		slNo.Format(_T("%d"), iOrders + 1);
		m_ordersListControl.InsertItem(iOrders, slNo);
		m_ordersListControl.SetItemText(iOrders, 1, ordersInfoArray->GetAt(iOrders).getOrderID());
		m_ordersListControl.SetItemText(iOrders, 2, ordersInfoArray->GetAt(iOrders).getOrderName());
		m_ordersListControl.SetItemText(iOrders, 3, ordersInfoArray->GetAt(iOrders).getOrderStatus());
		m_ordersListControl.SetItemText(iOrders, 4, ordersInfoArray->GetAt(iOrders).getOrderCatalog());
		m_ordersListControl.SetItemText(iOrders, 5, ordersInfoArray->GetAt(iOrders).getOrderCatalogType());
		m_ordersListControl.SetItemText(iOrders, 6, ordersInfoArray->GetAt(iOrders).getOrderDate());
	}
	if (iOrders == numberOfOrders)
		return true;
	return false;
}
