#pragma once

#include <cstdint>
#include <ios>
#include "streams.hpp"


using ReplicationClassID = uint32_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

class GameObject
{
public:
	REPLICATED('GOBJ', GameObject);
	GameObject() {};
	~GameObject() {};
	virtual void Destroy() {};
	virtual void Read(InputStream& stream) {};
	virtual void Write(OutputStream& stream) {};
	virtual void print() {};
};