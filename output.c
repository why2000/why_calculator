#define _OUTPUT_C
#ifdef _OUTPUT_C
/*
* =====================================================================================
*       Filename:	output.c
*    Description:	some output situations
*        Version:	1.1.2
*        Created:	2017.10.26 16:05:16
*      Time Used:	10h
*  Last Modified:	2017.10.28 01:49
*    Last Change:	error treatment added in dots input
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
extern int preci;//"why_calculator.c"

//�������뾫��
int preciquest(void) {
	
	char foo;
	printf("����ľ���Ҫ��Ϊһ�����ڵ���0��С�ڵ���15������\n");
	printf("�����뾫��\n");
	/*��ôΪʲô�������ַ������ԣ���������ղ��رյĻ���������������2+.23֮��ı��ʽ��ʱ�����������أ�*/
	//fflush(stdin);
	
	int right = scanf("%d", &preci);//�������������������ô��
	scanf("%c", &foo);//��Ȼ��İ�
	if (right&&preci >= 0 && preci <= 15&&foo=='\n') {
		printf("*********************************************************************************\n");
		printf("�������óɹ�����ǰ����Ϊ%d\n", preci);
		return 1;
	}
	else {
		printf("���Ȳ�����Ҫ������������\n");
		printf("*********************************************************************************\n");
		//setbuf(stdin, NULL);//��һ�����������fflush������Ӧʹ�õ�

		//***********************����������������������ǹرջ�������****************************
		
		char*buf = (char *)malloc(BUFSIZ);
		free(buf);
		buf = (char *)malloc(BUFSIZ);
		setbuf(stdin,buf);
		//**********************************************************************************
		return preciquest();
	}

}

//��ӡ�������Լ�������ʽ
void baseoutput(void) {
	printf("*********************************************************************************\n");
	printf("*                             ���׼�����V1.1.2                                  *\n");
	printf("*�˼�������ʵ�ֻ��������������Լ����ֵĳ˷�/��������                            *\n");
	printf("*��һ��ʹ�������� help �Բ鿴���������ʽ������Ҫ��                             *\n");
	printf("*����һ���Ϸ����������ʽ�������һ�������ʽ����������ɼ��������µı��ʽ     *\n");
	printf("*�˳�����������quit��exit                                                       *\n");
	printf("*���ľ���������change                                                           *\n");
	printf("*�߾����£������������1-3λ���ܶ�ʧ���ȣ�������������ķ�ʽ��ȡ��Ч����      *\n");
	printf("*                                                                        -by why*\n");
	printf("*                                                               2017/10/26 16:01*\n");
	printf("*********************************************************************************\n");
	preciquest();
	endingoutput();
	
}

//һ�μ�����ɺ���������
void endingoutput(void) {
	printf("*********************************************************************************\n");
	printf("�����������ʽ���м��㣬����quit��exit�Խ�����������help�Դ򿪰�������\n");
	printf("����change�Ը��ľ���\n");
	printf("*********************************************************************************\n");
}

//�����ķ־������
void outputresult(double result) {//resultΪ����Ľ��
	int intlen = 0;
	switch (preci) {
	case 0:
		printf("%.0f\n", result);
		break;
	case 1:
		printf("%.1f\n", result);
		break;
	case 2:
		printf("%.2f\n", result);
		break;
	case 3:
		printf("%.3f\n", result);
		break;
	case 4:
		printf("%.4f\n", result);
		break;
	case 5:
		printf("%.5f\n", result);
		break;
	case 6:
		printf("%.6f\n", result);
		break;
	case 7:
		printf("%.7f\n", result);
		break;
	case 8:
		printf("%.8f\n", result);
		break;
	case 9:
		printf("%.9f\n", result);
		break;
	case 10:
		printf("%.10f\n", result);
		break;
	case 11:
		printf("%.11f\n", result);
		break;
	case 12:
		printf("%.12f\n", result);
		break;
	case 13:
		printf("%.13f\n", result);
		break;
	case 14:
		printf("%.14f\n", result);
		break;
	case 15:
		printf("%.15f\n", result);
		break;
	}
	
	
}

//��ӡ��������
void outputhelp(void) {
	printf("*********************************************************************************\n");
	printf("*****************************�����ʹ��ȫӢ������********************************\n");
	printf("���������\n");
	printf("����������ֱ��������ʽ���ӣ�+������-���ˣ�*������/�����뷶����1+2\n");
	printf("�˷��������^�������Ϊ�������Ҳ�Ϊָ�������뷶����2^5\n");
	printf("�����������@�������Ϊ�����������Ҳ�Ϊ�����������뷶����5@2\n");
	printf("������������������ĺ���������ţ�Ӧ������ѧ����ʽ����д�淶��������\n");
	printf("���ţ�()�����ʹ��Ӣ�����ţ��÷�����ѧ����ͬ\n");
	printf("*********************************************************************************\n");

}

//����ϵͳ
int errorfound(const int index) {//indexΪ��������
/**************************�Ķ��˺���ʱ��Ҫ ɾ�� ö�������е��κ���****************************/
	enum errornum { TMRIGHT = 1, TMLEFT, NEGSQRT, COMPRESULT, ZERODENO, ABNOMALSYN, TMSYN, NOINPUT, TMDOTS};
	switch (index) {
	case TMRIGHT:
		printf("�����Ź���)))\n");
		break;
	case TMLEFT:
		printf("�����Ź���(((\n");
		break;
	case NEGSQRT:
		printf("�����������η�ʱ����С����@@@\n");
		break;
	case COMPRESULT:
		printf("���Ϊ������������^^^\n");
		break;
	case ZERODENO:
		printf("��ĸΪ��000\n");
		break;
	case ABNOMALSYN:
		printf("�޷�ʶ�������$$$\n");
		printf("��������ʽ���Ƿ������ĸ��ʹ������������\n");
		break;
	case TMSYN:
		printf("���������ʽ%%%%%%\n");
		break;
	case NOINPUT:
		printf("������???\n");
		break;
	case TMDOTS:
		printf("��⵽����С����...\n");
		break;
	}

	execstatus = 2;
	return 2;
}
#endif
