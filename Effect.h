//
// Created by daniel on 1/11/2018.
//

#pragma once

#include "Danla.h"
#include "Material.h"

HCLASS(EffectBase) : public Object
{
public:
	String name = "Unknown effect";
	int iterations = 1;
	virtual void Use () = 0;
	virtual HMaterial GetMaterial () = 0;
};

#define HTEMPLATE template<typename T, typename std::enable_if<std::is_base_of<Material, T>::value>::type* = nullptr>
HCLASSTU(T, Effect) : public EffectBase
{
public:
	
	Handle<T> material;
	
	
	Effect (Handle<T> material, String name, int iterations = 1);
	
	void Use () override;
	HMaterial GetMaterial () override;
};


template<typename T>
Effect<T>::Effect (Handle<T> material, String name, int iterations)
{
	this->material = material;
	this->iterations = iterations;
	this->name = name;
}

template<typename T>
void Effect<T>::Use ()
{
	material->Enable ();
}

template<typename T>
HMaterial Effect<T>::GetMaterial ()
{
	return material.template CastTo<Material>();
}
