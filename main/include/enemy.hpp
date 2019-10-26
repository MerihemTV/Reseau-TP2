#pragma once
#include "game_object.hpp"
#include <iostream>

class Enemy : public GameObject
{
public:
	REPLICATED('ENEM', Enemy);

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

	virtual void Destroy();
	virtual void Read(InputStream& stream);
	virtual void Write(OutputStream& stream); 
	virtual void print()
	{
		std::cout << "=========ENEMY=========" << std::endl;
		std::cout << "Type : " << m_type<< std::endl;
		std::cout << "=======================" << std::endl;
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