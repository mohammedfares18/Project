#include "stdafx.h"
#include "DataStorage.h"

//Initializes all values
PersonInfo::PersonInfo(CString personID, CString fullName, CString personDOB, CString personAge, CString personGender)
{
	this->personID = personID;
	this->fullName = fullName;
	this->personDOB = personDOB;
	this->personAge = personAge;
	this->personGender = personGender;
}

PersonInfo::PersonInfo()
{
}

PersonInfo::~PersonInfo()
{
}

// Retrieve PersonID
CString PersonInfo::getPersonID()
{
	return personID;
}


// Retrieve full name
CString PersonInfo::getFullName()
{
	return fullName;
}


// Retrieve Person date of birth
CString PersonInfo::getPersonDOB()
{
	return personDOB;
}

// Retrieve Person Age
CString PersonInfo::getPersonAge()
{
	return personAge;
}

// Retrieve Person Gender
CString PersonInfo::getPersonGender()
{
	return personGender;
}


//Initializes all values
EncounterInfo::EncounterInfo(CString encounterID, CString encounterType, CString encounterStatus)
{
	this->encounterID = encounterID;
	this->encounterType = encounterType;
	this->encounterStatus = encounterStatus;
}

EncounterInfo::EncounterInfo()
{
}

EncounterInfo::~EncounterInfo()
{
}

// Retrieve Encounter ID
CString EncounterInfo::getEncounterID()
{
	return encounterID;
}


// Retrieve Encounter type
CString EncounterInfo::getEncounterType()
{
	return encounterType;
}


// Retrieve Encounter status
CString EncounterInfo::getEncounterStatus()
{
	return encounterStatus;
}


TrackingInfo::TrackingInfo(CString trackingID, CString trackingBaseLoc, CString trackingCheckinID, CString trackingGroup, CString checkinDate, CString checkoutDate)
{
	this->trackingID = trackingID;
	this->trackingBaseLoc = trackingBaseLoc;
	this->trackingCheckinID = trackingCheckinID;
	this->trackingGroup = trackingGroup;
	this->checkinDate = checkinDate;
	this->checkoutDate = checkoutDate;
}

TrackingInfo::TrackingInfo()
{
}

TrackingInfo::~TrackingInfo()
{
}

// Retrieve Tracking ID
CString TrackingInfo::getTrackingID()
{
	return trackingID;
}

// Retrieve base location
CString TrackingInfo::getBaseLoc()
{
	return trackingBaseLoc;
}

// Retrieve Tracking group
CString TrackingInfo::getTrackingGroup()
{
	return trackingGroup;
}

// Retrieve Tracking checkin ID
CString TrackingInfo::getTrackingCheckinID()
{
	return trackingCheckinID;
}

// Retrieve Tracking Checkin Date
CString TrackingInfo::getCheckinDate()
{
	return checkinDate;
}

// Retrieve Tracking Checkout Date
CString TrackingInfo::getCheckoutDate()
{
	return checkoutDate;
}


OrdersInfo::OrdersInfo(CString orderID, CString orderName, CString orderStatus, CString orderCatalog, CString orderCatalogType, CString orderDate)
{
	this->orderID = orderID;
	this->orderName = orderName;
	this->orderStatus = orderStatus;
	this->orderCatalog = orderCatalog;
	this->orderCatalogType = orderCatalogType;
	this->orderDate = orderDate;
}

OrdersInfo::OrdersInfo()
{
}

OrdersInfo::~OrdersInfo()
{
}

//Retrieve order ID
CString OrdersInfo::getOrderID()
{
	return orderID;
}

//Retrieve order name
CString OrdersInfo::getOrderName()
{
	return orderName;
}

//Retrieve order status
CString OrdersInfo::getOrderStatus()
{
	return orderStatus;
}

//Retrieve order catalog
CString OrdersInfo::getOrderCatalog()
{
	return orderCatalog;
}

//Retrieve order catalog type
CString OrdersInfo::getOrderCatalogType()
{
	return orderCatalogType;
}

//Retrieve order date
CString OrdersInfo::getOrderDate()
{
	return orderDate;
}
