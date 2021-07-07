#include "stdafx.h"
#include "MedCordsFunctionalities.h"
#include "MedCords.h"

MedCordsFunctionalities::MedCordsFunctionalities()
{
}


MedCordsFunctionalities::~MedCordsFunctionalities()
{
}


/*-----------------------------------------------------------------------------------
	Function Name: ValidatePersonNames
	Parameters: CString firstName, CString lastName
	Return type: bool
	Description: This function is used to validate first and last names based on their length
-----------------------------------------------------------------------------------*/
bool MedCordsFunctionalities::ValidatePersonNames(CString firstName, CString lastName)
{
	// If both the names have less than 3 characters
	if( firstName.GetLength() < 3 && lastName.GetLength() < 3)
		return false;
	return true;
}


/*-----------------------------------------------------------------------------------
	Function Name: CheckForValidCharacter
	Parameters: char character
	Return type: bool
	Description: This function is used to check whether the character is
				 alphabet/space/backspace or not
-----------------------------------------------------------------------------------*/
bool MedCordsFunctionalities::CheckForValidCharacter(char character)
{
	if (isalpha(character) || character == ' ' || character == '\b')
		return true;
	return false;
}


/*-----------------------------------------------------------------------------------
	Function Name: ConvertDateToString
	Parameters: Date* date
	Return type: CString
	Description: This function converts the date structure passed into a readable date
				 format that is MM - DD - YYYY into a string
-----------------------------------------------------------------------------------*/
CString  MedCordsFunctionalities::ConvertDateToString(Date* date)
{
	CString dateString;
	int mon = date->mon;
	int day = date->day;
	int year = date->year;
	int cen = date->cen;
	if (year > 0 && year < 10)
		dateString.Format("%d - %d - %d0%d", mon, day, cen, year);
	else
		dateString.Format("%d - %d - %d%d", mon, day, cen, year);
	if (mon < 10)
	{
		dateString.Insert(0, "0");
		if(day < 10)
			dateString.Insert(5, "0");
	}
	else 
	{
		if (day < 10)
			dateString.Insert(5, "0");
	}
	return dateString;
}


/*-----------------------------------------------------------------------------------
	Function Name: ConvertDoubleToString
	Parameters: double value
	Return type: CString
	Description: This function converts the double value passed into a string
-----------------------------------------------------------------------------------*/
CString MedCordsFunctionalities::ConvertDoubleToString(double value)
{
	CString doubleString;
	doubleString.Format("%d", (int)value);
	return doubleString;
}
