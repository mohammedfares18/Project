#pragma once

//Class to store multiple person details with similar names
class PersonInfo
{
private:
	CString personID;
	CString fullName;
	CString personDOB;
	CString personAge;
	CString personGender;
public:
	PersonInfo(CString personID, CString fullName, CString personDOB, CString personAge, CString personGender);
	PersonInfo();
	~PersonInfo();
	// Retrieve Person ID
	CString getPersonID();
	// Retrieve full name
	CString getFullName();
	// Retrieve Person date of birth
	CString getPersonDOB();
	// Retrieve Person Age
	CString getPersonAge();
	// Retrieve Person Gender
	CString getPersonGender();
};


//Class to store multiple enciunter details of the selected patient
class EncounterInfo
{
private:
	CString encounterID;
	CString encounterType;
	CString encounterStatus;
public:
	EncounterInfo(CString encounterID, CString encounterType, CString encounterStatus);
	EncounterInfo();
	~EncounterInfo();
	// Retrieve Encounter ID
	CString getEncounterID();
	// Retrieve Encounter Type
	CString getEncounterType();
	// Retrieve Encounter Status
	CString getEncounterStatus();
};

//Class to store multiple tracking details of a particular encounter
class TrackingInfo
{
private:
	CString trackingID;
	CString trackingBaseLoc;
	CString trackingCheckinID;
	CString trackingGroup;
	CString checkinDate;
	CString checkoutDate;
public:
	TrackingInfo(CString trackingID, CString trackingBaseLoc, CString trackingCheckinID, CString trackingGroup, CString checkinDate, CString checkoutDate);
	TrackingInfo();
	~TrackingInfo();
	// Retrieve Tracking ID
	CString getTrackingID();
	// Retrieve base location
	CString getBaseLoc();
	// Retrieve Tracking checkin ID
	CString getTrackingCheckinID();
	// Retrieve Tracking group
	CString getTrackingGroup();
	// Retrieve Tracking Checkin Date
	CString getCheckinDate();
	// Retrieve Tracking Checkout Date
	CString getCheckoutDate();
};

//Class to store multiple orders details of a particular encounter
class OrdersInfo
{
private:
	CString orderID;
	CString orderName;
	CString orderStatus;
	CString orderCatalog;
	CString orderCatalogType;
	CString orderDate;

public:
	OrdersInfo(CString orderID, CString orderName, CString orderStatus, CString orderCatalog, CString orderCatalogType, CString orderDate);
	OrdersInfo();
	~OrdersInfo();
	//Retrieve order ID
	CString getOrderID();
	//Retrieve order name
	CString getOrderName();
	//Retrieve order status
	CString getOrderStatus();
	//Retrieve order catalog
	CString getOrderCatalog();
	//Retrieve order catalog type
	CString getOrderCatalogType();
	//Retrieve order date
	CString getOrderDate();
};

//Struct to store selected person details
struct patientDetails
{
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
};

struct encounterDetails
{
	CString m_encounterID;
	CString m_encounterType;
	CString m_encounterStatus;
	CString m_encounterReason;
	CString m_encounterRegDate;
	CString m_encounterDischDate;
	CString m_encounterFacility;
	CString m_encounterBuilding;
	CString m_encounterNurseUnit;
	CString m_encounterRoom;
	CString m_encounterBed;
};