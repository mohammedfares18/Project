#pragma once

#include "datestruct.h"

class MedCordsFunctionalities
{
public:
	MedCordsFunctionalities();
	~MedCordsFunctionalities();
	

	/*-----------------------------------------------------------------------------------
		Function Name: ValidatePersonNames
		Parameters: CString firstName, CString lastName
		Return type: bool
		Description: This function is used to validate first and last names based on their length
	-----------------------------------------------------------------------------------*/
	bool ValidatePersonNames(CString firstName, CString lastName);
	

	/*-----------------------------------------------------------------------------------
		Function Name: CheckForValidCharacter
		Parameters: char character
		Return type: bool
		Description: This function is used to check whether the character is 
					 alphabet/space/backspace or not
	-----------------------------------------------------------------------------------*/
	bool CheckForValidCharacter(char character);


	/*-----------------------------------------------------------------------------------
		Function Name: ConvertDateToString
		Parameters: Date* date
		Return type: CString
		Description: This function converts the date structure passed into a readable date
					 format that is MM - DD - YYYY into a string
	-----------------------------------------------------------------------------------*/
	CString ConvertDateToString(Date* date);

	
	/*-----------------------------------------------------------------------------------
		Function Name: ConvertDoubleToString
		Parameters: double value
		Return type: CString
		Description: This function converts the double value passed into a string
	-----------------------------------------------------------------------------------*/
	CString ConvertDoubleToString(double value);
};