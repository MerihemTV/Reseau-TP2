#pragma once
#include "game_object.hpp"
#include <iostream>

class Player : public GameObject
{
public:
	REPLICATED('PLAY', Player);

	// Constructors & Destructor
	Player() {};
	Player(float posX, float posY, float posZ, std::string name, float rotX, float rotY, float rotZ, float rotW)
		: m_posX(posX)
		, m_posY(posY)
		, m_posZ(posZ)
		, m_name(name)
		, m_rotX(rotX)
		, m_rotY(rotY)
		, m_rotZ(rotZ)
		, m_rotW(rotW)
	{
		std::cout << "Player created" << std::endl;
	}
	~Player() { std::cout << "Player destroyed #constructor" << std::endl; };

	virtual void Destroy();							// Called before destructor
	virtual void Read(InputStream& stream);			// Deserialize data from InputStream
	virtual void Write(OutputStream& stream);		// Serialize data to Outputstream
	virtual void print();							// Print Player datas in console

	// Getters
	float getPosX() { return m_posX; }
	float getPosY() { return m_posY; }
	float getPosZ() { return m_posZ; }
	std::string getName() { return m_name; }
	float getRotX() { return m_rotX; }
	float getRotY() { return m_rotY; }
	float getRotZ() { return m_rotZ; }
	float getRotW() { return m_rotW; }

	// Setters
	void setPosX(float posX) { m_posX = posX; }
	void setPosY(float posY) { m_posY = posY; }
	void setPosZ(float posZ) { m_posZ = posZ; }
	void setName(std::string name) { m_name = name; }
	void setRotX(float rotX) { m_rotX = rotX; }
	void setRotY(float rotY) { m_rotY = rotY; }
	void setRotZ(float rotZ) { m_rotZ = rotZ; }
	void setRotW(float rotW) { m_rotW = rotW; }

private:
	float m_posX;			// X value position
	float m_posY;			// Y value position
	float m_posZ;			// Z value position

	std::string m_name;		// Player name

	float m_rotX;			// X value rotation
	float m_rotY;			// Y value rotation
	float m_rotZ;			// Z value rotation
	float m_rotW;			// W value rotation
};