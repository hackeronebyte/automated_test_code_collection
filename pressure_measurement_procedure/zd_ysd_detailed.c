zd_ysd_detailed()
/**
 * 总商点击验收单某条记录进入详细
 */
{

    char base_str1[1024],base_str2[1024],base_str3[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//查看明细1  验收单号zd_reserved_no
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-03055-1\",\"on_line\":true,"
									"\"input_param\":{\"reserved_no\":\"{zd_reserved_no}\"},\"page_num\":1,"
									"\"page_size\":0}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=ysd_detailed1_code_count",LAST);//设置检查点
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-03055-1");
	web_custom_request("ysd_detailed1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{ysd_detailed1_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-03055-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-03055-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


    //查看明细2
    strcpy(base_str2,lr_eval_string("{\"sub_unit_num_id\":{zd_sub_unit_num_id},"
									"\"reserved_no\":\"{zd_reserved_no}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=ysd_detailed2_code_count",LAST);//设置检查点
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("checkReceiptReturn");
	web_custom_request("ysd_detailed2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykl.kvm.receipt.checkReceiptReturn&sid={zd_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{ysd_detailed2_code_count}"))>0){
			lr_end_transaction("checkReceiptReturn",LR_PASS);
		}else{
			lr_end_transaction("checkReceiptReturn",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

    //查看明细3 zd_single_po_num_id 总商采购单号
    strcpy(base_str3,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-0340\","
									"\"on_line\":true,\"input_param\":{\"reserved_no\":\"{zd_reserved_no}\","
									"\"head_sub_unit_num_id\":\"{zd_head_sub_unit_num_id}\","
									"\"po_num_id\":\"{zd_single_po_num_id}\"},"
									"\"page_num\":1,\"page_size\":1000}"));
	lr_convert_string_encoding(base_str3, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str3" );
	strcpy(base_str3,lr_eval_string("{base_str3}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");
	web_reg_find("Text=\"code\":0","Savecount=ysd_detailed3_code_count",LAST);//设置检查点
	//保存验收单关联准备数据
	//"series":"1054760355185655808
	web_reg_save_param("zd_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值 
	// "item_num_id":1543,
	web_reg_save_param("zd_item_num_id","RB=,","LB=\"item_num_id\":",LAST);//用关联函数取值 
	//"package_qty":131.0000,
	web_reg_save_param("zd_package_qty","RB=,","LB=\"package_qty\":",LAST);//用关联函数取值 
	
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-WM-0340");
	web_custom_request("ysd_detailed3",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str3}",
		LAST);
	if(atoi(lr_eval_string("{ysd_detailed3_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-0340",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-0340",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
	return 0;
}
