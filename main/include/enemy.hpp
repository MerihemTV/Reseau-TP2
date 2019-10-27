#pragma once
#include "game_object.hpp"
#include <iostream>

class Enemy : public GameObject
{
public:
	REPLICATED('ENEM', Enemy);

	// Constructors & Destructor
	Enemy() {};
	Enemy(float posX, float posY, float posZ, std::string type, float rotX, float rotY, float rotZ, float rotW)
		: m_posX(posX)
		, m_posY(posY)
		, m_posZ(posZ)
		, m_type(type)
		, m_rotX(rotX)
		, m_rotY(rotY)
		, m_rotZ(rotZ)
		, m_rotW(rotW)
	{
		std::cout << "Enemy created" << std::endl;
	}
	~Enemy() { std::cout << "Enemy destroyed #constructor" << std::endl; };

	virtual void Destroy();							// Called before destructor
	virtual void Read(InputStream& stream);			// Deserialize data from InputStream
	virtual void Write(OutputStream& stream);		// Serialize data to Outputstream
	virtual void print();							// Print Enemy datas in console
	
	// Getters
	float getPosX() { return m_posX; }
	float getPosY() { return m_posY; }
	float getPosZ() { return m_posZ; }
	std::string getType() { return m_type; }
	float getRotX() { return m_rotX; }
	float getRotY() { return m_rotY; }
	float getRotZ() { return m_rotZ; }
	float getRotW() { return m_rotW; }
	
	// Setters
	void setPosX(float posX) { m_posX = posX; }
	void setPosY(float posY) { m_posY = posY; }
	void setPosZ(float posZ) { m_posZ = posZ; }
	void setType(std::string type) { m_type = type; }
	void setRotX(float rotX) { m_rotX = rotX; }
	void setRotY(float rotY) { m_rotY = rotY; }
	void setRotZ(float rotZ) { m_rotZ = rotZ; }
	void setRotW(float rotW) { m_rotW = rotW; }

private:
	float m_posX;			// X value position
	float m_posY;			// Y value position
	float m_posZ;			// Z value position

	std::string m_type;		// Enemy type

	float m_rotX;			// X value rotation
	float m_rotY;			// Y value rotation
	float m_rotZ;			// Z value rotation
	float m_rotW;			// W value rotation
};