#pragma once
class user
{public:
	int regisiter();
	int login();
	int begin();

private:
	char ID[20];//�˺�
	char password[20];//����
	int	authority;//�û�Ȩ��

};