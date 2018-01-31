#include "stdafx.h"
#include "contactData.h"


contactData::contactData(Vector3D location, Vector3D normal, Material material, contactType contact): location(location), normal(normal), material(material), contact(contact)
{
}


contactData::contactData() : location(), normal(), material(), contact(NO_CONTACT)
{
}


contactData::~contactData()
{
}


Vector3D contactData::getNormal()const { return normal; }
Vector3D contactData::getLocation()const { return location; }
Material contactData::getMaterial()const { return material; }
contactType contactData::getContactType()const { return contact; }

