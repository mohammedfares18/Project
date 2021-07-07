#pragma once
#include "MedCords.h"
#include "DataStorage.h"
#include "SecDefs.h"
#include "Secrtl.h"
#include "crmexports.h"
#include "MedCordsFunctionalities.h"

class CDatabaseFunctionalities
{
public:
	CDatabaseFunctionalities();
	~CDatabaseFunctionalities();
	
private:
	//Array to store person info objects
	CArray<PersonInfo, PersonInfo> personInfoArray;
	//number of people
	int numberOfPeople;

	//Struct to store selected patient's details
	patientDetails pDetails;
	
	//Array to store encounter info objects
	CArray<EncounterInfo, EncounterInfo> encounterInfoArray;
	//number of encounters
	int numberOfEncounters;

	//Struct to store selected encounter's details
	encounterDetails eDetails;

	//Array to store tracking info objects
	CArray<TrackingInfo, TrackingInfo> trackingInfoArray;
	//number of tracking info
	int numberOftrackingInfo;

	//Array to store orders info objects
	CArray<OrdersInfo, OrdersInfo> ordersInfoArray;
	//number of orders
	int numberOfOrders;

	//Object of MedCordsFunctionalities
	MedCordsFunctionalities med;

public:
	//Crm Handle for the application
	static CrmHandle AppHnd;
	//Crm Handle for the task
	static CrmHandle TaskHnd;
	//Crm Handle for the request
	static CrmHandle ReqHnd;
	//Sr Handle for the reply
	static SrvHandle hReply;


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveSimilarPersonsInfo
		Parameters: CArray<PersonInfo, PersonInfo>* personInfoArray
		Return type: bool
		Description: This function retrieves person'd id,name,gender,age and date of birth 
					 and puts these details in pInfoArray
	-----------------------------------------------------------------------------------*/
	bool RetrieveSimilarPersonsInfo(CArray<PersonInfo, PersonInfo>* pInfoArray);


	/*-----------------------------------------------------------------------------------
		Function Name: RetrievePatientDetails
		Parameters: CString pID, patientDetails *pDetails
		Return type: bool
		Description: This function retrieves selected patient details with ID as pID and 
					 populates in pDetails structure
	-----------------------------------------------------------------------------------*/
	bool RetrievePatientDetails(CString pID, patientDetails *pDetails);


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveEncountersInfo
		Parameters: CString pID, CArray<EncounterInfo, EncounterInfo>* encInfoArray
		Return type: bool
		Description: This function retrieves all encounters for passed person ID
					 and populates in encInfoArray 
	-----------------------------------------------------------------------------------*/
	bool RetrieveEncountersInfo(CString pID, CArray<EncounterInfo, EncounterInfo>* encInfoArrray);
	

	/*-----------------------------------------------------------------------------------
		Function Name:  RetrieveEncounterDetails
		Parameters: CString encounterID, encounterDetails *eDetails
		Return type: bool
		Description: This function retrieves selected encounter details with ID as encounterID
					 and populates in eDetails structure
	-----------------------------------------------------------------------------------*/
	bool RetrieveEncounterDetails(CString encounterID, encounterDetails *eDetails);


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveTrackingInfo
		Parameters: CString encounterID, CArray<TrackingInfo, TrackingInfo>* tracInfo
		Return type: 
		Description: This function retrieves all tracking info for passed encounter ID and populates 
					 in tracInfoArray
	-----------------------------------------------------------------------------------*/
	bool RetrieveTrackingInfo(CString encounterID, CArray<TrackingInfo, TrackingInfo>* tracInfoArray);


	/*-----------------------------------------------------------------------------------
		Function Name: RetrieveOrdersInfo
		Parameters: CString encounterID, CArray<OrdersInfo, OrdersInfo>* ordInfoArray
		Return type: bool
		Description: This function retrieves the orders info for the selected encounter
	-----------------------------------------------------------------------------------*/
	bool RetrieveOrdersInfo(CString encounterID, CArray<OrdersInfo, OrdersInfo>* ordInfoArray);


	/*-----------------------------------------------------------------------------------
		Function Name: connectToDb
		Parameters: Zero parameters
		Return type: bool
		Description: This function connects to the CCL database with the predefined app ID and task ID
					 and return true for successful connection
	-----------------------------------------------------------------------------------*/
	static bool connectToDatabase();

	
	/*-----------------------------------------------------------------------------------
		Function Name: searchPatientsFromDatabase
		Parameters: CString firstName, CString lastName
		Return type: bool
		Description: This function retrives the reply from the CCL script with predefined request ID.
					 The reply contains all the details of the patients whose name(s) begin with first or
					 last name(s)
	-----------------------------------------------------------------------------------*/
	static bool searchPatientsFromDatabase(CString firstName, CString lastName);
};

