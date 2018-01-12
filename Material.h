#pragma once

#include "Standard.h"
#include "Shader.h"
#include <vector>

class UniformCell
{
public:
	Uniform* uniform;
	XFN_UploadUniform uploadFunctionPtr;
	UniformID id;
	String name;
	
	
	UniformCell();
	UniformCell (Uniform* uniform, String name);
	bool Initialize (HShader shader);
};

HCLASS(Material) : public Object
{
public:
	HShader shader;
	std::vector<UniformCell> uniformCells;
	
	// Statics
	
	UniformID staticTime;
	
	// Statics
	
	Material ();
	Material (HShader shader);
	
	void Enable ();
	void Initialize (HShader shader);
};

extern std::vector<UniformCell> uniformCellStack;

template<typename T, typename std::enable_if<std::is_base_of<Uniform, T>::value>::type* = nullptr>
UniformCell CreateCell (String name, T t)
{
	UniformCell uCell ((Uniform*)&t, name);
	uCell.uploadFunctionPtr = (XFN_UploadUniform)&T::UploadUniform;
	
	return uCell;
}

template<typename T, typename std::enable_if<std::is_base_of<Uniform, T>::value>::type* = nullptr>
T CreateUniform (String name)
{
	T t;
	
	UniformCell uCell = CreateCell(name, t);
	
	uniformCellStack.push_back (uCell);
	
	return t;
}

std::vector<UniformCell> SwapUniformCellStack ();

#define MATERIAL(m) HCLASS(m) : public Material { public: m (HShader shader) : Material(shader) { this->uniformCells = SwapUniformCellStack(); Initialize(shader); }
#define UNIFORM(type, name) type name = CreateUniform<type> (#name)
#define END_MATERIAL }

/* // Material Template


MATERIAL(MyMaterial)
	UNIFORM (Vector3, test);
END_MATERIAL;


*/