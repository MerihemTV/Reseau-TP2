#include "player.hpp"
#include <cmath>
#include <bitset>

void Player::Destroy()
{
	std::cout << "Player \"" << m_name << "\" destroyed." << std::endl;
	delete this;
}

void Player::Read(InputStream& stream)
{
	// ================================================================================	//
	//					Position values reading & decompression							//
	// ================================================================================	//
	uint64_t positions = stream.Read<uint64_t>();
	std::bitset<60> positionsBits(positions);

	uint32_t posX = 0 << 12,
		posY = 0 << 12,
		posZ = 0 << 12;
	// X Position value
	for (int i = 0; i < 20; i++)
	{
		int bit = (positionsBits[59 - i]) & 1;
		posX |= bit;
		if (i != 19) posX = posX << 1;
	}
	// Y Position value
	for (int i = 20; i < 40; i++)
	{
		int bit = (positionsBits[59 - i]) & 1;
		posY |= bit;
		if (i != 39) posY = posY << 1;
	}
	// Z Position value
	for (int i = 40; i < 60; i++)
	{
		int bit = (positionsBits[59 - i]) & 1;
		posZ |= bit;
		if (i != 59) posZ = posZ << 1;
	}
	m_posX = (static_cast<float>(posX) / 1000) - 500;
	m_posY = (static_cast<float>(posY) / 1000) - 500;
	m_posZ = (static_cast<float>(posZ) / 1000) - 500;

	// ================================================================================ //
	//								Name value reading									//
	// ================================================================================ //
	m_name = stream.ReadStr();

	// ================================================================================	//
	//					Quaternions values reading & decompression						//
	// ================================================================================	//
	uint32_t quaternions = stream.Read<uint32_t>();
	std::bitset<32> quaternionsBits(quaternions);
	int val1 = 0, val2 = 0, val3 = 0;
	int missingRot = 0;

	for (int i = 0; i < 10; i++)
	{
		int bit = (quaternionsBits[31 - i]) & 1;
		val1 |= bit;
		if (i != 9) val1 = val1 << 1;
	}
	for (int i = 10; i < 20; i++)
	{
		int bit = (quaternionsBits[31 - i]) & 1;
		val2 |= bit;
		if (i != 19) val2 = val2 << 1;
	}
	for (int i = 20; i < 30; i++)
	{
		int bit = (quaternionsBits[31 - i]) & 1;
		val3 |= bit;
		if (i != 29) val3 = val3 << 1;
	}
	for (int i = 30; i < 32; i++)
	{
		int bit = (quaternionsBits[31 - i]) & 1;
		missingRot |= bit;
		if (i != 31) missingRot = missingRot << 1;
	}

	enum LargestElement
	{
		x = 0, y = 1, z = 2, w = 3
	};
	switch (missingRot)
	{
	case x:
		m_rotY = static_cast<float>(val1) * 1407 / 1023 / 1000 - 0.707;
		m_rotZ = static_cast<float>(val2) * 1407 / 1023 / 1000 - 0.707;
		m_rotW = static_cast<float>(val3) * 1407 / 1023 / 1000 - 0.707;
		m_rotX = sqrt(1 - pow(m_rotY, 2) - pow(m_rotZ, 2) - pow(m_rotW, 2));
		break;
	case y:
		m_rotX = static_cast<float>(val1) * 1407 / 1023 / 1000 - 0.707;
		m_rotZ = static_cast<float>(val2) * 1407 / 1023 / 1000 - 0.707;
		m_rotW = static_cast<float>(val3) * 1407 / 1023 / 1000 - 0.707;
		m_rotY = sqrt(1 - pow(m_rotX, 2) - pow(m_rotZ, 2) - pow(m_rotW, 2));
		break;
	case z:
		m_rotX = static_cast<float>(val1) * 1407 / 1023 / 1000 - 0.707;
		m_rotY = static_cast<float>(val2) * 1407 / 1023 / 1000 - 0.707;
		m_rotW = static_cast<float>(val3) * 1407 / 1023 / 1000 - 0.707;
		m_rotZ = sqrt(1 - pow(m_rotX, 2) - pow(m_rotY, 2) - pow(m_rotW, 2));
		break;
	case w:
		m_rotX = static_cast<float>(val1) * 1407 / 1023 / 1000 - 0.707;
		m_rotY = static_cast<float>(val2) * 1407 / 1023 / 1000 - 0.707;
		m_rotZ = static_cast<float>(val3) * 1407 / 1023 / 1000 - 0.707;
		m_rotW = sqrt(1 - pow(m_rotX, 2) - pow(m_rotY, 2) - pow(m_rotZ, 2));
		break;
	}
}

