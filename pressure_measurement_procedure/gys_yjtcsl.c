gys_yjtcsl()
/**
 * 一键填充数量供四步
 */
{

    //一键填充数量第一步
	char base_str1[1024],base_str2[1024],base_str3[1024],url[50];
	strcpy(url,lr_eval_string(gys_base_url("/gateway")));
    lr_save_string(url,"url");



	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_009\","
									"\"input_param\":{\"po_num_id\":\"{gys_po_num_id}\"},"
									"\"data_sign\":\"0\",\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=gys_yjtcsl_code_count",LAST);//设置检查点
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("SUPPLIER_ORDER_009");
	web_custom_request("gys_yjtcsl",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str1}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_yjtcsl_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_009",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_009",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 


    //一键填充数量第二步
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_010\","
									"\"input_param\":{\"po_num_id\":\"{gys_po_num_id}\"},"
									"\"page_num\":1,\"page_size\":50,\"data_sign\":\"0\","
									"\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
    web_reg_find("Text=\"code\":0","Savecount=gys_yjtcs2_code_count",LAST);//设置检查点
	
	lr_start_transaction("SUPPLIER_ORDER_010");
	web_custom_request("gys_yjtcs2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str2}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_yjtcs2_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_010",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_010",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 


     //一键填充数量第三步
    strcpy(base_str3,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_015\","
									"\"input_param\":{\"po_num_id\":\"14011222000001002\"},"
									"\"data_sign\":\"0\",\"tenant_num_id\":\"201101\"}"));
	lr_convert_string_encoding(base_str3, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str3" );
	strcpy(base_str3,lr_eval_string("{base_str3}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");
    web_reg_find("Text=\"code\":0","Savecount=gys_yjtcs3_code_count",LAST);//设置检查点
	lr_start_transaction("SUPPLIER_ORDER_015");
	web_custom_request("gys_yjtcs3",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str3}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_yjtcs3_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_015",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_015",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

     //一键填充数量第四步
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_010\",\"input_param\":{\"po_num_id\":\"{gys_po_num_id}\"},\"page_num\":1,\"page_size\":50,\"data_sign\":\"0\",\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
    web_reg_find("Text=\"code\":0","Savecount=gys_yjtcs2_code_count",LAST);//设置检查点

	web_reg_save_param("gys_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值 
	web_reg_save_param("gys_sup_confirm_total_qty","RB=,","LB=\"sup_confirm_total_qty\":",LAST);//用关联函数取值 
	lr_start_transaction("SUPPLIER_ORDER_010");
	web_custom_request("gys_yjtcs2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str2}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_yjtcs2_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_010",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_010",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

   
	return 0;
}
