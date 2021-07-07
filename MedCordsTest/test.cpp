#pragma once
#include "pch.h"
#include "MedCords/stdafx.cpp"
#include "MedCords/Resource.h"
#include "MedCords/targetver.h"
#include "MedCords/MedCords.cpp"
#include "MedCords/DataStorage.cpp"
#include "MedCords/MedCordsDlg.cpp"
#include "MedCords/DatabaseFunctionalities.cpp"
#include "MedCords/MedCordsFunctionalities.cpp"
#include "MedCords/PatientDetailsDlg.cpp"
#include "MedCords/EncounterDialog.cpp"
#include "MedCords/TrackingDialog.cpp"
#include "MedCords/OrdersDialog.cpp"
#include "MedCords/CEditNames.cpp"

MedCordsFunctionalities med;
Date* date = new Date;
CMedCordsDlg mDlg;
CPatientDetailsDlg  pDlg;
CTrackingDialog tDlg;
COrdersDialog oDlg;
CDatabaseFunctionalities db;

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

EncounterInfo eObj("642876", "Outpatient", "Active");
TEST(DataStorageEncounter, GetEncounterID)
{
	ASSERT_EQ("642876", eObj.getEncounterID());
}

TEST(DataStorageEncounter, GetEncounterType)
{
	ASSERT_EQ("Outpatient", eObj.getEncounterType());
}

TEST(DataStorageEncounter, GetEncounterstatus)
{
	ASSERT_EQ("Active", eObj.getEncounterStatus());
}

TEST(Display, PatientsInfo1)
{
	PersonInfo obj("123457", "Mohammed", "12-01-1990", "30 years", "Male");
	mDlg.personInfoArray->Add(obj);
	ASSERT_EQ(true, mDlg.DisplayList());
}
TEST(Display, PatientsInfo2)
{
	PersonInfo obj1("123457", "Mohammed", "12-01-1990", "30 years", "Male");
	mDlg.personInfoArray->Add(obj1);
	PersonInfo obj2((mDlg.personInfoArray->GetAt(0).getPersonID()), (mDlg.personInfoArray->GetAt(0).getFullName()), (mDlg.personInfoArray->GetAt(0).getPersonDOB()), (mDlg.personInfoArray->GetAt(0).getPersonAge()), (mDlg.personInfoArray->GetAt(0).getPersonGender()));
	mDlg.personInfoArray->Add(obj2);
	ASSERT_EQ(true, mDlg.DisplayList());
}

TEST(Display, EncountersInfo1)
{
	EncounterInfo obj("764567", "Inpatient", "Active");
	pDlg.encounterInfoArray->Add(obj);
	ASSERT_EQ(true, pDlg.DisplayList());
}

TEST(Display, EncountersInfo2)
{
	EncounterInfo obj1("764567", "Inpatient", "Active");
	pDlg.encounterInfoArray->Add(obj1);
	EncounterInfo obj2((pDlg.encounterInfoArray->GetAt(0).getEncounterID()), (pDlg.encounterInfoArray->GetAt(0).getEncounterType()), (pDlg.encounterInfoArray->GetAt(0).getEncounterStatus()));
	pDlg.encounterInfoArray->Add(obj2);
	ASSERT_EQ(true, pDlg.DisplayList());
}


TEST(Display, TrackInfo1)
{
	TrackingInfo obj("764567", "location", "542356", "Emergency", "12 - 09 - 1992", "01 - 01 - 1990");
	tDlg.trackingInfoArray->Add(obj);
	ASSERT_EQ(true, tDlg.DisplayList());
}
TEST(Display, TrackInfo2)
{
	TrackingInfo obj1("764567", "location", "542356", "Emergency", "12 - 09 - 1992", "01 - 01 - 1990");
	tDlg.trackingInfoArray->Add(obj1);
	TrackingInfo obj2(tDlg.trackingInfoArray->GetAt(0).getTrackingID(), tDlg.trackingInfoArray->GetAt(0).getBaseLoc(), tDlg.trackingInfoArray->GetAt(0).getTrackingCheckinID(), tDlg.trackingInfoArray->GetAt(0).getTrackingGroup(), tDlg.trackingInfoArray->GetAt(0).getCheckinDate(), tDlg.trackingInfoArray->GetAt(0).getCheckoutDate());
	tDlg.trackingInfoArray->Add(obj2);
	ASSERT_EQ(true, tDlg.DisplayList());
}

TEST(Display, TrackInfo3)
{
	ASSERT_EQ(false, tDlg.MainDlgFunction("123456"));
}

TEST(Display, TrackInfo4)
{
	ASSERT_EQ(true, tDlg.RetrieveTrackingInfo());
}


TEST(Display, OrderInfo1)
{
	OrdersInfo obj("642567", "Antibiotic", "Ordered", "Tablets", "Pharmacy", "05 - 06 - 1991");
	oDlg.ordersInfoArray->Add(obj);
	ASSERT_EQ(true, oDlg.DisplayList());
}

