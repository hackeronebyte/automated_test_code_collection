md_zgsh()
/**
 * 主管审核 三步
 */
{
    char base_str1[500],base_str2[500],base_str3[500];

    //主管审核第一步  //lr_convert_string_encoding("登陆账号",LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8, "Account");
    /*
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-NON-TEMP-PURCHASE-REPL-APPLY\",\"on_line\":true,\"input_param\":{\"reserved_no_list\":[\"{md_sequence_num}\"]},\"page_num\":1,\"page_size\":0}"));
	lr_save_string(base_str1,"base_str1");

	b64_encode_string(lr_eval_string("{base_str1}"), "base_str1" );// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=zgsh_data_export_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
    lr_start_transaction("YKPPAY-SCM-NON-TEMP-PURCHASE-REPL-APPLY");
    web_custom_request("zgsh_data_export",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{zgsh_data_export_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-NON-TEMP-PURCHASE-REPL-APPLY",LR_PASS);
		}else{
            lr_end_transaction("YKPPAY-SCM-NON-TEMP-PURCHASE-REPL-APPLY",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

    */
	//主管审核第二步
    strcpy(base_str2,lr_eval_string("{\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"order_date\":\"{order_date}\","
									"\"apply_num_id\":\"{md_sequence_num}\","
									"\"auto_audit_sign\":0}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=apply_audit_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_audit");
    web_custom_request("apply_audit",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.audit&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{apply_audit_code_count}"))>0){
			lr_end_transaction("apply_audit",LR_PASS);
		}else{
            lr_end_transaction("apply_audit",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	//主管审核第三步
    strcpy(base_str3,lr_eval_string("{\"sql_id\":\"LDPPAY-0001\","
									"\"on_line\":true,\"input_param\":"
									"{\"apply_num_id\":\"{md_sequence_num}\"},"
									"\"page_num\":1,\"page_size\":1000}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=md_zgsh_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("LDPPAY-0001");
    web_custom_request("md_zgsh",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str3}",
		LAST);
	if(atoi(lr_eval_string("{md_zgsh_code_count}"))>0){
			lr_end_transaction("LDPPAY-0001",LR_PASS);
		}else{
            lr_end_transaction("LDPPAY-0001",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
    

	return 0;
}
