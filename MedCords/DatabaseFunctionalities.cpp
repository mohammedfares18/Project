#include "stdafx.h"
#include "DatabaseFunctionalities.h"

#include "stdlib.h"
#include "srvimpl.h"
#include "crm.h"
#include <fntcdataimport.h>

CDatabaseFunctionalities::CDatabaseFunctionalities()
{
}


CDatabaseFunctionalities::~CDatabaseFunctionalities()
{
}

CrmHandle CDatabaseFunctionalities::AppHnd = NULL;
CrmHandle CDatabaseFunctionalities::TaskHnd = NULL;
CrmHandle CDatabaseFunctionalities::ReqHnd = NULL;
CrmHandle CDatabaseFunctionalities::hReply = NULL;


/*-----------------------------------------------------------------------------------
	Function Name: connectToDb
	Parameters: Zero parameters
	Return type: bool
	Description: This function connects to the CCL database with the predefined app ID and task ID
				 and return true for successful connection
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::connectToDatabase()
{
	CString m_username;
	CString m_password;
	CString m_domain;

	SecStatus stat;
	SecContextHandle hSecContext;

	m_username.LoadString(IDS_USERNAME);
	m_password.LoadString(IDS_PASSWORD);
	m_domain.LoadString(IDS_DOMAIN);

	stat = SecAuthSession(&hSecContext, m_username, m_domain, m_password);
	stat = SecSetContext(hSecContext);

	CrmStatus CStat;
	CString appStr;
	appStr.LoadString(ID_APP_ID);
	SrvId appID = _ttoi(appStr);
	CStat = CrmBeginApp(appID, &AppHnd);
	if (CStat != eCrmOk) 
	{
		CString message;
		message.LoadString(IDS_STRING_START_APP);
		AfxMessageBox(message);
		return false;
	}

	CString taskStr;
	taskStr.LoadString(ID_TASK_ID);
	SrvId taskID = _ttoi(taskStr);
	CStat = CrmBeginTask(AppHnd, taskID, &TaskHnd);

	if (CStat != eCrmOk) 
	{
		CString message;
		message.LoadString(IDS_STRING_START_TASK);
		AfxMessageBox(message);
		return false;
	}
	return true;
}


/*-----------------------------------------------------------------------------------
	Function Name: searchPatientsFromDatabase
	Parameters: CString firstName, CString lastName
	Return type: bool
	Description: This function retrives the reply from the CCL script with predefined request ID.
				 The reply contains all the details of the patients whose name(s) begin with first or
				 last name(s)
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::searchPatientsFromDatabase(CString firstName, CString lastName)
{
	CrmStatus CStat;
	CrmHandle hStep;

	CString reqStr;
	reqStr.LoadString(ID_REQUEST_ID);
	SrvId reqID = _ttoi(reqStr);
	CStat = CrmBeginReq(TaskHnd, "", reqID, &hStep);

	if (CStat == eCrmOk)
	{
		SrvHandle hRequest, hItem;
		hRequest = CrmGetRequest(hStep);
		CString reqList, field1, field2;
		reqList.LoadString(IDS_STRING_REQ_QUAL);
		field1.LoadString(IDS_STRING_REQ_FN);
		field2.LoadString(IDS_STRING_REQ_LN);
		hItem = SrvAddItem(hRequest, reqList);
		SrvSetString(hItem, field1, firstName);
		SrvSetString(hItem, field2, lastName);
	}
	else
	{
		return false;
	}

	CStat = CrmPerform(hStep);
	if (CStat == eCrmOk)
	{
		hReply = CrmGetReply(hStep);
		CString statusData, st;
		statusData.LoadString(IDS_STRING_STATUS_DATA);
		st.LoadString(IDS_STRING_STATUS);
		SrvHandle hStatus = SrvGetStruct(hReply, statusData);
		CString status = SrvGetStringPtr(hStatus, st);
		return status;
	}
	else
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------------
	Function Name: RetrieveSimilarPersonsInfo
	Parameters: CArray<PersonInfo, PersonInfo>* personInfoArray
	Return type: bool
	Description: This function retrieves person'd id,name,gender,age and date of birth
				 and puts these details in pInfoArray
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrieveSimilarPersonsInfo(CArray<PersonInfo, PersonInfo>* pInfoArray)
{
	//To empty the personInfoArray
	personInfoArray.RemoveAll();

	CString personID, personFullName, personDOB, personGender, personAge;
	double d_pid;
	Date *p_dob =new Date;
	srv_size_t iCurInfo;
	CString previousID = _T("");
	int personCount = 0;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_pid = SrvGetDouble(hItem, _T("p_id"));
			personID = med.ConvertDoubleToString(d_pid);
			if (previousID == personID)
				continue;
			personCount++;
			previousID = personID;
			personFullName = SrvGetStringPtr(hItem, _T("p_full"));
			SrvGetDate(hItem, _T("p_dob"), p_dob);
			personDOB = med.ConvertDateToString(p_dob);
			personAge = SrvGetStringPtr(hItem, _T("p_age"));
			personGender = SrvGetStringPtr(hItem, _T("p_sex"));

			PersonInfo obj(personID, personFullName,personDOB, personAge, personGender);
			personInfoArray.Add(obj);
			
		}
	}

	numberOfPeople = personCount;


	for (int iPerson = 0; iPerson < numberOfPeople; iPerson++)
	{
		PersonInfo obj((personInfoArray.GetAt(iPerson).getPersonID()), (personInfoArray.GetAt(iPerson).getFullName()), (personInfoArray.GetAt(iPerson).getPersonDOB()), (personInfoArray.GetAt(iPerson).getPersonAge()), (personInfoArray.GetAt(iPerson).getPersonGender()));
		pInfoArray->Add(obj);
	}
	
	if (numberOfPeople > 0)
		return true;
	return false;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrievePatientDetails
	Parameters: CString pID, patientDetails *pDetails
	Return type: bool
	Description: This function retrieves selected patient details with ID as pID and
				 populates in pDetails structure
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrievePatientDetails(CString pID, patientDetails *pDetails)
{
	//Code to retrieve person details from database
	bool flag = true;

	CString personID, personDOB;
	Date *p_dob = new Date;
	double d_pid;
	srv_size_t iCurInfo;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_pid = SrvGetDouble(hItem, _T("p_id"));
			personID = med.ConvertDoubleToString(d_pid);
			if (pID == personID)
			{
				this->pDetails.m_personID = personID;
				this->pDetails.m_firstName = SrvGetStringPtr(hItem, _T("p_first"));
				this->pDetails.m_lastName = SrvGetStringPtr(hItem, _T("p_last"));
				this->pDetails.m_fullName = SrvGetStringPtr(hItem, _T("p_full"));
				SrvGetDate(hItem, _T("p_dob"), p_dob);
				this->pDetails.m_dateOfBirth = med.ConvertDateToString(p_dob);
				this->pDetails.m_age = SrvGetStringPtr(hItem, _T("p_age"));
				this->pDetails.m_gender = SrvGetStringPtr(hItem, _T("p_sex"));
				this->pDetails.m_streetAddr = SrvGetStringPtr(hItem, _T("str_add"));
				this->pDetails.m_city = SrvGetStringPtr(hItem, _T("city"));
				this->pDetails.m_state = SrvGetStringPtr(hItem, _T("state"));
				this->pDetails.m_country = SrvGetStringPtr(hItem, _T("country"));
				this->pDetails.m_zipCode = SrvGetStringPtr(hItem, _T("zip_code"));
				break;
			}
		}
	}


	//Put the details in Patient Details structure pointer(p)
	pDetails->m_fullName = this->pDetails.m_fullName;
	pDetails->m_firstName = this->pDetails.m_firstName;
	pDetails->m_lastName = this->pDetails.m_lastName;
	pDetails->m_dateOfBirth = this->pDetails.m_dateOfBirth;
	pDetails->m_age = this->pDetails.m_age;
	pDetails->m_gender = this->pDetails.m_gender;
	pDetails->m_personID = this->pDetails.m_personID;
	pDetails->m_streetAddr = this->pDetails.m_streetAddr;
	pDetails->m_city = this->pDetails.m_city;
	pDetails->m_country = this->pDetails.m_country;
	pDetails->m_state = this->pDetails.m_state;
	pDetails->m_zipCode = this->pDetails.m_zipCode;
	
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveEncountersInfo
	Parameters: CString pID, CArray<EncounterInfo, EncounterInfo>* encInfoArray
	Return type: bool
	Description: This function retrieves all encounters for passed person ID
				 and populates in encInfoArray
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrieveEncountersInfo(CString pID, CArray<EncounterInfo, EncounterInfo>* eInfoArray)
{
	//To empty the encounter info array
	encounterInfoArray.RemoveAll();

	CString personID, enc_ID, enc_Status, enc_Type;
	double d_pid,d_eid;
	CString previousID = _T("");
	srv_size_t iCurInfo;
	int encCount = 0;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_pid = SrvGetDouble(hItem, _T("p_id"));
			personID = med.ConvertDoubleToString(d_pid);
			if (pID == personID)
			{
				d_eid= SrvGetDouble(hItem, _T("enc_id"));
				if (d_eid == 0)
					break;
				enc_ID = med.ConvertDoubleToString(d_eid);
				if (enc_ID == previousID)
					continue;
				previousID = enc_ID;
				enc_Type = SrvGetStringPtr(hItem, _T("enc_type"));
				enc_Status = SrvGetStringPtr(hItem, _T("enc_status"));
				
				EncounterInfo obj(enc_ID, enc_Type, enc_Status);
				encounterInfoArray.Add(obj);
				encCount++;
			}
		}
	}

	numberOfEncounters = encCount;
	for (int iEncounter = 0; iEncounter < numberOfEncounters; iEncounter++)
	{
		EncounterInfo obj((encounterInfoArray.GetAt(iEncounter).getEncounterID()), (encounterInfoArray.GetAt(iEncounter).getEncounterType()), (encounterInfoArray.GetAt(iEncounter).getEncounterStatus()));
		eInfoArray->Add(obj);
	}
	
	return true;
}


/*-----------------------------------------------------------------------------------
	Function Name:  RetrieveEncounterDetails
	Parameters: CString encounterID, encounterDetails *eDetails
	Return type: bool
	Description: This function retrieves selected encounter details with ID as encounterID
				 and populates in eDetails structure
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrieveEncounterDetails(CString encounterID, encounterDetails *eDetails)
{
	bool flag = true;
	
	CString encID;
	Date *date = new Date;
	double d_eid;
	srv_size_t iCurInfo;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_eid = SrvGetDouble(hItem, _T("enc_id"));
			encID = med.ConvertDoubleToString(d_eid);
			if (encID == encounterID)
			{
				this->eDetails.m_encounterID = encounterID;
				this->eDetails.m_encounterType = SrvGetStringPtr(hItem, _T("enc_type"));
				this->eDetails.m_encounterStatus = SrvGetStringPtr(hItem, _T("enc_status"));
				this->eDetails.m_encounterReason = SrvGetStringPtr(hItem, _T("enc_reason"));
				SrvGetDate(hItem, _T("enc_reg_dt"), date);
				this->eDetails.m_encounterRegDate = med.ConvertDateToString(date);
				SrvGetDate(hItem, _T("enc_disch_dt"), date);
				this->eDetails .m_encounterDischDate = med.ConvertDateToString(date);
				this->eDetails.m_encounterFacility = SrvGetStringPtr(hItem, _T("enc_facility"));
				this->eDetails.m_encounterBuilding = SrvGetStringPtr(hItem, _T("enc_building"));
				this->eDetails.m_encounterNurseUnit = SrvGetStringPtr(hItem, _T("enc_nurse_unit"));
				this->eDetails.m_encounterRoom = SrvGetStringPtr(hItem, _T("enc_room"));
				this->eDetails.m_encounterBed = SrvGetStringPtr(hItem, _T("enc_bed"));
				break;
			}
		}
	}

	eDetails->m_encounterID = this->eDetails.m_encounterID;
	eDetails->m_encounterType = this->eDetails.m_encounterType;
	eDetails->m_encounterStatus = this->eDetails.m_encounterStatus;
	eDetails->m_encounterReason = this->eDetails.m_encounterReason;
	eDetails->m_encounterRegDate = this->eDetails.m_encounterRegDate;
	eDetails->m_encounterDischDate = this->eDetails.m_encounterDischDate;
	eDetails->m_encounterFacility = this->eDetails.m_encounterFacility;
	eDetails->m_encounterBuilding = this->eDetails.m_encounterBuilding;
	eDetails->m_encounterNurseUnit = this->eDetails.m_encounterNurseUnit;
	eDetails->m_encounterRoom = this->eDetails.m_encounterRoom;
	eDetails->m_encounterBed = this->eDetails.m_encounterBed;	
	
	return flag;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveTrackingInfo
	Parameters: CString encounterID, CArray<TrackingInfo, TrackingInfo>* tracInfo
	Return type:
	Description: This function retrieves all tracking info for passed encounter ID and populates
				 in tracInfoArray
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrieveTrackingInfo(CString encounterID, CArray<TrackingInfo, TrackingInfo>* tInfoArray)
{
	//To empty the encounter info array
	trackingInfoArray.RemoveAll();

	CString enc_ID, tracID, tracBaseLoc, tracCheckinID, tracGroup, checkinDate, checkoutDate;
	double d_eid, d_tid, d_tcid;
	Date *date = new Date;
	srv_size_t iCurInfo, iTracInfo;
	int tracCount = 0;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_eid = SrvGetDouble(hItem, _T("enc_id"));
			enc_ID = med.ConvertDoubleToString(d_eid);
			if (enc_ID == encounterID)
			{
				for (iTracInfo = 0; iTracInfo < SrvGetItemCount(hItem, _T("tracking_data")); iTracInfo++)
				{
					SrvHandle hItem2 = SrvGetItem(hItem, _T("tracking_data"), iTracInfo);
					if (NULL == hItem2)
						continue;
					d_tid = SrvGetDouble(hItem2, _T("trac_id"));
					tracID = med.ConvertDoubleToString(d_tid);
					tracBaseLoc = SrvGetStringPtr(hItem2, _T("trac_base_loc"));
					d_tcid = SrvGetDouble(hItem2, _T("trac_checkin_id"));
					tracCheckinID = med.ConvertDoubleToString(d_tcid);
					tracGroup = SrvGetStringPtr(hItem2, _T("trac_group"));
					SrvGetDate(hItem2, _T("trac_checkin_dt"), date);
					checkinDate = med.ConvertDateToString(date);
					SrvGetDate(hItem2, _T("trac_checkout_dt"), date);
					checkoutDate = med.ConvertDateToString(date);

					CString emptyDate;
					emptyDate.LoadString(IDS_STRING_EMPTY_DATE);
					if (checkinDate == emptyDate)
					{
						checkinDate.LoadString(IDS_STRING_NOT_CI);
						checkoutDate.LoadString(IDS_STRING_NOT_CO);
					}
					else if (checkoutDate == emptyDate)
					{
						checkoutDate.LoadString(IDS_STRING_NOT_CO);
					}
					TrackingInfo obj(tracID, tracBaseLoc, tracCheckinID, tracGroup, checkinDate, checkoutDate);
					trackingInfoArray.Add(obj);
					tracCount++;
				}
				break;
			}
		}
	}
	
	numberOftrackingInfo = tracCount;
	for (int iTracking = 0; iTracking < numberOftrackingInfo; iTracking++)
	{
		TrackingInfo obj(trackingInfoArray.GetAt(iTracking).getTrackingID(), trackingInfoArray.GetAt(iTracking).getBaseLoc(), trackingInfoArray.GetAt(iTracking).getTrackingCheckinID(), trackingInfoArray.GetAt(iTracking).getTrackingGroup(), trackingInfoArray.GetAt(iTracking).getCheckinDate(), trackingInfoArray.GetAt(iTracking).getCheckoutDate());
		tInfoArray->Add(obj);
	}

	return true;
}


/*-----------------------------------------------------------------------------------
	Function Name: RetrieveOrdersInfo
	Parameters: CString encounterID, CArray<OrdersInfo, OrdersInfo>* ordInfoArray
	Return type: bool
	Description: This function retrieves the orders info for the selected encounter
-----------------------------------------------------------------------------------*/
bool CDatabaseFunctionalities::RetrieveOrdersInfo(CString encounterID, CArray<OrdersInfo, OrdersInfo>* oInfoArray)
{
	//To empty the encounter info array
	ordersInfoArray.RemoveAll();

	CString enc_ID, ordID, ordName, ordStatus, ordCatalog, ordCatalogType, ordDate;
	double d_eid, d_oid;
	Date *date = new Date;
	srv_size_t iCurInfo, iOrdInfo;
	int ordCount = 0;
	if (NULL != hReply)
	{
		for (iCurInfo = 0; iCurInfo < SrvGetItemCount(hReply, _T("patient_data")); iCurInfo++)
		{
			SrvHandle hItem = SrvGetItem(hReply, _T("patient_data"), iCurInfo);
			if (NULL == hItem)
				continue;
			d_eid = SrvGetDouble(hItem, _T("enc_id"));
			enc_ID = med.ConvertDoubleToString(d_eid);
			if (enc_ID == encounterID)
			{
				for (iOrdInfo = 0; iOrdInfo < SrvGetItemCount(hItem, _T("orders_data")); iOrdInfo++)
				{
					SrvHandle hItem2 = SrvGetItem(hItem, _T("orders_data"), iOrdInfo);
					if (NULL == hItem2)
						continue;
					d_oid = SrvGetDouble(hItem2, _T("ord_id"));
					ordID = med.ConvertDoubleToString(d_oid);
					ordName = SrvGetStringPtr(hItem2, _T("ord_name"));
					ordStatus = SrvGetStringPtr(hItem2, _T("ord_status"));
					ordCatalog = SrvGetStringPtr(hItem2, _T("ord_catalog"));
					ordCatalogType = SrvGetStringPtr(hItem2, _T("ord_catalog_type"));
					SrvGetDate(hItem2, _T("ord_date"), date);
					ordDate = med.ConvertDateToString(date);

					OrdersInfo obj(ordID, ordName, ordStatus, ordCatalog, ordCatalogType, ordDate);
					ordersInfoArray.Add(obj);
					ordCount++;
				}
				break;
			}
		}
	}

	numberOfOrders = ordCount;
	for (int iOrders = 0; iOrders < numberOfOrders; iOrders++)
	{
		OrdersInfo obj(ordersInfoArray.GetAt(iOrders).getOrderID(), ordersInfoArray.GetAt(iOrders).getOrderName(), ordersInfoArray.GetAt(iOrders).getOrderStatus(), ordersInfoArray.GetAt(iOrders).getOrderCatalog(), ordersInfoArray.GetAt(iOrders).getOrderCatalogType(), ordersInfoArray.GetAt(iOrders).getOrderDate());
		oInfoArray->Add(obj);
	}

	return true;
}
