//====================================================================================================
// Filename:	CResource.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Resource/CResource.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CResource::CResource(void)
	: mResourceID(0)
	, mRefCount(1)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CResource::~CResource(void)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

Utility::Key CResource::GetResourceID(void) const
{
	return mResourceID;
}

//----------------------------------------------------------------------------------------------------

int CResource::GetRefCount(void) const
{
	return mRefCount;
}

//----------------------------------------------------------------------------------------------------

void CResource::SetResourceID(Utility::Key kID)
{
	mResourceID = kID;
}

//----------------------------------------------------------------------------------------------------

void CResource::IncrementRefCount(void)
{
	// Increment the reference count
	mRefCount++;
}

//----------------------------------------------------------------------------------------------------

void CResource::DecrementRefCount(void)
{
	// Decrement the reference count
	mRefCount--;
}