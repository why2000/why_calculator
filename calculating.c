#define _CALCU_C
#ifdef _CALCU_C
/*
* =====================================================================================
*       Filename:	calculating.c
*    Description:	funs about calculating
*        Version:	1.1.2
*        Created:	2017.10.26 16:05:58
*      Time Used:	10h
*  Last Modified:	2017.10.28 00:05
*    Last Change:	One error judgement deleted
*         Author:	���Ե(Tree Wu), why2000@hust.edu.cn
*        Company:	Huazhong University of Science and Technology
* =====================================================================================
*/


#include<why_calculator.h>
//#define NOW 1
#ifdef NOW//������

int main(void) {


	return 0;
}

#endif //NOW
extern int execstatus;//"why_calculator.c"

//�������ܣ�������
double calculate(char *repol) {//repolΪ�����ϵ��沨��ջ
	double stack[MAXSIZE];//����ջ
	char dnum[MAXSIZE];//��ȡ������
	int pol = 0;//repol��ȡ��
	int top = -1;//ջ����
	while (repol[pol] != '\0') {
		if ((repol[pol] >= '0'&&repol[pol] <= '9')||repol[pol]=='.') {//��ȡ�����ַ���
			int now = 0;
			while (repol[pol] != ' ') {
				dnum[now++] = repol[pol++];
			}
			dnum[now++] = '\0';
			stack[++top] = numbertrans(dnum);//�����ַ�����ת��
			pol++;
		}
		else {
			//************************����7�����������***************************
			if (top == 0) {
				return errorfound(7);
			}
			//**************************ERROR7*********************************
			switch (repol[pol++]) {
			case '@'://�������㣬��׺�к��ȡ�ģ�stack[top]��Ϊ�����Ĵ������ȶ�ȡ��Ϊ����������,Ŀǰ��֧�ֶԸ�������
				if (stack[top-1]>=0) {//��������Ϊ��ʱҪ�󿪷�����Ϊ������
					stack[top - 1] = pow(stack[top - 1], 1.0 / stack[top]);
					--top;
					break;
				}
				else if ((isint(stack[top])&&(int)stack[top]%2&&stack[top-1]<0)) {
					stack[top - 1] = -pow(-stack[top - 1], 1.0 / stack[top]);
					--top;
					break;
				}

				//***********************����3�������������η�ʱ����С����*****************************
				else {
					return errorfound(3);
				}
				//********************************ERROR3*****************************************

			case '^'://�����㣬���ȡ��Ϊָ�����ȶ�ȡ��Ϊ����
				if (stack[top-1]>=0) {
					stack[top - 1] = pow(stack[top - 1], stack[top]);
					--top;
					break;
				}
				else if (isint(1.0 / stack[top]) && ((int)(1.0 / stack[top]) % 2) && stack[top - 1] < 0) {
					stack[top - 1] = pow(stack[top - 1], stack[top]);
					--top;
					break;
				}
				//***********************����4�����Ϊ������������****************************
				else {
					return errorfound(4);
				}
				//*****************************ERROR4************************************

			case '*'://�˷�����
				stack[top - 1] *= stack[top];
				--top;
				break;
			case '/'://�������㣬���ȡ��Ϊ�������ȶ�ȡ��Ϊ������
				if (stack[top]) {
					stack[top - 1] /= stack[top];
					--top;
					break;
				}
				//***********************����5����ĸΪ0*************************************
				else {
					return errorfound(5);
				}
				//*****************************ERROR5*************************************
			case '+'://�ӷ�����
				stack[top - 1] += stack[top];
				--top;
				break;
			case '-'://��������
				stack[top - 1] -= stack[top];
				--top;
				break;
			}
			
		}
		
	}
	return stack[top];
}

//�������ܣ������ж�
int isint(double n) {//
	if (n >= 0)
		if ((n - (int)n) < 1e-15 || (n - (int)n) < -0.999999999999999) return 1;
		else return 0;
	else
		if (-(n - (int)n) < 1e-15 || -(n - (int)n) < -0.999999999999999) return 1;
		else return 0;

}

//�������ܣ����ַ�����ʽ�ĸ�����ת����double����
double numbertrans(const char *dnum) {//dunmΪ�ַ�����ʽ�ĸ�����
	double intpart = 0, floatpart = 0, flo = 1;//�������֣�С�����֣�����λ
	int now = 0;
	double result = 0;
	while (dnum[now] >= '0' && dnum[now] <= '9')
	{
		intpart = intpart * 10 + dnum[now++] - '0';//�������ֶ�ȡ����ʮ��n
	}

	if (dnum[now] == '.') //С�����ֶ�ȡ
	{
		while (dnum[++now] != '\0')
		{	
			//*****************************����9������С����**************************
			if (dnum[now] == '.') {
				return errorfound(9);
			}
			//********************************ERROR9*******************************
			floatpart = floatpart * 10 + dnum[now] - '0';
			flo *= 10;
		}
	}
	

	result = intpart + floatpart / flo;
	return result;
}
#endif //_CALCU_C
