#pragma once
class Move {
public:
	void go(int sector); // ����
	void rotate(int sector); // ������� �� �����
private:
	void SetMotorsSpeed(float v1, float v2, float v3); // �������� �������� ��������� �� ������
};