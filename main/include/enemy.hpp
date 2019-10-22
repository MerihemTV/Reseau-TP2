#pragma once
#include "game_object.hpp"

class Enemy : public GameObject
{
public:
	REPLICATED('ENEM', Enemy);
	Enemy();
	Enemy(float x, float y, float z, std::string name, float rotx, float roty, float rotz, float rotw);
	virtual void Read(InputStream& stream)
	{
		m_posX = stream.Read<float>();
		m_posY = stream.Read<float>();
		m_posZ = stream.Read<float>();
		m_type = stream.ReadStr();
		m_rotX = stream.Read<float>();
		m_rotY = stream.Read<float>();
		m_rotZ = stream.Read<float>();
		m_rotW = stream.Read<float>();
	}
	virtual void Write(OutputStream& stream)
	{
	//	posX = static_cast<int>(m_posX * 1000) + 500;	// 10 bits
	//	posY = static_cast<int>(m_posY * 1000) + 500;	// 10 bits
	//	posZ = static_cast<int>(m_posZ * 1000) + 500;	// 10 bits








		stream.Write(m_posX);
		stream.Write(m_posY);
		stream.Write(m_posZ);
		stream.WriteStr(m_type);
		stream.Write(m_rotX);
		stream.Write(m_rotY);
		stream.Write(m_rotZ);
		stream.Write(m_rotW);
	}

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