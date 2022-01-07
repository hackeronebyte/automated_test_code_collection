md_ysd_query()
/**
 * 微商验收单查询
 */
{
    char base_str1[1024],base_str2[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//查询全部验收单
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\",\"on_line\":true,\"input_param\":{\"order_date_begin\":\"2020-01-01\",\"order_date_end\":\"{today}\",\"sub_unit_num_id\":\"{md_sub_unit_num_id}\"},\"page_num\":1,\"page_size\":100}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_query_all_code_count",LAST);//设置检查点
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("md_ysd_query_all",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_query_all_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//根据发货通知单查询单个验收单  zd_fhtzd_so_num_id(zd_fhtzd_save() 保存第二步（查询） )
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\",\"on_line\":true,\"input_param\":{\"so_num_id\":\"{zd_fhtzd_so_num_id}\",\"order_date_begin\":\"2020-01-01\",\"order_date_end\":\"{today}\",\"sub_unit_num_id\":\"{md_sub_unit_num_id}\"},\"page_num\":1,\"page_size\":100}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=single_ysd_query_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	//"reserved_no":"19011130000000069",
	web_reg_save_param("md_ysd_reserved_no","RB=\",","LB=\"reserved_no\":\"",LAST);//用关联函数取值 
	//"series":"1054781791568756736",
	web_reg_save_param("md_ysd_fh_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值 

	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("single_ysd_query",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{single_ysd_query_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}



	return 0;
}
