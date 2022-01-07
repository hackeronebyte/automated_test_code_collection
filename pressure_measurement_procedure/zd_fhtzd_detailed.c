zd_fhtzd_detailed()
/**
 * 总商发货通知单点击进入 两步
 */
{
    char base_str1[1024],base_str2[1024],url[50],zd_so_num_id[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//点击进入第一步
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-02355\","
									"\"on_line\":true,\"input_param\":{\"so_num_id\":\"{zd_so_num_id}\"},"
									"\"page_num\":1,\"page_size\":0}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=fhtzd_detailed1_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-SCM-02355");
	web_custom_request("fhtzd_detailed1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{fhtzd_detailed1_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-02355",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-02355",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

    //点击进入第二步
	strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-0236\",\"on_line\":true,\"input_param\":{\"so_num_id\":\"{zd_so_num_id}\",\"head_sub_unit_num_id\":\"{zd_sub_unit_num_id}\"},\"page_num\":1,\"page_size\":10000}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=fhtzd_detailed2_code_count",LAST);//设置检查点
	//"series":"1054710492880355328",
	web_reg_save_param("zd_fhtzd_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值 
	//"item_num_id": 1214,
	web_reg_save_param("zd_fhtzd_item_num_id","RB=,","LB=\"item_num_id\":",LAST);//用关联函数取值 
	//"lock_qty": 131,
	web_reg_save_param("zd_fhtzd_lock_qty","RB=,","LB=\"lock_qty\":",LAST);//用关联函数取值 
	
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-SCM-0236");
	web_custom_request("fhtzd_detailed2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{fhtzd_detailed2_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-0236",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-0236",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	return 0;
}
