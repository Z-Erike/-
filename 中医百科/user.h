#pragma once
class user
{public:
	int regisiter();
	int login();
	int begin();

private:
	char ID[20];//账号
	char password[20];//密码
	int	authority;//用户权限

};