TEST(Display, OrderInfo2)
{
	OrdersInfo obj1("642567", "Antibiotic", "Ordered", "Tablets", "Pharmacy", "05 - 06 - 1991");
	oDlg.ordersInfoArray->Add(obj1);
	OrdersInfo obj2(oDlg.ordersInfoArray->GetAt(0).getOrderID(), oDlg.ordersInfoArray->GetAt(0).getOrderName(), oDlg.ordersInfoArray->GetAt(0).getOrderStatus(), oDlg.ordersInfoArray->GetAt(0).getOrderCatalog(), oDlg.ordersInfoArray->GetAt(0).getOrderCatalogType(), oDlg.ordersInfoArray->GetAt(0).getOrderDate());
	oDlg.ordersInfoArray->Add(obj2);
	ASSERT_EQ(true, oDlg.DisplayList());
}

TEST(Display, OrderInfo3)
{
	ASSERT_EQ(false, oDlg.MainDlgFunction("123456"));
}

TEST(Display, OrderInfo4)
{
	ASSERT_EQ(true, oDlg.RetrieveOrdersInfo());
}


TEST(CheckForValidCharacter, AlphabetLowerCase)
{
	ASSERT_EQ(true, med.CheckForValidCharacter('a'));
}

TEST(CheckForValidCharacter, AlphabetUpperCase)
{
	ASSERT_EQ(true, med.CheckForValidCharacter('Z'));
}

TEST(CheckForValidCharacter, BlankSpace)
{
	ASSERT_EQ(true, med.CheckForValidCharacter(' '));
}

TEST(CheckForValidCharacter, Digit)
{
	ASSERT_EQ(false, med.CheckForValidCharacter('1'));
}

TEST(CheckForValidCharacter, SpecialCharacter)
{
	ASSERT_EQ(false, med.CheckForValidCharacter('@'));
}

TEST(CheckForValidCharacter, BackSpace)
{
	ASSERT_EQ(true, med.CheckForValidCharacter('\b'));
}

TEST(ValidatePersonNames, BothNamesWithLessThanThreeCharacters)
{
	ASSERT_EQ(false, med.ValidatePersonNames("ab", "cd"));
}

TEST(ValidatePersonNames, FirstNameWithThreeOrMoreCharacters)
{
	ASSERT_EQ(true, med.ValidatePersonNames("abc", "cd"));
}

TEST(ValidatePersonNames, LastNameWithThreeOrMoreCharacters)
{
	ASSERT_EQ(true, med.ValidatePersonNames("ab", "cde"));
}

TEST(ValidatePersonNames, BothNamesWithThreeOrMoreCharacters)
{
	ASSERT_EQ(true, med.ValidatePersonNames("abc", "def"));
}

TEST(ConvertDoubleToString, PositiveNumber)
{
	ASSERT_EQ("1234567", med.ConvertDoubleToString(1234567));
}

TEST(ConvertDoubleToString, NegativeNumber)
{
	ASSERT_EQ("-1234567", med.ConvertDoubleToString(-1234567));
}

TEST(ConvertDoubleToString, Zero)
{
	ASSERT_EQ("0", med.ConvertDoubleToString(0));
}

TEST(ConvertDateToString, YearGreaterThan10)
{
	date = new Date;
	date->cen = (uchar)20;
	date->year = (uchar)21;
	date->mon = (uchar)11;
	date->day = (uchar)23;
	ASSERT_EQ(_T("11 - 23 - 2021"), med.ConvertDateToString(date));
}

TEST(ConvertDateToString, YearLessThan10)
{
	date = new Date;
	date->cen = (uchar)19;
	date->year = (uchar)3;
	date->mon = (uchar)12;
	date->day = (uchar)30;
	ASSERT_EQ(_T("12 - 30 - 1903"), med.ConvertDateToString(date));
}

TEST(ConvertDateToString, DayLessThan10)
{
	date = new Date;
	date->cen = (uchar)19;
	date->year = (uchar)03;
	date->mon = (uchar)11;
	date->day = (uchar)2;
	ASSERT_EQ(_T("11 - 02 - 1903"), med.ConvertDateToString(date));
}

TEST(ConvertDateToString, MonthLessThan10)
{
	date = new Date;
	date->cen = (uchar)19;
	date->year = (uchar)03;
	date->mon = (uchar)5;
	date->day = (uchar)16;
	ASSERT_EQ(_T("05 - 16 - 1903"), med.ConvertDateToString(date));
}

TEST(ConvertDateToString, DayAndMonthLessThan10)
{
	date = new Date;
	date->cen = (uchar)19;
	date->year = (uchar)03;
	date->mon = (uchar)7;
	date->day = (uchar)3;
	ASSERT_EQ(_T("07 - 03 - 1903"), med.ConvertDateToString(date));
}


