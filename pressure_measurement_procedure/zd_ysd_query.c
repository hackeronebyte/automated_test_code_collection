zd_ysd_query()
/**
 * ���̲�ѯ���յ�ȫ��
 */
{
    char base_str1[1024],base_str2[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//��ѯȫ�����յ�
	//zd_sub_unit_num_id ���̵�¼��Ļ�ȡ
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\",\"on_line\":true,"
									"\"input_param\":{\"order_date_begin\":\"2020-01-01\","
									"\"order_date_end\":\"{today}\",\"sub_unit_num_id\":\"{zd_sub_unit_num_id}\"},"
									"\"page_num\":1,\"page_size\":100}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=ysd_query_all_code_count",LAST);//���ü���
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("ysd_query_all",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{gys_savel_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}



    //��ѯ�������յ�  gys_po_num_id �ɹ�����
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\","
									"\"on_line\":true,\"input_param\":{\"po_num_id\":\"{gys_po_num_id}\","
									"\"order_date_begin\":\"2020-01-01\",\"order_date_end\":\"{today}\","
									"\"sub_unit_num_id\":\"{zd_sub_unit_num_id}\"},"
									"\"page_num\":1,\"page_size\":100}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=ysd_query_single_code_count",LAST);//���ü���

	//"reserved_no":"19011130000000070",���յ���
	web_reg_save_param("zd_reserved_no","RB=\",","LB=\"reserved_no\":\"",LAST);//�ù�������ȡֵ 
	//"sub_unit_num_id":120011,
	web_reg_save_param("zd_head_sub_unit_num_id","RB=,","LB=\"sub_unit_num_id\":",LAST);//�ù�������ȡֵ 
	// "po_num_id":"14011222000001003", ���̲ɹ����� zd_single_po_num_id
	web_reg_save_param("zd_single_po_num_id","RB=\",","LB=\"po_num_id\":\"",LAST);//�ù�������ȡֵ 

	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("ysd_query_single",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{ysd_query_single_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	return 0;
}
