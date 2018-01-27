//
// Created by daniel on 1/20/2018.
//

#pragma once

#include "Standard.h"
_HCLASS(RenderGroupBase);
_HCLASST(template<typename T>, T, RenderGroup);

#include "AttributeBuffer.h"
#include "AttributeBatch.h"
#include "Material.h"
#include "Shapes.h"
#include "World.h"

HCLASS(RenderGroupBase) : Object
{
public:
	virtual void Render () = 0;
};

void AddRenderGroupToWorld (HRenderGroupBase renderGroup, HWorld world);

HCLASST(template<typename T>, T, RenderGroup) : public RenderGroupBase
{
private:
	std::vector<T> positionBuffer;
	HAttributeBuffer<T> positionAttributeBuffer;
	HMaterial material;
public:
	HAttributeBatch attributeBatch;
	
	/// @brief Creates a RenderGroup
	/// @param _attributeBatch			The desired attributeBatch, shouldn't contain a position buffer.
	/// @param positionAttributeID		The attribute ID for the position attribute buffer inside of the _attributeBatch.
	/// @param preAllocSize				The pre-allocated position buffer size. If you expect to have a lot of positions in this RenderGroup then add a lot.
	RenderGroup (HAttributeBatch _attributeBatch, int positionAttributeID, HMaterial _material, HWorld world, int preAllocSize = 50);
	
	int GetSize ();
	
	void Add (T position);
	void Render () override;
};

template<typename T>
RenderGroup<T>::RenderGroup (HAttributeBatch _attributeBatch, int positionAttributeID, HMaterial _material,
							 HWorld world, int preAllocSize)
{
	attributeBatch = _attributeBatch;
	positionBuffer.reserve(preAllocSize);
	material = _material;
	
	AddRenderGroupToWorld(this, world);
	
	bool containsPositionBuffer = attributeBatch->GetBufferWithAttributeID(positionAttributeID, positionAttributeBuffer.link);
	
	if (!containsPositionBuffer)
	{
		printf ("Error in RenderGroup init: attributeBatch does not contain position buffer with id %i\n", positionAttributeID);
		return;
	}
}


template<typename T>
void RenderGroup<T>::Add (T position)
{
	positionBuffer.push_back(position);
}

template<typename T>
void RenderGroup<T>::Render ()
{
	material->Enable();
	attributeBatch->Enable();
	positionAttributeBuffer->UploadR(positionBuffer);
	DrawShape(attributeBatch);
	positionBuffer.clear();
}

template<typename T>
int RenderGroup<T>::GetSize ()
{
	return positionBuffer.size();
}



