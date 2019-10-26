#pragma once
#include "game_object.hpp"
#include <iostream>

class Player : public GameObject
{
public:
	REPLICATED('PLAY', Player);

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

	virtual void Destroy();
	virtual void Read(InputStream& stream);
	virtual void Write(OutputStream& stream);
	virtual void print()
	{
		std::cout << "=========PLAYER=========" << std::endl;
		std::cout << "Name : " << m_name << std::endl;
		std::cout << "=======================" << std::endl;
	}

private:
	float m_posX;
	float m_posY;
	float m_posZ;

	std::string m_name;

	float m_rotX;
	float m_rotY;
	float m_rotZ;
	float m_rotW;
};