void Player::Write(OutputStream& stream)
{
	// Position Compression (64 bits = 8 bytes in total )
	int posX = static_cast<int>((m_posX + 500) * 1000);	// Int in [0;1000000] -> 20 bits
	int posY = static_cast<int>((m_posY + 500) * 1000); // Int in [0;1000000] -> 20 bits
	int posZ = static_cast<int>((m_posZ + 500) * 1000); // Int in [0;1000000] -> 20 bits

	uint64_t compressedPosition = posX;
	compressedPosition = compressedPosition << 20;
	compressedPosition |= posY;
	compressedPosition = compressedPosition << 20;
	compressedPosition |= posZ;

	// Quaternion Compression (32 bits = 4 bytes in total)
	int rotX = static_cast<int>((m_rotX + 0.707) * 1000 * 1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotY = static_cast<int>((m_rotY + 0.707) * 1000 * 1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotZ = static_cast<int>((m_rotZ + 0.707) * 1000 * 1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotW = static_cast<int>((m_rotW + 0.707) * 1000 * 1023 / 1407);	// Int in [0;1023] -> 10 bits

	enum LargestElement
	{
		x = 0, y = 1, z = 2, w = 3
	};
	struct PacketQuaternion
	{
		LargestElement le : 2;
		int val1 : 10, val2 : 10, val3 : 10;
		PacketQuaternion(LargestElement le_, int val1_, int val2_, int val3_) : le(le_), val1(val1_), val2(val2_), val3(val3_) {};
	};

	// Max value determination
	int maxVal = rotX;
	PacketQuaternion quaternion(x, rotY, rotZ, rotW);
	if (rotY > maxVal)
	{
		quaternion.le = y;
		quaternion.val1 = rotX;
		quaternion.val2 = rotZ;
		quaternion.val3 = rotW;
		maxVal = rotY;
	}
	if (rotZ > maxVal)
	{
		quaternion.le = z;
		quaternion.val1 = rotX;
		quaternion.val2 = rotY;
		quaternion.val3 = rotW;
		maxVal = rotZ;
	}
	if (rotW > maxVal)
	{
		quaternion.le = w;
		quaternion.val1 = rotX;
		quaternion.val2 = rotY;
		quaternion.val3 = rotZ;
		maxVal = rotW;
	}

	uint32_t compressedQuaternion = quaternion.val1;
	compressedQuaternion = compressedQuaternion << 10;
	compressedQuaternion |= quaternion.val2;
	compressedQuaternion = compressedQuaternion << 10;
	compressedQuaternion |= quaternion.val3;
	compressedQuaternion = compressedQuaternion << 2;
	compressedQuaternion |= quaternion.le;

	// Write in Output Stream
	stream.Write(compressedPosition);
	stream.WriteStr(m_name);
	stream.Write(compressedQuaternion);
}

void Player::print()
{
	std::cout << "=========PLAYER=========\n";
	std::cout << "Name : " << m_name << "\n";
	std::cout << "--------position--------\n";
	std::cout << "X : " << m_posX << "\n";
	std::cout << "Y : " << m_posY << "\n";
	std::cout << "Z : " << m_posZ << "\n";
	std::cout << "--------rotation--------\n";
	std::cout << "X : " << m_rotX << "\n";
	std::cout << "Y : " << m_rotY << "\n";
	std::cout << "Z : " << m_rotZ << "\n";
	std::cout << "========================\n";
}