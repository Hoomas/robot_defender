#include "move.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

void Move::SetMotorsSpeed(float v1, float v2, float v3) {
	// ����� ����� ����������� �������� ��������� �� ���� ������
}

void Move::go(int sector) {
	float v1, v2, v3; // �������� �������, ������� � �������� �������
	if (sector == 1) {  // � ����������� �� �������, ����� �������� �������� ������ ��� ����������� �������� ��� ���� � ��� �����������
		v1 = v2 = 255;
		v3 = 0;
	}
	else if (sector == 2) {
		v1 = 255 / (cos(60*M_PI / 180));
		v2 = 0;
		v3 = 255 * sin(60 * M_PI / 180) / (cos(60 * M_PI / 180) * cos(30 * M_PI / 180));
	} 
	else if (sector == 3) {
		v1 = v3 = 255;
		v2 = 0;
	}
	else if (sector == 4) {
		v1 = 0;
		v2 = 255 * sin(30 * M_PI / 180) / (cos(30 * M_PI / 180));
		v3 = 255 / (cos(60 * M_PI / 180));
	}
	else if (sector == 5) {
		v1 = 0;
		v2 = v3 = -255;
	}
	else if (sector == 6) {
		v1 = -255 * sin(30 * M_PI / 180) / (cos(30 * M_PI / 180));
		v2 = -255 / (cos(60 * M_PI / 180));
		v3 = 0;
	}
	else if (sector == 7) {
		v1 = v2 = -255;
		v3 = 0;
	}
	else if (sector == 8) {
		v1 = -255 / (cos(60 * M_PI / 180));
		v2 = 0;
		v3 = -255 * sin(60 * M_PI / 180) / (cos(60 * M_PI / 180) * cos(30 * M_PI / 180));
	}
	else if (sector == 9) {
		v1 = v3 = -255;
		v2 = 0;
	}
	else if (sector == 10) {
		v1 = 0;
		v2 = -255 * sin(30 * M_PI / 180) / (cos(30 * M_PI / 180));
		v3 = -255 / (cos(60 * M_PI / 180));
	}
	else if (sector == 11) {
		v1 = 0;
		v2 = v3 = 255;
	}
	else if (sector == 12) {
		v1 = 255 * sin(30 * M_PI / 180) / (cos(30 * M_PI / 180));
		v2 = 255 / (cos(60 * M_PI / 180));
		v3 = 0;
	}

	SetMotorsSpeed(v1, v2, v3); //����������� �������� ������������� �� ������
}
void Move::rotate(int sector) {
	float v1, v2, v3;
	if (sector == 1) {						//����� ��� ��������� � ������� 1 (����� ����� �������), �������� �� ����������
		v1 = v2 = v3 = 0;
	}
	else if (sector > 1 && sector < 8) {	//����� ��� ��������� � �������� 2-7 (������) ����� �������������� �������
		v1 = v2 = v3 = 255;
	}
	else if (sector > 7 && sector <= 12) {  //����� ��� ��������� � �������� 8-12 (�����) ����� �������������� ������
		v1 = v2 = v3 = -255;
	}

	SetMotorsSpeed(v1, v2, v3); //����������� �������� ������������� �� ������
}