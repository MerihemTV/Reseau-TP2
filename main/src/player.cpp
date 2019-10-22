#include "player.hpp"
#include <cmath>
#include <algorithm>

void Player::Read(InputStream& stream)
{
	m_posX = stream.Read<float>();
	m_posY = stream.Read<float>();
	m_posZ = stream.Read<float>();
	m_name = stream.ReadStr();
	m_rotX = stream.Read<float>();
	m_rotY = stream.Read<float>();
	m_rotZ = stream.Read<float>();
	m_rotW = stream.Read<float>();
}

void Player::Write(OutputStream& stream)
{
	m_posX = stream.Read<float>();
	m_posY = stream.Read<float>();
	m_posZ = stream.Read<float>();
	m_name = stream.ReadStr();
	m_rotX = stream.Read<float>();
	m_rotY = stream.Read<float>();
	m_rotZ = stream.Read<float>();
	m_rotW = stream.Read<float>();
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

	// Name Compression
	uint16_t sizeName = static_cast<uint16_t>(m_name.size());

	// Quaternion Compression (32 bits = 4 bytes in total)
	int rotX = static_cast<int>((m_rotX + 0.707) * 1000) * (1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotY = static_cast<int>((m_rotY + 0.707) * 1000) * (1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotZ = static_cast<int>((m_rotZ + 0.707) * 1000) * (1023 / 1407);	// Int in [0;1023] -> 10 bits
	int rotW = static_cast<int>((m_rotW + 0.707) * 1000) * (1023 / 1407);	// Int in [0;1023] -> 10 bits

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
	stream.Write(sizeName);
	stream.WriteStr(m_name);
	stream.Write(compressedQuaternion);
}
