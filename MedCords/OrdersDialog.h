#pragma once
#include "afxcmn.h"
#include "DatabaseFunctionalities.h"
#include "DataStorage.h"
#include "DialogFunctionalities.h"

// COrdersDialog dialog

class COrdersDialog : public CDialogEx, public DialogFunctionalities
{
	DECLARE_DYNAMIC(COrdersDialog)

public:
	COrdersDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COrdersDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORD_DETAILS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	// This is the variable to control the orders list
	CListCtrl m_ordersListControl;

	//Selected Encounter ID
	CString selectedEncounterID;

	//Object to invoke functions of DatabaseFunctionalities class
	CDatabaseFunctionalities databaseObject;

	//number of orders
	int numberOfOrders;

public:
	//Array to store orders info objects
	CArray<OrdersInfo, OrdersInfo>* ordersInfoArray;

	
	/*-----------------------------------------------------------------------------------
		Function Name: MainDlgFunction
		Parameters: CString selectedEncounterID
		Return type: bool
		Description: This function is the entry point for the implementation of orders
					 dialog box
	-----------------------------------------------------------------------------------*/
	bool MainDlgFunction(CString selectedEncounterID);

	
	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveOrdersInfo
		Parameters: Zero parameters
		Return type: bool
		Description: This function retrieves the orders info from the DatabaseFunctionalities Class
	-----------------------------------------------------------------------------------*/
	bool RetrieveOrdersInfo();


	/*-----------------------------------------------------------------------------------
		Function Name: DisplayList (Virtual function from DialogFunctionalities class)
		Parameters: Zero parameters
		Return type: bool
		Description: This function is used to Display the orders list in the orders list control
	-----------------------------------------------------------------------------------*/
	virtual bool DialogFunctionalities::DisplayList() override;
};
