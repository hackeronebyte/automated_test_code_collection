zd_temp_pur_single_detailed()
/**
 * 单个集单和详细查询
 */
{



    char base_str[1024],base_str1[1024],base_str2[1024],url[50];
    strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//单个集单查询
    strcpy(base_str,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-PRE-PO-LIST\","
								   "\"on_line\":true,\"input_param\":{\"pre_po_num_id\":\"{all_pre_po_num_id}\","
								   "\"status_num_id\":\"1\",\"begin_date\":\"{today}\","
								   "\"end_date\":\"{today}\"},\"page_num\":1,\"page_size\":1000}"));
    lr_convert_string_encoding(base_str, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str" );
    strcpy(base_str,lr_eval_string("{base_str}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");


	web_reg_find("Text=\"code\":0","Savecount=temp_pur_single_code_count",LAST);//设置检查点
	//单个关联获取预采单号:
    web_reg_save_param("zd_pre_po_num_id","RB=\",","LB=\"pre_po_num_id\":\"",LAST);//用关联函数取值
	//"series":"1048810884262174720",
	web_reg_save_param("zd_series","RB=\",","LB=\"series\":\"",LAST);//用关联函数取值

	web_add_header("Authorization","{zd_author}");
	lr_start_transaction("YKPPAY-SCM-PRE-PO-LIST");
	web_custom_request("temp_pur_single",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str}",
		LAST);
	if(atoi(lr_eval_string("{temp_pur_single_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}



	//详细查询1
    strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-PRE-PO-LIST\","
									"\"on_line\":true,\"input_param\":{\"pre_po_num_id\":\"{zd_pre_po_num_id}\"},"
									"\"page_num\":1,\"page_size\":0}"));
    lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
    strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");


	web_reg_find("Text=\"code\":0","Savecount=temp_pur_detailed1_code_count",LAST);//设置检查点

	web_add_header("Authorization","{zd_author}");
	lr_start_transaction("YKPPAY-SCM-PRE-PO-LIST");
	web_custom_request("temp_pur_detailed1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{temp_pur_detailed1_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 


   

    //详细查询2
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-PRE-PO-DTL-LIST\","
									"\"on_line\":true,\"input_param\":{\"pre_po_num_id\":\"{zd_pre_po_num_id}\"},"
									"\"page_num\":1,\"page_size\":1000}"));
    lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
    strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");


	web_reg_find("Text=\"code\":0","Savecount=temp_pur_detailed1_code_count",LAST);//设置检查点
	web_reg_save_param("supply_unit_num_id","RB=,","LB=\"supply_unit_num_id\":",LAST);//用关联函数取值
  
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-SCM-PRE-PO-DTL-LIST");
	web_custom_request("temp_pur_detailed2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{temp_pur_query_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-PRE-PO-DTL-LIST",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-PRE-PO-DTL-LIST",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

	return 0;
}
