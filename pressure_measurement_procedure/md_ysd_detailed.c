md_ysd_detailed()
/**
 * 微商验收单详细进入 五步
 */
{
    char base_str1[1024],base_str2[1024],base_str3[1024],base_str4[1024],base_str5[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//微商验收单详细进入 第一步 md_ysd_reserved_no(md_ysd_reserved_no)
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\",\"on_line\":true,\"input_param\":{\"reserved_no\":\"{md_ysd_reserved_no}\"},\"page_num\":1,\"page_size\":0}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_detailed1_code_count",LAST);//设置检查点
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("md_ysd_detailed1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_detailed1_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	//微商验收单详细进入 第二步 地区
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-0031\",\"on_line\":true,\"input_param\":{},\"page_num\":1,\"page_size\":0}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=YKPPAY-0031_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-0031");
	web_custom_request("YKPPAY-0031",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{YKPPAY-0031_code_count}"))>0){
			lr_end_transaction("YKPPAY-0031",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-0031",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商验收单详细进入 第三步 单位
    strcpy(base_str3,lr_eval_string("{\"sql_id\":\"YKPPAY-0030\",\"on_line\":true,\"input_param\":{},\"page_num\":1,\"page_size\":0}"));
	lr_convert_string_encoding(base_str3, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str3" );
	strcpy(base_str3,lr_eval_string("{base_str3}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");
	web_reg_find("Text=\"code\":0","Savecount=YKPPAY-0030_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("YKPPAY-0030");
	web_custom_request("YKPPAY-0030",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str3}",
		LAST);
	if(atoi(lr_eval_string("{YKPPAY-0030_code_count}"))>0){
			lr_end_transaction("YKPPAY-0030",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-0030",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商验收单详细进入 第四步
    strcpy(base_str4,lr_eval_string("{\"sub_unit_num_id\":{md_sub_unit_num_id},\"reserved_no\":\"{md_ysd_reserved_no}\"}"));
	lr_convert_string_encoding(base_str4, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str4" );
	strcpy(base_str4,lr_eval_string("{base_str4}"));
	lr_save_string(base_str4,"base_str4");
	strcpy(base_str4,base64_encode(lr_eval_string("{base_str4}"),strlen(base_str4)));
	lr_save_string(base_str4,"base_str4");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_checkReceiptReturn_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("md_ysd_checkReceiptReturn");
	web_custom_request("md_ysd_checkReceiptReturn",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str4}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_checkReceiptReturn_code_count}"))>0){
			lr_end_transaction("md_ysd_checkReceiptReturn",LR_PASS);
		}else{
			lr_end_transaction("md_ysd_checkReceiptReturn",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


    //微商验收单详细进入 第五步（head_sub_unit_num_id 注意处理这个关联参数）
    strcpy(base_str5,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-0340\",\"on_line\":true,\"input_param\":{\"reserved_no\":\"{md_ysd_reserved_no}\",\"head_sub_unit_num_id\":\"{zd_sub_unit_num_id}\",\"po_num_id\":\"0\"},\"page_num\":1,\"page_size\":1000}"));
	lr_convert_string_encoding(base_str5, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str5" );
	strcpy(base_str5,lr_eval_string("{base_str5}"));
	lr_save_string(base_str5,"base_str5");
	strcpy(base_str5,base64_encode(lr_eval_string("{base_str5}"),strlen(base_str5)));
	lr_save_string(base_str5,"base_str5");
	web_reg_find("Text=\"code\":0","Savecount=YKPPAY-WM-0340_code_count",LAST);//设置检查点
	//"item_num_id":1214,
    web_reg_save_param("md_ysd_item_num_id","RB=,","LB=\"item_num_id\":",LAST);//用关联函数取值 
	//"package_qty":131.0000,
    web_reg_save_param("md_ysd_package_qty","RB=,","LB=\"package_qty\":",LAST);//用关联函数取值 
	//"series":"1054781792642498560",
	web_reg_save_param("md_ysd_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值 

	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("YKPPAY-WM-0340");
	web_custom_request("YKPPAY-WM-0340",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str5}",
		LAST);
	if(atoi(lr_eval_string("{YKPPAY-WM-0340_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-0340",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-0340",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	return 0;
}
