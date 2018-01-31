#pragma once
#include"Vector3D.h"
#include "Material.h"

enum contactType { NO_CONTACT, GOOD_CONTACT, SELF_INTERSECT };

class contactData
{
public:
	contactData(Vector3D location, Vector3D normal, Material material, contactType contact);
	contactData();
	~contactData();

	Vector3D getNormal()const;
	Vector3D getLocation()const;
	Material getMaterial()const;
	contactType getContactType()const;

private:
	Vector3D location, normal;
	Material material;
	contactType contact;
};
