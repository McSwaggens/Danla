#pragma once

#include "Standard.h"
_HCLASS(Material);

#include "Shader.h"
#include "Texture.h"
#include "TextureUnit.h"
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
	virtual void Upload ();
};

class UniformTextureCell : public UniformCell
{
public:
	HTexture* texture;
	TextureUnit textureUnit;
	
	
	UniformTextureCell (HTexture* texture, String name, TextureUnit textureUnit);
	
	void Upload () override;
};

HCLASS(Material) : public Object
{
public:
	HShader shader;
	std::vector<UniformCell*> uniformCells;
	
	// Statics
	
	UniformID staticTime;
	UniformID staticPVMatrix;
	
	// Statics
	
	Material ();
	
	void Enable ();
	void Initialize (HShader shader);
	
	~Material() override;
};

extern std::vector<UniformCell*> uniformCellStack;

template<typename T, typename std::enable_if<std::is_base_of<Uniform, T>::value>::type* = nullptr>
UniformCell* CreateCell (String name, T& t)
{
	UniformCell* uCell = new UniformCell ((Uniform*)&t, name);
	uCell->uploadFunctionPtr = (XFN_UploadUniform)&T::UploadUniform;
	
	return uCell;
}

template<typename T, typename std::enable_if<std::is_base_of<Uniform, T>::value>::type* = nullptr>
T CreateUniform (String name, T& txx)
{
	T t;
	
	UniformCell* uCell = CreateCell(name, txx);
	
	uniformCellStack.push_back (uCell);
	
	return t;
}


HTexture CreateUniformTexture (String name, TextureUnit textureUnit);





std::vector<UniformCell*> SwapUniformCellStack ();

#define MATERIALO(m, parent) HCLASS(m) : public parent { public: inline m () {} inline explicit m (HShader shader) { this->uniformCells = SwapUniformCellStack(); Initialize(shader); }
#define MATERIAL(m) MATERIALO(m, Material)
#define UNIFORM(type, name) type name = CreateUniform<type> (#name, name)
#define TEXTURE(name, texUnit) HTexture name = CreateUniformTexture (#name, TextureUnit(texUnit))
#define END_MATERIAL }

/* // Material Template


MATERIAL(MyMaterial)
	UNIFORM (Vector3, test);
END_MATERIAL;


*/