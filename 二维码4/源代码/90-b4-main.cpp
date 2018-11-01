/*1550431 ����� �ƿ�3��*/
//�����˳����ú���
#include "90-b4.h"

int main()
{
	int version;
	QR_point *qr;
	char *saver,*t_saver= get_input(),*translated_saver,*final_codewords;
	saver = G2U(t_saver);//GBK -> UTF-8

	//�汾ѡ��
	version = decide_version(saver);

	//��������
	translated_saver=translate_char_into_01(saver, version);
	if(translated_saver==NULL)
	{
		//�����Ѿ��ں����ڲ���ʾ
		delete[]t_saver;//ɾ��GBK�ַ���
		delete[]saver;//ɾ��UTF-8�ַ���
		return 0;
	}
	//cout << translated_saver << endl;
	//Sleep(10000000);

	//���о���
	final_codewords = encode(translated_saver, version);
	if(final_codewords==NULL)
	{
		//�����Ѿ��ں����ڲ���ʾ
		delete[]translated_saver;
		delete[]t_saver;//ɾ��GBK�ַ���
		delete[]saver;//ɾ��UTF-8�ַ���
		return 0;
	}
	//cout <<version<<' '<<strlen(translated_saver)/8<<' '<<strlen( final_codewords)/8 << endl;
	//Sleep(10000000);

	//���ɶ�ά����
	//ѡ��MASK00��M����ȼ�
	qr = generate_QR_code(version);
	if (qr == NULL)//�����ռ��ں������Ѿ��ͷ�
	{
		delete[]translated_saver;
		delete[]final_codewords;
		delete[]t_saver;//ɾ��GBK�ַ���
		delete[]saver;//ɾ��UTF-8�ַ���
		return 0;
	}

	//��������
	fill_in_all_bits(qr, version, final_codewords);

	//����Ĥ
	add_mask(qr, version);

	setfontsize(hout, L"������",15-version/3 );
	setconsoleborder(hout, 9*version+50, 5 * version + 30);
	system("cls");

	//��ͼ
	output_QR_code(qr, version);

	delete[]translated_saver;
	delete[]final_codewords;
	delete[]t_saver;//ɾ��GBK�ַ���
	delete[]saver;//ɾ��UTF-8�ַ���
	free_QR_code(qr);//ɾ����ά����Ϣ
	return 1;
}