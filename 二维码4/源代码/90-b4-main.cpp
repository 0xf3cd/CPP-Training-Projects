/*1550431 王甯琪 计科3班*/
//输出、顺序调用函数
#include "90-b4.h"

int main()
{
	int version;
	QR_point *qr;
	char *saver,*t_saver= get_input(),*translated_saver,*final_codewords;
	saver = G2U(t_saver);//GBK -> UTF-8

	//版本选择
	version = decide_version(saver);

	//编码数据
	translated_saver=translate_char_into_01(saver, version);
	if(translated_saver==NULL)
	{
		//错误已经在函数内部提示
		delete[]t_saver;//删除GBK字符串
		delete[]saver;//删除UTF-8字符串
		return 0;
	}
	//cout << translated_saver << endl;
	//Sleep(10000000);

	//进行纠错
	final_codewords = encode(translated_saver, version);
	if(final_codewords==NULL)
	{
		//错误已经在函数内部提示
		delete[]translated_saver;
		delete[]t_saver;//删除GBK字符串
		delete[]saver;//删除UTF-8字符串
		return 0;
	}
	//cout <<version<<' '<<strlen(translated_saver)/8<<' '<<strlen( final_codewords)/8 << endl;
	//Sleep(10000000);

	//生成二维码盘
	//选择MASK00，M纠错等级
	qr = generate_QR_code(version);
	if (qr == NULL)//出错，空间在函数中已经释放
	{
		delete[]translated_saver;
		delete[]final_codewords;
		delete[]t_saver;//删除GBK字符串
		delete[]saver;//删除UTF-8字符串
		return 0;
	}

	//填入数据
	fill_in_all_bits(qr, version, final_codewords);

	//加掩膜
	add_mask(qr, version);

	setfontsize(hout, L"新宋体",15-version/3 );
	setconsoleborder(hout, 9*version+50, 5 * version + 30);
	system("cls");

	//画图
	output_QR_code(qr, version);

	delete[]translated_saver;
	delete[]final_codewords;
	delete[]t_saver;//删除GBK字符串
	delete[]saver;//删除UTF-8字符串
	free_QR_code(qr);//删除二维码信息
	return 1;
}