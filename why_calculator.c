
#define _MAIN_C
#ifdef _MAIN_C

/*
* =====================================================================================
*       Filename:	why_calculator.c
*    Description:	a simple calculator
*        Version:	1.1.2
*        Created:	2017.10.26 16:04:15
*      Time Used:	10h
*  Last Modified:	2017.10.27 11:44
*    Last Change:	formated the main fun, making it more flexible
*         Author:	���Ե(Tree Wu), why2000@hust.edu.cn
*        Company:	Huazhong University of Science and Technology
* =====================================================================================
*/
//���·���
//1.���Ӹ�����ʶ�����ȡ��-a=(0-a)��		fixed
//2.���ڶ����������ʶ��				fixed
//3.����������ض���ĸ�����ʶ��			fixed
//4.���ڸ������������η���֧��           fixed
#include<why_calculator.h>

//�쳣��ȫָʾ��
//0:����������1:�������У�2:�����˴μ��㣬����:�쳣����
int execstatus = 1;
//���ȣ���ʾ������С��λ��
int preci=15;

//������ִ�к���
void exectute(void) {
	char input[MAXSIZE];
	char repol[MAXSIZE];
	char buf[MAXSIZE];
	double result;
	baseoutput();
	while (execstatus) {//��Ϊ0ʱ��������
		if (execstatus != 2 && execstatus != 1) {//�����쳣����ʱ
			printf("δ֪�����밴�������������\n");
			system("pause");
			exit(-1);
		}
		execstatus = readinput(input,buf);//��ȡ����
		if (execstatus == 2) {//�����������μ�������ʱ��������ﲢ������һ������
			endingoutput();
			execstatus = 1;
			continue;
		}
		translate(input, repol);//ת��Ϊ�沨�����ʽ
		if (execstatus == 2) {//������һ������
			endingoutput();
			execstatus = 1;
			continue;
		}
		//puts(repol);//����沨��ת���Ƿ���ȷ���ǵ���ʱע��
		
		result = calculate(repol);
		if (execstatus == 2) {//������һ������
			endingoutput();
			execstatus = 1;
			continue;
		}
	
		printf("%s = ", buf);
		outputresult(result);
		endingoutput();
	}
	


}
#define NOW 1
#ifdef NOW//����ʱͣ��
//����������
int main(void) {
	exectute();
	return 0;
}

#endif //NOW

#endif //_MAIN_C


