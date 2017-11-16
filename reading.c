#define _READ_C
#ifdef _READ_C
/*
* =====================================================================================
*       Filename:	reading.c
*    Description:	read input and change it into a reverse polish style
*        Version:	1.1.2
*        Created:	2017.10.26 16:04:47
*      Time Used:	10h
*  Last Modified:	2017.10.27 23:58
*    Last Change:	deal with dots
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

#endif
extern int execstatus;//"why_calculator.c"

//�������ܣ���������ı��ʽ(buf)���ڸ�ʽ�������������һ�������˸��ŵİ汾(input)�Խ��к������㣬ͬʱ������������ָ��
int readinput(char *input, char *buf) {//input���к�������,buf���ڸ�ʽ�����
	int i = 0,j=0;
	int minus = 0;

	while (((input[i] = fgetc(stdin))) != '\n')
	{
		buf[j] = input[i];
		if (input[i] == '-') {//�ǳ����ص�û����֤��ȷ�Ե��Լ�����һ��������ĸ����ı�������취
			if (i == 0) {//��������λʱֱ����0
				input[i++] = '0';
				input[i] = '-';
			}
			else if (input[i - 1] == '(') {//�����������ź�ʱֱ����0
			/*******������ܺ�����ĺϲ��������ȡinput[-1]�ᵼ���ڴ����******/
				input[i++] = '0';
				input[i] = '-';
			}
			
			else{//���������ֵĺ���ʱ��������
				input[i++] = '+';
				input[i++] = '(';
				input[i++] = '0';
				input[i] = '-';
				++minus;
			}
		}
		if (input[i] == '+') {//˳�������һ������
			if (i == 0) {//��λ��0
				input[i++] = '0';
				input[i] = '+';
			}
			else if (input[i - 1] == '(') {//�����ź���0
				input[i++] = '0';
				input[i] = '+';
			}	
		}if (input[i] == '.'&&!(input[i-1]>='0'&&input[i-1]<='9')) {//��Ȼ����С����
				input[i++] = '0';
				input[i] = '.';//�κ������û�������ֺ����С����ֻҪֱ�ӱ��0.������
			
		}
		if (input[i] == ' ')
		{
			i--;
			j--;
		}
		i++;
		j++;
	}
	buf[j] = '\0';
	for (int k = 1; k <= minus; k++) {//��ȫ���ڴ���������������
		input[i++] = ')';
	}
	//**********************����8��������******************************
	if (input[0]=='\n') {
		return errorfound(8);
	}
	//************************ERROR8*********************************

	input[i] = '\0';
	
	
	//�������
	//1.exit����quit���˳�����
	//2.help �򿪰�������
	//3.change �޸ľ���
	if (strcmp(input, "quit")==0 || strcmp(input, "exit")==0) {
		strcpy(input, "");
		return 0;
	}
	else if (strcmp(input, "help") == 0) {
		outputhelp();
		return 2;
	}
	else if (strcmp(input, "change") == 0) {
		preciquest();
		return 2;
	}
	else {
		return 1;
	}


}

//����׺���봮ת����ѹ���沨��ջ
int translate(const char *input, char *repol) {//inputΪ�����ֺ�������룬repolΪ�沨��ջ�����ں�������
	char stack[MAXSIZE];//inջ���ڴ����
	int	now = 0;//input��ȡ��
	int top = -1;//inջ����,��ȡtopΪ��ʱ��ʾ���ִ���
	int pol = 0;//repolջд���
	while (input[now]!='\0') {
		//1.���Ŵ���
		if (input[now] == '(') {//�������������ȼ�ֱ����ջ
			stack[++top] = input[now++];
		}
		else if (input[now] == ')') {//ע�������ű�����Զ�����������ջ�У����������ж������
			//�������Ϸ����ų�ջ
			while (stack[top] != '('&&top >= 0) {
				repol[pol++] = stack[top--];
			}
			//*************************����1�������Ŷ���������********************************
			if (top < 0) {
				repol[pol] = '\0';//�����沨��ջ��д�룬������0�������������
				return errorfound(1);
			}
			//********************************ERROR1**************************************
			--top;//����������
			++now;//����������
		}
		//2.��ȡ�����
		else if (input[now]=='@'||input[now]=='^') {//��߼������@��^������/�˷���ͬ������������Ϸ���ȫ���������ջѹ��repol���ٽ�����ѹ����ջ
			while (top >= 0 && (stack[top] == '@' || stack[top] == '^')) {
				repol[pol++] = stack[top--];
			}
			stack[++top] = input[now++];
		}
		else if (input[now] == '*' || input[now] == '/') {//�θ߼������*��/��ͬ����߼��������ջѹ��repol,�ٽ�����ѹ����ջ
			while (top >= 0 && (stack[top] == '@' || stack[top] == '^' || stack[top] == '*' || stack[top] == '/')) {
				repol[pol++] = stack[top--];
			}
			stack[++top] = input[now++];
		}
		else if (input[now] == '+' || input[now] == '-') {//�ͼ������+��-���������Ϸ���ȫ���������ջѹ��repol,�ٽ�����ѹ����ջ
			while (top >= 0 && stack[top] != '(') {
				repol[pol++] = stack[top--];

			}
			stack[++top] = input[now++];
		}
		else if((input[now] >= '0'&&input[now] <= '9') || (input[now] == '.')) {//���֣������㣩ֱ��д���沨��ջ
			//�˴��ɿ�������Ŀ \\codevstest\\sliver1 ��д�ĺ������й�����չ���������ƶ���
			//�����뷨����ȡ0xΪʮ�����ƣ�1x~fx��Ӧ1~15����
			while ((input[now] >= '0'&&input[now] <= '9')||input[now]=='.') {
				repol[pol++] = input[now++];
			}
			repol[pol++] = ' ';//���ֶ��������ʶ����ֹrepol��ѹ���������ֲ�������
		}
		//**************************����6���޷�ʶ�������**************************************
		else {
			return errorfound(6);
		}
		//**********************************ERROR6*****************************************
	}
	while (top >= 0) {//����ѹ��repol
			//***********************����2�������Ŷ���������************************************
			if (stack[top] == '(') {
				repol[pol++]='\0';//�����沨��ջ��д�룬������0�������������
				return errorfound(2);
			}
			//******************************ERROR2******************************************
			repol[pol++] = stack[top--];
		}
	repol[pol++] = '\0';//�沨��ջд�����


}

#endif //_READ_C