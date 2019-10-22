#pragma once
#include "game_object.hpp"

class Enemy : public GameObject
{
public:
	REPLICATED('ENEM', Enemy);

	virtual void Destroy();
	virtual void Read(InputStream& stream);
	virtual void Write(OutputStream& stream);

private:
	float m_posX;
	float m_posY;
	float m_posZ;

	std::string m_type;

	float m_rotX;
	float m_rotY;
	float m_rotZ;
	float m_rotW;
};